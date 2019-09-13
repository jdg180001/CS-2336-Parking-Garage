/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

*******************************************************************************/
/*The main() displays necessary instructions during the run. 

There may not be a possible user input to terminate the run. 
In my IDE, inputing any keyboard shortcut such as 
"ctrl c" was how I terminated the run. (Or clicking stop).

There are checks to handle invalid, "unexpected" inputs.
Test input 2 reflects this.*/

#include <iostream>
#include <vector>
#include <string>
#include "ParkingGarage.h"
using namespace std;

int main()
{
    cout << "Would you like to provide input values? If so, enter '1', otherwise default values will be used." << endl;
    
    //default
    int numLevels = 5;
    int spacesPerLevel = 30;
    int spacesPerRow = 10;
    int percentLargeSpaces = 20;
    int percentCompactSpaces = 60;
    int percentMotorcycleSpaces = 20;
    
    //ask user for values to make the garage
    int i;
    cin >> i;
    if (i == 1) {
        cout << "How many levels?" << endl;
        cin >> i;
        while(cin.fail() || i < 0) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> i;
        }
        numLevels = i;
        
        cout << "How many spaces per level?" << endl;
        cin >> i;
        while(cin.fail() || i < 0) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> i;
        }
        spacesPerLevel = i;
        
        cout << "How many spaces per row? Be sure this evenly divides the spaces per level." << endl;
        cin >> i;
        while(cin.fail() || i < 0 || (spacesPerLevel % i) != 0) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> i;
        }
        spacesPerRow = i;
        
        cout << "What percent of each level's spaces are large spaces? Input between 0 and 100." << endl;
        cin >> i;
        while(cin.fail() || i < 0 || i > 100) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> i;
        }
        percentLargeSpaces = i;
        
        cout << "What percent of each level's spaces are motorcycle spaces? Input between 0 and " << (100 - percentLargeSpaces) << endl;
        cin >> i;
        while(cin.fail() || i < 0 || i > (100 - percentLargeSpaces)) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> i;
        }
        percentMotorcycleSpaces = i;
    }
    
    //display the values that will be used to create the garage
    percentCompactSpaces = 100 - percentLargeSpaces - percentMotorcycleSpaces;
    cout << endl << "Proceeding with: " << endl
        << "   " << numLevels               << " levels" << endl
        << "   " << spacesPerLevel          << " spaces per level" << endl
        << "   " << spacesPerRow            << " spaces per row" << endl
        << "   " << percentLargeSpaces      << " percent large spaces" << endl
        << "   " << percentCompactSpaces    << " percent compact spaces" << endl
        << "   " << percentMotorcycleSpaces << " percent motorcycle spaces" << endl << endl;
    
    //garage constructor    
    ParkingGarage p = ParkingGarage(numLevels, spacesPerLevel, spacesPerRow, percentLargeSpaces, percentMotorcycleSpaces);
    cout << "Your empty garage has been generated." << endl
         << "This garage approximates the number of large, compact, and motorcycle spots from the given percentages." << endl << endl;
         
    //show empty garage state     
    p.printGarage();
    
    cout << "\nPlease input 3 integers, separated by spaces.\n" << endl;
    cout << "These numbers represent the number of buses, cars, and motorcycles you would like to park, respectively." << endl;
    cout << "If you would like to unpark (remove) vehicles, enter negative numbers." << endl;
    cout << "For example, if I wanted to unpark 4 buses, not change the number of cars, and park 12 motorcycles,\nI would enter \"-4 0 12\"." << endl;
    cout << "\nNote that unparking occurs first, then parking occurs in the order of bus, car, and motorcycle." << endl;
    cout << "If you want to park 1 motorcycle before 1 bus and 1 car, please enter \"0 0 1\", then \"1 1 0\"."<< endl;
    cout << "To switch to smart parking, type \"0 0 0\".\n" << endl;
    
    //final method in main(). it is recursive so that the user can input as much as they want to.
    //there is no user input which terminates the program, I just close the run when I am done.
    p.requestInput();
    
    return 0;
}


