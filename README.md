# String Calculator

This is a string parser which accepts strings in an arithmetic form and calculates the result. If the input has an invalid input, the parser should detect the invalid input and return an error describing the error.

Supported arithmetic operations by the parser till the monment of writing this docu are **(addition, substraction, multiplication, divison, reminder of division, power of a value, sin, sinh, asin, asinh, cos, cosh, acos, acosh, tan, tanh, atan, atanh, abs, sqrt, cbrt, exp, floor, ceil, log, log10)**.


- The user types the input to be calculated
- The program reads the input as a string and prints the result
- The program should throw an error for many unaccepted input cases

## Workflow (Linux)
- Clone the repository:  
git clone [git@github.com:Abdsaddik/String_Calculator.git](git@github.com:Abdsaddik/String_Calculator.git)
- Change to the directory ../String_Calculator
- make
- ./Calculator
## How to use this calculator
After one run the program, one can simply type the mathematic that he wants to be calculated and then print 'ENTER'.
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
sin(sin(sin(90)))  
0.702981543566823
```
**Note**  
In the same manner one can use other arithmetich operations such as cos, cosh, etc  

```
> abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) * abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) - ( 9 - 60 ) + cos(0) + sin(90)  
101.8939966636  
> (((10/5) * (9%7))/2) * 3 - (5 - (2 * 3))  
7  
> 10 + ( 10 + 5  
please check your input, you may forgot a parenthesis  
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
