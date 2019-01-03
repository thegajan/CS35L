#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_info(const char* err_msg);

int main(int argc, const char* argv[]) {
  if (argc != 3) 
    err_info("Wrong number of arguments"); 
 
  char * from = argv[1];
  char * to = argv[2];

  if (strlen(from) != strlen(to))
    err_info("Inputs are not the same length.");

  int i,j;
  int len = strlen(from); 
  for(i = 0; i < len; i++)
    for(j = i + 1; j < len; j++)
      if (from[i] == from[j])
        err_info("Input should not contain duplicates.");

  char curr = getchar();
  if(ferror(stdin)){
    err_info("Error trying to read from stdin");
  }
  
  while(!feof(stdin)){
    int i;
    for(i = 0; i < strlen(from); i++){
      if(from[i] == curr){
        curr = to[i];
        break;
      }
    }

    putchar(curr);
    
    curr = getchar();
    if(ferror(stdin))
      err_info("Error trying to read from stdin");
  }

  return 0;
}

void err_info(const char* err_msg) {
    fprintf(stderr, err_msg);
    exit(1);
}
