/******************************************************************************
Author: A. Saddik
string calculator (Terminal Calculator
The user adds an arithmetic expression which is calculated by the program

The core of this program is based on the function string_parse(). This function parses text input and outputs the result to the terminal.
One can pass to this function a pointer of the type (char *) or (double *) and these pointers will hold the result value.
*******************************************************************************/

#include "calculator.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void text_parser_with_terminal();
void demo_example();
int printandread(char * terminal_input);

int main() {
	demo_example();
	//text_parser_with_terminal();
}


/*read the string as an input from the terminal*/
int printandread(char * terminal_input) {
    strcpy(terminal_input, "");
    printf("> ");
    fgets(terminal_input, STRING_SIZE, stdin);
    return quit_program(terminal_input);
}

// this example uses the text parser which is based on the function string_parse() for infinity
void text_parser_with_terminal(){
	char my_input[STRING_SIZE];
	while (1) {
		if(!printandread(my_input)){
			break;
		}
		/*parse the input and output the result*/
		string_parse(my_input, NULL, NULL);
	}
}

//
void demo_example(){
	// this should pint 60 to stdout
	string_parse("10 + 10 * ( 3 + 2)", NULL, NULL);
}

