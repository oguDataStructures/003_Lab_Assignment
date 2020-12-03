#include <string>
#include<stack>
#include<iostream>
#include<sstream>
using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string& s) {
	// Fill this in
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	stack<char> k;
	k.push('0');
	int i = 0;
	string const delims{ "-+/*()" };
	size_t beg, pos = 0;
	string stringNumber;
	string nums;
	while ((beg = s.find_first_not_of(delims, pos)) != string::npos) {
		pos = s.find_first_of(delims, beg + 1);
		stringNumber = s.substr(beg, pos - beg);
		if (stringNumber == "") continue;
		nums += stringNumber + ' ';
		if (s[pos] == '*') {
			char num1 = k.top();
			if (num1 == '+' || num1 == '-') {
				k.push(s[pos]);
			}
		}
		else if (s[pos] == '/') {
			char num1 = k.top();
			if (num1 == '+' || num1 == '-') {
				k.push(s[pos]);
			}
		}
		else if (s[pos] == '+') {
			char num1 = k.top();
			if (num1 == '0') {
				k.push(s[pos]);
			}
			if (num1 == '*' || num1 == '/') {
				k.pop();
				nums += num1;
				nums+=' ';
			}
			else if (num1 == '+' || num1 == '-') {
				k.push(s[pos]);
			}
		}
		else if (s[pos] == '-') {
			char num1 = k.top();
			if (num1 == '*' || num1 == '/') {
				k.pop();
				nums += num1;
				nums += ' ';
			}
			else if (num1 == '+' || num1 == '-') {
				k.push(s[pos]);
			}
		}
		else if (s[pos] == '(') {
			k.push('(');
		}
		else if (s[pos] == ')')
		{
			while (k.top() != '0' && k.top() != '(')
			{
				char c = k.top();
				k.pop();
				nums += c;
				nums += ' ';
			}
			if (k.top() == '(')
			{
				char c = k.top();
				k.pop();
			}
		}
		i++;
	}
	string result;

	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	stack<string> k;
	stringstream ss(s);
	string stringNumber;
	while (getline(ss, stringNumber, ' '))
	{
		if (stringNumber == "") continue;
		cout << stringNumber << "" << endl;
		if (stringNumber != "*" && stringNumber != "/" && stringNumber != "+" && stringNumber != "-") {
			k.push(stringNumber);
		}
		else if (stringNumber == "*") {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			num1 *= num2;
			k.push(to_string(num1));
		}
		else if (stringNumber == "/") {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			if (num1 < num2)
			{
				num2 /= num1;
				k.push(to_string(num2));
			}
			else
			{
				num1 /= num2;
				k.push(to_string(num1));
			}


		}
		else if (stringNumber == "+") {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			num1 += num2;
			k.push(to_string(num1));
		}
		else {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			if (num1 < num2)
			{
				num2 -= num1;
				k.push(to_string(num2));
			}
			else
			{
				num1 -= num2;
				k.push(to_string(num1));
			}
		}

	}
	return stoi(k.top());





} // end-EvaluatePostfixExpression










  /*stack<string> k;
	stringstream ss(s);
	string stringNumber;
	while (ss)
	{
		ss >> stringNumber;
		if (stringNumber == " ") break;
		if (stringNumber != "*" && stringNumber != "/" && stringNumber != "+" && stringNumber != "-") {
			k.push(stringNumber);
		}
		else if (stringNumber == "*") {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			num1 *= num2;
			k.push(to_string(num1));
		}
		else if (stringNumber == "/") {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			num1 /= num2;
			k.push(to_string(num1));
		}
		else if (stringNumber == "+") {
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			num1 += num2;
			k.push(to_string(num1));
		}
		else{
			int num1 = stoi(k.top());
			k.pop();
			int num2 = stoi(k.top());
			k.pop();
			num2 -= num1;
			k.push(to_string(num1));
		}

	}
	return 0;*/