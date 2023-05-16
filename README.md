# cs205-search-proj
This is the repository for the "Black and White Puzzle" search problem. UCR CS205 Spring 2023

## To Run
$make to compile, $make test to compile and run
$make clean to remove executable and non permanent text files

## Structure
* Header Folder contains all the code
  * algorithms.h contains search node class, manhattan and misplaced tile heuristics, and the general search algorithm
  * menu.h has the simple user interface
  * puzzle_generator.h has the code to generate the board
* Src folder has the main.cpp file
  * Only runs menu
  * Has commented out tests used throughout development
* Makefile has the commands to compile everything easily
* size8_trace.txt has puzzle solution using misplaced tile heuristic
* sz8-diameter.txt has the configuration which required the greatest number of moves to solve optimally
  * search for this was not exhaustive
* After running a puzzle, Trace.txt will contain the printout of the latest run