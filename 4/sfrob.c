/*
 * Gajan Nagaraj
 * 904937784
 * Lab 7 
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int frobcmp(char const * a, char const * b);
void err_info(const char* err_msg);
char xor(const char c);
void print_words(char ** word_p_arr, int word_p_arr_count);

int main(void) {
  //We need to create an array to store all the words that we tak in from stdin
  //We take a pointer to a single word and an array of pointers to words
  char * word_p;
  char ** word_p_arr;
  //Store our current word
  char curr;
  //Iterators for array
  int word_count = 0, word_p_arr_count = 0; 
  //Allocate space for the arrays
  word_p = (char*)malloc(sizeof(char));
  word_p_arr = (char**)malloc(sizeof(char*));
  //While we can, collect inputs from stdin
  while((!ferror(stdin)) && (!feof(stdin))) {
    curr = getchar();
    if (ferror(stdin)) {
      err_info("IO Error");
    } 
    if (curr == EOF)
      break;
    else if (curr == ' ' && word_count == 0)
      continue;
    //Reallocate the word array to make more space 
    word_p = realloc(word_p, (word_count + 1) * sizeof(char));  
    word_p[word_count] = curr;
    word_count++;

    if (word_p == NULL)
      err_info("Memory Reallocation");
  
    if (word_count > 1 && curr == ' '){ 
      //Reallocate the word array to make more space 
      word_p_arr = realloc(word_p_arr, (word_p_arr_count + 1) * sizeof(char*));    
      word_p_arr[word_p_arr_count] = word_p;
      word_p_arr_count++;

      if (word_p_arr == NULL)
        err_info("Memory Reallocation");

      word_p = (char*)malloc(0); 
      word_count = 0;
    }
  }

  if (word_count !=0) {
    //Reallocate the word array to make more space 
    word_p = realloc(word_p, (word_count + 1) * sizeof(char));
    word_p[word_count] = ' ';
    word_count++;

    if (word_p == NULL) 
      err_info("Memory Reallocation");

    //Reallocate the word array to make more space 
    word_p_arr = realloc(word_p_arr, (word_p_arr_count + 1) * sizeof(char*));
    word_p_arr[word_p_arr_count] = word_p;
    word_p_arr_count++;

    if (word_p_arr == NULL)
      err_info("Memory Reallocation");
    
    word_p = (char*)malloc(0); 
    word_count = 0;
  }
  //sort, print, and free word array 
  qsort(word_p_arr, word_p_arr_count, sizeof(char*), frobcmp);
  print_words(word_p_arr, word_p_arr_count);
  free(word_p_arr);
  exit(0);
}

int frobcmp(char const * a, char const * b) {
  const char * a_char = *(const char **) a;
  const char * b_char = *(const char **) b;
  //loop through all the chars and check conditions specified in spec
  for (;;) {
    //a == b
    if ((*a_char == ' ') && (*b_char == ' ')) 
      return 0;
    //a > b, b shorter
    else if (*b_char == ' ') 
      return 1;
    //a < b, a shorter
    else if (*a_char == ' ') 
      return -1;
    else
      //a > b
      if (xor(*a_char) > xor(*b_char)) 
        return 1;
      //a < b
      else if (xor(*a_char) < xor(*b_char))  
        return -1;
    a_char++;
    b_char++;
  }
  return 0;
}

//print the error that is happening
void err_info(const char* err_msg) {
    fprintf(stderr, "%s Error: %d\n", err_msg, errno);
    exit(1);
}

char xor(const char c) {
  return c ^ 42;
}

//output the sorted data to stdout and free all dynamically allocated space
void print_words(char ** word_p_arr, int word_p_arr_count) {
  int x,y;
  for (x = 0; x < word_p_arr_count; x++) {
    for (y = 0; word_p_arr[x][y] != ' '; y++) {
      putchar(word_p_arr[x][y]);
    }
    putchar(' ');
  }
}
