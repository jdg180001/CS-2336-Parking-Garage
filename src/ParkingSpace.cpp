/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

*******************************************************************************/


#include "ParkingSpace.h"

/**
 * ParkingSpace implementation
 */
 
ParkingSpace::ParkingSpace() {
}

ParkingSpace::ParkingSpace(char t) {
    setFull(false);
    setType(t);
    setVehicle('0'); //0 for no vehicle

}

ParkingSpace::~ParkingSpace() {

}


bool ParkingSpace::getFull() {
    return full;
}


void ParkingSpace::setFull(bool b) {
    full = b;
    return;
}


char ParkingSpace::getType() {
    return type;
}


void ParkingSpace::setType(char t) {
    type = t;
    return;
}

char ParkingSpace::getVehicle() {
    return vehicle;
}


void ParkingSpace::setVehicle(char v) {
    vehicle = v;
    return;
}
