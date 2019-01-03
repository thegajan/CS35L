/*
 * Gajan Nagaraj
 * 904937784
 * Lab 7 
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int frobcmp(char const * a, char const * b);
void err_info(const char* err_msg);
char xor(const char c);
void print_words(char ** word_p_arr, int word_p_arr_count);

int num_cmp = 0, upper = 0;

int main(int argc, char * argv[]) {
  //check if -f is an option
  if(argc > 2)
    err_info("Too many arguments.");
  const char * f = "-f";
  if(argc == 2 && strcmp(f, argv[1]) == 0)
    upper = 1;
  //First we must get the file stats
  struct stat file_stats;
  if(fstat(0,&file_stats) < 0)
    err_info("Cannot stat file.");
  //We must check to see if the file is a regular file and perform the appropriate actions per the spec
  int curr_size = 0;
  if(S_ISREG(file_stats.st_mode))
    curr_size = file_stats.st_size; 
  //We need to create an array to store all the words that we tak in from stdin
  //We take a pointer to a single word and an array of pointers to words
  char * word_p;
  char ** word_p_arr;
  //Store our current word
  char curr = ' ';
  //Iterators for array
  int word_count = 0, word_p_arr_count = 0; 
  //Allocate space for the arrays
  word_p = (char*)malloc(curr_size * sizeof(char));
  word_p_arr = (char**)malloc(0);
  //While we can, collect inputs from stdin
  while(read(0, &curr, sizeof(char)) > 0) {
    //If the file grows, we allocate more space
    if(curr_size <= word_count){
      curr_size++;
      word_p = realloc(word_p, curr_size * sizeof(char));
      if(word_p == NULL)
        err_info("Cannot reallocate memory for char.");
    }
    //Skip spaces
    if (curr == ' ' && word_count == 0)
      continue;
    if (word_count > 0 && curr == ' ' && word_p[word_count - 1] == ' ')
      continue;
    //store the char
    word_p[word_count] = curr;
    word_count++;
  }
  
  if(word_p[word_count - 1] != ' '){
    curr_size++;
    word_p = realloc(word_p, curr_size * sizeof(char));
     
    if (word_p == NULL)
      err_info("Memory Reallocation");
    
    word_p[word_count] = ' ';
    word_count++;
  }

  //Add all the words in word_p to word_p_arr so that we can sort and print them
  int i, word = 0;
  for(i = 0; i < word_count; i++){
    if(word_p[i] == ' '){
      word_p_arr = realloc(word_p_arr, (word_p_arr_count + 1) * sizeof(char*));
      if(word_p_arr == NULL)
        err_info("Cannot reallocate memory for char.");
      word_p_arr[word_p_arr_count] = word_p + word;
      word_p_arr_count++;
      word = i + 1;
    }
  }
  //sort, print, and free word array 
  qsort(word_p_arr, word_p_arr_count, sizeof(char*), frobcmp);
  print_words(word_p_arr, word_p_arr_count);
  free(word_p);
  free(word_p_arr);
  exit(0);
}

int frobcmp(char const * a, char const * b) {
  const char * a_char = *(const char **) a;
  const char * b_char = *(const char **) b;
  //loop through all the chars and check conditions specified in spec
  for (;;) {
    num_cmp++;
    //a == b
    if ((*a_char == ' ') && (*b_char == ' ')) 
      return 0;
    //a > b, b shorter
    else if (*b_char == ' ') 
      return 1;
    //a < b, a shorter
    else if (*a_char == ' ') 
      return -1;
    else{
      if(upper == 0){
      //a > b
        if (xor(*a_char) > xor(*b_char)) 
          return 1;
        //a < b
        else if (xor(*a_char) < xor(*b_char))  
          return -1;
      }
      else if (upper == 1){
        if (*a > 0 && *b > 0 && toupper(xor(*a_char)) > toupper(xor(*b_char))) 
          return 1;
        //a < b
        else if (*a > 0 && *b > 0 && toupper(xor(*a_char)) < toupper(xor(*b_char)))  
          return -1;
      }
    }
    a_char++;
    b_char++;
  }
  return 0;
}

//print the error that is happening
void err_info(const char* err_msg){
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    exit(1);
}

char xor(const char c) {
  return c ^ 42;
}

//output the sorted data to stdout 
void print_words(char ** word_p_arr, int word_p_arr_count) {
  int x,y;
  char space_char = ' ';
  for (x = 0; x < word_p_arr_count; x++) {
    for (y = 0; word_p_arr[x][y] != ' '; y++) {
      if(write(1, &word_p_arr[x][y], 1) < 1)
        err_info("Cannot write.");
    }
    if(write(1, &space_char, 1) < 1)
      err_info("Cannot write.");
  }
  fprintf(stderr, "Number of Comparisons: %i\n", num_cmp);
}
