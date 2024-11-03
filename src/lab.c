#include <stdlib.h>
#include <sys/time.h> /* for gettimeofday system call */
#include "lab.h"

/**
 * @brief Standard insertion sort that is faster than merge sort for small array's
 *
 * @param A The array to sort
 * @param p The starting index
 * @param r The ending index
 */
static void insertion_sort(int A[], int p, int r)
{
  int j;

  for (j = p + 1; j <= r; j++)
    {
      int key = A[j];
      int i = j - 1;
      while ((i > p - 1) && (A[i] > key))
        {
	  A[i + 1] = A[i];
	  i--;
        }
      A[i + 1] = key;
    }
}


void mergesort_s(int A[], int p, int r)
{
  if (r - p + 1 <=  INSERTION_SORT_THRESHOLD)
    {
      insertion_sort(A, p, r);
    }
  else
    {
      int q = (p + r) / 2;
      mergesort_s(A, p, q);
      mergesort_s(A, q + 1, r);
      merge_s(A, p, q, r);
    }

}

void merge_s(int A[], int p, int q, int r)
{
  int *B = (int *)malloc(sizeof(int) * (r - p + 1));

  int i = p;
  int j = q + 1;
  int k = 0;
  int l;

  /* as long as both lists have unexamined elements */
  /*  this loop keeps executing. */
  while ((i <= q) && (j <= r))
    {
      if (A[i] < A[j])
        {
	  B[k] = A[i];
	  i++;
        }
      else
        {
	  B[k] = A[j];
	  j++;
        }
      k++;
    }

  /* now only at most one list has unprocessed elements. */
  if (i <= q)
    {
      /* copy remaining elements from the first list */
      for (l = i; l <= q; l++)
        {
	  B[k] = A[l];
	  k++;
        }
    }
  else
    {
      /* copy remaining elements from the second list */
      for (l = j; l <= r; l++)
        {
	  B[k] = A[l];
	  k++;
        }
    }

  /* copy merged output from array B back to array A */
  k = 0;
  for (l = p; l <= r; l++)
    {
      A[l] = B[k];
      k++;
    }

  free(B);
}

double getMilliSeconds()
{
  struct timeval now;
  gettimeofday(&now, (struct timezone *)0);
  return (double)now.tv_sec * 1000.0 + now.tv_usec / 1000.0;
}

/**
 * @brief The function that is called by each thread to sort their chunk
 *
 * @param args see struct parallel_args
 * @return void* always NULL
 */
void *parallel_mergesort(void *args){
  struct parallel_args *pargs = (struct parallel_args *)args;
  int *A = pargs->A;
  int start = pargs->start;
  int end = pargs->end;
  mergesort_s(A, start, end);
  //printf("the arguments passed into mergesort:%d %d\n",start,end);
  return NULL;
}

  /**
   * @brief Sorts an array of ints into ascending order using multiple
   * threads
   *
   * @param A A pointer to the start of the array
   * @param n The size of the array
   * @param num_threads The number of threads to use.
   */
    
  void mergesort_mt(int *A, int n, int num_thread){

    
    //int MasterArraylength = n;

    int subArraySize=n/num_thread; //the size of each sub array. 

    int r = n-1;//index of last element.
    //int p =0; //starting index of the array.
    //printf("%d",A[0]);

    //create dynamic number of threads
    pthread_t threads[num_thread];

    struct parallel_args *args_array[num_thread]; // Array to store pointers to struct parallel_args

    int curOffset=0; //starts at the begining of the array.
    for (int t = 0; t < num_thread; t++) {

      struct parallel_args *args = malloc(sizeof(struct parallel_args));
      args->A =A; /* Pointer to the integer array */;
      args->start =curOffset; /* Starting index of the subarray */;
      args->end =(curOffset+subArraySize-1); /* Ending index of the subarray */;
      
      args_array[t]=args;

      pthread_create(&threads[t],  NULL, parallel_mergesort, (void*)args);
      curOffset+=subArraySize;
      //on last iteration we go to the end of the array in the case therese odd number of intial elements
      if(t==(num_thread-1)){
        args->end =r;
        pthread_create(&threads[t],  NULL, parallel_mergesort, (void*)args);
     
      }}  
      //wait for all threads to finish and join them 
      for (int t = 0; t < num_thread; t++) {
        pthread_join(threads[t], NULL);
      }
      //perform final merge of the sub arrays....
      mergesort_s(A, 0, r);

      for (int t = 0; t < num_thread; t++) {
        free(args_array[t]);
      }
      

    //free(threads);



  }
