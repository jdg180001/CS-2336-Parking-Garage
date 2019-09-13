/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

This is the base unit class. This class is important because it allows parking spaces
to be displayed as either their type ('l', 'c', 'm') or their vehicle ('B', 'C', 'M'). 
HOWEVER, what is most important about these objects is that they maintain what the
type of parking space was even after a car has been parked and removed.

*******************************************************************************/

//guard
#ifndef _PARKINGSPACE_H
#define _PARKINGSPACE_H

#include <iostream>

class ParkingSpace {
public: 

    ParkingSpace();
    
    //Row contructor calls this one
    //used only to initialize the empty garage with either large ('l'), compact ('c'), or motorcycle('m') spots
    ParkingSpace(char t);
    
    ~ParkingSpace();
        
    bool getFull();
    
    //whether or not a vehicle is ocupying the parking space    
    void setFull(bool b);
        
    char getType();
        
    void setType(char v);
    
    char getVehicle();
    
    //type of vehicle occupying the space. Bus ('B'), car ('C'), or motorcycle ('M'). 
    //'0' for no vehicle    
    void setVehicle(char v);

private: 
    bool full;
    char type;
    char vehicle;
};

#endif //_PARKINGSPACE_H
