# String_Calculator

This is a string parser which accepts strings in an arithmetic form and calculates the result. If the input has an invalid input, the parser should detect the invalid input and return an error describing the error.

Supported arithmetic operations by the parser till the monment of writing this docu are **(addition, substraction, multiplication, divison and reminder of division, sin, sinh, cos, cosh, abs, sqrt, exp)**.

**The tag v1.2 should work in a stable state.**

- The user types the input to be calculated
- The program reads the input as a string and prints the result
- The program should throw an error for many unaccepted input cases

## Workflow (Linux)
- Clone the repository:  
git clone [git@github.com:Abdsaddik/String_Calculator.git](git@github.com:Abdsaddik/String_Calculator.git)
- Change to the directory ../String_Calculator
- make
- ./Calculator
 
## Output Examples in Terminal
```
> 5 + 5  
10  
> abs(-7)  
7  
> exp(1)  
2.718282  
> abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) * abs(-((10/5 * 9%7)/2 *3 - (5 - 2 * 3))) - ( 9 - 60 ) + cos(0) + sin(90)  
101.893997  
> (((10/5) * (9%7))/2) * 3 - (5 - (2 * 3))  
7  
> 10 + ( 10 + 5  
please check your input, you may forgot a parenthesis  
> 10 10  
invalid input, missing an arithmetic sign  
> q  
quit the program
```
