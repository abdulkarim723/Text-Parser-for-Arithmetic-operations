/******************************************************************************
Author: A. Saddik
string calculator (Terminal Calculator
The user adds an arithmetic expression which is calculated by the program
*******************************************************************************/

#include "calculator.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main() {
    double result;
    bool close_program = false;
    char ** res_str = (char ** ) malloc(sizeof(char * ));
    * res_str = (char * ) malloc(sizeof(char) * 30);
    char ** my_input = (char ** ) malloc(sizeof(char * ));
    /*check the success of memory allocation*/
    if (!my_input || !res_str) {
        printf("memory allocation failed\n"
            "exit the program\n");
        return memory_allocation_failed;
    }

    * my_input = (char * ) malloc(sizeof(char) * STRING_SIZE);
    if (! * my_input) {
        printf("memory allocation failed\n"
            "exit the program\n");
        return memory_allocation_failed;
    }

    while (1) {
        print_func(my_input);
        close_program = quit_program(my_input[0]);
        if (close_program) {
            break;
        }
        /*parse the input and output the result*/
        string_parse(my_input[0], res_str[0], & result);
    }
    free(res_str);
    free(my_input);
    return EXIT_SUCCESS;
}
