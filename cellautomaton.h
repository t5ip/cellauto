#ifndef __CELLAUTOMATON_H
#define __CELLAUTOMATON_H

#include "grid.h"

using namespace std;

class CellAutomaton
{
public: 
    CellAutomaton();
    void setWidthAndHeight(int iWidth, int iHeight);    
    void setRule(int iNewRule);
    void initializeRandomly();
    void initializeWithOne();
    int getValueInCoordinates(int iCol, int iRow);
    void gotoNextState();
private: 
    Grid currentGrid;
    Grid nextGrid;
    Grid displayGrid;
    int iRule;
    int iWidth;
    int iHeight;
    int iRange;
};

#endif
