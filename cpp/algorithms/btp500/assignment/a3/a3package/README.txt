This package includes the main as well as other utility functions that
you may need in order to create your game tree.  It includes a function
that will do the explosions and calculate what the new board will look
like.   All you have to do is call it.  All function descriptions are
stored in expgame.h.

Aside from the main, I have also included 2 interactive players objects.
P1 and P2 are classes derived from Player.  Your P1 and P2 will be similar
except that the row/col chosen will be determined by a game tree as
opposed to interactively (thus you should not be calling any of the dio*
functions).  You will need to replace the appropriate files to test your
program (ie if you are testing your P1, then replace p1.h and p1.cpp)

I have also included a compilation script (c.bat).  When you compile your
program you will need to supply the name of your <userid>.cpp file.  If you
are using one of my interactive players, you will need to also supply 
leung.cpp.  This is the compilation script I will use in class as well.
Sample usage:

c leung.cpp student.cpp

