/*
 * Gajan Nagaraj
 * 904937784
 * Lab 7 
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int frobcmp(char const * arr_a, char const* arr_b)
{
  const char * a = *(const char **) arr_a;
  const char * b = *(const char **) arr_b;
  while (1)
  {
    if ((*a == ' ') && (*b == ' ')) // Both at end of arrays, equal
    {
      return 0;
    }
    else if (*a == ' ') // End of array a, a < b
    {
      return -1;
    }
    else if (*b == ' ') // End of array b, a > b
    {
      return 1;
    }
    else
    {
      if ((*a ^ 42) < (*b ^ 42))  // Unfobricated a < b
      {
        return -1;
      }
      else if ((*a ^ 42) > (*b ^ 42)) // Unfobricated b < a
      {
        return 1;
      }
    }

    //else, continue checking
    a++;
    b++;
  }

  return 0;
}

void err_info(const char* err_msg) {
    fprintf(stderr, "%s Error: %d\n", err_msg, errno);
    exit(1);
}

int main(void) {
  //We need to create an array to store all the words that we tak in from stdin
  //We take a pointer to a single word and an array of pointers to words
  char * word_p;
  char ** word_p_arr;
  char curr;
  int word_count = 0, word_p_arr_count = 0; 
  //Allocate space for the arrays
  word_p = (char*)malloc(sizeof(char));
  word_p_arr = (char**)malloc(sizeof(char*));

  while((!ferror(stdin)) && (!feof(stdin))) {
    curr = getchar();
    if (ferror(stdin)) {
      err_info("IO Error");
    } 
    if (curr == EOF)
      break;
    else if (curr == ' ' && word_count == 0)
      continue;
   
    word_p = realloc(word_p, (word_count + 1) * sizeof(char));  
    word_p[word_count] = curr;
    word_count++;

    if (word_p == NULL)
      err_info("Memory Reallocation");
  
    if (word_count > 1 && curr == ' '){ 
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
    word_p = realloc(word_p, (word_count + 1) * sizeof(char));
    word_p[word_count] = ' ';
    word_count++;

    if (word_p == NULL) 
      err_info("Memory Reallocation");

    word_p_arr = realloc(word_p_arr, (word_p_arr_count + 1) * sizeof(char*));
    word_p_arr[word_p_arr_count] = word_p;
    word_p_arr_count++;

    if (word_p_arr == NULL)
      err_info("Memory Reallocation");
    
    word_p = (char*)malloc(0); 
    word_count = 0;
  }
  
  qsort(word_p_arr, word_p_arr_count, sizeof(char*), frobcmp);
  
  int i,j;
  for (i = 0; i < word_p_arr_count; i++) {
    for (j = 0; word_p_arr[i][j] != ' '; j++) {
      putchar(word_p_arr[i][j]);
    }
    putchar(' ');
  }
  free(word_p_arr);
  exit(0);
}

