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

/* maximum string size */
#define STRING_SIZE     1024

/*calculate the given input 'str'*/
int calculate(char* str, int len);
/*calculate the substring length for every single number in the main string*/
int calculate_numlen(char* str_num);
/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char* str , int str_len);
/*parse the string given from the user as an input*/
int string_parse(char ** str);
/*this function checks signs correctness of the string*/
int check_sign( char* str);
/*read the string as an input from the terminal*/
void print_func(char** terminal_input);
/*check if the input has invalid char*/
int check_str(char* str);

enum calc_status{addition, substraction};

#endif /* CALCULATOR_H_ */
