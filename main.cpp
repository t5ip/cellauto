#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

#define WIDTH 90
#define RANGE 1
#define STATEWIDTH RANGE*2 + 1

using namespace std;

// Give rule as first parameter. Default is rule 30.

// Todo: make width, range and initial state parameterisable from command line.
int main(int argc, char **argv)
{
    int iArray[WIDTH] = {0};
    int iNextArray[WIDTH] = {0};
    int iState[STATEWIDTH] = {0};

    int iRule = 30; 

    if (1 < argc) 
    {
        iRule = atoi(argv[1]); 
    }

    iArray[44] = 1;

    while (1)
    {
        for (int i=0; i<WIDTH; i++)
        {
            int iPos = 0;

            for (int j=i-RANGE; j<=i+RANGE; j++)
            {
                if ((j>0) && (j<WIDTH))
                {
                    if (1 == iArray[j])
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
            
            int iVal = 0; 

            for (int j=0; j<STATEWIDTH; j++)
            {
                iVal += iState[j] << j;
            }
            
            iNextArray[i] = (iRule >> iVal)&1; 
        }

        for (int i=0; i<WIDTH; i++)
        {
            if (0 == iArray[i])
            {
                cout << " ";
            }
            else
            {
                cout << "O";
            }
        }

        memcpy(iArray, iNextArray, WIDTH*sizeof(int));
        
        cout << endl;
        sleep(1);
    }
}
