/*
 * calculator.c
 *
 *  Created on: Aug 31, 2020
 *      Author: A. Saddik
 */

#include "calculator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/*DO NOT CHANGE THE SEQUENCE OF THIS STRING ARRAY. IT IS DANGEROUS.*/
const char researved_words[reserved_strings][10] = {
    "abs(",
    "sqrt(",
    "exp(",
    "cos(",
    "cosh(",
    "acos(",
    "acosh(",
    "sin(",
    "sinh(",
    "asin(",
    "asinh(",
    "tan(",
    "tanh(",
    "atan(",
    "atanh(",
    "floor(",
    "log(",
    "log10(",
    "cbrt(",
    "ceil"
};

/*read the string as an input from the terminal*/
int printandread(char * terminal_input) {
    strcpy(terminal_input, "");
    printf("> ");
    fgets(terminal_input, STRING_SIZE, stdin);
    return quit_program(terminal_input);
}

int quit_program(const char * str) {
    if ((!strncmp(str, "q", 1) && strlen(str) == 2) ||
        (!strncmp(str, "quit", 4) && strlen(str) == 5)) {
        printf("quit the program\n");
        return false;
    }
    return true;
}

/*parse the string given from the user as an input*/
int string_parse(const char * str_o, char * result_string, double * result) {

	char result_str[Res_STR_SIZE];
	double Res;
    if ((!strncmp(str_o, "clean", 5) && strlen(str_o) == 6)) {
        printf("\033[2J"); // Clear screen
        return clean_screen;
    }

    if (strlen(str_o) == 1) {
        return empty_string;
    }
    char ** str = (char ** ) malloc(sizeof(char * ));
    if (!str) {
        printf("memory allocation failed\n"
            "exit the program\n");
        return memory_allocation_failed;
    }
    str[0] = (char * ) malloc(sizeof(char) * STRING_SIZE);
    if (! * (str)) {
        printf("memory allocation failed\n"
            "exit the program\n");
        return memory_allocation_failed;
    }
    strncpy(str[0], str_o, STRING_SIZE);
    str[STRING_SIZE] = '\0';
    int ret;
    int len = strlen(str[0]) - 1;
    /*remove the new line in case of terminal use*/
    if(str[0][len] == '\n'){
    	memset(str[0] + len, '\0', 1);
    }
    ret = check_reserved_words(str[0]);
    if (ret < 0) {
        return ret;
    }
    ret = check_errors(str[0], strlen(str[0]));
    if (ret < 0) {
        return ret;
    }
    int parenthesis_number = check_parentheses(str[0], strlen(str[0]));
    if (parenthesis_number == parentheses_error) {
        return parenthesis_number;
    }

    if (parenthesis_number > 0) {
        calculate_parentthesis_content(str[0], strlen(str[0]), parenthesis_number);
    }
    check_sign(str[0], strlen(str[0]));
//    * result = calculate(str[0], strlen(str[0]));
//    sprintf(result_str, "%.15f", * result);
    Res = calculate(str[0], strlen(str[0]));
	sprintf(result_str, "%.15f", Res);
	if(result){
		*result = Res;
	}

    control_fraction(result_str, strlen(result_str));
    /* print the result */
    printf("%s\n", result_str);
    if(result_string){
		strcpy(result_string, result_str);
	}
    free(str);
    return EXIT_SUCCESS;
}

double calculate_parentthesis_content(char * str_o, int len, int parenthesis_num) {
    char str[1024];
    double result;
    strncpy(str, str_o, len);
    str[len] = '\0';
    char * strstart, * strend, * tmpstr;
    int cnt;
    tmpstr = str;
    /*update the input*/
    while (parenthesis_num) {
        for (cnt = 0; cnt < parenthesis_num; cnt++) {
            strstart = strstr(tmpstr, "(");
            tmpstr += (strstart - tmpstr) + 1;
        }
        strend = strstr(tmpstr, ")");
        result = str_reconst(str, strstart, strend);
        parenthesis_num--;
        check_sign(str, strlen(str));
        tmpstr = str;
    }
    check_sign(str, strlen(str));
    strcpy(str_o, str);
    return result;
}
/*reconstruct the current string to its new value*/
double str_reconst(char * str, char * str_start, char * str_end) {
    double result = 0;
    char par_str[STRING_SIZE];
    char str_left_side[STRING_SIZE];
    char str_right_side[STRING_SIZE];
    strncpy(str_left_side, str, str_start - str);
    str_left_side[str_start - str] = '\0';
    strncpy(str_right_side, str_end + 1, strlen(str_end + 1));
    str_right_side[strlen(str_end + 1)] = '\0';
    str_start[str_end - str_start] = '\0';
    result = calculate(str_start + 1, str_end - str_start);
    if (str_end - str_start == 1) {
        printf("it is not allowed to leave empty parentheses content\n");
        return empty_parentheses_content;
    }
    sprintf(par_str, "%.15f", result);

    strcpy(str, str_left_side);
    strncat(str, par_str, strlen(par_str));
    strncat(str, str_right_side, strlen(str_right_side));
    return result;
}

