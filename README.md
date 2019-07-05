# cellauto

Cellular automata visualization

=== Dependencies === 

You will need to install libsdl, libsdl-dev, libconfig++, libconfig++-dev

== Building ===

Run make 

You can change the main function in the Makefile. 

sdl_gol_main shows 2d cellular automata with sdl.

sdl_main shows 1d cellular automata with sdl and takes only one argument: (cellauto [rule])

1D and 2D automata will be merged to the same main program soon. Also the whole program must 
be refactored as an exercise.

=== Running === 

cellauto -r[rule] -s[steps] 

Example: 

cellauto -r 224 

=== Unit tests === 

cd tests 

make

./test 

This should be integrated to the main folder Makefile so that running make runs 
unit tests for the files that have changed.

=== Some interesting rules ===

cellauto -r 224

cellauto -r 107

cellauto -r 1003

cellauto -r 204 -s 50 

Note that -s parameter initializes the automaton with only one cell active. 

Without the -s parameter, the automaton starts from a random state. 

A third argument should be added for the initial state and -s argument should not affect the initial state.
