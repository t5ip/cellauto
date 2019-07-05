#include "catch.hpp"
#include "../cellautomaton.h"

int getSumOfCells(CellAutomaton &automaton)
{
    int iSumOfValues = 0;
    for (int i=0; i<automaton.getWidth(); i++) 
    {
        for (int ii=0; ii<automaton.getHeight(); ii++) 
        {
            iSumOfValues += automaton.getValueInCoordinates(i,ii);
        }        
        
    }        
    return iSumOfValues;
}

TEST_CASE( "Initialize with one.", "[cellautomaton]" )
{
    CellAutomaton automaton;
    int iWidth = 200;
    int iHeight = 100;
    automaton.setWidthAndHeight(iWidth,iHeight);
    automaton.initializeWithOne();

    SECTION( "initializeWithOne" ) 
    {
        int iValue = automaton.getValueInCoordinates(iWidth/2,iHeight/2);
        REQUIRE(1 == iValue);
    }
}


TEST_CASE( "Rule 224. Initialize with one.", "[cellautomaton]" )
{
    CellAutomaton automaton;
    int iWidth = 200;
    int iHeight = 100;
    int iRule = 224; 
    automaton.setWidthAndHeight(iWidth,iHeight);
    automaton.initializeWithOne();
    automaton.setRule(224);

    SECTION( "Take one step" ) 
    {
        automaton.gotoNextState();
        REQUIRE(0 == getSumOfCells(automaton));
    }
}
