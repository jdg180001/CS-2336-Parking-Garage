/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

This class has a direct composition relationship with ParkingSpace by having a vector<ParkingSpace>.

This class is where almost all of the math/efficiency is located. The methods are almost all designed
around trying to save as many large parking spaces for buses as possible.

*******************************************************************************/

//guard
#ifndef _ROW_H
#define _ROW_H

#include <vector>
#include "ParkingSpace.h"
using namespace std;

class Row {
public: 
    //Level constructor calls this one after deciding how many of each size space is necessary
    Row(int numLargeSpaces, int numCompactSpaces, int numMotorcycleSpaces);
        
    ~Row();
    
    int getNumSpaces();
    
    //returns an integer index of the RIGHT end of where a bus could be parked in a row
    //if no possible index found, returns -1
    int getPossibleBusIndex();
    
    //returns a valid index of where a car could be parked in a row.
    //prioritizes putting cars in compact spots before large spots
    //integer parameter attempt handles this prioritization. 
    //attempt is incrmented tail recursively but only for a max of two calls
    //if no possible index found, returns -1
    int getPossibleCarIndex(int attempt);
    
    //returns a valid index of where a motorcycle could be parked in a row.
    //prioritizes putting cars in motorcycl before compact spots before large spots
    //integer parameter attempt handles this prioritization. 
    //attempt is incrmented tail recursively but only for a max of three calls
    //if no possible index found, returns -1
    int getPossibleMotorcycleIndex(int attempt);
    
    //parks bus at an index in a row. 
    //when called in regular parking mode, the index is always valid due to the call to getPossibleBusIndex()
    //when called in smart parking mode, the index must be checked
    void parkBus(int index);
    
    //parks car at an index in a row. 
    //when called in regular parking mode, the index is always valid due to the call to getPossibleCarIndex()
    //when called in smart parking mode, the index must be checked
    void parkCar(int index);
    
    //parks motorcycle at an index in a row. 
    //when called in regular parking mode, the index is always valid due to the call to getPossibleMotorcycleIndex()
    //when called in smart parking mode, the index must be checked
    void parkMotorcycle(int index);
    
    //bool return to tell when a bus is successfuly removed so that no more are removed afterwards
    bool removeBus();
    
    //bool return to tell when a car is successfuly removed so that no more are removed afterwards
    bool removeCar();
    
    //bool return to tell when a motorcycle is successfuly removed so that no more are removed afterwards
    bool removeMotorcycle();
    
    //user attempts to park a bus at this index. the index is the left end of the bus unless there is insufficient space to the right,
    //then the index could become any part of the bus
    void smartParkBus(int index);
    
    //user attempts to remove bus at this index. the index can be any spot where a bus is, it does not have to be an end or center.
    void smartRemoveBus(int index);
    
    //index to remove car at
    void smartRemoveCar(int index);
    
    //index to remove motorcycle at
    void smartRemoveMotorcycle(int index);
    
    void printRow();

private: 
    vector<ParkingSpace> spaces;
};

#endif //_ROW_H
