/******************************************************************************

CS2336_001   Course Project   Jacob Glenny   jdg180001

*******************************************************************************/


#include "Level.h"
using namespace std;

/**
 * Level implementation
 */

Level::Level(int spacesPerLevel, int spacesPerRow, int percentLargeSpaces, int percentMotorcycleSpaces) {
    //calculate total number of each type of parking space (approximate)
    int numLargeSpaces = spacesPerLevel * percentLargeSpaces / 100;
    int numMotorcycleSpaces = spacesPerLevel * percentMotorcycleSpaces / 100;
    int numCompactSpaces = spacesPerLevel - numLargeSpaces - numMotorcycleSpaces;
    
    int l = 0;
    int c = 0;
    int m = 0;
    //decrements from the totals and increments l c m until a full row can be constructed, until all totals are 0
    //this puts all of the large spaces on a level next to each other, important for buses
    for (int i = 0; i < spacesPerLevel; i++) {
        if(numLargeSpaces > 0) {
            numLargeSpaces--;
            l++;
        } else if(numCompactSpaces > 0) {
            numCompactSpaces--;
            c++;
        } else if(numMotorcycleSpaces > 0) {
            numMotorcycleSpaces--;
            m++;
        } else {
            rows.push_back(Row(l, c, m));
        }
        
        if ((l + c + m) == spacesPerRow) {
            rows.push_back(Row(l, c, m));
            l = 0;
            c = 0;
            m = 0;
        }
    }
}

Level::~Level() {

}

int Level::getNumRows() {
    return rows.size();
}

void Level::printLevel() {
    for(int i = 0; i < getNumRows(); i++) {
        Row current = rows.at(i);
        current.printRow();
    }
    cout << endl;
    return;
}