/*calculate the given input 'str'*/
double calculate(char * str, int len) {
    /*do devision and multiplication operations*/
    if (strchr(str, '^') || strchr(str, '%') || strchr(str, '/') || strchr(str, '*')) {
        calculate_dev_mul(str, len);
    }
    check_sign(str, strlen(str));
    /*num_len is needed to determine the digits length of each number str*/
    int num_len = 0;
    /*result: is the last result of the calculation operations*/
    double result = 0;
    char tmp[Res_STR_SIZE];
    int ret = 0;
    enum calc_status calc_stat;
    /*as the string str was reconstructed in the function calculate_dev_mul(), we need to update the value of len*/
    len = strlen(str);
    while (num_len < len) {
        if ( * str == ' ') {
            str++;
            num_len++;
            continue;
        }
        /*ret value will be 0 for all none digit characters*/
        ret = calculate_numlen(str);
        switch (ret) {
        case 0:
            switch (str[0]) {
            case '+':
                calc_stat = addition;
                break;
            case '-':
                calc_stat = substraction;
                break;
            }
            str++;
            num_len++;
            continue;

        default:
            num_len += ret;
            strncpy(tmp, str, ret);
            tmp[ret] = '\0';
            str += ret;
        }
        switch (calc_stat) {
        case addition:
            result += strtod(tmp, NULL);
            break;
        case substraction:
            result -= strtod(tmp, NULL);
            break;
        default:
            /* we need this default for the first number of the string, otherwise
            the calculation will not be correct*/
            result += strtod(tmp, NULL);
        }
    }
    return result;
}

/*as in math, the devision had the first priority then comes multiplication*/
double calculate_dev_mul(char * str, int len) {
    /*here I made the assumption, that every single double has a maximum size of 20 char digit*/
    char right_num[50];
    char left_num[50];
    char result_str[50];
    double right_number, left_number, result = 0;
    int ret;
    char str_left_side[STRING_SIZE];
    char str_right_side[STRING_SIZE];
    char * dev_mult;
    char * tmp = NULL;
    while ((dev_mult = strchr(str, '^')) != NULL || (dev_mult = strchr(str, '%')) != NULL || (dev_mult = strchr(str, '/')) != NULL || (dev_mult = strchr(str, '*')) != NULL) {
        tmp = dev_mult;
        while ( * dev_mult == ' ' || * dev_mult == '^' || * dev_mult == '%' || * dev_mult == '/' || * dev_mult == '*') {
            dev_mult++;
            len--;
            continue;
        }

        ret = calculate_numlen_sign(dev_mult);

        strncpy(right_num, dev_mult, ret);
        right_num[ret] = '\0';
        strncpy(str_right_side, dev_mult + ret, strlen(str) - (dev_mult - str) + ret);
        str_right_side[strlen(str) - (dev_mult - str) + ret] = '\0';
        dev_mult = tmp;
        while ( * dev_mult == ' ' || * dev_mult == '^' || * dev_mult == '%' || * dev_mult == '/' || * dev_mult == '*') {
            dev_mult--;
            len--;
            continue;
        }
        ret = calculate_numlen_backward(dev_mult);
        strncpy(left_num, dev_mult - ret + 1, ret);
        left_num[ret] = '\0';
        strncpy(str_left_side, str, (tmp - str) - (tmp - dev_mult));
        str_left_side[dev_mult - str - ret + 1] = '\0';
        right_number = strtod(right_num, NULL);
        left_number = strtod(left_num, NULL);
        switch ( * tmp) {
        case '^':
            result = pow(left_number, right_number);
            break;
        case '%':
            result = (long int) left_number % (long int) right_number;
            break;
        case '/':
            result = left_number / right_number;
            break;
        case '*':
            result = left_number * right_number;
            break;
        }
        sprintf(result_str, "%0.15f", result);

        /*reconstruct the string 'str'*/
        strcpy(str, str_left_side);
        strncat(str, result_str, strlen(result_str));
        strncat(str, str_right_side, strlen(str_right_side));
        if (!len) {
            break;
        }
        len--;
    }
    return result;
}

