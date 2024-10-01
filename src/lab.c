/**Update this file with the starter code**/
#include <string.h>
#include "../src/lab.h"
#include <errno.h>

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
    //     char *prompt = getenv(env);
    //      if (prompt == NULL) {
    //     prompt = "shell>";  // Default prompt
    //     return prompt;
    // }
        
    // return prompt;
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
    //dir = strtok(NULL, " "); 
   //printf(dir);
    //case to get home no args
          if (!dir){ 
            //get env then cd home
            const char *home = getenv("HOME");

            //check if getting home path failed
            if (home == NULL) {
            struct passwd *pw = getpwuid(getuid());
            //home = pw->pw_dir;
           
            }


            chdir(home); // Attempt to change to home directory
            return 0;
            //if that fails now call getpwuid

          }
          //case where args
          else { 

            //printf("args case");
           //try to run args if it fails return error
           if (chdir(dir) != 0 ) {
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
  bool do_builtin(struct shell *sh, char **argv){
    return true;

  }

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
  void sh_init(struct shell *sh);

  /**
   * @brief Destroy shell. Free any allocated memory and resources and exit
   * normally.
   *
   * @param sh
   */
  void sh_destroy(struct shell *sh){


  }

  /**
   * @brief Parse command line args from the user when the shell was launched
   *
   * @param argc Number of args
   * @param argv The arg array
   */
  void parse_args(int argc, char **argv){
    //parse the arguments

  }


