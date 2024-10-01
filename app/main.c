#include <stdio.h>
#include <stdlib.h>
//#include <type.h>
#include <unistd.h>
#include <lab.h>
#include "../src/lab.h"
//step 4 code
#include <readline/readline.h>
#include <readline/history.h>
void print_version() {
    printf("Shell version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
}
void retr_cwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current directory: %s\n", cwd);  // Print the current working directory
    } else {
        perror("getcwd");
    }
}

int main(int argc, char *argv[])
{
  //printf("hellod world\n");
 // char *my_prompt = getenv("MY_PROMPT"); //added to grab the user prompt Task5

  //if (my_prompt == NULL) {
  //      my_prompt = "Shell>";  // Default prompt
   // }
  char *my_prompt = get_prompt("MY_PROMPT");

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

    //catch case of invalid flags

  //
  char *line;
  using_history();

  while ((line=readline(my_prompt))){ // change so that reads getEnv to select the symbol or string
      
      //user command prompts go here
      //Task 6
      //Exit
      //cd -use env for current directory
      //history command

     if (strncmp(line, "exit", 4) == 0) {
            int exit_status = 0;  // Default exit status is 0 (normal exit)

            // Need case for non-normal exit nonzero

            free(line);  // Clean up before exiting
            printf("freeing prompt");
            free(my_prompt);
            return exit_status;
        }
      if (strncmp(line, "pwd", 3) == 0) {
            
            char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("%s\n", cwd);
                } else {
                    perror("getcwd() error");
                }
            
            
        }
      if (strncmp(line, "history", 7) == 0) {
           

            printf("history");
           
            
        }

      if (strncmp(line, "cd", 2) == 0) {

        char *dir = strtok(line, " ");
        dir = strtok(NULL, " ");  // Get the directory
           
        change_dir(dir);
     

          //      //struct passwd *pw = getpwuid(getuid());
          //          // dir = pw->pw_dir;
          //           //dir = pw->pw_dir;
          //     //printf("no argumetn passed%s,",dir);
              
          //   }
          //   //check for valid path? 
          //   if (chdir(dir) != 0) {
          //       //perror("cd");
          //       chdir(dir);
          //   } else { //the directory call is valid so now we execute

          //      char cwd[1024];
          //       if (getcwd(cwd, sizeof(cwd)) != NULL) {
          //           printf("Changed directory to: %s\n", cwd);
          //       } else {
          //           perror("getcwd() error");
          //       }

          //   }



          //   //if second argument found change to taht directory 


        }
     
      
      //printf("%s\n",line);
      add_history(line);
      //printf("%s\n",cwd);
      free(line);
      
  }
  printf("freeing prompt");
  return 0;
}
