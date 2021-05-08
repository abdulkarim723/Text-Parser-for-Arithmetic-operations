/******************************************************************************
Author: A. Saddik
string calculator (Terminal Calculator
The user adds an arithmetic expression which is calculated by the program

The core of this program is based on the function string_parse(). This function parses text input and outputs the result to the terminal.
One can pass to this function a pointer of the type (char *) or (double *) and these pointers will hold the result value.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "terminal.h"


void demo_example();

int main() {
	demo_example();
	// uncomment to use the terminal case
	// text_parser_with_terminal();
}


// use example of the text parser and printing out the result
void demo_example(){
	char str[50];
	double var;
	// you can change the input your self and test the result
	const char* input = "10 + 10 * ( 3 + 2)";
	const char* input1 = "abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) * "
			"abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) - ( 9 - 60 ) + cos(0) + sin(90)";
	// This function enables the user from getting the result in two formats, string of chars or double
	// if one need the result only in one format, can one simply pass NULL for the non used format
	string_parse(input, str, &var);
	printf(" %s = %s (string format)\n", input,  str);
	printf(" %s = %.2f (double format)\n", input, var);
	string_parse(input1, str, &var);
	printf(" %s = %s (string format)\n", input,  str);
	printf(" %s = %.15f (double format)\n", input, var);
}

