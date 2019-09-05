#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool isValidInfixString(string& input);
//return true if the string is valid, false if not
//also remove extraneous ! at the start of an expression
string removeWhitespace(string input);
//returns a string with all whitespace removed
int higherPrecedence(char elem1, char elem2);
//returns -1 if elem1 has lower precedence than elem2
//returns 0 if elem1 and elem2 have same precedence
//returns 1 if elem1 has higher precedence than elem2
bool evaluatePostfix(string& postfix);
//evaluate a given postfix boolean expression
void convertToPostfix(string validStr, string& postfix);
//convert a given infix boolean expression to postfix

int evaluate(string infix, string& postfix, bool& result) {
	// cout << "Before processing: " << infix << endl;
	string spaceRemoved = removeWhitespace(infix); //remove whitespaces
	// cout << "After removing spaces:" << spaceRemoved << endl;	
	if (isValidInfixString(spaceRemoved) == false) { //first check if infix string is valid
		// cout << "Invalid string!" << endl;
		return 1;
	}
	// cout << "Valid string!" << endl;
	string validStr = spaceRemoved;
	//string is now valid
	postfix = "";
	convertToPostfix(validStr, postfix);
	result = evaluatePostfix(postfix);	
	return 0;
}

void convertToPostfix(string validStr, string& postfix) {
	stack<char> operators;
	for (size_t i = 0; i < validStr.size(); i++) {
		char temp = validStr.at(i);
		switch (temp) {
		case 'T':
		case 'F':
			// cout << "Found a T or F" << endl;
			postfix = postfix + temp; //append the operand
			break;
		case '(':
			// cout << "Found a (" << endl;
			operators.push(temp);
			break;
		case ')':
			// cout << "Found a )" << endl;
			while (operators.top() != '(') {
				postfix = postfix + operators.top();
				operators.pop();
			}
			operators.pop(); //removing the (
			break;
		case '!':
			// cout << "Found a !" << endl;
			while (operators.empty() == false && operators.top() != '('
				&& operators.top() != '!'
				&& (higherPrecedence(temp, operators.top()) == -1 || //less than...
					higherPrecedence(temp, operators.top()) == 0)) { //or equal precedence
				postfix = postfix + operators.top();
				operators.pop();
			}
			operators.push(temp);
			break;
		case '^':
		case '&':
			// cout << "Found a ^ or &" << endl;
			while (operators.empty() == false && operators.top() != '('
				&& (higherPrecedence(temp, operators.top()) == -1 || //less than...
					higherPrecedence(temp, operators.top()) == 0)) { //or equal precedence
				postfix = postfix + operators.top();
				operators.pop();
			}
			operators.push(temp);
			break;
		}
	}
	while (operators.empty() == false) {
		postfix = postfix + operators.top();
		operators.pop();
	}
	// cout << "Passed part 1" << endl;
	// cout << "Postfix expression: " << postfix << endl;
}

bool evaluatePostfix(string& postfix) {
	//---------------------------------------
//PART 2: Evaluate the postfix expression
	stack<char> operands;
	char temp = postfix.at(0);
	for (size_t i = 0; i < postfix.size(); i++) {
		if (operands.empty() == false) {
			// cout << "Top of stack is currently " << operands.top() << endl;
		}
		temp = postfix.at(i);
		if (temp == 'T' || temp == 'F') {
			// cout << "Adding operand to stack" << endl;
			operands.push(temp);
		}
		else if ((temp == '^' || temp == '&') && operands.size() >=2 ) {
			char operand2 = operands.top();
			operands.pop();
			char operand1 = operands.top();
			operands.pop();
			char evaluated;
			if (temp == '&') { //AND operator
				// cout << "Evaluating &" << endl;
				if (operand1 == 'T' && operand2 == 'T') {
					evaluated = 'T';
				}
				else {
					evaluated = 'F';
				}
				operands.push(evaluated);
			}
			else if (temp == '^') { //XOR operator
				// cout << "Evaluating ^" << endl;
				if ((operand1 == 'F' && operand2 == 'T') ||
					(operand1 == 'T' && operand2 == 'F')) {
					evaluated = 'T';
				}
				else {
					evaluated = 'F';
				}
				operands.push(evaluated);
			}
		}
		else { //NOT operator
			// cout << "Evaluating !" << endl;
			char operand1 = operands.top();
			operands.pop();
			char evaluated;
			if (operand1 == 'T') {
				evaluated = 'F';
			}
			else if (operand1 == 'F') {
				evaluated = 'T';
			}
			operands.push(evaluated);
		}
	}
	// cout << "Done evaluating! Result is : " << operands.top() << endl;
	if (operands.size() != 1) {
		return false;
	}
	if (operands.top() == 'T') {
		return true;
	}
	return false;
}

string removeWhitespace(string input) {
	string result = "";
	for (size_t i = 0; i < input.size(); i++) {
		if (input.at(i) != ' ') {
			result = result + input.at(i);
		}
	}
	return result;
}

