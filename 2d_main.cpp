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
    int iState[STATEWIDTH] = {0};

    int iRule = 30; 

    int iHop = 1;
    int iLoop = 0;

    if (1 < argc) 
    {
        iRule = atoi(argv[1]); 
    }

    // random initial state
    for (int i=0; i<WIDTH; i++)
    {
        for (int ii=0; ii<HEIGHT; ii++)
        {
            iArray[i][ii] = rand()%2;   
        }
    }

    while (1)
    {
        for (int i=0; i<WIDTH; i++)
        {
            for (int ii=0; ii<HEIGHT; ii++)
            {
                int iPos = 0;
                
                for (int j=i-RANGE; j<=i+RANGE; j++)
                {
                    for (int jj=ii-RANGE; jj<=ii+RANGE; jj++)
                    {
                        if ((j>0) && (j<WIDTH) &&
                            (jj>0) && (jj<HEIGHT))
                        {
                            if (1 == iArray[j][jj])
                            {
                                iState[iPos] = 1;
                            }           
                            else
                            {
                                iState[iPos] = 0;
                            }
                        }
                        iPos++;
                    }
                }
                
                int iVal = 0; 

                for (int j=0; j<STATEWIDTH; j++)
                {
                    iVal += iState[j] << j;
                }
                
                iNextArray[i][ii] = (iRule >> iVal)&1; 

            }   
        }

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
       
        memcpy(iArray, iNextArray, WIDTH*HEIGHT*sizeof(int));
        
        if (0 == (iLoop++)%iHop)
        { 
            sleep(1);
        }
    }
}
