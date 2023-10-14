# sudoku
Bob Bjorklund and Simon Blamo CSC345 project 2

C project to validate sudoku solution 3 ways, and explore speed differences of the different methods
>methods implemented are:
>
>3 threads, one for columns, one for rows, and one for squares  
>27 threads, one for each row, column, and square  
>3 processes, one for columns, one for rows, and one for squares  

Usage: command line argument 1, 2, or 3  
store potential solution in "input.txt" formatted 9 lines of space separated integers ie "1 2 3 4 5 6 7 8 9"  
1 runs 3 threads  
2 runs 27 threads  
3 runs 3 processes  
