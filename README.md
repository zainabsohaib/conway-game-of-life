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
It was working with single thread but when we add multiple threads it was not taking input from file it took alot of time to resolve.

## DESCRIPTION
This program runs Conway's Game Of Life utilizing pthreads to split the task of processing. The game board is divided up between threads by rows, and when there are more threads than rows, individual rows are divided up between threads as well.
# CONWAY FILE:
