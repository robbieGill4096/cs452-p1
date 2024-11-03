#include "harness/unity.h"
#include "../src/lab.h"
#include <stdlib.h>


static int defaultRange = 10;
static int defaultSize = 103;
static int defaultSeed = 1;
static int *expected = NULL;
static int *actual = NULL;

void setUp(void) {
  actual = malloc(sizeof(int) *defaultSize);
  expected = malloc(sizeof(int) *defaultSize);
  srandom(defaultSeed);
  for (int i = 0; i < defaultSize; i++){
    int value = random() % defaultRange;
    actual[i]= value;
    expected[i] =value;
  }
}

void tearDown(void) {
  free(actual);
  free(expected);
}

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 }

void test_mergesort_mt_small_one_thread(void)
{
  //Run our sort and the C library qsort to compare to
  mergesort_mt(actual, defaultSize, 1);
  qsort(expected, defaultSize, sizeof(int), compare_ints);
  TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, defaultSize);
}

void test_mergesort_mt_small_two_threads(void)
{
  mergesort_mt(actual, defaultSize, 2);
  qsort(expected, defaultSize, sizeof(int), compare_ints);
  TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, defaultSize);
}

void test_mergesort_mt_small_three_threads(void)
{
  mergesort_mt(actual, defaultSize, 3);
  qsort(expected, defaultSize, sizeof(int), compare_ints);
  TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, defaultSize);
}


int main(void) {


  int MasterArray[] = {1,7,4,3,9,1,2};
  int num_threads = 3;
  //mergesort_s(myNumbers,0,6);
  //printf("\n\n",myNumbers);
  int MasterArraylength = sizeof(MasterArray) / sizeof(MasterArray[0]);

  int r = MasterArraylength-1;//index of last element
  int p =0;

  //printf("The length of the array:%d",MasterArraylength);

  int subArraySize= MasterArraylength/num_threads;

  int curOffset=p;
  //printf("the size of the sub array is: %d, ",subArraySize);
  for(int i=0;i<(num_threads-1);i++)
{
        //printf("%d, ",myNumbers[i]);
   for(int j=0; j<(subArraySize); j++){

        printf("%d, ",MasterArray[(j+curOffset)]);
   }
  curOffset+=subArraySize;
   printf("\n");
}
//for last thread of the loop we go from the current offset to the end of the list 
for(int k=curOffset;k<=r;k++){
  printf("%d, ",MasterArray[(k)]);

}

//printf("%d, ",MasterArray[(curOffset)]);
//printf("%d, ",MasterArray[(1+curOffset)]);
//printf("%d, ",MasterArray[(2+curOffset)]);






  for(int i=0;i<MasterArraylength;i++)
{
        //printf("%d, ",MasterArray[i]);
}
printf("\n");
mergesort_mt(MasterArray,MasterArraylength,3);
printf("\n");
//printf("11/5=%d\n"(11/5));

  UNITY_BEGIN();
  RUN_TEST(test_mergesort_mt_small_one_thread);
  RUN_TEST(test_mergesort_mt_small_two_threads);
  RUN_TEST(test_mergesort_mt_small_three_threads);
  return UNITY_END();


}