#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>
#include <libconfig.h++>
#include <vector>

#define WIDTH 200
#define HEIGHT 100
#define PIXELSIZE 5
#define WINDOWSIZE_X WIDTH*PIXELSIZE
#define WINDOWSIZE_Y HEIGHT*PIXELSIZE
#define RANGE 1
#define STATEWIDTH RANGE*2 + 1

using namespace std;
using namespace libconfig;

// Give rule as first parameter. Default is rule 30.

SDL_Surface *demo_screen;
int iRule = 224; // Conway's game of life
vector< vector<int> > iArray;
int iNextArray[WIDTH][HEIGHT] = {0};
int iDisplay[WIDTH][HEIGHT] = {0};
int iRow = 0;
int iStop = 1000000;
int iIteration = 0;
int iMetarule = 0;

// Todo: make width, range and initial state parameterisable from command line.
int handle()
{
    int iHop = 1;
    int iLoop = 0;

    if ((iIteration > iStop) && (-1 != iStop))
    {
        return 0;
    }
    
    for (int i=0; i<WIDTH; i++)
    {
        for (int ii=0; ii<HEIGHT; ii++)
        {
            int iLive = 0; 
            
            for (int j=i-RANGE; j<=i+RANGE; j++)
            {
                for (int jj=ii-RANGE; jj<=ii+RANGE; jj++)
                {

                    int iCol = j; 
                    int iRow = jj;

                    if (0 > j) 
                    {
                        iCol = WIDTH + j;
                    }    
                    if (0 > jj) 
                    {
                        iRow = HEIGHT + jj;
                    }    
                    if (WIDTH <= j) 
                    {
                        iCol = j - WIDTH;
                    }    
                    if (HEIGHT <= jj) 
                    {
                        iRow = jj - HEIGHT;
                    }

                    //cout << "iCol" << iCol << "iRow" << iRow << endl;  
                
                    if ((iCol>=0) && (iCol<WIDTH) &&
                        (iRow>=0) && (iRow<HEIGHT))
                    {
                        if (1 == iArray[iCol][iRow])
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
                  => every other bit is zero => total rule is 160+64=224 => so this must be the same 
                  coding as in "Two-Dimensional Cellular Automata" by Packard&Wolfram (1984), whom it is here
                  respectfully quoted:
                  "A notorious example of an outer totalistic nine-neighbor square cellular automaton is the 
                   'Game of Life', with a rule specified by code C=224."
            */
            
            //iNextArray[i][ii] = ((1 << (iLive + iArray[i][ii]))&iRule) > 0;   
            iNextArray[i][ii] = ((1 << ((2*iLive) + iArray[i][ii]))&(iRule)) > 0;

            // Debug:
            /*if (iNextArray[i][ii] > 0)
            {
                int iTmp = (1 << ((2*iLive) + iArray[i][ii]));
                cout << "Live: " <<  iLive << " Rule: " << iRule << " Array: " << iArray[i][ii];
                cout << "  (1 << ((2*iLive) + iArray[i][ii]) " << iTmp  << endl;
            }*/
            
            // Conway's Game of Life
            /*if (0 == iArray[i][ii])
            {
                // iNextArray[i][ii] = ((1 << (2*(iLive-1)))&iRule) > 0;  
                int iVal = ((1 << ((2*iLive) + iArray[i][ii]))&iRule) > 0;  
                
                if (3 == iLive)
                {
                    iNextArray[i][ii] = 1;
                }

                if (iVal != iNextArray[i][ii])
                {
                    cout << "err:" << iVal << "    " << iNextArray[i][ii] << endl;
                }
            }
            else
            {
                if (2 > iLive)
                {
                    iNextArray[i][ii] = 0;
                }
                
                if ((2 == iLive) || (3 == iLive)) 
                {
                    iNextArray[i][ii] = 1;
                }
                
                if (3 < iLive)
                {
                    iNextArray[i][ii] = 0;
                }
            }*/
        }   
    }

    iLoop++;

    /*if (iLoop > 0)
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
    }*/
    
    //memcpy(&iArray, iNextArray, WIDTH*HEIGHT*sizeof(int));
    //memcpy(iDisplay, &iArray, WIDTH*HEIGHT*sizeof(int));

    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGHT; j++)
        {
            iArray[i][j] = iNextArray[i][j];
            iDisplay[i][j] = iArray[i][j];
        }
    }

    iIteration++;
}
void draw()
{
    //cout << "draw()" << endl;
	int i,bpp,rank,x,y;
	int ii=0;
	int jj=0;
	Uint32 *pixel;
	/* Lock surface */
	SDL_LockSurface(demo_screen);
	rank = demo_screen->pitch/sizeof(Uint32);
	pixel = (Uint32*)demo_screen->pixels;
	/* Draw all dots */
	    
    int x_pixel = 0;
    int y_pixel = 0;

    for(int y = 0; y < HEIGHT; y++)
	{
        
        x_pixel = 0;

        for (int x = 0; x < WIDTH; x++)
        {
            /* Set pixel */
       /* for (int i=0; i<WIDTH; i++)
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

        cout << endl;*/
            if (0 == iDisplay[x][y])
            {
                for (int i=x_pixel; i<x_pixel + PIXELSIZE; i++)
                {
                    for (int ii=y_pixel; ii<y_pixel + PIXELSIZE; ii++)
                    {
                        pixel[i+ii*rank] = SDL_MapRGBA(demo_screen->format,255,255,255,255);
                        //cout << "O";
                    }
                }
            }
            else
            {
                for (int i=x_pixel; i<x_pixel + PIXELSIZE; i++)
                {
                    for (int ii=y_pixel; ii<y_pixel + PIXELSIZE; ii++)
                    {
                        pixel[i+ii*rank] = SDL_MapRGBA(demo_screen->format,0,0,0,255);
                        //cout << "O";
                    }
                }
            }
            
            x_pixel += PIXELSIZE;;
        }
        //cout << endl;
        //fflush(stdout);

        y_pixel += PIXELSIZE;
	}
	/* Unlock surface */
	SDL_UnlockSurface(demo_screen);
}

int main(int argc,char **argv)
{
    //Config config;
    //config.readFile("./cellauto.cfg");
    
    iArray.resize(WIDTH);
    for (int i=0; i<WIDTH; i++)
    {
        iArray[i].resize(HEIGHT);
    }

    if (1 < argc) 
    {
        iRule = atoi(argv[1]); 
    }
    else
    {
        iRule = 224;
    }
    
    if (2 < argc) 
    {
        iStop = atoi(argv[2]); 
    }
    else
    {
        iStop = -1;
    }
    
    if (3 < argc) 
    {
        if (0 == atoi(argv[3]))
        {
            iArray[WIDTH/2][HEIGHT/2] = 1;
        }
        else
        {
            // Set rand seed
            time_t t = time(NULL);
            srand(static_cast<int>(t));
            
            for (int i=0; i < WIDTH; i++)
            {
                for (int ii=0; ii < HEIGHT; ii++)
                {
                    int iRand = rand();
                    int iVal = atoi(argv[3]);
                    iArray[i][ii] = iRand%iVal;

                    if (0 == iArray[i][ii])
                    {
                        iArray[i][ii] = 1;
                    }
                    else
                    {
                        iArray[i][ii] = 0;
                    }
                }
            }
        }
    }
    else
    {
        time_t t = time(NULL);
        srand(static_cast<int>(t));
        
        for (int i=0; i < WIDTH; i++)
        {
            for (int ii=0; ii < HEIGHT; ii++)
            {
                int iRand = rand();
                int iVal = 5;
                iArray[i][ii] = iRand%iVal;

                if (0 == iArray[i][ii])
                {
                    iArray[i][ii] = 1;
                }
                else
                {
                    iArray[i][ii] = 0;
                }
            }
        }
        //iArray[WIDTH/2][HEIGHT/2]= 1;

        //iArray[100][100]= 1;
        //iArray[100][101]= 1;
        //iArray[101][100]= 1;
        //iArray[101][101]= 1;
    }
    if (4 < argc) 
    {
        iMetarule = atoi(argv[4]);
    }
    else
    {
        iMetarule = 0;         
    }   

	SDL_Event ev;
	int active;
	/* Initialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stderr,"Could not initialize SDL: %s\n",SDL_GetError());
	/* Open main window */
	demo_screen = SDL_SetVideoMode(WINDOWSIZE_X,WINDOWSIZE_Y,0,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(!demo_screen)
		fprintf(stderr,"Could not set video mode: %s\n",SDL_GetError());
	/* Main loop */
	active = 1;

    printf("speed up: press +, slow down: press -\n");
    fflush(stdout); 
	
    while(active)
	{
		/* Handle events */
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_QUIT)
				active = 0; /* End */

            if (SDL_KEYDOWN == ev.type)
            {
                //printf("pressed %d", ev.key.keysym.sym);

/*                switch (ev.key.keysym.sym)
                {
                    case 43:
                    {
                        printf("speeding up. speed is: %f\n", demo_time_coeff);
                        fflush(stdout);
                        demo_time_coeff *= 2;
                        break;
                    }
                    case 45:
                    {
                        printf("slowing down. speed is: %f\n", demo_time_coeff);
                        fflush(stdout);
                        demo_time_coeff /= 2;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }*/
            }
		}
		/* Start time */
		//demo_start_time();
		/* Handle simulation */
		handle();
		/* Clear screen */
		SDL_FillRect(demo_screen,NULL,SDL_MapRGBA(demo_screen->format,0,0,255,255));
		/* Draw simulation */
		draw();
		/* Show screen */
		SDL_Flip(demo_screen);
		/* End time */
		//demo_end_time();
        //cout << "active" << endl;
        //fflush(stdout);
	}
	/* Exit */
	SDL_Quit();
	return 0;
}