int calculate_numlen_sign(char * str_num) {
    int cnt = 0;
    bool do_once = true, do_one = true;
    while (1) {
        if (str_num[cnt] == ' ' && do_once == true) {
            cnt++;
            continue;
        } else if ((str_num[cnt] == '-' || str_num[cnt] == '+') && do_one == true) {
            do_once = false;
            do_one = false;
            cnt++;
        } else if (isdigit(str_num[cnt]) || (str_num[cnt] == '.' && isdigit(str_num[cnt + 1]))) {
            cnt++;
            do_one = false;
        }
        //
        else
            break;
    }
    return cnt;
}

/*calculate the substring length for every single number in the main string*/

int calculate_numlen(char * str_num) {
    int cnt = 0;
    while (isdigit(str_num[cnt]) || (str_num[cnt] == '.' && isdigit(str_num[cnt + 1])) ||
        (str_num[cnt] == '-' && isdigit(str_num[cnt + 1]) && !isdigit(str_num[cnt + 1]))) {
        cnt++;
    }
    return cnt;
}

/*calculate the substring length for every single number in the main string backwards*/
int calculate_numlen_backward(char * str_num) {
    int cnt = 0;
    while (isdigit(str_num[cnt]) || (str_num[cnt] == '.' && isdigit(str_num[cnt - 1])) ||
        (str_num[cnt] == '-' && isdigit(str_num[cnt + 1]) && !isdigit(str_num[cnt + 1]))) {
        cnt--;
    }
    return abs(cnt);
}

/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char * str_o, int len) {
    char str_cpy[STRING_SIZE];
    strcpy(str_cpy, str_o);
    str_cpy[len] = '\0';
    char * str = str_cpy;
    char * tmp;
    char * start_add = str;
    char parenthesis[] = "()";
    int cnt = 0;
    int number_of_parentheses[2] = {
        0,
        0
    };
    for (cnt = 0; cnt < 2; cnt++) {
        while ((tmp = strchr(str, parenthesis[cnt])) != NULL) {
            number_of_parentheses[cnt]++;
            str = tmp + 1;
        }
        str = start_add;
    }
    if (number_of_parentheses[0] != number_of_parentheses[1]) {
        printf("please check your input, you may forget a parentheses\n");
        return parentheses_error;
    }
    return number_of_parentheses[0];
}

/*this function checks signs correctness of the string
 * is function is implemented after removing parentheses*/
int check_sign(char * str, int len) {
    char * tmp;
    while (len) {
        if ( * str == '-') {
            tmp = str;
            str++, len--;
            while (len) {
                if ( * str == ' ') {
                    str++, len--;
                    continue;
                } else if ( * str == '-') {
                    * str = ' ';
                    * tmp = '+';
                    break;
                } else if ( * str == '+') {
                    * str = ' ';
                    * tmp = '-';
                    break;
                } else {
                    /*in case *str is a digit or '*' or '/'*/
                    break;
                }

            }
        }
        str++;
        len--;
    }
    return EXIT_SUCCESS;
}

int is_arith_sign(char * str) {
    if ( * str == '+' || * str == '-' || * str == '/' || * str == '*' || * str == '%') {
        return true;
    } else {
        return false;
    }
}

/*this function returns error for such input ' 10 10', '(10) (10)', '* 10 + 5' or '10 + 5 *'
 * it checks for invalid chars*/
