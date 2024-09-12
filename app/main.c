#include <stdio.h>
#include <stdlib.h>
//#include <type.h>
#include <unistd.h>

int main(void)
{
  printf("hellod world\n");
  int c;

  while ((c=getopt(argc,argv, "abc:")) != -1)
    switch(c){

      case 'a':
        printf("get a here");
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
    }

  return 0;
}
