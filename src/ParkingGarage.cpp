/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

*******************************************************************************/


#include "ParkingGarage.h"
using namespace std;

/**
 * ParkingGarage implementation
 */

ParkingGarage::ParkingGarage(int numLevels, int spacesPerLevel, int spacesPerRow, int percentLargeSpaces, int percentMotorcycleSpaces) {
    levels.push_back(Level(spacesPerLevel, spacesPerRow, percentLargeSpaces, percentMotorcycleSpaces));
    Level copy = levels.front();
    
    //each level is the same
    for (int i = 0; i < numLevels-1; i++) {
        levels.push_back(copy);
    }
}

ParkingGarage::~ParkingGarage() {

}

int ParkingGarage::getNumLevels() {
    return levels.size();
}


void ParkingGarage::parkMultiple(int numBuses, int numCars, int numMotorcycles) {
    for (int i = 0; i < numBuses; i++) {
        parkSingle('B', 1);
    }
    
    for (int i = 0; i < numCars; i++) {
        parkSingle('C', 1);
    }
    
    for (int i = 0; i < numMotorcycles; i++) {
        parkSingle('M', 1);
    }
    return;
}


void ParkingGarage::parkSingle(char type, int attempt) {
    int succeed = false;
    string v;
    int index;
    bool endRecursion = false;
        
    for (int i = 0; i < getNumLevels(); i++) {
        Level l = levels.at(i);
        for (int j = l.getNumRows() - 1; j >= 0; j--) {
            Row r = l.rows.at(j);
            switch (type) {
                //find valid index or return -1
                case 'B' : index = r.getPossibleBusIndex();               v = "bus";        break;
                case 'C' : index = r.getPossibleCarIndex(attempt);        v = "car";        break;
                case 'M' : index = r.getPossibleMotorcycleIndex(attempt); v = "motorcycle"; break;
            }
            //if index is valid (not -1) and nothing has been parked yet (succeed is false), call the corresponding park function
            //and mark succeed true to prevent multiple parking.
            if (!(index == -1 || succeed)) {
                switch (type) {
                    case 'B' : r.parkBus(index);        break;
                    case 'C' : r.parkCar(index);        break;
                    case 'M' : r.parkMotorcycle(index); break;
                }
                succeed = true;
                l.rows.erase(l.rows.begin() + j);
                l.rows.insert(l.rows.begin() + j, r);
                levels.erase(levels.begin() + i);
                levels.insert(levels.begin() + i, l);
            }
        }
    }
    //buses only go in large spots, so no recursion needed.
    //cars go in compact or large spots, so the first pass of the method checks for compact spots and the second for large.
    //This prevents cars from "wasting" large spots and preventing busses from parking.
    //Same principal for motorcycles, except 3 passes.
    endRecursion = type == 'B' || (attempt >= 2 && type == 'C') || (attempt >= 3 && type == 'M');
    if (!(succeed || endRecursion)) {
        if (type == 'C')
            parkSingle('C', attempt + 1);
        if (type == 'M') 
            parkSingle('M', attempt + 1);
    } 
    else if (!succeed)
        cout << "There is no room to park a " << v << "." << endl;
    else
        cout << "Your " << v << " successfully parked." << endl;
    return;
}

void ParkingGarage::removeSingle(char type) {
    bool succeed = false;
    string v;
    for (int i = 0; i < getNumLevels(); i++) {
        Level l = levels.at(i);
        for (int j = 0; j < l.getNumRows(); j++) {
            Row r = l.rows.at(j);
            //again, the bool succeed prevents several removals.
            if (!(succeed)) {
                switch (type) {
                    case 'B' : succeed = r.removeBus(); v = "bus";               break;
                    case 'C' : succeed = r.removeCar(); v = "car";               break;
                    case 'M' : succeed = r.removeMotorcycle(); v = "motorcycle"; break;
                }
                l.rows.erase(l.rows.begin() + j);
                l.rows.insert(l.rows.begin() + j, r);
                levels.erase(levels.begin() + i);
                levels.insert(levels.begin() + i, l);
            }
        }
    }
    if (!succeed) {
            cout << "No " << v << " found to remove." << endl;
        } else {
            cout << "Your " << v << " successfully removed." << endl;
        }
    return;
}

void ParkingGarage::smartPark(char type, int level, int row, int space) {
    Level l = levels.at(level);
    Row r = l.rows.at(row);
    string v;
    switch (type) {
        case 'B' : r.smartParkBus(space);   v = "bus";        break;
        case 'C' : r.parkCar(space);        v = "car";        break;
        case 'M' : r.parkMotorcycle(space); v = "motorcycle"; break;
    }
    cout << "\nAttempting to smart park " << v << ".";
    l.rows.erase(l.rows.begin()  + row);
    l.rows.insert(l.rows.begin() + row, r);
    levels.erase(levels.begin()  + level);
    levels.insert(levels.begin() + level, l);
    return;
}

