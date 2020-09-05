# String_Calculator

This program parses arithmetic input **(only addition, substraction, multiplication and divison)** from terminal and calculates the result. 

- Fractional numbers are supported
- The user types the string in the terminal
- The program reads the input and  prints the result
- The user can organise his string in parentheses. But if the number of parentheses is not correct the program refuses the input
- Spaces between the numbers are allowed

## Workflow (Linux)
- Clone the repository:  
git clone [git@github.com:Abdsaddik/String_Calculator.git](git@github.com:Abdsaddik/String_Calculator.git)
- Change to the directory ../String_Calculator
- make
- ./Calculator
 
**For the time of writing this note: I am still working in my free time on this repo and adding features to it. I will try to publish tags for hopefully "nice working commits"**
## Output Examples
> enter a string to be calculated:  
enter 'q' to quit  
10 + ( 10  - ( -10 + 15) - (-15 + 5)) - ( 10 + 5 )  
10.000000  
  
> enter a string to be calculated:    
enter 'q' to quit  
10 + (10 - 5) - ( 7 - 3 )  
11.000000  

> enter a string to be calculated:  
enter 'q' to quit  
10 + ( 10 + 5  
please check your input, you may forgot a parentheses  

> enter a string to be calculated:  
enter 'q' to quit  
100 * 2 / 4 + 5 - 10  
45.000000  

> enter a string to be calculated:  
enter 'q' to quit  
10 * (100/4) - ( 10 + 5)  
235.000000  