int check_errors(char * str, int len) {
    //   int len = strlen(str);
    int ret;
    char * str_ptr, * str_ptr_second, * tmp;
    char * strstart = str;
    bool str_status = false;
    char * strend = str + len;
    char digits[] = "0123456789";
    if (!strpbrk(str, digits)) {
        printf("can not read any number, check your input please\n");
        return no_numbers_found;
    }
    /*if the string starts with one of the following chars "*%/", return an error*/
    if ((str_ptr = strpbrk(str, "*/%")) != NULL) {
        while (str_ptr >= strstart) {
            str_ptr--;
            if (isdigit( * str_ptr)) {
                str_status = true;
                break;
            }
        }
        if (!str_status) {
            printf("extra_arithmetic_sign, input is invalid\n");
            return extra_arithmetic_sign;
        }
    }
    /********************************************************************************/
    /* return an error in case of duplicated arithmetic sign except the minus '-'*/
    str_status = false;
    tmp = str;
    while ((str_ptr = strpbrk(tmp, "*/%+")) != NULL) {
        tmp = str_ptr + 1;
        if ((str_ptr_second = strpbrk(tmp, "*/%")) != NULL) {
            while (str_ptr_second > tmp) {
                if (isdigit( * tmp) || * tmp == '(') {
                    str_status = true;
                    /*every thing is fine*/
                    break;
                }
                tmp++;
            }
            if (!str_status) {
                printf("extra_arithmetic_sign, input is invalid\n");
                return extra_arithmetic_sign;
            }
        }
    }

    /*if the string ends with an arithmetic sign, then it returns error */
    str_status = false;
    if (((str_ptr = strrchr(str, '*')) != NULL || (str_ptr = strrchr(str, '/')) != NULL || (str_ptr = strrchr(str, '%')) != NULL ||
            (str_ptr = strrchr(str, '+')) != NULL || (str_ptr = strrchr(str, '-')) != NULL) && str_ptr < strend) {
        while (str_ptr < strend) {
            str_ptr++;
            if (isdigit( * str_ptr)) {
                str_status = true;
                break;
            }

        }
        if (!str_status) {
            printf("extra_arithmetic_sign, input is invalid\n");
            return extra_arithmetic_sign;
        }
    }

    while (len > 0) {
        if (!isdigit( * str) && * str != '(' && * str != ')' && !is_arith_sign(str) &&
            *
            str != ' ' && * str != '.' && * str != '^') {
            printf("invalid input\n");
            return invalid_input_character;
        } else if (isdigit( * str)) {
            ret = calculate_numlen(str);
            str += ret;
            len -= ret;
            while (len) {
                if ( * str == ' ' || * str == ')') {
                    str++;
                    len--;
                    continue;
                }
                /*return error for such input ' 10 10' or '(10) 10'*/
                else if ((isdigit( * str)) || ( * str == '(')) {
                    printf("invalid input, missing an arithmetic sign\n");
                    return no_arithmetic_sign;
                } else {
                    /*string index tuning*/
                    str--;
                    len++;
                    break;
                }
            }
        }
        str++;
        len--;
    }
    return 0;
}

