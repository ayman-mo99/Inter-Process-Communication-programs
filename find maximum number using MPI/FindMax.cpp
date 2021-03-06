#include<iostream>
#include<stdio.h>
#include<mpi.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

  int  myrank , size  ;

  MPI_Status status;
  MPI_Init(&argc,&argv);// start MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);// Get my rank
  MPI_Comm_size(MPI_COMM_WORLD, &size);// Get the total number of processors
		
   int length ;//the length of tha master array
	
  if(myrank ==0){

	  ifstream red("arraydata.txt");    // open the text file
    	  red>>length;                      // read the length of the array
	  double master_array[length];      // create the master array  
    	  for(int i = 0 ; i<length ; i++){
    		red>>master_array[i];       // read the array 
          }


int x = length / (size-1);  // the length of local array
 
 for(int j = 1 ; j<size ; j++){// send a part of the array for each process 

   MPI_Send(&x , 1 , MPI_INT ,j,17,MPI_COMM_WORLD);//send the length of local array  
   MPI_Send(&master_array[(j-1)*x] , x , MPI_DOUBLE ,j,17,MPI_COMM_WORLD);//send local array
 
 }
                          
double max;              //maximum number
int indexof_max ;        //index of the maximum number

double local_max;	 //the received number
int local_index ;        //to take the local index 


 for(int q = 1 ; q<size ; q++){//receive local maximum and the his index
	
        MPI_Recv(&local_index , 1 , MPI_DOUBLE ,q,17,MPI_COMM_WORLD,&status); 
	MPI_Recv(&local_max , 1 , MPI_DOUBLE ,q,17,MPI_COMM_WORLD,&status); 

	if (max<local_max){     //find the muximum number and his index
	     max=local_max; 
	     indexof_max = ((q-1)*x) + local_index;//convert the local index into the index in the master array 			
 	} 
 }


 for(int i = (size-1)*x ; i< length ;i++){ // the remander unmbers

	if(max< master_array[i]){
 	     max = master_array[i];
             indexof_max = i;
	}
 }

   printf("\nthe maximum number is %lf and his index is %d \n",max,indexof_max);
	
 }

 
else{
   
     int index=0;
     int local_length;

     MPI_Recv(&local_length , 1 , MPI_INT ,0,17,MPI_COMM_WORLD,&status);//take length
     double arr[local_length];

     MPI_Recv(arr , local_length , MPI_DOUBLE ,0,17,MPI_COMM_WORLD,&status);//take array
     double  temp = arr[0];
		
     for(int i =0 ; i<local_length;i++){//find the maximum number

         if(temp < arr[i]){
	        temp = arr[i];
                index = i;
	 } 	
      }

      MPI_Send(&index , 1 , MPI_DOUBLE ,0,17,MPI_COMM_WORLD);//send max 
      MPI_Send(&temp , 1 , MPI_DOUBLE ,0,17,MPI_COMM_WORLD);//send max       
}

	MPI_Finalize();// end MPI

return 0 ;

}



