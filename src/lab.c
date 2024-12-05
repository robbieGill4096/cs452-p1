#define _GNU_SOURCE
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include "../src/lab.h"
#include <bits/mman-linux.h>




/**
   * Find the buddy of a given pointer and kval relative to the base address we got from mmap
   * @param pool The memory pool to work on (needed for the base addresses)
   * @param buddy The memory block that we want to find the buddy for
   * @return A pointer to the buddy
   */
struct avail *buddy_calc(struct buddy_pool *pool, struct avail *buddy) {
    uintptr_t addr = (uintptr_t)buddy - (uintptr_t)pool->base;
    uintptr_t buddy_addr = addr ^ (UINT64_C(1) << buddy->kval);
    return (struct avail *)((uintptr_t)pool->base + buddy_addr);
}
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
    pool->kval_m = btok(size); //storing maximum size k value
    pool->numbytes = UINT64_C(1) << pool->kval_m;
    //now use mmap to allocate memory
    pool->base = mmap(NULL, pool->numbytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (pool->base == MAP_FAILED) {
        perror("buddy: couldnt not allocate memory pool!");
    }
    for(size_t i = 0; i < pool->kval_m; i++){
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
  void buddy_free(struct buddy_pool *pool, void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Calculate the block's address and size
    struct avail *block = (struct avail *)((uintptr_t)ptr - sizeof(struct avail));
    size_t kval = block->kval;

    // Mark the block as free
    block->tag = BLOCK_AVAIL;

    // Attempt to merge with buddy if possible
    while (kval < pool->kval_m) {
        struct avail *buddy = buddy_calc(pool, block);
        if (buddy->tag != BLOCK_AVAIL || buddy->kval != kval) {
            break;
        }

        // Remove buddy from the free list
        buddy->prev->next = buddy->next;
        buddy->next->prev = buddy->prev;

        // Merge the block and buddy
        if (block > buddy) {
            struct avail *temp = block;
            block = buddy;
            buddy = temp;
        }

        block->kval++;
        kval = block->kval;
    }

    // Add the merged block to the free list
    block->next = pool->avail[kval].next;
    block->prev = &pool->avail[kval];
    pool->avail[kval].next->prev = block;
    pool->avail[kval].next = block;

    // Clear lower-level free lists
    for (size_t i = 0; i < kval; i++) {
        pool->avail[i].next = &pool->avail[i];
        pool->avail[i].prev = &pool->avail[i];
    }
}

  /**
   * Changes the size of the memory block pointed to by ptr.
   * The function may move the memory block to a new location
   * (whose address is returned by the function).
   * The content of the memory block is preserved up to the
   * lesser of the new and old sizes, even if the block is
   * moved to a new location. If the new size is larger,
   * the value of the newly allocated portion is indeterminate.
   *
   * In case that ptr is a null pointer, the function behaves
   * like malloc, assigning a new block of size bytes and
   * returning a pointer to its beginning.
   *
   * if size is equal to zero, and ptr is not NULL, then the  call
   * is equivalent to free(ptr)
   *
   * @param pool The memory pool
   * @param ptr Pointer to a memory block
   * @param size The new size of the memory block
   * @return Pointer to the new memory block
   */
void *buddy_realloc(struct buddy_pool *pool, void *ptr, size_t size) {
    if (ptr == NULL) {
        return buddy_malloc(pool, size);
    }

    if (size == 0) {
        buddy_free(pool, ptr);
        return NULL;
    }

    struct avail *block = (struct avail *)((uintptr_t)ptr - sizeof(struct avail));
    size_t k = btok(size);
    if (k < MIN_K) {
        k = MIN_K;
    }

    if (block->kval == k) {
        return ptr;
    }

    void *new_ptr = buddy_malloc(pool, size);
    if (new_ptr == NULL) {
        return NULL;
    }

    size_t copy_size = (UINT64_C(1) << block->kval) - sizeof(struct avail);
    if (size < copy_size) {
        copy_size = size;
    }

    memcpy(new_ptr, ptr, copy_size);
    buddy_free(pool, ptr);
    return new_ptr;
}


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
void *buddy_malloc(struct buddy_pool *pool, size_t size) {
    if (size == 0 || pool == NULL) {
        return NULL;
    }

    size_t k = btok(size); 
    if (k < MIN_K) {
        k = MIN_K;
    }

    //printf("Requested size: %zu, calculated k: %zu\n", size, k);

    for (size_t i = k; i <= pool->kval_m; i++) {
        if (pool->avail[i].next != &pool->avail[i]) {
            struct avail *block = pool->avail[i].next;
            pool->avail[i].next = block->next;
            block->next->prev = &pool->avail[i];

            //printf("Allocating block at level %zu\n", i);

            while (i > k) { //continue to split until reached desired size
                i--;
                if (i < MIN_K) {
                    break;
                }
                //split the block
                struct avail *buddy = (struct avail *)((uintptr_t)block + (UINT64_C(1) << i));
                buddy->tag = BLOCK_AVAIL;
                buddy->kval = i;
                buddy->next = pool->avail[i].next;
                buddy->prev = &pool->avail[i];
                pool->avail[i].next->prev = buddy;
                pool->avail[i].next = buddy;

                //printf("Splitting block: new buddy at level %zu\n", i);
            }

            block->tag = BLOCK_RESERVED;
            block->kval = k;
            //printf("Allocated block: kval = %u, block address = %p\n", block->kval, (void *)block);
            //return (void *)block;
            return (void *)((uintptr_t)block + sizeof(struct avail));
            //modified to pass tests mem-1 was breaking code
           
        }
    }

    return NULL; // No available block found
}
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
      perror("buddy: destroy failed! returning -1");
    }
  }

