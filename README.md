# Inter-Process-Communication-programs
This repository will contains programs that is developed using different IPC systems.Also, we will put parallel programming projects

## The description of each program 

### simple client server program using POSIX
Use POSIX (Memory Sharing IPC) to create a client, server programs such that:
* The Server should create a shared memory and fill it with (-1), then he listens on this memory until reading a change. 
* The Client uses a random function to generate an integer number between 1 and 10 and places this number in the shared memory. 
* If the Server read a number other than (7), he changes it back to (-1). 
* If the Client read number (-1), he replaces it again with a new random number and so on. 
* The client and server terminate only if the shared memory contains 7. 

