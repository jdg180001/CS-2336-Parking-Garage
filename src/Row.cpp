/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

*******************************************************************************/


#include "Row.h"
using namespace std;

/**
 * Row implementation
 */

Row::Row(int numLargeSpaces, int numCompactSpaces, int numMotorcycleSpaces) {
    for (int i = 0; i < numLargeSpaces; i++) {
        spaces.push_back(ParkingSpace('l'));
    }
    for (int i = 0; i < numCompactSpaces; i++) {
        spaces.push_back(ParkingSpace('c'));
    }
    for (int i = 0; i < numMotorcycleSpaces; i++) {
        spaces.push_back(ParkingSpace('m'));
    }
}

Row::~Row() {

}

int Row::getNumSpaces() {
    return spaces.size();
}

//"bus index" I define as the right most large space that precedes 5 consecutive available large spaces.
//I know this is contradictory to my user inputs for smart parking, which begins at the left most space.
int Row::getPossibleBusIndex() {
    int count = 0;
    //row size < 5, a bus index can't exist.
    if (getNumSpaces() < 5) {
        return -1;
    } else {
        ParkingSpace p;
        //for every space on a row (right to left), when an available large space is found, 
        //count to see if there are 5 consecutive spaces. if so, return that right index as valid.
        for (int i = getNumSpaces() - 1; i >= 0; i--) {
            p = spaces.at(i);
            if (p.getType() == 'l' && !p.getFull()) {
                count = 1;
                for (int j = 1; j < 5; j++) {
                    if (i-j >= 0) {
                        p = spaces.at(i-j);
                        if(p.getType() == 'l' && !p.getFull()) {
                            count++;
                        }
                    }
                }
                if (count == 5) {
                    return i;
                }
            }
        }
    }
    return -1;
}

//attempt one, find an open compact space
//attempt two, settle for an open large space
int Row::getPossibleCarIndex(int attempt) {
    ParkingSpace p;
    for (int i = getNumSpaces() - 1; i >= 0; i--) {
        p = spaces.at(i);
        if (!p.getFull() && (p.getType() == 'c' || (attempt == 2 && p.getType() == 'l'))) {
            return i;
        }
    }
    return -1;
}

//attempt one, find an open motorcycle space
//attempt two, try for an open compact space
//attempt three, settle for an open large space
int Row::getPossibleMotorcycleIndex(int attempt) {
    ParkingSpace p;
    for (int i = getNumSpaces() - 1; i >= 0; i--) {
        p = spaces.at(i);
        if (!p.getFull() && (p.getType() == 'm' || (attempt == 2 && p.getType() == 'c') || (attempt == 3 && p.getType() == 'l'))) {
            return i;
        }
    }
    return -1;
}

//I know the index will be valid, so just mark 5 spots as having a bus
void Row::parkBus(int index) {
    ParkingSpace p;
    for (int i = 0; i < 5; i++) {
        p = spaces.at(index-i);
        p.setFull(true);
        p.setVehicle('B');
        spaces.erase(spaces.begin() + index-i);
        spaces.insert(spaces.begin() + index-i, p);
    }
    return;
}

//check index for within bounds, 
//then check the space is the right size for a car
//while the ParkingGarage::parkSingle() call to this method always provides a valid index, 
//these checks are in place to prevent user error of smart parking.
void Row::parkCar(int index) {
    if (index < 0 || index > getNumSpaces()) {
        return;
    }
    ParkingSpace p = spaces.at(index);
    if (!p.getFull() && (p.getType() == 'c' || p.getType()  == 'l')) {
        p.setFull(true);
        p.setVehicle('C');
        spaces.erase(spaces.begin() + index);
        spaces.insert(spaces.begin() + index, p);
        return;
    }
}

//check index for within bounds, 
//then check the space is the right size for a car
//while the ParkingGarage::parkSingle() call to this method always provides a valid index, 
//these checks are in place to prevent user error of smart parking.
void Row::parkMotorcycle(int index) {
    if (index < 0 || index > getNumSpaces()) {
        return;
    }
    ParkingSpace p = spaces.at(index);
    if (!p.getFull()) {
        p.setFull(true);
        p.setVehicle('M');
        spaces.erase(spaces.begin() + index);
        spaces.insert(spaces.begin() + index, p);
        return;
    }
}

//finds the first space with a Bus, then empties that space and the next 4, as they MUST also have buses.
//boolean return tells if the remove was successful
bool Row::removeBus() {
    ParkingSpace p;
    for (int i = 0; i < getNumSpaces(); i++) {
        p = spaces.at(i);
        if(p.getVehicle() == 'B') {
            for (int j = 0; j < 5; j++) {
                p = spaces.at(i + j);
                p.setFull(false);
                p.setVehicle('0');
                spaces.erase(spaces.begin() + i + j);
                spaces.insert(spaces.begin() + i + j, p);
            }
            return true;
        }
    }
    return false;
}

