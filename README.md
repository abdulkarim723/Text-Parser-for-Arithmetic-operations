# String_Calculator

This is a string parser which accepts strings in an arithmetic form and calculates the result. If the input has an invalid input, the parser should detect the invalid input and return an error describing the error. **there are still invalid input cases which this parser is not covering yet, if there are issues please open an issue to prove this parser further. I would be happy to hear your feedback**

Supported arithmetic operations by the parser till the monment of writing this docu are **(addition, substraction, multiplication, divison and reminder of division)**  Further arithmetik operations shall be comming soon.

- Fractional numbers are supported
- The user types the string in the terminal
- The program reads the input and prints the result
- The user can organise his string in parentheses. But if the number of parentheses is not correct the program refuses the input
- Spaces between the numbers are allowed

## Workflow (Linux)
- Clone the repository:  
git clone [git@github.com:Abdsaddik/String_Calculator.git](git@github.com:Abdsaddik/String_Calculator.git)
- Change to the directory ../String_Calculator
- make
- ./Calculator
 
**For the time of writing this note: I am still working in my free time on this repo and adding features to it. I will try to publish tags for hopefully "nice working commits"**
## Output Examples in Terminal
> enter a string to be calculated:  
enter 'q' to quit  
(10/5 * 9%7)/2 *3 - (5 - 2 * 3)  
7.000000  
  
> enter a string to be calculated:  
enter 'q' to quit  
10 + ( 10 + 5  
please check your input, you may forgot a parenthesis  

> enter a string to be calculated:  
enter 'q' to quit  
10 10  
invalid input, missing an arithmetic sign  
