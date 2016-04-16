#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <SDL.h>

#define WIDTH 1000
#define HEIGHT 500
#define WINDOWSIZE_X 1000
#define WINDOWSIZE_Y 500
#define RANGE 1
#define STATEWIDTH RANGE*2 + 1

using namespace std;

// Give rule as first parameter. Default is rule 30.

SDL_Surface *demo_screen;
int iRule = 30;
int iArray[WIDTH] = {0};
int iNextArray[WIDTH] = {0};
int iDisplay[WIDTH][HEIGHT] = {0};
int iRow = 0;
int iStop = 1000000;
int iIteration = 0;
int iMetarule = 0;

// Todo: make width, range and initial state parameterisable from command line.
int handle()
{
    int iState[STATEWIDTH] = {0};

    int iHop = 100;
    int iLoop = 0;

    if (iIteration > iStop)
    {
        return 0;
    }

    //while (1)
    //{
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

            if (0 < iMetarule)
            {
                iRule |= iMetarule;
                iRule = iRule%256;
            }
        }

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
        
        memcpy(iArray, iNextArray, WIDTH*sizeof(int));

        for (int iD=0; iD<WIDTH; iD++)
        {
            iDisplay[iD][iRow] = iArray[iD];
        }

        iRow = (iRow + 1)%HEIGHT;

        if (0 == (iLoop++)%iHop)
        { 
            //sleep(1);
        }
    //}

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
	for(int y = 0; y < HEIGHT; y++)
	{
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
                pixel[x+y*rank] = SDL_MapRGBA(demo_screen->format,255,255,255,255);
                //cout << "O";
            }
            else
            {
                pixel[x+y*rank] = SDL_MapRGBA(demo_screen->format,0,0,0,255);
                //cout << " ";
            }
        }
        //cout << endl;
        //fflush(stdout);
	}
	/* Unlock surface */
	SDL_UnlockSurface(demo_screen);
}

int main(int argc,char **argv)
{
    if (1 < argc) 
    {
        iRule = atoi(argv[1]); 
    }
    else
    {
        iRule = 30;
    }
    
    if (2 < argc) 
    {
        iStop = atoi(argv[2]); 
    }
    else
    {
        iStop = 100000000;
    }
    
    if (3 < argc) 
    {
        if (0 == atoi(argv[3]))
        {
            iArray[WIDTH/2] = 1;
        }
        else
        {
            for (int i=0; i < WIDTH; i++)
            {
                iArray[i] = rand()%atoi(argv[3]);
            }
        }
    }
    else
    {
        iArray[WIDTH/2] = 1;
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
