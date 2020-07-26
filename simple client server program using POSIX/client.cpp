#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
int main()
{
  const int SIZE = 4096;
  const char *name = "OS";
  int fd;
  int *data;
  // open the shared memory object 
  fd = shm_open(name, O_RDWR, 0666);
  // memory map the shared memory object 
  data = (int *)mmap(0, SIZE, PROT_READ| PROT_WRITE , MAP_SHARED, fd, 0);

  // here we print the number we find in the shared memory
  printf("%s","the memory contains :");
  for(int i = 0 ;i<10 ; i++){
   	printf("%d ",data[i]);
   }
   printf("%s\n",".");
   //if we find any number that is (-1) change him to a rndom number 
   srand(time(0));
   int c=0;// to count the number of (7) we find
   for(int i = 0 ;i<10 ; i++){
        if(data[i]==-1){
            data[i]=(rand()%10);
	}
        else if(data[i]==7){
		c++;
	} 
    }
   //we print the numbers after the changes
   printf("%s","we changed the memory to :");
   for(int i = 0 ;i<10 ; i++){
      printf("%d ",data[i]);
   }
   printf("%s\n",".");

   if(c==10){// if all numbers was 7
    	shm_unlink(name);//remove the shared memory object
     	return 0;
    }

    system("./server");//call the server
		
    return 0;
}
