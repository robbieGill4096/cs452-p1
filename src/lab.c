#include <stddef.h>
  /**
   * Initialize a new memory pool using the buddy algorithm. Internally,
   * this function uses mmap to get a block of memory to manage so should be
   * portable to any system that implements mmap. This function will round
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
  void buddy_init(struct buddy_pool *pool, size_t size){}

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
  void buddy_destroy(struct buddy_pool *pool){}

