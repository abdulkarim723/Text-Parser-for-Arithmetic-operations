/*
 * calculator.c
 *
 *  Created on: Aug 31, 2020
 *      Author: A. Saddik
 */

#include "calculator.h"

/*read the string as an input from the terminal*/
void print_func(char ** terminal_input) {
  printf("> enter a string to be calculated:\n"
    "> enter 'q' to quit\n"
    "> ");
  fgets(terminal_input[0], STRING_SIZE, stdin);
}

/*parse the string given from the user as an input*/
int string_parse(char ** str) {
  int cnt, ret;
  char * strstart, * strend, * tmpstr;
  /*check if the input has invalid chars*/
  if (check_str(str[0])) {
    printf("> please check your input, it seems you entered an invalid expression\n\n> ");
    return invalid_input_character;
  }
  ret = check_digit_sign_sequence(str[0]);
  if (ret < 0) {
    return ret;
  }
  /*check if the given string has parentheses and if they are correctly closed*/
  ret = check_parentheses(str[0]);
  if (ret == parentheses_error) {
    printf("> please check your input, you may forgot a parentheses\n\n> ");
    return ret;
  }

  double result = 0;
  char par_str[STRING_SIZE];
  char str_left_side[STRING_SIZE];
  char str_right_side[STRING_SIZE];
  tmpstr = str[0];

  /*remove the new line*/
  memset(tmpstr + strlen(tmpstr) - 1, '\0', 1);
  /*update the input*/
  while (ret) {
    for (cnt = 0; cnt < ret; cnt++) {
      strstart = strstr(tmpstr, "(");
      tmpstr += (strstart - tmpstr) + 1;
    }
    strend = strstr(tmpstr, ")");
    result = calculate(strstart, strend - strstart);
    #ifdef DEBUG_PRINT
    printf("result = %f, strstart = %s\n", result, strstart);
    #endif
    sprintf(par_str, "%.6f", result);
    strncpy(str_left_side, str[0], strstart - str[0]);
    str_left_side[strstart - str[0]] = '\0';
    #ifdef DEBUG_PRINT
    printf("left string = %s\nstrstart = %s\n", str_left_side, strstart);
    #endif
    strncpy(str_right_side, strend + 1, strlen(strend));
    #ifdef DEBUG_PRINT
    printf("right string = %s\n", str_right_side);
    #endif
    strcpy(str[0], str_left_side);
    strncat(str[0], par_str, strlen(par_str));
    strncat(str[0], str_right_side, strlen(str_right_side));
    #ifdef DEBUG_PRINT
    printf("new string = %s\n", str[0]);
    #endif
    ret--;
    check_sign(str[0]);
    tmpstr = str[0];
  }
  check_sign(str[0]);
  result = calculate(str[0], strlen(str[0]));
  /* print the input with its result */
  printf("> %f\n\n", result);
  return EXIT_SUCCESS;
}

/*calculate the given input 'str'*/
double calculate(char * str, int len) {
  /*num_len is needed to determine the digits length of each number str*/

  int num_len = 0;
  /*result: is the last result of the calculation operations*/
  double result = 0;
  /* allocate memory for tmp variable to be sure that we have a memory for it*/
  char * tmp = (char * ) malloc(STRING_SIZE);
  int ret = 0;
  enum calc_status calc_stat;
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
      case '*':
        calc_stat = multiplication;
        break;
      case '/':
        calc_stat = division;
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
    case multiplication:
      result *= strtod(tmp, NULL);
      break;
    case division:
      result /= strtod(tmp, NULL);
      break;
    default:
      /* we need this default for the first number of the string, otherwise
      the calculation will not be correct*/
      result += strtod(tmp, NULL);
    }
    /* set the default value for this flag to addition, this line is important to assure right functionality*/
    //calc_stat = addition;
  }
  free(tmp);
  return result;
}

//double calculate_test(char * str, int len) {
//   char right_num[20]; char left_num[20];  double right_number, left_number, result;
//  int ret;
//  char* tmp;
//  while(len){
//  char* devision = strchr(str, '/');
//  tmp = devision;
//  if(devision){
//	ret = calculate_numlen(devision);
//	strncpy(right_num, devision + 1, ret);
//	right_num[ret] = '\0';
//	memset(devision + 1, ret, 0);
//	ret = calculate_numlen_backward(devision - 1);
//	strncpy(left_num, devision - 1 - ret, ret);
//	right_num[ret] = '\0';
//	memset(devision - 1 - ret, ret, 0);
//	right_number = strtod(right_num, NULL);
//	left_number = strtod(left_num, NULL);
//	result = left_number/right_number;
//	}
//  }
// return result;
//}

/*calculate the substring length for every single number in the main string*/

int calculate_numlen(char * str_num) {
  int cnt = 0;
  while (isdigit(str_num[cnt]) || (str_num[cnt] == '.' && isdigit(str_num[cnt - 1])) ||
    (str_num[cnt] == '-' && isdigit(str_num[cnt + 1]) && !isdigit(str_num[cnt - 1]))) {
    cnt++;
  }
  return cnt;
}

/*calculate the substring length for every single number in the main string backwards*/
int calculate_numlen_backward(char * str_num) {
  int cnt = 0;
  while (isdigit(str_num[cnt]) || (str_num[cnt] == '.' && isdigit(str_num[cnt - 1])) ||
    (str_num[cnt] == '-' && isdigit(str_num[cnt + 1]) && !isdigit(str_num[cnt - 1]))) {
    cnt--;
  }
  return abs(cnt);
}

/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char * str) {
  short str_len = strlen(str);
  int cnt = 0, number_of_parentheses_left = 0, number_of_parentheses_right = 0;
  for (cnt = 0; cnt < str_len; cnt++) {
    if (str[cnt] == '(') {
      number_of_parentheses_left += 1;
    } else if (str[cnt] == ')') {
      number_of_parentheses_right += 1;
    }
  }
  if (number_of_parentheses_right != number_of_parentheses_left) {
    return parentheses_error;
  }
  return number_of_parentheses_right;
}

/*this function checks signs correctness of the string
 * is function is implemented after removing parentheses*/
int check_sign(char * str) {
  int len = strlen(str);
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

/*check if the input has invalid char*/
int check_str(char * str) {
  int len = strlen(str);
  len--;
  while (len) {
    if (!isdigit( * str)) {
      if ( * str != '(' && * str != ')' && * str != '+' && * str != '-' && * str != '*' && * str != '/' &&
        *
        str != ' ' && * str != '.' && * str != 'q') {
        printf("> unaccepted input <%c>\n", * str);
        return invalid_input_character;
      }
    }
    len--;
    str++;
  }
  return EXIT_SUCCESS;
}

int is_arith_sign(char * str) {
  if ( * str == '+' || * str == '-' || * str == '/' || * str == '*') {
    return 1;
  } else {
    return 0;
  }
}

/*this function returns error for such input ' 10 10' or '(10) (10)'*/
int check_digit_sign_sequence(char * str) {
  int len = strlen(str);
  int ret;
  while (len) {
    if (isdigit( * str) || *str == ')') {
      ret = calculate_numlen(str);
      str += ret;
      len -= ret;
      while (len) {
        if ( * str == ' ') {
          str++;
          len--;
          continue;
        }
        /*return error for such input ' 10 10' or '(10) 10'*/
        else if (isdigit( * str) || *str == '('){
          printf("> invalid input, missing an arithmetic sign\n\n");
          return no_arithmetic_sign;
        } else {
          break;
        }
      }
    }
    str++;
    len--;
  }
  return 0;
}
