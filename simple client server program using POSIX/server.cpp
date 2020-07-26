#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
int main()
{
  const int SIZE = 4096;
  const char *name = "OS";
  int fd;
  int *data;
// we assume that the memory contains 10 numbers only
/* create the shared memory object */
  fd = shm_open(name,O_CREAT | O_RDWR|O_EXCL,0666);

  if(fd<0){// if already there is a shared memory named os

     fd = shm_open(name, O_RDWR, 0666);
     data = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
     int c=0;// to count the number of "7" in the memory
     for(int i = 0 ;i<10 ; i++){
	 if(data[i]!=7){// if we read a number other than (7)
	     data[i]=-1; // we change him back to (-1)
	 }else{
	     c++;// here we count the number of (7)
	  }   
     }
	
     if(c==10){// if all numbers become 7
        printf("\n%s\n","server: all numbers are 7");
	return 0;
      }

      system("./client");// call the client
      return 0;
   }

   printf(" %s","the server created the shred memory \n");

   /* configure the size of the shared memory object */
   ftruncate(fd, SIZE);
   /* memory map the shared memory object */
   data = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

   for(int i = 0 ;i<10 ; i++){ // we fill the data array with "-1"
      data[i]=-1;
   }
   munmap(data,SIZE); // we put the the data in the shared memory
   system("./client");// call the client
   return 0;
}
