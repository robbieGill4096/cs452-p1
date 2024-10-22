/**Update this file with the starter code**/
#include <string.h>
#include "../src/lab.h"
#include <errno.h>
#include <ctype.h>
#include <pwd.h>
#include <stdio.h>
//added imports
#include <unistd.h>
#include "../src/lab.h"
#include <pthread.h>

#include <readline/readline.h>
#include <readline/history.h>

char *line = NULL;
int history_base = 1;
// char **cmd_parse(char const *line){
    
// }

// void cmd_free(char **line){
//     for(int i = 0; i < 10; i++){
//         if(line[i] != NULL){
//             free(line[i]);
//         }
//     }
//     free(line);
// }

// char *trim_white(char *line){
    
//     return line;
// }
   /**
   * @brief Set the shell prompt. This function will attempt to load a prompt
   * from the requested environment variable, if the environment variable is
   * not set a default prompt of "shell>" is returned.  This function calls
   * malloc internally and the caller must free the resulting string.
   *
   * @param env The environment variable
   * @return const char* The prompt
   */
 char *get_prompt(const char *env){
    
    char *prompt = getenv(env);
    //check if no custom shell design is given
    if(prompt == NULL){
        //default shell design
        //dynamically allocate memory because of the test file
        prompt = strdup("shell>");
        //should i check for an allocation failure?
    }
    else {

        prompt = strdup(prompt);
        return prompt;
    }

    return prompt;
 }

/**
   * Changes the current working directory of the shell. Uses the linux system
   * call chdir. With no arguments the users home directory is used as the
   * directory to change to.
   *
   * @param dir The directory to change to
   * @return  On success, zero is returned.  On error, -1 is returned, and
   * errno is set to indicate the error.
   */
 
int change_dir(char **dir) {
    char *path = NULL;
    if (dir[1] != NULL) {
        path = dir[1]; 
    }
   

    const char *home = NULL;
          if (!path){ 
            //get env then cd home
            home = getenv("HOME");

            //check if getting home path failed
            if (home == NULL) {
                struct passwd *pw = getpwuid(getuid());
                home = pw->pw_dir;
                chdir(home);
            }


            chdir(home); // Attempt to change to home directory
            return 0;
            //if that fails now call getpwuid

          }
          //case where args
          else { 

            //printf("args case");
           //try to run args if it fails return error

           //need to fix dir so it only passes *dir 

           if (chdir(path) != 0 ) {
              errno = ENOENT;
              return -1;}

           else{
              //succsffully change to a dir
              //chdir(*dir);
              return 0; 
              }
           }
           
}


  /**
   * @brief Convert line read from the user into to format that will work with
   * execvp. We limit the number of arguments to ARG_MAX loaded from sysconf.
   * This function allocates memory that must be reclaimed with the cmd_free
   * function.
   *
   * @param line The line to process
   *
   * @return The line read in a format suitable for exec
   */
  char **cmd_parse(char const *line){
    long ARG_MAX = sysconf(_SC_ARG_MAX);

    // Allocate memory for the argument list
    char **cmd = malloc(ARG_MAX * sizeof(char *));
    if (cmd == NULL) {
        
        return NULL;
    }

    // Make a writable copy of the line
    char *line_copy = strdup(line);
    if (line_copy == NULL) {
        free(cmd);
        return NULL;
    }

    // Use the writable copy for tokenization
    char *token = strtok(line_copy, " ");
    int i = 0;
    while (token != NULL) {
        cmd[i] = strdup(token);  // Duplicate each token
        token = strtok(NULL, " ");
        i++;
    }
    cmd[i] = NULL;  // Null-terminate the argument array
    
    free(line_copy);  // Free the copy of the input line after tokenization
    return cmd;
}


  /**
   * @brief Free the line that was constructed with parse_cmd
   *
   * @param line the line to free
   */

  void cmd_free(char **line) {
    if (line == NULL) {
        return;  // No action needed if the line is already NULL
    }

    // Free each string in the array
    for (int i = 0; line[i] != NULL; i++) {
        free(line[i]);  // Free each duplicated token
    }

    // Free the array itself
    free(line);
}

/**
   * @brief Trim the whitespace from the start and end of a string.
   * For example "   ls -a   " becomes "ls -a". This function modifies
   * the argument line so that all printable chars are moved to the
   * front of the string
   *
   * @param line The line to trim
   * @return The new line with no whitespace
   */
  char *trim_white(char *line){

    // Trim leading whitespace
    while (*line != '\0' && isspace(*line)) {
        line++;
    }

    // Trim trailing whitespace
    char *end = line + strlen(line) - 1;
    while (end > line && isspace(*end)) {
        end--;
    }
    end[1] = '\0';  // Null-terminate the string

    return line;
  }


  /**
   * @brief Takes an argument list and checks if the first argument is a
   * built in command such as exit, cd, jobs, etc. If the command is a
   * built in command this function will handle the command and then return
   * true. If the first argument is NOT a built in command this function will
   * return false.
   *
   * @param sh The shell
   * @param argv The command to check
   * @return True if the command was a built in command
   */
//   bool do_builtin(struct shell *sh, char **argv){
//     if (argv[0] == NULL) {
//         return false;  // No command to process
//     }

//     if (strcmp(argv[0], "exit") == 0) {
//         free(line);
//         exit(0);  // Exit the shell
//     }

//     if (strncmp(line, "pwd", 3) == 0) {
//         char cwd[1024];
//         if (getcwd(cwd, sizeof(cwd)) != NULL) {
//             printf("%s\n", cwd);
//         } else {
//             perror("getcwd() error");
//         }
//     }

//     if (strncmp(line, "history", 7) == 0) {
//         register HIST_ENTRY **the_list;
//         register int i;

