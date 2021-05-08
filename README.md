# Text Parser for Arithmetic Operations

This is a string parser which accepts strings in an arithmetic form and calculates the result. If the input has an invalid input, the parser should detect the invalid input and return an error describing the error.

Supported arithmetic operations by the parser are **(addition, substraction, multiplication, divison, reminder of division, power of a value, sin, sinh, asin, asinh, cos, cosh, acos, acosh, tan, tanh, atan, atanh, abs, sqrt, cbrt, exp, floor, ceil, log, log10)**.

## Workflow (Linux)
- Clone the repository:  
git clone [git@github.com:Abdsaddik/Text-Parser-for-Arithmetic-operations.git](git@github.com:Abdsaddik/Text-Parser-for-Arithmetic-operations.git)
- Change to the directory ../String_Calculator
- Then one can run the program as followed illustrated
### One time run
Simply, run ```./run.sh``` in the terminal. The following output should be printed on the terminal
```
build the program ...
successfuly build
run the program
 10 + 10 * ( 3 + 2 ) = 60 (string format)
 10 + 10 * ( 3 + 2 ) = 60.00 (double format)
 abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) * abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) - ( 9 - 60 ) + cos(0) + sin(90) = 101.893996663600561 (string format)
 abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) * abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) - ( 9 - 60 ) + cos(0) + sin(90) = 101.893996663600561 (double format)
build files removed successfully!
```
### Terminal mode
- uncomment line 21 in main.c **text_parser_with_terminal();**
- comment line 19 in main.c **demo_example();** 
- uncomment line 18 in calculator.h **#define PRINT_OUT**
- ./run.sh
- The user types the input to be calculated and then print 'ENTER'
- The program reads the input and prints the result
- The program should throw an error for many unaccepted input cases
## Output Examples in Terminal
**Addition**  
```
> 5 + 5  
10  
```
**Absolute value of a number**  
```
> abs(-7)  
7  
```
**Power of value e**  
```
> exp(1)  
2.718281828459045  
```
**Power of a value**  
```
> 2^8  
256  
```
**Sine and hyperbolic tangent**  
Calculate the sine or hyperbolic tangent of a value in radian  
**Example of sin()**  
```
> sin(180)  
-0.80115263573383  
```
**Example of tanh()**  
```
> tanh(0.4)
0.379948962255225  
```
**Mixed Example**  
```
> sin(180) + tanh(0.4)
-0.421203673478605
```
**Nested Functions are supported**
```
> sin(sin(sin(90)))  
0.702981543566823
```
**Note**  
In the same manner one can use other arithmetic operations such as cos, cosh, etc  

```
> abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) * abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) - ( 9 - 60 ) + cos(0) + sin(90)  
101.8939966636  
> (((10/5) * (9%7))/2) * 3 - (5 - (2 * 3))  
7  
> 10 + ( 10 + 5  
please check your input, you may forget a parenthesis  
> 10 10  
invalid input, missing an arithmetic sign  
```
**Quit the program**  
type 'q' or 'quit' in the terminal and press 'ENTER'  
```
> q  
quit the program
```
```
> quit  
quit the program
```  
**clean the terminal**  
```
> clean
```
as a result, the terminal is cleaned
