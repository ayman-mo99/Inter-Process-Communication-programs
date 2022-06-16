# Inter-Process-Communication-programs
This repository will contains programs that is developed using different IPC systems.Also, we will put parallel programming projects

## The description of each program 

### Simple client server program using POSIX
Use POSIX (Memory Sharing IPC) to create a client, server programs such that:
* The Server should create a shared memory and fill it with (-1), then he listens on this memory until reading a change. 
* The Client uses a random function to generate an integer number between 1 and 10 and places this number in the shared memory. 
* If the Server read a number other than (7), he changes it back to (-1). 
* If the Client read number (-1), he replaces it again with a new random number and so on. 
* The client and server terminate only if the shared memory contains 7. 


### Find maximum number using MPI
Write a MPI program that find the maximum value of an array with length N :
* Process with rank 0 will be Master process.
* The Master process reads the length and the values of the array elements from a file “arraydata.txt” by Master node. 
* The Master process sends the length of the array to the other processes. 
* The Master process divides and distributes the array data to the other processes. 
* Each process finds the maximum value of its local array and the index of this value. 
* Each process sends its local maximum and the index to the Master node. 
* The Master node finds global maximum value and its index.
