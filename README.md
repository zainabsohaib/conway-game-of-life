# HCI 104475 : Conway Game of Life - An OS course project

### PROJECT MEMBERS
* **63726** | **Zainab sohaib**
* 63646 | Taha khan

## APPROACH
We have use these following approches in this project :
* Threads
* Mutex
* Libraries(time,pthread,ctype,string,stdlib,stdio)
* Processes
* Text file

## PROBLEMS FACES

### Problem 1: 
First problem was undefine reference we were not calling barrier class variables properly in conway file.

### Problem 2: 
Second problem we faced in our project was segmentation fault(core dumped).

### Problem 3:
It was working with single thread but when we add multiple threads it was not taking input from file it took alot of time to resolve this problem.

## DESCRIPTION
This program runs Conway's Game Of Life utilizing pthreads to split the task of processing. The game board is divided up between threads by rows, and when there are more threads than rows, individual rows are divided up between threads as well.Explanation of all files is mentioned below:
### CONWAY FILE:
Split and barrier are two header files which are added in this main file conway.We have declare rows,coloums,size variables for taking input here size variable will take size of board(splitter varable is taken for board) or screen.First method read_split is reading input from file input.txt.Char argument passed here is pointing input file it will save its address.Exit failure function is use to show failure if user enter wrong file instead of input.txt it will come out of program.In this method melloc is use for memory allocation to store size of integer.Malloc function basically returns void type pointer,then in do while loop it will print the character were star is for 1 and dot is for 0.Here cursor is doing same work as i++ do in for loop pointing to the next,then to make sure we intialize our board properly we have use this condition that until cursor is equal to size of board this do while will not stop.Print_splitter method is printing the board,if board position is equal to to zero it will print zero or one(. and *).Game_generation method is making generations,it will check its neighbours first it will check previous row for neighbours where it has use three conditions that if row is not equal to zero then it will add nieghbours all these three conditions will run infinitely.Then it will check current row for neighbours all this work is done for creating neighbours.Last two conditions will check the main criteria that if it has more then three or less then 2 neighbours it will die of lonlinesses or overcrowd and copy zero but if it has three neighbours it will copy 1.Thread_race method is for running the thread it will store arguments of rows and coloumn in actual,this barrier_wait function is call from barrier class.
