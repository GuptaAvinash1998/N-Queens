/*
 * Avinash Gupta
 * G01009180
 * CS262 Lab Section: 2B3
 *Project 1
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//These are functions that can be used to calculte the max and min
#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
      _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
      _a < _b ? _a : _b; })


void initializer(int a[], int size){//This function initializes the array
//O(N)
  int h = 0;
  for(h=0;h<size;h++){//loops through the first size elements of the array and initializes them

	a[h] = h;
  }
}
void randperm(int b[], int n){//This is the function that is used to generate the random permutations for the board
//O(N)
  long r = 0;//stores the random value
  int k = n-1;//keeps track of the last element
  int temp = 0;//This is a temporary variable
  int j = 0;//This is also a temporary variable
  
  //The way randoerm works is it taken in an array and based on the size of the array, it generates n-1 permutations
  //So i keeps track of that
  //The number generated from the random function represents the index that has to be swapped with the last element
  //For example if your array is [0,1,2,3] and the number generated is 2 the you have the elmeent at the 2nd index which is 2
  //and swap it with 3 and now the array will be [0,1,3,2], so just like this we have different solutions
  for(int i=n-1;i>0;i--){

	r = random()%n;//creates the random number
	j = b[r];//stores the element in that index
	temp = b[k];//stores the last element 
	b[k] = j;//swaps the values
	j = temp;
	b[r] = j;
  } 

}

int checkboard(int a[], int n){ //checks if the permutation solves the N-queens problem
//O(N^2)    
    int i1 = 0;//This is the first index
    int i2 = 1;//This is the second index
    int solved = 1;//This is a boolean value
    
    while(i1<n-1){//checks if the first index goes to the second last element
        
        i2 = i1+1;//second index will alsways be one higher than the first index
        
        while(i2<n){ //checks if the second index goes to the last element  
         
	    //The conditions for solving the solution is that no 2 queens should share the same row or column and they cannot be diagonal to each other
	    //The queens will be in the same row if 2 indecies have the same value, i.e there are duplicates. We do not check that here because this condition is already taken care of in randperm
	    //The queens will be diagonal to each other if the absolute value of the difference of the the indicies and the values in the indicies are the same. That is what we are checking here
	    //If the difference is the same, then the solution is not solved
	    //else it is
	    if((abs(a[i1] - a[i2]) == abs(i1-i2))){
                
		return 0;
            }
            
            i2++;
            
        }
        
        i1++;
    }
    
    return solved;
}

void displayboard(int b[], int n){//This displays the board
//O(N^2)    
    int g1 = 0;//index 1
    int g2 = 0;//index 2
    
    while(g1<n){//both have to be below n
        
        g2 = 0;
        
        while(g2<n){
            
            if(g2 == b[g1]){//index 2 will keep increasing and at the same time it will check if the vlaue that it has right now is the same as the value of the in the first index
                
                printf(" * ");//i.e if this is a queen, then it will print a star
            }else{
                printf(" - ");//else a dash
            }
            g2++;
        }
        printf("\n");
        g1++;
    }
}

void printPerm(int b[], int n){//prints the permutation of the solution
//O(N)    
    printf("[ ");
    for(int i=0;i<n;i++){//loops through each element
        
        printf("%d ",b[i]);//prints it out
    }
    printf("]\n");
}

int fact(int n){//calcultes the factorial of the number n
//O(N)
  int product = 1;

  for(int i=n;i>=1;i--){

	product *= i;
  }
  return product;
}

int main(){

  int board_size = 4;//This is the starting board size
  int i = 0;//This is a variable that keeps track of the size
  int queens_array[20];//Initial starting array
  
  int min = 9999;//used to find the min
  int max = 0;//used to find the max
  
  srandom(9180);//initializes the random number generator
  long attempt = 0;//keeps track of the number of permutations
  int sol = 0;//This stores the value that is returned after calling check board

  int rand_perm_cntr = 0;//counts the number of times rand perm has been called in each solution
  int check_board_cntr = 0;//counts the number of times check board has been called in each solution
 
  int sum = 0;//This keeps track of the sum of all the permutation in order to calculate the average
    
  for(i=board_size;i<21;i++){//starts with board size 4 and goes on till 20
	
	initializer(queens_array,i);//initializes the array

	int bsize = i;//bsize is a variable that also keeps track of teh board size
	int looper = 1;//This is the number of solutions found
	sum = 0;//reinitializes sum for every board size
	
 	while(looper <= 10){
    	
    	do{
    	    randperm(queens_array,i);//gets the random permutation
	    attempt++;//increments the attempt
	    rand_perm_cntr++;//increments the number of times rand perm has been called

	    sol = checkboard(queens_array,i);//check if the permutation is good and stores the value in a variable
	    check_board_cntr++;//increments the cntr for number of times checkboard has been called
    	    
    	}while(!sol);//does all this while the the solution is not found
	
		
     	if(sol == 1 && looper == 1){//if the solution has been found and we found only the first solution
    	    
     	    printf("This permutation does solve the problem for the board of size %d\n",i);
     	    printPerm(queens_array,i);//we print out the solved permutation
     	    displayboard(queens_array,i);//we also display the solved board
	    
     	}

	 printf("Solution %d found after %ld permutations\n",looper,attempt);
    	 
     	 looper++;//increments the solutions cntr
	 min = min(min,attempt);//calulates min and max using the macros
	 max = max(max,attempt);

	 #ifndef MACRO_GUARD //This is a macro guard that is used to test out the functions

		printf("For solution %d, we ran randperm %d times and checkboard %d times\n",looper-1,rand_perm_cntr,check_board_cntr);

	 #endif

	 //min = 9999999;
	 rand_perm_cntr = 0;//restes the cntrs
	 check_board_cntr = 0;

	 sum += attempt;//increments teh value of sum
 	}
	
	attempt = 0;//resets the permutation cntr
	
	printf("\n");
	
  	long avg = 0;//stores the average
  	
  	printf("size		min		max		mean		size**size		size!\n");
	
	double power = pow((double)i,(double)i);//calulates the power
	avg = sum/10; //calculates the average
  	printf("%d		%d		%d		%ld		%lf			%d\n",i,min,max,avg,power,fact(bsize));//calculates the required number for the stats on each board
	printf("\n");
	
  }
  return 1;
}
