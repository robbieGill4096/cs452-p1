#include <stdio.h>
#include <stdlib.h>
//#include <type.h>
#include <unistd.h>
#include <lab.h>

void print_version() {
    printf("Shell version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
}

int main(int argc, char *argv[])
{
  //printf("hellod world\n");
  
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
        printf("default case");
        break;
    }

    //catch case of invalid flags

  return 0;
}
