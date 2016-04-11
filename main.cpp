#include <string.h>
#include <unistd.h>
#include <iostream>

#define WIDTH 90
#define RANGE 1
#define STATEWIDTH RANGE*2 + 1

using namespace std;

// Should be rule 30 

// todo: make it parameterisable from the command line (which rule is used).
int main(int argc, char **argv)
{
    int iArray[WIDTH] = {0};
    int iNextArray[WIDTH] = {0};
    int iState[STATEWIDTH] = {0};

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
            
            //printf("%d", iVal);

            switch (iVal)
            {
                case 0: 
                {
                    iNextArray[i] = 0;   
                    break;
                }
                case 1: 
                {
                    iNextArray[i] = 1;   
                    break;
                }
                case 2: 
                {
                    iNextArray[i] = 1;   
                    break;
                }
                case 3: 
                {
                    iNextArray[i] = 1;   
                    break;
                }
                case 4: 
                {
                    iNextArray[i] = 1;   
                    break;
                }
                case 5: 
                {
                    iNextArray[i] = 0;   
                    break;
                }
                case 6: 
                {
                    iNextArray[i] = 0;   
                    break;
                }
                case 7: 
                {
                    iNextArray[i] = 0;   
                    break;
                }
            }
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
