#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>
#include <libconfig.h++>
#include <vector>
#include <argp.h>
#include "grid.h"

#define WIDTH 200
#define HEIGHT 100
#define PIXELSIZE 5
#define WINDOWSIZE_X WIDTH*PIXELSIZE
#define WINDOWSIZE_Y HEIGHT*PIXELSIZE
#define RANGE 1
#define STATEWIDTH RANGE*2 + 1

using namespace std;
using namespace libconfig;

/* Stuff for argp */
const char *argp_program_version = "0.1";
const char *argp_program_bug_address = 
    "<pikaviesti.testitili@gmail.com>";
static char doc[] = 
    "A program displaying cellular automata.";

static char args_doc[] = "ARG1 ARG2";

static struct argp_option options[] = {
    {"rule", 'r', "RULE", 0, "The cellular automata rule" },
    {"stop", 's', "STOP", 0, "Steps before program is stopped"},
    { 0 }
};

struct arguments
{
    char *args[2]; /*arg1 & arg2*/
    int m_iRule; 
    int m_iStop;
};

/*Parse a single option*/
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = reinterpret_cast<struct arguments*>(state->input);
    
    switch (key)
    {
        case 'r':
        {
            arguments->m_iRule = atoi(arg);
            break;
        }
        case 's':
        {
            arguments->m_iStop = atoi(arg);
            break;
        }
        case ARGP_KEY_ARG:
        {
            if (2 <= state->arg_num)
            {
                /* Too many arguments*/
                argp_usage(state);
                break;
            }
        }
        default:
        {
            return ARGP_ERR_UNKNOWN;
        }
    }
    return 0;
}   

// Give rule as first parameter. Default is rule 30.

SDL_Surface *demo_screen;
int iRule = 224; // Conway's game of life
Grid currentGrid;
int iNextArray[WIDTH][HEIGHT] = {0};
int iDisplay[WIDTH][HEIGHT] = {0};
int iRow = 0;
int iStop = 1000000;
int iIteration = 0;

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

                    if ((iCol>=0) && (iCol<WIDTH) &&
                        (iRow>=0) && (iRow<HEIGHT))
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
            iNextArray[i][ii] = ((1 << ((2*iLive) + currentGrid.getValue()))&(iRule)) > 0;

        }   
    }

    iLoop++;

    // todo: make iDisplay and iNextArray also grid objects 
    // use an overloaded =operator to do the copying
    for (int i=0; i<WIDTH; i++)
    {
        currentGrid.setColumnToEdit(i);        
        currentGrid.setColumnToInspect(i);        
        for (int j=0; j<HEIGHT; j++)
        {
            currentGrid.setRowToEdit(j);        
            currentGrid.setRowToInspect(j);        
            currentGrid.setValue(iNextArray[i][j]);
            iDisplay[i][j] = currentGrid.getValue();
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

static struct argp argp = {options, parse_opt, args_doc, doc };

int main(int argc,char **argv)
{
    struct arguments arguments; 

    arguments.m_iRule = 224;
    arguments.m_iStop = -1;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    printf("rule: %d, stop: %d\n", arguments.m_iRule, arguments.m_iStop);
    Config config;
    //config.readFile("./cellauto.cfg");

    currentGrid.setWidthAndHeight(WIDTH, HEIGHT);

    iRule = arguments.m_iRule; 
    iStop = arguments.m_iStop;
    
    if (3 < argc) 
    {
        if (0 == atoi(argv[3]))
        {
            currentGrid.setColumnToEdit(WIDTH/2);
            currentGrid.setRowToEdit(HEIGHT/2);
            currentGrid.setValue(1);
        }
        else
        {
            // Set rand seed
            time_t t = time(NULL);
            srand(static_cast<int>(t));
            
            for (int i=0; i < WIDTH; i++)
            {
                currentGrid.setColumnToEdit(i);
                for (int ii=0; ii < HEIGHT; ii++)
                {
                    int iRand = rand();
                    int iVal = atoi(argv[3]);
                    
                    currentGrid.setRowToEdit(ii);
                    currentGrid.setValue(iRand%iVal);
                    currentGrid.invertValue();
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
            currentGrid.setColumnToEdit(i);
            for (int ii=0; ii < HEIGHT; ii++)
            {
                int iRand = rand();
                int iVal = 5;
                currentGrid.setRowToEdit(ii);
                currentGrid.setValue(iRand%iVal);
                currentGrid.invertValue();
            }
        }
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
