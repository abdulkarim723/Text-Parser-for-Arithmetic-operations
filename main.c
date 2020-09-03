/******************************************************************************
Author: A. Saddik
string calculator
The user adds an arithmetic expression which is calculated by the program
Parentheses and spaces are allowed
*******************************************************************************/

#include "calculator.h"

int main() {
  int ret;
  char ** my_input = (char ** ) malloc(sizeof(char));
  my_input[0] = (char * ) malloc(sizeof(char) * STRING_SIZE);
  if (!my_input[0] || !my_input) {
    printf("> memory allocation failed\n"
      "> exit the program\n");
    return -1;
  }
  while (1) {
    /*communicate with the user and read the input from the terminal*/
    print_func(my_input);

    /*if the user inserted 'q', the program should close*/
    if (!strncmp(my_input[0], "q", 1)) {
      printf("> quit the program\n");
      break;
    }
    /*parse the input and output the result*/
    ret = string_parse(my_input);
    if (ret) {
      continue;
    }
  }
  free(my_input);
  return EXIT_SUCCESS;
}
