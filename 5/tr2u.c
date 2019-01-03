#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_info(const char* err_msg);

int main(int argc, const char* argv[]) {
  if (argc != 3)
    err_info("Wrong number of arguments.\n"); 
 
  char * from = argv[1];
  char * to = argv[2];

  if (strlen(from) != strlen(to))
    err_info("Inputs are not the same length.\n");

  int i,j;
  int len = strlen(from); 
  for(i = 0; i < len; i++)
    for(j = i + 1; j < len; j++)
      if (from[i] == from[j])
        err_info("Input should not contain duplicates.\n");
  
  char buffer[1];
  int curr = read(STDIN_FILENO, buffer, 1);
  if(curr < 0)
    err_info("Error trying to read from stdin.\n");
  
  while(curr > 0){
    int i;
    for(i = 0; i < strlen(from); i++){
      if(from[i] == buffer[0]){
        buffer[0] = to[i];
        break;
      }
    }

    write(STDOUT_FILENO, buffer, 1);
    curr = read(STDIN_FILENO, buffer, 1);
    if(curr < 0)
      err_info("Error trying to read from stdin.\n");
  }

  return 0;
}

void err_info(const char* err_msg) {
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    exit(1);
}
