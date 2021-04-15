PROBLEM:
Mazes have been an intriguing subject for many years. Experimental psychologists train rats 
to search mazes for food, and many a mystery novelist has used an English country garden maze as 
setting for a murder. We also interested in mazes since they present a nice application of stacks.   You 
are  going  to  develop  a  program  that  runs  a  maze.  Although   this  program  takes  many  false  paths 
before it finds a correct one, once found it can correctly rerun the maze without taking any false paths.
In  your  program,  the  first  issue  that  confronts  us  is  the  representation  of  the  maze.  The 
obvious  choice  is  a  two  dimensional  array  in  which  zeros  represents  the  open paths  and  ones  the 
barriers. Figure-2 shows a simple maze. We assume that you start at the top left and exit at the bottom 
right. Let X marks the spot of our current location ,  and then  Figure-1  shows the possible moves from 
this position. So you have eight directions of movements (except borders).
Some important issues:
Your program must find ALL possible solution paths.
Maze size is not constant. (but maximum 30x30)
You must use stack while solving the problem. In addition, usage of  any  other  data 
structure is allowed.

INPUT:
Your program has  one input file.  Example  “maze.txt” file  is below. Several input files will be 
used to explore your application’s robustness level;
011001100011111
100111011100111
011000101110011
110111101101100
110100101101111
101101101100101
011110011111011
101101101111110
110011101100001
001111010011110
010011011111110

OUTPUT:
After  execution,  output  of  the  program  is  written  to  a  file  named  “path.txt”.  It  contains  ALL
possible solution paths of the maze (If there is no solution, it must be stated);
Solution 1:
#..............
.##............
...#...........
..#............
..#............
.#.............
#....##........
.#..#..#.......
..##...#..####.
........##....#
..............#
Solution 2:
#..............
.##...#........
...###.#.......
.......#.......
.......#.......
.......#.......
......#........
.......#.......
.......#..####.
........##....#
..............#