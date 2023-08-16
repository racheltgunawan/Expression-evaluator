# LAB 1 - Evaluating Arithmetic Expressions

## Goal
Practice the methods offered by the C++ standard library string class by writing a C++ program that reads in an arithmetic expression evaluates the expression and finds the result of evaluation the expression. This lab will serve as practice and review of CSC 1230 topics as string class and methods, and file input/output.

The main program will do the following operations:
1. Calls the function `ValidateExpressions` on line 14. This function has been provided for you, and it will test the two functions that you need to implement for this lab. When the function is done, it is going to return a number that represents how many points out of one hundred you get for your tests. This will be most of your lab grade.
2. After the validation part you will write code to:
   1. Read from the keyboard the name of an input file, and then a name of an output file.
   2. Open the input file, report if there was an error (like file not found), if not continue.
   3. For each line on the input file (each line contains an arithmetic expression), you will evaluate the line and output a JSON line into the output file.

When passed an arithmetic expression as a string (`expression`) containing numbers and the binary operators `+`, `-`, `*`, `/`, and `%`, it will return a boolean value indicating if the expression was valid or not. If the expression was valid, the function will set the parameter `value` to what the expression evaluates to. If the expression was not valid, it will set the parameter `value` to zero.

Examples:
```c++
int v;
bool ok =  Evaluate("2+3+4", v);
```
The previous example would assign `true` to `ok` and `v` would have the value `9`.

```c++
int v;
bool ok =  Evaluate("2+3*4", v);
```
The previous example would assign `true` to `ok` and `v` would have the value `14`. Note that the multiplication is evaluated first.

```c++
int v;
bool ok =  Evaluate("2+3+4a", v);
```
The previous example would assign `false` to `ok` and `v` would have the value `0`. Note that the expression is not valid!

Examples

Evaluating `2+5*3-1`
```
Step 1:     2+15-1
Step 2:     17-1
Step 3:     16      Finished
```
Evaluating `4*5+10/2-1`
```
Step 1:     20+10/2-1
Step 2:     20+5-1
Step 3:     25-1
Step 4:     24      Finished
```

Evaluating `12+3*3-4a`
```
Step 1:     12+9-4a
Step 2:     21-4a   Finished
```

Note that the third example did not end on a number! So, the expression was not valid.
