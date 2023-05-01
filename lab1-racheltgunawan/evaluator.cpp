/*
  Title:    Lab 1 – evaluator.cpp
  Purpose:  implement the Evaluate and CreateJSONLine functions
            called by the main program to generate the JSON file
            with the evaluation of arithmetic expressions.
  Author:   Rachel Gunawan
  Date:     January 22, 2020
*/
#include "evaluator.h"

#include <cassert>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

/** GetNumber takes the params
  * @param expression the expression string
  * @param index the index of the operator
  * @param increment if taking the left operand, increment = -1. if taking the right, increment = +1
  *
  * function @return a string value that contains the number.
  *
  * the for loop starts at the index of the operator and will increment/decrement if number being retrieved
  * is the left or right operand. appends the number to variable num until loop reaches a char that is not
  * a number.
  */
string GetNumber(string& expression, int index, int increment){
    string num = "";
    while(isdigit(expression[index + increment]) && index >= 0 && index < expression.length()){
        num += expression[index + increment];
        index += increment;
    }
    if(expression[0] == '-' && increment == -1) // appends negative if there is a negative at the beginning
        num += '-';
    return num;
}

/**
 * ReverseString takes the
 * @param expression the expression string
 */
void ReverseString(string& expression){
    int length = expression.length();
    for (int i = 0; i < length / 2; i++)
        std::swap(expression[i], expression[length - i - 1]);
}

/**
 * GetOperands retrieves the operands on both sides of the operator by calling the GetNumber.
 * @param expression expression string
 * @param index index of the operator
 * @param leftNumber passed by reference to store left operand
 * @param rightNumber passed by reference to store right operand
 */
void GetOperands(string expression, int index, string& leftNumber, string& rightNumber){
    leftNumber = GetNumber(expression, index, -1);
    ReverseString(leftNumber);
    rightNumber = GetNumber(expression, index, 1);
}

/**
 * NotValid checks if the number passed is valid.
 * @param num number string
 * @return true if the number has a letter in it and false if valid
 */
bool NotValid(string num){
    for(int i = 0; i < num.length(); i++){
        if(isalpha(num[i]))
            return true;
    }
    return false;
}

/**
 * DoOperations processes the left and right operands at a specific operator. first retrieves numbers with
 * GetOperands function, checks if valid, and then does operations based on the operator found at @param index.
 * also checks if number is valid. if not, returns error. if valid, returns new expression
 * @param exp passed by reference. string expression
 * @param index index at which the operator is found
 * @return error if error found and the expression if valid
 */
string DoOperations(string& exp, int index) {
    string left, right;
    GetOperands(exp, index, left, right);

    if(NotValid(left) || NotValid(right)|| left == "" || right == ""){
        return "error";
    }else{
        int result;
        if(exp[index] == '/'){
            result = stoi(left) / stoi(right);
        }else if(exp[index] == '*'){
            result = stoi(left) * stoi(right);
        }else if(exp[index] == '%'){
            result = stoi(left) % stoi(right);
        }else if(exp[index] == '+'){
            result = stoi(left) + stoi(right);
        }else if(exp[index] == '-'){
            result = stoi(left) - stoi(right);
        }
        exp = exp.replace(index - left.length(), 1 + left.length() + right.length(), std::to_string(result));
        return exp;
    }

}

/**
 * SmallestIndex retrieves the smallest index of where the *, /, and % operators are found
 * @param arr contains integers of the indexes of *, /, %.
 * @return the int of the smallest index
 */
int SmallestIndexPEMD(int arr[], string exp){
    arr[0] = exp.find('*');
    arr[1] = exp.find('/');
    arr[2] = exp.find('%');
    int smallest = arr[0];
    for(int i = 1; i < 3; i++){
        if(smallest == -1){
            smallest = arr[i];
        }else{
            if(arr[i] != -1 && arr[i] < smallest)
                smallest = arr[i];
        }
    }
    return smallest;
}

