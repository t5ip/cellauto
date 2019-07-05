#include "cellautomaton.h"
#include <time.h>
#include <stdlib.h>

CellAutomaton::CellAutomaton()
{
    // Default rule is Conway's Game of Life
    iRule = 224;
    iWidth = 0;
    iHeight = 0;
    iRange = 1;
}

void CellAutomaton::setWidthAndHeight(int iNewWidth, int iNewHeight)
{
    iWidth = iNewWidth;
    iHeight = iNewHeight;
    currentGrid.setWidthAndHeight(iWidth, iHeight);
    nextGrid.setWidthAndHeight(iWidth, iHeight);
    displayGrid.setWidthAndHeight(iWidth, iHeight);
}

void CellAutomaton::setRule(int iNewRule)
{
    iRule = iNewRule;
}

void CellAutomaton::initializeRandomly()
{
    // Set rand seed
    time_t t = time(NULL);
    srand(static_cast<int>(t));
    
    for (int i=0; i < iWidth; i++)
    {
        currentGrid.setColumnToEdit(i);
        for (int ii=0; ii < iHeight; ii++)
        {
            int iRand = rand()&255;
            
            currentGrid.setRowToEdit(ii);
            if (127 < iRand)
            {
                currentGrid.setValue(1);
            }
            currentGrid.invertValue();
        }
    }
}

void CellAutomaton::initializeWithOne()
{
    currentGrid.setColumnToEdit(iWidth/2);
    currentGrid.setRowToEdit(iHeight/2);
    currentGrid.setValue(1);
    
    displayGrid.setColumnToEdit(iWidth/2);
    displayGrid.setRowToEdit(iHeight/2);
    displayGrid.setValue(1);
}

int CellAutomaton::getValueInCoordinates(int iCol, int iRow)
{
    displayGrid.setColumnToInspect(iCol);
    displayGrid.setRowToInspect(iRow);
    return displayGrid.getValue();
}

// todo: add unit tests for this method (using catch) 
// Then refactor to manageable smaller methods.
void CellAutomaton::gotoNextState()
{
    for (int i=0; i<iWidth; i++)
    {
        for (int ii=0; ii<iHeight; ii++)
        {
            int iLive = 0; 
            
            for (int j=i-iRange; j<=i+iRange; j++)
            {
                for (int jj=ii-iRange; jj<=ii+iRange; jj++)
                {

                    int iCol = j; 
                    int iRow = jj;

                    if (0 > j) 
                    {
                        iCol = iWidth + j;
                    }    
                    if (0 > jj) 
                    {
                        iRow = iHeight + jj;
                    }    
                    if (iWidth <= j) 
                    {
                        iCol = j - iWidth;
                    }    
                    if (iHeight <= jj) 
                    {
                        iRow = jj - iHeight;
                    }

                    if ((iCol>=0) && (iCol<iWidth) &&
                        (iRow>=0) && (iRow<iHeight))
                    {
                        currentGrid.setColumnToInspect(iCol);
                        currentGrid.setRowToInspect(iRow);
                        if (1 == currentGrid.getValue())
                        {
                            if ((i == iCol) && (ii == iRow))
                            {
                                ; // don't count self to live count    
                            }
                            else
                            {
                                iLive++;
                            }
                        }           
                    }
                }
            }

            /* Coding is 101010101010101010 => positions with 0 mark the bits 
               which are checked if cell is dead. Positions with 1 are checked 
               if cell is alive. 

               => Conway's Game of Life is given by: 
               1. If 3 neighbours are alive and cell is dead => cell becomes alive 
                => put fourth bit with zeroes to 1 => 2^6=64
               2. If 2 or 3 neighbours are alive and cell is alive => cell stays alive 
                  => put third and fourth bit with 1 to value 1 => 2^5+2^7 = 128 + 32 = 160
               3. If cell is alive and has less than 2 or more than 3 live neighbours => cell dies 
                  => every other bit is zero => total rule is 160+64=224
            */
            
            //iNextArray[i][ii] = ((1 << (iLive + iArray[i][ii]))&iRule) > 0;   
            currentGrid.setColumnToInspect(i);
            currentGrid.setRowToInspect(ii);
            
            nextGrid.setColumnToEdit(i);
            nextGrid.setRowToEdit(ii);

            nextGrid.setValue( ((1 << ((2*iLive) + currentGrid.getValue()))&(iRule)) > 0);

        }   
    }

    // Change state of the grid 
    currentGrid = nextGrid;
    displayGrid = currentGrid;
}

int CellAutomaton::getWidth()
{
    return iWidth;
}

int CellAutomaton::getHeight()
{
    return iHeight;
}