//boolean return tells if the remove was successful
bool Row::removeCar() {
    ParkingSpace p;
    for (int i = 0; i < getNumSpaces(); i++) {
        p = spaces.at(i);
        if(p.getVehicle() == 'C') {
            p.setFull(false);
            p.setVehicle('0');
            spaces.erase(spaces.begin() + i);
            spaces.insert(spaces.begin() + i, p);
            return true;
        }
    }
    return false;
}

//boolean return tells if the remove was successful
bool Row::removeMotorcycle() {
    ParkingSpace p;
    for (int i = 0; i < getNumSpaces(); i++) {
        p = spaces.at(i);
        if(p.getVehicle() == 'M') {
            p.setFull(false);
            p.setVehicle('0');
            spaces.erase(spaces.begin() + i);
            spaces.insert(spaces.begin() + i, p);
            return true;
        }
    }
    return false;
}

//parks a bus using the user input index as the left end of the bus.
//HOWEVER, if there is not sufficient room to the right, it looks back to the left to potentially park the bus.
void Row::smartParkBus(int index) {
    //check for user input index within bounds
    if (index < 0 || index > getNumSpaces()) {
        return;
    }
    ParkingSpace p;
    int countR = 0;
    int countL = 0;
    
    //count 5 spaces (right)
    for (int i = 0; i < 5; i++) {
        p = spaces.at(index + i);
        if (!p.getFull() && p.getType() == 'l')
            countR++;
    }
    //if the right side counter didn't make it to 5, count to the left
    if (countR < 5) {
        for (int i = 0; i < 5 - countR; i++) {
        p = spaces.at(index - i - 1);
            if ((index - i - 1) >= 0 && !p.getFull() && p.getType() == 'l')
                countL++;
        }
    }
    //if 5 total consecutive spots found, park a bus (using parkBus which parks from the right end.)  that's why it adds 4.
    if (countR + countL == 5)
        parkBus(index + 4 - countL);
    return;
}

//this method ensures that buses dont get cut in half by a "smart remove" user supplying an index other than the end of a bus
void Row::smartRemoveBus(int index) {
    //check for user input index within bounds
    if (index < 0 || index > getNumSpaces()) {
        return;
    }
    
    ParkingSpace p = spaces.at(index);
    int count = 0;
    
    if (p.getVehicle() == 'B') {
        //count the number of consective bus spaces to the RIGHT of the index user wants to remove from
        for (int i = 1; (i + index) < getNumSpaces(); i++) {
            p = spaces.at(index + i);
            if (p.getVehicle() == 'B') {
                count++;
            }
        }
        //modulo 5, remove the RIGHT portion of the buss. 
        //does not change the part of the bus AT the user input index (because the for loop begins with int i = 1).
        for (int i = 1; i < ((count) % 5) + 1; i++) {
            p = spaces.at(index + i);
            p.setFull(false);
            p.setVehicle('0');
            spaces.erase(spaces.begin() + index + i);
            spaces.insert(spaces.begin() + index + i, p);
        }
        
        //count the number of consective bus spaces to the LEFT of the index user wants to remove from
        p = spaces.at(index);
        count = 0;
        for (int i = index - 1; i >= 0; i--) {
            p = spaces.at(i);
            if (p.getVehicle() == 'B') {
                count++;
            }
        }
        //modulo 5, remove the LEFT portion of the buss.
        //DOES also remove part of the bus at the user input index (because for loop begins with int i = 0).
        for (int i = 0; i < ((count) % 5) + 1; i++) {
            p = spaces.at(index - i);
            p.setFull(false);
            p.setVehicle('0');
            spaces.erase(spaces.begin() + index - i);
            spaces.insert(spaces.begin() + index - i, p);
        }
    }
    return;
}

void Row::smartRemoveCar(int index) {
    //check for user input index within bounds
    if (index < 0 || index > getNumSpaces()) {
        return;
    }
    ParkingSpace p = spaces.at(index);
    if(p.getVehicle() == 'C') {
        p.setFull(false);
        p.setVehicle('0');
        spaces.erase(spaces.begin() + index);
        spaces.insert(spaces.begin() + index, p);
    }
    return;
}

void Row::smartRemoveMotorcycle(int index) {
    //check for user input index within bounds
    if (index < 0 || index > getNumSpaces()) {
        return;
    }
    ParkingSpace p = spaces.at(index);
    if(p.getVehicle() == 'M') {
        p.setFull(false);
        p.setVehicle('0');
        spaces.erase(spaces.begin() + index);
        spaces.insert(spaces.begin() + index, p);
    }
    return;
}

void Row::printRow() {
    for(int i = 0; i < getNumSpaces(); i++) {
        ParkingSpace p = spaces.at(i);
        if(p.getVehicle() == '0')
            cout << p.getType();
        else
            cout << p.getVehicle();
    }
    cout << " ";
    return;
}
