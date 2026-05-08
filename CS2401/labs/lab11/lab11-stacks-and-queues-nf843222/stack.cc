/*************************************************************************
   The implementations of the calculator-useful functions
	John Dolan			Spring 2014
*************************************************************************/

#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

bool isop(char op){
    return op =='+' || op == '-' || op == '*' || op == '/';
}

int evaluate(int num1, int num2, char op){
    if(op == '+') return num1 + num2;
    if(op == '-') return num1 - num2;
    if(op == '*') return num1 * num2;
    if(op == '/') return num1 / num2;
    else return 0;
}

double evaluate(double num1, double num2, char op){
    if(op == '+') return num1 + num2;
    if(op == '-') return num1 - num2;
    if(op == '*') return num1 * num2;
    if(op == '/') return num1 / num2;
    else return 0;
}

//Finish this function
void EvaluateExpression(std::istream& ins, std::ostream& outs){
    char c;
	int onenum, twonum;
	stack <int>nums;     //define a stack called "nums" here

	if(&outs == &cout)
		outs << "Please enter your expression:\n";

	c = ins.get(); // priming read for the sentinel loop.
	while(c != '\n'){
		if(isdigit(c)){
			ins.putback(c);
			ins >> onenum;
			nums.push(onenum);  // stack operation here.
		}
		else if(isop(c)){
			if(!(nums.empty())){
				twonum = nums.top();
				nums.pop();
				if(!(nums.empty())){
					onenum = nums.top();
					nums.pop();
					nums.push(evaluate(onenum, twonum, c));
				}
				else{
					outs << "Error: Expression doesn't contain enough numbers.\n";
					return;
				}
// pop two numbers from the stack
// evaluate them using the evaluate from stack_useful
// push result onto the stack
			}
			else{
				outs << "Error: Expression doesn't contain enough numbers.\n";
				return;
			}
		}

		c = ins.get(); // reading at the bottom of the sentinel loop
	} // bottom of the loop that reads a single expression from the keyboard

	if(nums.empty()){
		outs << "Error: Incorrect amount of numbers entered" << endl;
	}
	else{
		onenum = nums.top();
		nums.pop();
		if(nums.empty()){
			outs << "Result: " << onenum << endl;
		}
		else{
			outs << "Error: Incorrect amount of numbers entered." << endl;
		}
	}
	// output the final result from the top of the stack
	// but only after you check to make sure there's something on the stack
	// outs << "Error: Incorrect amount of numbers entered\n";
	// outs << "Result: " << result << endl;
}