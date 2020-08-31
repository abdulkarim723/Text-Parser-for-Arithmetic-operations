/*
 * calculator.c
 *
 *  Created on: Aug 31, 2020
 *      Author: A. Saddik
 */

#include "calculator.h"

/*read the string as an input from the terminal*/
void print_func(char** terminal_input){
    terminal_input[0] = malloc(STRING_SIZE * sizeof(char) );
    printf("enter a string to be calculated:\n"
    "only addition and substraction is permitted\n"
    "enter 'q' to quit\n");
    fgets(terminal_input[0], 1024, stdin);
}

/*parse the string given from the user as an input*/
int string_parse(char ** str){
	/*we need to make a copy of the original strings for display reasons*/
	char* input_str = (char*)malloc(sizeof(char) * STRING_SIZE);

	int str_len = (int)strlen(str[0]); int cnt; char* strstart, *strend, *tmpstr;
	int ret = check_parentheses(str[0] , str_len); int result = 0;
	char par_str[50];
	tmpstr = str[0];
	/*remove the new line*/
	memset(tmpstr + strlen(tmpstr) - 1, '\0', 1);

	strcpy(input_str, str[0]);

	while(ret){
		for(cnt=0; cnt<ret;cnt++){
		strstart = strstr(tmpstr, "(");
		tmpstr += (strstart - tmpstr) + 1;
		}
		strend = strstr(tmpstr, ")");

		tmpstr = strstart + 1;
		result = calculate(strstart, strend - strstart);

		sprintf(par_str, "%d", result);
		memset(strstart, ' ', strend - strstart + 1);
		memcpy(strstart, par_str, strlen(par_str) );
		ret--;
		check_sign(str[0]);
		tmpstr = str[0];
	}
	result = calculate(str[0], strlen(str[0]));
	/* print the input with its result */
    printf("%s = %i\n\n", input_str, result);
	return 0;
}

/*calculate the given input 'str'*/
int calculate(char* str, int len){
    /*num_len is needed to determine the digits length of each number str*/

    int num_len = 0;
    /*result: is the last result of the calculation operations*/
    int result = 0;
    /* allocate memory for tmp variable to be sure that we have a memory for it*/
    char* tmp = (char*)malloc(STRING_SIZE);
    int ret=0;
    //printf("str = %s, len = %d\n", str, len);
    enum calc_status calc_stat;
    while(num_len<len){
        /*ret value will be 0 for all none digit characters*/
       ret = calculate_numlen(str);
       switch(ret){
       case 0:
          switch(str[0]){
              case '+':
              calc_stat = addition;
              break;
              case '-':
              calc_stat = substraction;
              break;
          }
          str++;  num_len++;
          continue;

       default:
          num_len += ret;
          strncpy(tmp, str, ret);
          tmp[ret] = '\0';
          str += ret;
       }
       switch(calc_stat){
           case addition:
           result += atoi(tmp);
	   break;
           case substraction:
           result -= atoi(tmp);
           break;
           default:
           /* we need this default for the first number of the string, otherwise
           the calculation will not be correct*/
           result += atoi(tmp);
       }
	/* set the default value for this flag to addition, this line is important to assure right functionality*/
	calc_stat = addition;
    }

    return result;
}

/*calculate the substring length for every single number in the main string*/
int calculate_numlen(char* str_num){
    int cnt=0;
    while(isdigit(str_num[cnt])){
        cnt++;
    }
    return cnt;
}

/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char* str , int str_len){
    int cnt = 0 , number_of_parentheses_left = 0, number_of_parentheses_right = 0;
    for(cnt=0;cnt<str_len;cnt++){
        if(str[cnt] == '(' ){
            number_of_parentheses_left += 1;
        }
        else if(str[cnt] == ')'){
            number_of_parentheses_right += 1;
        }
    }
    if(number_of_parentheses_right != number_of_parentheses_left){
        return -1;
    }
    return number_of_parentheses_right;
}

/*this function checks signs correctness of the string*/
int check_sign( char* str){
	int len = strlen(str); char* tmp;
	while(len){
		if(*str == '-' ){
			tmp = str;
			str++, len--;
			while(len){
				if(*str == ' '){
					str++, len--;
					continue;
				}
				else if(*str == '-' ){
					*str = ' ';
					*tmp = '+';
					break;
				}
				else
					break;
			}
		}
		str++;
		len--;
	}
	return 0;
}

/*check if the input has invalid char*/
int check_str(char* str){
	int len = strlen(str);
	len--;
	while(len){
		if(!isdigit(*str)){
			if(*str != '(' && *str != ')' && *str != '+' && *str != '-' && *str != ' ' && *str != 'q'){
				printf("unaccepted input <%c>\n", *str);
				return 1;
			}
		}
		len--; str++;
	}
	return 0;
}

