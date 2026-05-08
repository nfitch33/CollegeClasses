/*************************************************************************
    These are a couple of functions that are useful in writing
    calculators. The evaluate is given in two forms, allowing for
    either floating point or integer calculators.
      John Dolan			Spring 2014
*************************************************************************/

#include <cstdlib>
#include <iostream>
#include <stack>

double evaluate(double num1, double num2, char op);
int evaluate(int num1, int num2, char op);
bool isop(char op);

// Finish this function
void EvaluateExpression(std::istream& ins, std::ostream& outs);