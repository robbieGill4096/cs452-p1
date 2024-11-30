#define _GNU_SOURCE
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include "../src/lab.h"
#include <bits/mman-linux.h>

//avail;
//buddy_pool pool;
/**
   * Converts bytes to its equivalent K value defined as bytes <= 2^K
   * @param bytes The bytes needed
   * @return K The number of bytes expressed as 2^K
   * will fail on bytes=1
   */
  size_t btok(size_t bytes){

   size_t k = 0;
    
    bytes--;//keeps from overstepping on even count
    while (bytes > 0) {
        //printf("there are 2^%d\n",(int)bytes);
        bytes >>= 1;
        k++;
    }
    return k; //log_2(bytes)=k
  }



  /**
   * Initialize a new memory pool using the buddy algorithm. Internally,
   * this function uses mmap to gemplements t a block of memory to manage so should be
   * portable to any system that immap. This function will round
   * up to the nearest power of two. So if the user requests 503MiB
   * it will be rounded up to 512MiB.
   *
   * Note that if a 0 is passed as an argument then it initializes
   * the memory pool to be of the default size of DEFAULT_K. If the caller
   * specifies an unreasonably small size, then the buddy system may
   * not be able to satisfy any requests.
   *
   * NOTE: Memory pools returned by this function can not be intermingled.
   * Calling buddy_malloc with pool A and then calling buddy_free with
   * pool B will result in undefined behavior.
   *
   * @param size The size of the pool in bytes.
   * @param pool A pointer to the pool to initialize
   */
  void buddy_init(struct buddy_pool *pool, size_t size){

    //check if 0 byte argument is passed and set to default size
    //if the size is less than the minimum size, set to minimum size

    //allocate block of memory to nearest base 2 
    //int closestSize = pow(2, ceil(log2(size)));
    //printf("the size is %d",size);
    //printf("the closest size is :%d",closestSize);
    //
    //you can take your buddy system and hijack normal malloc
    if (size ==0){size=UINT64_C(1) << DEFAULT_K;}
    pool->kval_m = btok(size); //storing mazinum size k value
    pool->numbytes = UINT64_C(1) << pool->kval_m;
    //now use mmap to allocate memory
    pool->base = mmap(NULL, pool->numbytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (pool->base == MAP_FAILED) {
        perror("buddy: couldnt not allocate memory pool!");
    }
    for(int i = 0; i <pool->kval_m; i++){
      //empty circular list
      //array of ciricular lists
      pool->avail[i].next = &pool->avail[i];
      pool->avail[i].prev = &pool->avail[i];
      pool->avail[i].kval = i;
      pool->avail[i].tag = BLOCK_UNUSED; 

    }
    //now itialize the last one that has the real block in it
    

    pool->avail[pool->kval_m].next = pool->base;
    pool->avail[pool->kval_m].prev = pool->base;
    //pool->avail[pool->]
    struct avail *ptr = (struct avail *) pool->base; //lots of strategic casting
    ptr->tag = BLOCK_AVAIL;
    ptr->kval = pool->kval_m;
    ptr->next = &pool->avail[pool->kval_m];
    ptr->prev = &pool->avail[pool->kval_m];


  }

   /**
   * A block of memory previously allocated by a call to malloc,
   * calloc or realloc is deallocated, making it available again
   * for further allocations.
   *
   * If ptr does not point to a block of memory allocated with
   * the above functions, it causes undefined behavior.
   *
   * If ptr is a null pointer, the function does nothing.
   * Notice that this function does not change the value of ptr itself,
   * hence it still points to the same (now invalid) location.
   *
   * @param pool The memory pool
   * @param ptr Pointer to the memory block to free
   */
  void buddy_free(struct buddy_pool *pool, void *ptr){}

    /**
   * Allocates a block of size bytes of memory, returning a pointer to
   * the beginning of the block. The content of the newly allocated block
   * of memory is not initialized, remaining with indeterminate values.
   *
   * If size is zero, the return value will be NULL
   * If pool is NULL, the return value will be NULL
   *
   * @param pool The memory pool to alloc from
   * @param size The size of the user requested memory block in bytes
   * @return A pointer to the memory block
   */
  void *buddy_malloc(struct buddy_pool *pool, size_t size){}

 /**
   * Inverse of buddy_init.
   *
   * Notice that this function does not change the value of pool itself,
   * hence it still points to the same (now invalid) location.
   *
   * @param pool The memory pool to destroy
   */
  void buddy_destroy(struct buddy_pool *pool){

    int status = munmap(pool->base, pool->numbytes);
    if(status == -1){
      perror("buddy: destroy failed!");
    }
  }

