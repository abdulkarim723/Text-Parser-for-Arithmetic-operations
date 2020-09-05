/*
 * calculator.h
 *
 *  Created on: Aug 31, 2020
 *      Author: A. Saddik
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "error_handling.h"


/* maximum string size */
#define STRING_SIZE 1024

// uncomment to print more stuffs regarding string parsing of the input
//#define DEBUG_PRINT

/*calculate the given input 'str'*/
double calculate(char * str, int len);
/*calculate the substring length for every single number in the main string*/
int calculate_numlen(char * str_num);
/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char * str);
/*parse the string given from the user as an input*/
int string_parse(char ** str);
/*this function checks signs correctness of the string*/
int check_sign(char * str);
/*read the string as an input from the terminal*/
void print_func(char ** terminal_input);
/*check if the input has invalid char*/
int check_str(char * str);
/*this function makes check if there are no sign between two numbers*/
int check_digit_sign_sequence(char* str);

enum calc_status {
  addition,
  substraction,
  multiplication,
  division
};

#endif /* CALCULATOR_H_ */
