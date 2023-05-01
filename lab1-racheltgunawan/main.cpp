// Title: Lab 1 - main.cpp
//
// Purpose: Practice the methods offered by the C++ standard library string class by writing a C++ program
// that reads in an arithmetic expression and prints out a step by step evaluation of the expression.
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson, Carlos Arias

#include "evaluator.h"
#include "test_scripts.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

    double count = ValidateExpressions();

    cout << "Your approximate grade is = " << count << endl;

    ifstream inFS;
    ofstream outFS;

    string inputFile, outputFile;

    cout << "Enter expression input file name: ";
    cin >> inputFile;

    cout << "Enter expression output file name: ";
    cin >> outputFile;

    inFS.open(inputFile);
    outFS.open(outputFile);

    if(!inFS.is_open()){
        cout << "File " << inputFile << " cannot be opened" << endl;
        return 1;
    }
    if(!outFS.is_open()){
        cout << "File" << outputFile << " cannot be opened" << endl;
        return 1;
    }

    string expression;
    while(getline(inFS, expression)){
        if(!inFS.fail()){
            int value;
            bool valid = Evaluate(expression, value);
            string jsonLine = CreateJSONLine(expression, value, !valid);
            outFS << jsonLine << endl;
        }else{
            cout << "Error" << endl;
        }
    }

    inFS.close();
    outFS.close();

    return 0;
}