void ParkingGarage::smartRemove(char type, int level, int row, int space) {
    Level l = levels.at(level);
    Row r = l.rows.at(row);
    string v;
    switch (type) {
        case 'B' : r.smartRemoveBus(space);        v = "bus";        break;
        case 'C' : r.smartRemoveCar(space);        v = "car";        break;
        case 'M' : r.smartRemoveMotorcycle(space); v = "motorcycle"; break;
    }
    cout << "\nAttempting to smart remove " << v << ".";
    l.rows.erase(l.rows.begin()  + row);
    l.rows.insert(l.rows.begin() + row, r);
    levels.erase(levels.begin()  + level);
    levels.insert(levels.begin() + level, l);
    return;
}

void ParkingGarage::requestInput() {
    int b, c, m;
    int b0, c0, m0;
    int negativeInput = 0;
    
    //get 3 integer inputs, try to prevent user error by clearing cin if a non-integer is input (cin fail)
    cin >> b;
    while(cin.fail()) {
        cout << "Invalid input. Please enter exactly 3 integers separated by spaces." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestInput();
        return;
    }
    
    cin >> c;
    while(cin.fail()) {
        cout << "Invalid input. Please enter exactly 3 integers separated by spaces." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestInput();
        return;
    }
    
    cin >> m;
    while(cin.fail()) {
        cout << "Invalid input. Please enter exactly 3 integers separated by spaces." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestInput();
        return;
    }
    
    //store the original values to check for (b == c == m == 0) later
    b0 = b;
    c0 = c;
    m0 = m;
    
    //unparking before parking because it's more space efficient
    if (b < 0) {
        for (int i = 0; i < (b * -1); i++) {
            removeSingle('B');
        }
        b = 0;
    }
    if (c < 0) {
        for (int i = 0; i < (c * -1); i++) {
            removeSingle('C');
        }
        c = 0;
    }
    if (m < 0) {
        for (int i = 0; i < (m * -1); i++) {
            removeSingle('M');
        }
        m = 0;
    }
    
    //parking
    parkMultiple(b, c, m);

    //condition to start smart parking
    if (b0 == 0 && c0 == 0 && m0 == 0) {
        cout << "Smart Parking: To add or remove a vehicle from a single location," << endl;
        cout << "type (+ or -), then (B, C, or M), then three integers representing the level, row, and parking space, respectively." << endl;
        cout << "For example: to remove a bus from the bottom level, the leftmost row, and the leftmost parking space, you could type \"- B 0 0 0\".\n" << endl;
        requestSmartInput();
        return;
    }
    cout << endl;
    printGarage();
    //recursion to continue letting user input instructions
    requestInput();
    return;
}

void ParkingGarage::requestSmartInput() {
    cout << "Now using smart park." << endl
         << "Enter '0' instead of '+' or '-' to return to regular parking." << endl;
         
    char plusMinus; //'+' '-' '0' only
    char type; //'B' 'C' 'M' only
    int level; //integer - out of bounds are handled in the row.cpp functions.
    int row;   //integer - out of bounds are handled in the row.cpp functions.
    int space; //integer - out of bounds are handled in the row.cpp functions.
    
    cin >> plusMinus;
    while(cin.fail() || !(plusMinus == '+' || plusMinus == '-')) {
        //'0' to change modes out of smart parking (similar to "0 0 0" to get into smart parking)
        if (plusMinus == '0') {
            cout << "0 entered, returning to regular parking.\n" << endl;
            cout << "Please input 3 integers, separated by spaces." << endl;
            cout << "These numbers represent the number of buses, cars, and motorcycles you would like to park, respectively." << endl;
            cout << "If you would like to unpark (remove) vehicles, enter negative numbers." << endl;
            cin.clear();
            cin.ignore(256,'\n');
            requestInput();
            return;
        }
        cout << "Invalid input. Continue smart parking." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestSmartInput();
        return;
    }
    
    cin >> type;
    while(cin.fail() || !(type == 'B' || type == 'C' || type == 'M')) {
        cout << "Invalid input. Continue smart parking." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestSmartInput();
        return;
    }
    
    cin >> level;
    while(cin.fail()) {
        cout << "Invalid input. Continue smart parking." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestSmartInput();
        return;
    }
    
    cin >> row;
    while(cin.fail()) {
        cout << "Invalid input. Continue smart parking." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestSmartInput();
        return;
    }
    
    cin >> space;
    while(cin.fail()) {
        cout << "Invalid input. Continue smart parking." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        requestSmartInput();
        return;
    }
    
    //park or unpark, '+' or '-'
    if (plusMinus == '+') {
        smartPark(type, level, row, space);
    } 
    else if (plusMinus == '-') {
        smartRemove(type, level,  row, space);
    }
    
    cout << endl;
    printGarage();
    //recursion to continue letting user input smart instructions
    requestSmartInput();
    return;
}


void ParkingGarage::printGarage() {
    for(int i = getNumLevels() - 1; i >= 0; i--) {
        Level current = levels.at(i);
        cout << "Level " << (i) << ":  ";
        current.printLevel();
    }
    cout << endl;
    return;
}
