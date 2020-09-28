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

#include <stdbool.h>

#include <math.h>

/* maximum string size */
#define STRING_SIZE 1024
/*currently only one string is allocated*/
#define Num_Strings 1
/*number of supported math  expressions*/
#define reserved_strings 7

/*calculate the substring length for every single number in the main string*/
int calculate_numlen(char * str_num);
/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char * str, int len);
/*parse the string given from the user as an input*/
int string_parse(char * str);
/*this function checks signs correctness of the string*/
int check_sign(char * str);
/*read the string as an input from the terminal*/
void print_func(char ** terminal_input);

/*this function makes check if there are no sign between two numbers*/
int check_errors(char * str, int len);

int is_arith_sign(char * str);
/*do devision and multiplication operations*/
double calculate_dev_mul(char * str, int len);
/*calculate the given input 'str'*/
double calculate(char * str, int len);

int calculate_numlen_backward(char * str_num);

double str_reconst(char * str, char * start, char * end);

double calculate_parentthesis_content(char * str_o, int len, int parenthesis_num);

int check_reserved_words(char * str);
enum calc_status {
    addition,
    substraction
};

enum error_enum {
    parentheses_error = -10,
	invalid_input_character,
	no_arithmetic_sign,
	extra_arithmetic_sign,
	no_numbers_found,
	memory_allocation_failed,
	empty_parentheses_content,
	negative_num
};

#endif /* CALCULATOR_H_ */
