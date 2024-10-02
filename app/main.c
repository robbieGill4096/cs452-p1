#include <stdio.h>
#include <stdlib.h>
//#include <type.h>
#include <unistd.h>
#include <lab.h>
#include "../src/lab.h"
//step 4 code
#include <readline/readline.h>
#include <readline/history.h>
//void print_version() {
  //  printf("Shell version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
//}

int main(int argc, char *argv[])
{
  struct shell shell;
  sh_init(&shell);
  sh_destroy(&shell);


  char *my_prompt = get_prompt("MY_PROMPT");
  //int opt;
  //parse the command line args like print version
  parse_args(argc,argv);

  char *line;
  using_history();

  while ((line=readline(my_prompt))){ // change so that reads getEnv to select the symbol or string
      add_history(line);
      //user command prompts go here
      //Task 6
      //Exit
      //cd -use env for current directory
      //history command

     
     if (strncmp(line, "exit", 4) == 0) {
            int exit_status = 0;  // Default exit status is 0 (normal exit)

            // Need case for non-normal exit nonzero

            free(line);  // Clean up before exiting
            //printf("freeing prompt");
            free(my_prompt);
            return exit_status;
        }
      if (strncmp(line, "pwd", 3) == 0) {
            
            char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("%s\n", cwd);
                    //printf("TEst pwd value: %s",getcwd(NULL,0));
                } else {
                    perror("getcwd() error");
                }
            
            
        }
      if (strncmp(line, "history", 7) == 0) {
             register HIST_ENTRY **the_list;
          register int i;

          the_list = history_list ();
          if (the_list)
            for (i = 0; the_list[i]; i++)
              printf ("%d: %s\n", i + history_base, the_list[i]->line);
        }

      if (strncmp(line, "cd", 2) == 0) {

        //char *dir = strtok(line, " "); functioning code
        //dir = strtok(NULL, " ");  // Get the directory functioning code
        //change_dir(dir); functioning code
         
         char **cmd = cmd_parse(line);
         
        //printf("Path: %s\n", cmd[0]);
        //printf("Path: %s\n", cmd[1]);
        change_dir(cmd);

        }
      if (strncmp(line, "jobs", 4) == 0) {

        printf("JObs command run");

        }
     
      
      //printf("%s\n",line);
      //add_history(line);
      //printf("%s\n",cwd);
      free(line);
      
      
  }
  printf("freeing prompt");
  return 0;
}
