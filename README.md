# cellauto

Cellular automata visualization

You will need to install libsdl, libsdl-dev, libconfig++, libconfig++-dev

Run make 

Then run

cellauto -r[rule] -s[steps] 

Example: 

cellauto -r 224 

sdl_gol_main shows 2d cellular automata with sdl.

You can change the main function in the Makefile. 

sdl_main shows 1d cellular automata with sdl and takes only one argument: (cellauto [rule])

1D and 2D automata will be merged to the same main program soon. Also the whole program must be refactored as an exercise.

Some interesting rules: 

cellauto -r 224
cellauto -r 107
cellauto -r 1003
cellauto -r 204 -s 50
