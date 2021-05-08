/*
 * terminal.c
 *
 *  Created on: Jan 10, 2021
 *      Author: abdulkarim
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "calculator.h"

int terminal_interact(const char * str) {
    if ((!strncmp(str, "q", 1) && strlen(str) == 2) ||
        (!strncmp(str, "quit", 4) && strlen(str) == 5)) {
        printf("quit the program\n");
        return false;
    }
    return true;
}

/*read the string as an input from the terminal*/
int printandread(char * terminal_input) {
    strcpy(terminal_input, "");
    printf("> ");
    fgets(terminal_input, STRING_SIZE, stdin);
    return terminal_interact(terminal_input);
}

// this example uses the text parser dependent on terminal.
void text_parser_with_terminal(){
	char my_input[STRING_SIZE];
	char str[50];
	while (1) {
		// this function reads the terminal input and points it to the pointer my_input
		if(!printandread(my_input)){
			break;
		}

		if ((!strncmp(my_input, "clean", 5) && strlen(my_input) == 6)){
			printf("\033[2J"); // Clear screen
			continue;
		}
		/*parse the input and output the result*/
		int ret = string_parse(my_input, str, NULL);

		/* print the result */
		if(my_input[0] != '\n' && !ret){
			printf("%s\n", str);
		}
	}
}