//         the_list = history_list();
//         if (the_list) {
//             for (i = 0; the_list[i]; i++) {
//                 printf("%d: %s\n", i + history_base, the_list[i]->line);
//             }
//         }
//     }

//     if (strncmp(line, "cd", 2) == 0){

//         //char *dir = strtok(line, " "); functioning code
//         //dir = strtok(NULL, " ");  // Get the directory functioning code
//         //change_dir(dir); functioning code
         
//          char **cmd = cmd_parse(line);
         
//         //printf("Path: %s\n", cmd[0]);
//         //printf("Path: %s\n", cmd[1]);
//         change_dir(cmd);

//         }

//     return true;
// }

  /**
   * @brief Initialize the shell for use. Allocate all data structures
   * Grab control of the terminal and put the shell in its own
   * process group. NOTE: This function will block until the shell is
   * in its own program group. Attaching a debugger will always cause
   * this function to fail because the debugger maintains control of
   * the subprocess it is debugging.
   *
   * @param sh
   */
  void sh_init(struct shell *sh){// Check if the shell is interactive
    sh->shell_is_interactive = isatty(STDIN_FILENO);

    // Set the process group ID
    sh->shell_pgid = getpid();

    // Set the terminal file descriptor
    sh->shell_terminal = STDIN_FILENO;

    // Initialize terminal modes
    if (tcgetattr(sh->shell_terminal, &sh->shell_tmodes) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Set the shell prompt
    sh->prompt = strdup("my_shell> ");
    if (sh->prompt == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    // Put the shell in its own process group
    if (setpgid(sh->shell_pgid, sh->shell_pgid) < 0) {
        perror("setpgid");
        exit(EXIT_FAILURE);
    }

    // Grab control of the terminal
    tcsetpgrp(sh->shell_terminal, sh->shell_pgid);
}

  // /**
  //  * @brief Destroy shell. Free any allocated memory and resources and exit
  //  * normally.
  //  *
  //  * @param sh
  //  */
   void sh_destroy(struct shell *sh){
    // Free the allocated prompt
    if (sh->prompt != NULL) {
        free(sh->prompt);
        sh->prompt = NULL;  // Set to NULL to avoid dangling pointer
        //printf("shell destroyed");
    }
}

  /**
   * @brief Parse command line args from the user when the shell was launched
   *
   * @param argc Number of args
   * @param argv The arg array
   */
  void parse_args(int argc, char **argv){
    //parse the arguments
    int opt;
    while ((opt=getopt(argc,argv, "vbc:")) != -1)
    switch(opt){

      case 'v':
        print_version(); 
        break;
      case 'b':
        printf("get b here");
        break;
      case 'c':
        printf("get c here");
        break;
      case 'd':
        printf("get d here");
        break;
      case '?':
        printf("? here");
        break;
      default:
        //printf("default case");
        break;
    }

  }

void print_version() {
    printf("Shell version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
    
}

struct queue {
    void **data;
    int capacity;
    int front;
    int rear;
    int size;
    bool shutdown;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
};

queue_t queue_init(int capacity) {
    queue_t q = (queue_t)malloc(sizeof(struct queue));
    if (!q) return NULL;

    q->data = (void **)malloc(capacity * sizeof(void *));
    if (!q->data) {
        free(q);
        return NULL;
    }

    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->shutdown = false;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);

    return q;
}

/**
 * @brief Frees all memory and related data signals all waiting threads.
 *
 * @param q a queue to free
 */
void queue_destroy(queue_t q){
    if (q == NULL) return;

    free(q->data);
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
    free(q);


}

/**
 * @brief Adds an element to the back of the queue
 *
 * @param q the queue
 * @param data the data to add
 */
void enqueue(queue_t q, void *data){
    pthread_mutex_lock(&q->lock);

    // Wait until there is space in the queue or the queue is shutdown
    while (q->size == q->capacity && !q->shutdown) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }

    // If the queue is shutdown, do not add the data
    if (q->shutdown) {
        pthread_mutex_unlock(&q->lock);
        return;
    }

    // Add the data to the rear of the queue
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = data;
    q->size++;

    // Signal that the queue is not empty
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}

/**
 * @brief Removes the first element in the queue.
 *
 * @param q the queue
 */
void *dequeue(queue_t q) {
    pthread_mutex_lock(&q->lock);

    // Wait until there is an element in the queue or the queue is shutdown
    while (q->size == 0 && !q->shutdown) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }

    // If the queue is shutdown and empty, return NULL
    if (q->shutdown && q->size == 0) {
        pthread_mutex_unlock(&q->lock);
        return NULL;
    }

    // Remove the data from the front of the queue
    void *data = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    // Signal that the queue is not full
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);

    return data;
}

/**
 * @brief Set the shutdown flag in the queue so all threads can
 * complete and exit properly
 *
 * @param q The queue
 */
void queue_shutdown(queue_t q) {
    pthread_mutex_lock(&q->lock);
    q->shutdown = true;
    pthread_cond_broadcast(&q->not_empty);
    pthread_cond_broadcast(&q->not_full);
    pthread_mutex_unlock(&q->lock);
}
/**
 * @brief Returns true is the queue is empty
 *
 * @param q the queue
 */
bool is_empty(queue_t q) {
    pthread_mutex_lock(&q->lock);
    bool empty = (q->size == 0);
    pthread_mutex_unlock(&q->lock);
    return empty;
}

/**
 * @brief
 *
 * @param q The queue
 */
bool is_shutdown(queue_t q) {
    pthread_mutex_lock(&q->lock);
    bool shutdown = q->shutdown;
    pthread_mutex_unlock(&q->lock);
    return shutdown;
}