bool isValidInfixString(string& input) {
	if (input.empty() == true) { //not valid if empty
		// cout << "EMPTY STRING" << endl;
		return false;
	}
	int counterOpen = 0;
	int counterClosed = 0;
	for (size_t i = 0; i < input.size(); i++) { //only T, F, ^, &, and ! should be present
		if (input.at(i) != 'T' && input.at(i) != 'F' &&
			input.at(i) != '^' && input.at(i) != '&' &&
			input.at(i) != '!' && input.at(i) != '(' &&
			input.at(i) != ')') {
			// cout << "BAD CHAR FOUND, INVALID EXPRESSION" << endl;
			return false; //stop looping
		}
		if (input.at(i) == '(') {
			counterOpen++;
		}
		if (input.at(i) == ')') { 
			counterClosed++;
		}
	}
	if (counterOpen != counterClosed) {
		//if # of open parentheses is different from close parentheses
		// cout << "MISSING MATCHING PARENTHESES" << endl;
		return false;
	}
	//valid consecutive characters
	for (size_t i = 0; i < input.size() - 1; i++) {
		if ((input.at(i) == 'T' || input.at(i) == 'F') &&
			(input.at(i + 1) == 'T' || input.at(i+1) == 'F')) {
			// cout << "CANNOT HAVE CONSECUTIVE T OR F" << endl;
			return false;
		} //for consecutive T's or F's
		if ((input.at(i) == '^' || input.at(i) == '&') &&
			(input.at(i + 1) == '^' || input.at(i+1) == '&')) {
			// cout << "CANNOT HAVE CONSECUTIVE ^ OR &" << endl;
			return false;
		} //consecutive ^'s or &'s
		if ((input.at(i) == '!') &&
			(input.at(i + 1) == '^' || input.at(i+1) == '&' || input.at(i+1) == ')')) {
			// cout << "! CANNOT BE FOLLOWED BY ^ OR &" OR ) << endl;
			return false;
		} //! should never be followed by & or ^
		if ((input.at(i) == 'T' || input.at(i) == 'F') &&
			(input.at(i + 1) == '(' || input.at(i+1) == '!')) {
			// cout << "T OR F CANNOT BE FOLLOWED BY ( or !" << endl;
			return false;
		}//T or F should never be immediately be followed by a parentheses
		if (input.at(i) == '(' && input.at(i + 1) == ')') {
			// cout << "EMPTY SET OF PARENTHESES FOUND" << endl;
			return false;
		}		
	}
	if (input.at(input.size() - 1) == '(') { //cannot end with (
		return false;
	}
	int index = input.size()-1;
	while (input.at(index) == ')') {
		index--;
	}

	if (input.at(input.size() - 1) == '^' || 
		input.at(input.size() - 1) == '&' || 
		input.at(input.size() - 1) == '!' ||
		input.at(index) == '^' || input.at(index) == '&' || input.at(index) == '!') {
		// cout << "MUST END WITH T OR F" << endl;
		return false;
	}
	if (input.at(0) == '^' || input.at(0) == '&') {
		//cout <<"CANNOT START WITH ^ OR & <<endl;
		return false;
	}
	return true;
}

int higherPrecedence(char elem1, char elem2) {
	//! = 3, & = 2, ^ = 1
	if (elem1 != '!' && elem1 != '&' && elem1 != '^' &&
		elem2 != '!' && elem2 != '&' && elem2 != '^') {
		// cout << "Higher precedence error! Bad values passed" << endl;
		// cout << "Element 1: " << elem1 << " and Element 2: " << elem2 << endl;
		return 2;
	}
	int elem1Eq, elem2Eq;
	if (elem1 == '!') {
		elem1Eq = 3;
	}
	else if (elem1 == '&') {
		elem1Eq = 2;
	}
	else if (elem1 == '^') {
		elem1Eq = 1;
	}
	if (elem2 == '!') {
		elem2Eq = 3;
	}
	else if (elem2 == '&') {
		elem2Eq = 2;
	}
	else if (elem2 == '^') {
		elem2Eq = 1;
	}
	if (elem1Eq == elem2Eq) {
		return 0;
	}
	else if (elem1Eq < elem2Eq) {
		return -1;
	}
	return 1; //that is, if elem1Eq > elem2Eq
}

int main(){	
	string pf;
	bool answer;
	assert(evaluate("T", pf, answer) == 0 && answer == true);
	assert(evaluate("(F)", pf, answer) == 0 && answer == false);
	assert(evaluate("T ^(F)", pf, answer) == 0 && answer == true);
	assert(evaluate("T ^ !F", pf, answer) == 0 && answer == false);
	assert(evaluate("!(T&!!  !!F)", pf, answer) == 0 && answer == true);
	assert(evaluate("!T&F ", pf, answer) == 0 && answer == false);
	assert(evaluate("T^F&F", pf, answer) == 0 && answer == true);
	assert(evaluate("T&! (F^T&T^F  )^!!!(F&T&F)", pf, answer) == 0 && answer == true);
	assert(evaluate("TS DF:L", pf, answer) == 1);
	assert(evaluate("( F^T&!  F)", pf, answer) == 0 && answer == true);
	assert(evaluate("(( F))&((! T))", pf, answer) == 0 && answer == false);
	assert(evaluate("T^!F&T^T^(!F&T^!!T&F)", pf, answer) == 0 && answer == false);
	assert(evaluate("!!(F^T&F)", pf, answer) == 0 && answer == false);
	assert(evaluate("F^!T&T^!F", pf, answer) == 0 && answer == true);	
	assert(evaluate("T&(F^!T&T^!F)&!!(F^T&!F)", pf, answer) == 0 && answer == true);
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	cout << "Passed all tests! Yay!" << endl;
}