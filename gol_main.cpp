#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

#define WIDTH 90
#define HEIGHT 30
#define RANGE 1
#define STATEWIDTH (RANGE*2 + 1)*(RANGE*2 + 1)


using namespace std;

// Give rule as first parameter. Default is rule 30.

// Todo: make width, range and initial state parameterisable from command line.
int main(int argc, char **argv)
{
    int iArray[WIDTH][HEIGHT]         = {0};
    int iNextArray[WIDTH][HEIGHT]     = {0};

    int iRule = 30; 
    // Start visualization at which step
    int iStartVisual = 0;

    int iHop = 1;
    int iLoop = 0;

    if (1 < argc) 
    {
        iRule = atoi(argv[1]); 
    }
    
    if (2 < argc) 
    {
        iStartVisual = atoi(argv[2]); 
    }

    if (3 < argc) 
    {
        // random initial state
        for (int i=0; i<WIDTH; i++)
        {
            for (int ii=0; ii<HEIGHT; ii++)
            {
                iArray[i][ii] = rand()%9;   
            }
        }
    }
    else
    {
        iArray[44][14] = 1;
    }

    while (1)
    {
        for (int i=0; i<WIDTH; i++)
        {
            for (int ii=0; ii<HEIGHT; ii++)
            {
                int iLive = 0; 
                
                for (int j=i-RANGE; j<=i+RANGE; j++)
                {
                    for (int jj=ii-RANGE; jj<=ii+RANGE; jj++)
                    {
                        if ((j>0) && (j<WIDTH) &&
                            (jj>0) && (jj<HEIGHT) && (j != jj))
                        {
                            if (1 == iArray[j][jj])
                            {
                                iLive++;
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
                      => every other bit is zero => total rule is 160+64=224 => so this must be the same 
                      coding as in "Two-Dimensional Cellular Automata" by Packard&Wolfram (1984), whom it is here
                      respectfully quoted:
                      "A notorious example of an outer totalistic nine-neighbor square cellular automaton is the 
                       'Game of Life', with a rule specified by code C=224."
                */
                
                iNextArray[i][ii] = ((1 << (iLive + iArray[i][ii]))&iRule) > 0;   
                
                // Conway's Game of Life
                /*if (0 == iArray[i][ii])
                {
                    iNextArray[i][ii] = ((1 << iLive)&iRule) > 0;  
                    if (3 == iLive)
                    {
                        iNextArray[i][ii] = 1;
                    }
                }
                else
                {
                    if (2 > iLive)
                    {
                        iNextArray[i][ii] = 0;
                    }
                    else if ((2 == iLive) || (3 == iLive)) 
                    {
                        iNextArray[i][ii] = 1;
                    }
                    else if (3 < iLive)
                    {
                        iNextArray[i][ii] = 0;
                    }
                }*/
            }   
        }

        iLoop++;

        if (iLoop > iStartVisual)
        {
            for (int ii=0; ii<HEIGHT; ii++)
            {
                for (int i=0; i<WIDTH; i++)
                {
                    if (0 == iArray[i][ii])
                    {
                        cout << " ";
                    }
                    else
                    {
                        cout << "O";
                    }
                }
                cout << endl;
            }
            
            if (0 == (iLoop%iHop))
            { 
                sleep(1);
            }
        }
        
        memcpy(iArray, iNextArray, WIDTH*HEIGHT*sizeof(int));
    }
}
