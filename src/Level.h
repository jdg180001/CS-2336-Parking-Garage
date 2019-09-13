/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

This class has a direct composition relationship with Row by having a vector<Row>.

The constructor is the most important part as it takes the user inputted 
(or default) percentage values for the types of spaces and approximates them to numbers.

*******************************************************************************/

//guard
#ifndef _LEVEL_H
#define _LEVEL_H

#include <vector>
#include "Row.h"
using namespace std;

class Level {
public: 
    Level(int spacesPerLevel, int spacesPerRow, int percentLargeSpaces, int percentMotorcycleSpaces);
        
    ~Level();
        
    int getNumRows();
    
    void printLevel();
    
private: 
    vector<Row> rows;
    friend class ParkingGarage;
};

#endif //_LEVEL_H
