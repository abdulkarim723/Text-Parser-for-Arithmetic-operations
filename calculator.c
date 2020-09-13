/*
 * calculator.c
 *
 *  Created on: Aug 31, 2020
 *      Author: A. Saddik
 */

#include "calculator.h"

/*read the string as an input from the terminal*/
void print_func(char ** terminal_input) {
  strcpy(terminal_input[0], "");
  printf("> enter a string to be calculated:\n"
    "> enter 'q' to quit\n"
    "> ");
  fgets(terminal_input[0], STRING_SIZE, stdin);
}

/*parse the string given from the user as an input*/
int string_parse(char ** str) {
  int cnt, ret;
  char * strstart, * strend, * tmpstr;

  /*remove the new line*/
  memset(str[0] + strlen(str[0]) - 1, '\0', 1);
  ret = check_digit_sign_sequence(str[0]);
  if (ret < 0) {
    return ret;
  }
  /*check if the given string has parentheses and if they are correctly closed*/
  ret = check_parentheses(str[0]);
  if (ret == parentheses_error) {
    printf("> please check your input, you may forgot a parentheses\n\n");
    return ret;
  }

  double result = 0;
  char par_str[STRING_SIZE];
  char str_left_side[STRING_SIZE];
  char str_right_side[STRING_SIZE];
  tmpstr = str[0];


  /*update the input*/
  while (ret) {
    for (cnt = 0; cnt < ret; cnt++) {
      strstart = strstr(tmpstr, "(");
      tmpstr += (strstart - tmpstr) + 1;
    }
    strend = strstr(tmpstr, ")");
    strncpy(str_left_side, str[0], strstart - str[0]);
	str_left_side[strstart - str[0]] = '\0';
	strncpy(str_right_side, strend + 1, strlen(strend + 1));
	str_right_side[strlen(strend + 1)] = '\0';
	strstart[strend - strstart] = '\0';
    result = calculate(strstart + 1, strend - strstart);
    sprintf(par_str, "%.6f", result);

    strcpy(str[0], str_left_side);
    strncat(str[0], par_str, strlen(par_str));
    strncat(str[0], str_right_side, strlen(str_right_side));
    ret--;
    check_sign(str[0]);
    tmpstr = str[0];
  }
  result = calculate(str[0], strlen(str[0]));
  /* print the input with its result */
  printf("> %f\n\n", result);
  return EXIT_SUCCESS;
}

/*calculate the given input 'str'*/
double calculate(char * str, int len) {
  /*do devision and multiplication operations*/
  if(strchr(str, '/') || strchr(str, '*')){
	calculate_dev_mul(str, len);
  }
  /*num_len is needed to determine the digits length of each number str*/
  int num_len = 0;
  /*result: is the last result of the calculation operations*/
  double result = 0;
  char tmp[20];
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
  char right_num[20];
  char left_num[20];
  char result_str[20];
  double right_number, left_number, result = 0;
  int ret;
  char str_left_side[STRING_SIZE];
  char str_right_side[STRING_SIZE];
  char * dev_mult;
  char * tmp = NULL;
  while ((dev_mult = strchr(str, '/')) != NULL || (dev_mult = strchr(str, '*')) != NULL) {
    tmp = dev_mult;
    while ( * dev_mult == ' ' || * dev_mult == '/' || * dev_mult == '*') {
      dev_mult++;
      len--;
      continue;
    }
    ret = calculate_numlen(dev_mult);
    strncpy(right_num, dev_mult, ret);
    right_num[ret] = '\0';
    strncpy(str_right_side, dev_mult + ret, strlen(str) - (dev_mult - str) + ret);
    str_right_side[strlen(str) - (dev_mult - str) + ret] = '\0';
    dev_mult = tmp;
    while ( * dev_mult == ' ' || * dev_mult == '/' || * dev_mult == '*') {
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
    case '/':
      result = left_number / right_number;
      break;
    case '*':
      result = left_number * right_number;
      break;
    }
    sprintf(result_str, "%0.6f", result);

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
  char* tmp;  char* start_add = str;  char parenthesis[] = "()";
  int cnt = 0;
  int number_of_parentheses[2] = {0,0};
  for(cnt=0; cnt<2;cnt++){
  while((tmp = strchr(str, parenthesis[cnt])) != NULL){
	  number_of_parentheses[cnt]++;
	  str = tmp + 1;
  }
  str = start_add;
  }
  if (number_of_parentheses[0] != number_of_parentheses[1]) {
      return parentheses_error;
  }
  return number_of_parentheses[0];
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

int is_arith_sign(char * str) {
  if ( * str == '+' || * str == '-' || * str == '/' || * str == '*') {
    return 1;
  } else {
    return 0;
  }
}

/*this function returns error for such input ' 10 10' or '(10) (10)'
 * it checks for invalid chars*/
int check_digit_sign_sequence(char * str) {
  int len = strlen(str);
  int ret;
  while (len>0) {
  if (!isdigit( * str) && * str != '(' && * str != ')' && !is_arith_sign(str) &&
		  * str != ' ' && * str != '.' && * str != 'q') {
	  printf("> invalid input\n\n");
      return invalid_input_character;
		}
  else if (isdigit( * str) ) {
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
        else if ((isdigit( *str)) || (*str == '(')) {
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