char * find_last_word(char * str) {
    int cnt = 0;
    bool RetType = false;
    char * par_start, * tmp, * ret_ptr;
    while ((par_start = strchr(str, '(')) != NULL) {
        tmp = par_start - 1;
        while (isalpha( * tmp)) {
            tmp--;
        }
        for (cnt = 0; cnt < reserved_strings; cnt++) {
            if (!strncmp(tmp + 1, researved_words[cnt], strlen(researved_words[cnt]))) {
                ret_ptr = tmp + 1;
                RetType = true;
                break;
            }

        }
        str = par_start + 1;
    }

    if (RetType == true) {
        return ret_ptr;
    }
	return NULL;

}
/*this function is to calculate the content of the reserved key words such as 'abs' and 'sqrt'*/
int check_reserved_words(char * str) {
    char str_par[50];
    char str_left[STRING_SIZE], str_right[STRING_SIZE];
    char * ptr, * parenthesis_start, * parenthesis_end, * tmp, * ret_ptr;
    int parenthesis_left = 1, parenthesis_right = 0;
    int cnt;
    double result;
    while ((ptr = find_last_word(str)) != NULL) {
        parenthesis_start = strchr(ptr, '(');
        for (cnt = 0; cnt < reserved_strings; cnt++) {
            if (!strncmp(ptr, researved_words[cnt], parenthesis_start - ptr)) {
                break;
            }
        }
        tmp = parenthesis_start + 1;
        while ((ret_ptr = strpbrk(tmp, "()")) != NULL) {
            tmp = ret_ptr + 1;
            switch ( * ret_ptr) {
            case '(':
                parenthesis_left++;
                break;
            case ')':
                parenthesis_right++;
                parenthesis_end = ret_ptr;
                break;
            }
            if (parenthesis_left == parenthesis_right) {
                parenthesis_left = 1, parenthesis_right = 0;
                break;
            }
        }
        strncpy(str_right, parenthesis_end + 1, strlen(parenthesis_end));

        /*delete the reserved word*/
        memset(ptr, ' ', parenthesis_start - ptr);
        int ret = check_errors(parenthesis_start, parenthesis_end - parenthesis_start + 1);
        if (ret < 0) {
            return ret;
        }
        int parenthesis_number = check_parentheses(parenthesis_start, parenthesis_end - parenthesis_start + 1);
        if (parenthesis_number == parentheses_error) {
            return parenthesis_number;
        }

        if (parenthesis_number > 0) {
            result = calculate_parentthesis_content(parenthesis_start, parenthesis_end - parenthesis_start + 1, parenthesis_number);
        }
        switch (cnt) {
        case ABS:
            result = abs(result);
            sprintf(str_par, "%.15f", result);
            break;
        case SQRT:
            if (result < 0) {
                printf("only positive numbers are accepted for square root\n");
                return negative_num;
            }
            result = sqrt(result);
            sprintf(str_par, "%.15f", result);
            break;
        case EXP:
            result = exp(result);
            sprintf(str_par, "%.15f", result);
            break;
        case COS:
            result = cos(result);
            sprintf(str_par, "%.15f", result);
            break;
        case COSH:
            result = cosh(result);
            sprintf(str_par, "%.15f", result);
            break;
        case ACOS:
            if (result < -1 || result > 1) {
                printf("out of range input for acos() function\n");
                return out_of_range;
            }
            result = acos(result);
            sprintf(str_par, "%.15f", result);
            break;
        case ACOSH:
            if (result < 1) {
                printf("out of range input for acosh() function\n");
                return out_of_range;
            }
            result = acosh(result);
            sprintf(str_par, "%.15f", result);
            break;
        case SIN:
            result = sin(result);
            sprintf(str_par, "%.15f", result);
            break;
        case SINH:
            result = sinh(result);
            sprintf(str_par, "%.15f", result);
            break;
        case ASIN:
            if (result < -1 || result > 1) {
                printf("out of range input for asin() function\n");
                return out_of_range;
            }
            result = asin(result);
            sprintf(str_par, "%.15f", result);
            break;
        case ASINH:
            result = asinh(result);
            sprintf(str_par, "%.15f", result);
            break;
        case TAN:
            result = tan(result);
            sprintf(str_par, "%.15f", result);
            break;
        case TANH:
            result = tanh(result);
            sprintf(str_par, "%.15f", result);
            break;
        case ATAN:
            result = atan(result);
            sprintf(str_par, "%.15f", result);
            break;
        case ATANH:
            if (result < -1 || result > 1) {
                printf("out of range input for atanh() function\n");
                return out_of_range;
            }
            result = atanh(result);
            sprintf(str_par, "%.15f", result);
            break;
        case FLOOR:
            result = floor(result);
            sprintf(str_par, "%.15f", result);
            break;
        case LOG:
            if (result <= 0) {
                printf("only positive numbers are accepted for logarithm\n");
                return negative_num;
            }
            result = log(result);
            sprintf(str_par, "%.15f", result);
            break;
        case LOG10:
            if (result <= 0) {
                printf("only positive numbers are accepted for logarithm\n");
                return negative_num;
            }
            result = log10(result);
            sprintf(str_par, "%.15f", result);
            break;
        case CBRT:
            result = cbrt(result);
            sprintf(str_par, "%.15f", result);
            break;
        case CEIL:
            result = ceil(result);
            sprintf(str_par, "%.15f", result);
            break;
        }
        /*reconstruct the original string*/
        strncpy(str_left, str, parenthesis_start - str);
        str_left[parenthesis_start - str] = '\0';
        strcpy(str, str_left);
        strncat(str, str_par, strlen(str_par));
        strncat(str, str_right, strlen(str_right));
    }
    return 0;
}

/*this function ignores the zeros which has no value*/
int control_fraction(char * str, int len) {
    int cnt;
    int DigitsNum = 15;
    for (cnt = 0; cnt < DigitsNum; cnt++) {
        if (str[len - 1] == '0') {
            str[len - 1] = '\0';
            len--;
            if (cnt == (DigitsNum - 1)) {
                str[len - 1] = '\0';
            }
            continue;
        }
        break;
    }
    return 0;
}
