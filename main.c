/******************************************************************************
Author: A. Saddik
string calculator
The user adds an arithmetic expression which is calculated by the program
Parentheses and spaces are allowed
*******************************************************************************/

#include "calculator.h"

int main() {
  int count;
  bool close_program = false;
  char ** my_input = (char ** ) malloc(sizeof(char));
  /*check the success of memory allocation*/
  if (!my_input) {
    printf("> memory allocation failed\n"
           "> exit the program\n");
    return memory_allocation_failed;
  }

  /*allocate memory for several substrings 'Num_Strings'
   * currently there are only one substring */
  for(count=0; count<Num_Strings; count++){
  *(my_input + count) = (char *) malloc(sizeof(char) * STRING_SIZE);
  if(! *(my_input + count)){
	printf("> memory allocation failed\n"
		   "> exit the program\n");
    return memory_allocation_failed;
  }
  }


  while (1) {
    /* the purpose of using this for loop is for future development. The goal is to save several inputs from the user
	  and enable the user from calling his input history*/
	for(count=0; count<Num_Strings; count++){
    /*communicate with the user and read the input from the terminal*/
    print_func(my_input);

    /*if the user inserted 'q', the program should close*/
    if (!strncmp(*(my_input + count), "q", 1)) {
      printf("> quit the program\n");
      close_program = true;
      break;
    }
    /*parse the input and output the result*/
    string_parse(*(my_input + count));
	}
	/*check this flag to close the program in a good manner*/
	if(close_program){
	  break;
	}
  }

  free(my_input);
  /*free heap memory for all substrings*/
  for(count=0; count<Num_Strings; count++){
  free(*(my_input + count));
  }
  return EXIT_SUCCESS;
}