/**
 * SimplifyExpressionPEMD handles the beginning of PEMDAS (except in this case we have *, /, %)
 * first finds the first occurrence of the operators through the function SmallestIndex
 * and then calls DoOperators. continues until no more of the operators found in expression
 * @param exp passed by reference to change expression
 * @return true if was able to complete expression
 */
bool SimplifyExpressionPEMD(string& exp){
    int arr[3];
    int *arr2 = arr;
    int smallest = SmallestIndexPEMD(arr2, exp);
    while(smallest != -1){
        exp = DoOperations(exp, smallest);
        if(exp == "error")
            return false;
        smallest = SmallestIndexPEMD(arr2, exp);
    }
    return true;
}

/**
 * SmallestIndex retrieves the smallest index of where the + and - operators are found
 * @param exp is the string expression
 * @return the int of the smallest index
 */

int SmallestIndexAS(string& exp){
    int iadd = exp.find('+');
    int isubtract = exp.find('-');
    if(isubtract == 0)
        isubtract = exp.substr(1).find('-') + 1;
    int smallest = iadd;
    if(smallest == -1){
        smallest = isubtract;
    }else{
        if(isubtract != -1 && isubtract < iadd)
            smallest = isubtract;
    }
    return smallest;
}

/**
 * SimplyExpressionAS takes care of the AS part of PEMDAS.
 * @param exp expression passed by reference
 * @return true if able to finish the operation, and false if unable
 */
bool SimplifyExpressionAS(string& exp){
    int smallest = SmallestIndexAS(exp);
    while(smallest != -1 && smallest != 0){
        exp = DoOperations(exp, smallest);
        if(exp == "error")
            return false;
        smallest = SmallestIndexAS(exp);
    }
    return true;
}

/**
 * This function takes in an arithmetic expression, the function returns the value
 * that the expression evaluates to, that is if the expression is correctly formatted.
 * The operators the expression can have are: +, -, *, /, %
 * The expression doesn't have any spaces between its parts
 * Examples:
 *      2+3*5
 *      2*3+4/2
 * The function will evaluate *, / and % first left to right, and then + and - left to right.
 * For instance 2+3*5, would evaluate 3*5 first resulting in 2+15, and this one resulting in 17.
 * Expressions can be malformed. Example:
 *      4*2+3a
 * In this case the expression would evaluate to 8+3a and would not be able to move from there.
 * Two possible errors:
 *      Division by zero -- let your program crash in this case
 *      Overflow -- let the logic error
 * @param expression the string containing the arithmetic expression
 * @param value The value of evaluating the expression, or zero if the expression was malformed
 * @return true indicating that everything was OK, false otherwise.
 */
bool Evaluate(const string& expression, int& value){
    string exp = expression;
    if(!SimplifyExpressionPEMD(exp)){
        value = 0;
        return false;
    }else{
        if(!SimplifyExpressionAS(exp)){
            value = 0;
            return false;
        }else{
            value = stoi(exp);
            return true;
        }
    }
}

/**
 *  Creates a JSON line given the expression that was been evaluated, the value that
 *  resulted from the evaluation and whether there was an error or not.
 *  Given the following function call:
 *  CreateJSONLine("2+5*3", 17, false)
 *  The resulting JSON (the string returned by the function) would be:
 *  {"expr":"2+5*3", "result":17, "error":false}
 * @param expression The arithmetic expression that was recently evaluated
 * @param result the result of executing the arithmetic expression
 * @param error indicates whether or not the expression wasn't valid, and therefore unable to be
 *              evaluated.
 * @return a JSON string containing the fields: expr, result and error, set with the values sent
 *          as parameter.
 */
string CreateJSONLine(const string& expression, int result, bool error){
    string iserror = (error) ? "true" : "false";
    return "{\"expr\":\"" + expression + "\", \"result\":" + std::to_string(result) + ", \"error\":" + iserror + "}";
 }