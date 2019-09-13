/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

This class is the only one with an object constructed in main().

This class has a direct composition relationship with Level by having a vector<Level>, but really composes every class.

This class is what the user sees and interacts with.
Much of this class is handling user input.

*******************************************************************************/

//guard
#ifndef _PARKINGGARAGE_H
#define _PARKINGGARAGE_H

#include <string>
#include <vector>
#include "Level.h"
using namespace std;

class ParkingGarage {
public: 
    //user inputted or default values go into contructor
    ParkingGarage(int numLevels, int spacesPerLevel, int spacesPerRow, int percentLargeSpaces, int percentMotorcycleSpaces);
        
    ~ParkingGarage();
    
    int getNumLevels();
    
    //just a for loop iterating numBuses, numCars, and numMotorcycles times.
    //calls parkSingle with appropriate character  
    void parkMultiple(int numBuses, int numCars, int numMotorcycles);
    
    //type: Bus ('B'), car ('C'), or motorcycle ('M').    
    //attempt: always == 1 until recursive calls increment this to 2 or 3 max, for car and motorcycle respectively
    void parkSingle(char type, int attempt);
    
    //type: Bus ('B'), car ('C'), or motorcycle ('M').  
    void removeSingle(char type);
    
    //type: Bus ('B'), car ('C'), or motorcycle ('M').  
    //level numbers displayed in output but they are bottom to top.
    //rows and space indices are left to right.
    //together, these 3 coordinates are where to park.
    //this method only takes user input.
    void smartPark(char type, int level, int row, int space);
    
    //type: Bus ('B'), car ('C'), or motorcycle ('M').  
    //level numbers displayed in output but they are bottom to top.
    //rows and space indices are left to right.
    //together, these 3 coordinates are where to UNPARK.
    //this method only takes user input.
    void smartRemove(char type, int level, int row, int space);
    
    //recursively request user input forever, also indirect recursion with requestSmartInput, as they can
    //both switch between calling themselves or each other.
    //user input "0 0 0" switches to smart, user input '0' switches to regular.
    void requestInput();
    void requestSmartInput();
    
    void printGarage();
    
private: 
    vector<Level> levels;
};

#endif //_PARKINGGARAGE_H
