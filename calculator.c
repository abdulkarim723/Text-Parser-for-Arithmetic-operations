/*
 * calculator.c
 *
 *  Created on: Aug 31, 2020
 *      Author: A. Saddik
 */

#include "calculator.h"

/*read the string as an input from the terminal*/
void print_func(char ** terminal_input) {
  printf("enter a string to be calculated:\n"
    "enter 'q' to quit\n");
  fgets(terminal_input[0], STRING_SIZE, stdin);
}

/*parse the string given from the user as an input*/
int string_parse(char ** str) {

  /*we need to make a copy of the original string for display reasons*/
  char * input_str = (char * ) malloc(sizeof(char) * STRING_SIZE);
  int str_len = strlen(str[0]);
  int cnt;
  char * strstart, * strend, * tmpstr;
  /*check if the given string has parentheses and if they are correctly closed*/
  int ret = check_parentheses(str[0], str_len);
  if (ret == -1) {
    printf("please check your input, you may forgot a parentheses\n\n");
    return ret;
  }
  double result = 0;
  char par_str[50];
  tmpstr = str[0];
  /*remove the new line*/
  memset(tmpstr + strlen(tmpstr) - 1, '\0', 1);

  /*update the input*/
  strcpy(input_str, str[0]);
  while (ret) {
    for (cnt = 0; cnt < ret; cnt++) {
      strstart = strstr(tmpstr, "(");
      tmpstr += (strstart - tmpstr) + 1;
    }
    strend = strstr(tmpstr, ")");

    tmpstr = strstart + 1;
    result = calculate(strstart, strend - strstart);

    sprintf(par_str, "%f", result);
    memset(strstart, ' ', strend - strstart + 1);
    memcpy(strstart, par_str, strlen(par_str));
    ret--;
    check_sign(str[0]);
    tmpstr = str[0];
  }
  result = calculate(str[0], strlen(str[0]));
  /* print the input with its result */
  printf("%s = %f\n\n", input_str, result);
  free(input_str);
  return 0;
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
  //printf("str = %s, len = %d\n", str, len);
  enum calc_status calc_stat;
  while (num_len < len) {
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
    calc_stat = addition;
  }

  return result;
}

/*calculate the substring length for every single number in the main string*/
int calculate_numlen(char * str_num) {
  int cnt = 0;
  while (isdigit(str_num[cnt]) || str_num[cnt] == '.') {
    cnt++;
  }
  return cnt;
}

/*check if the given string has parentheses and if they are correctly closed*/
int check_parentheses(char * str, int str_len) {
  int cnt = 0, number_of_parentheses_left = 0, number_of_parentheses_right = 0;
  for (cnt = 0; cnt < str_len; cnt++) {
    if (str[cnt] == '(') {
      number_of_parentheses_left += 1;
    } else if (str[cnt] == ')') {
      number_of_parentheses_right += 1;
    }
  }
  if (number_of_parentheses_right != number_of_parentheses_left) {
    return -1;
  }
  return number_of_parentheses_right;
}

/*this function checks signs correctness of the string*/
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
        } else
          break;
      }
    }
    str++;
    len--;
  }
  return 0;
}

/*check if the input has invalid char*/
int check_str(char * str) {
  int len = strlen(str);
  len--;
  while (len) {
    if (!isdigit( * str)) {
      if ( * str != '(' && * str != ')' && * str != '+' && * str != '-' && * str != '*' && * str != '/' &&
        * str != ' ' && * str != '.' && * str != 'q') {
        printf("unaccepted input <%c>\n", * str);
        return 1;
      }
    }
    len--;
    str++;
  }
  return 0;
}
