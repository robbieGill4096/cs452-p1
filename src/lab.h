#ifndef LAB_H
#define LAB_H
#include <stdlib.h>
#include <stdbool.h>


/**My added imports **/
#include <sys/types.h> // Include for pid_t
#include <termios.h>
#define lab_VERSION_MAJOR 1
#define lab_VERSION_MINOR 0



#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief opaque type definition for a queue
     */
    typedef struct queue *queue_t;

    /**
     * @brief Initialize a new queue
     *
     * @param capacity the maximum capacity of the queue
     * @return A fully initialized queue
     */
    queue_t queue_init(int capacity);

    /**
     * @brief Frees all memory and related data signals all waiting threads.
     *
     * @param q a queue to free
     */
    void queue_destroy(queue_t q);

    /**
     * @brief Adds an element to the back of the queue
     *
     * @param q the queue
     * @param data the data to add
     */
    void enqueue(queue_t q, void *data);

    /**
     * @brief Removes the first element in the queue.
     *
     * @param q the queue
     */
    void *dequeue(queue_t q);

    /**
     * @brief Set the shutdown flag in the queue so all threads can
     * complete and exit properly
     *
     * @param q The queue
     */
   void queue_shutdown(queue_t q);

    /**
     * @brief Returns true is the queue is empty
     *
     * @param q the queue
     */
    bool is_empty(queue_t q);

    /**
     * @brief
     *
     * @param q The queue
     */
    bool is_shutdown(queue_t q);


/**
     * @brief Definition of the shell structure
     */
struct shell {
    int shell_is_interactive;
    pid_t shell_pgid;
    int shell_terminal;
    struct termios shell_tmodes;
    char *prompt;
};

void print_version();


#ifdef __cplusplus
} // extern "C"
#endif

#endif