/******************************************************************************
Author: A. Saddik
string calculator (Terminal Calculator
The user adds an arithmetic expression which is calculated by the program
*******************************************************************************/

#include "calculator.h"

int main() {
    int count;
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

    /*allocate memory for several substrings 'Num_Strings'
     * currently there are only one substring */
    for (count = 0; count < Num_Strings; count++) {
        *(my_input + count) = (char * ) malloc(sizeof(char) * STRING_SIZE);
        if (! * (my_input + count)) {
            printf("memory allocation failed\n"
                "exit the program\n");
            return memory_allocation_failed;
        }
    }

    while (1) {
        /* the purpose of using this for loop is for future development. The goal is to save several inputs from the user
	  and enable the user from calling his input history*/
        for (count = 0; count < Num_Strings; count++) {
            /*communicate with the user and read the input from the terminal*/
            print_func(my_input);

            /*if the user inserted 'q' or 'quit', the program should close*/
            if ((!strncmp( * (my_input + count), "q", 1) && strlen(my_input[0])==2) ||
                (!strncmp( * (my_input + count), "quit", 4)  && strlen(my_input[0])==5)) {
                printf("quit the program\n");
                close_program = true;
                break;
            }
            /*parse the input and output the result*/
            string_parse( * (my_input + count), res_str[0], & result);
        }
        /*check this flag to close the program in a good manner*/
        if (close_program) {
            break;
        }
    }
    free(res_str);
    free(my_input);
    /*free heap memory for all substrings*/
    for (count = 0; count < Num_Strings; count++) {
        free( * (my_input + count));
    }
    return EXIT_SUCCESS;
}
