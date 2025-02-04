﻿#include<string>
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
	string result;
	stack<char> stk;
	char a = '0';
	int k = 0, p, flag = 0;
	int precedence[100];
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] > 39 && s[i] < 48) {
			if (s[i] == '+' || s[i] == '-') {
				precedence[k] = 1;
				k++;
			}
			else if (s[i] == '*' || s[i] == '/') {
				precedence[k] = 2;
				k++;
			}
			else if (s[i] == '(' || s[i] == ')') {
				precedence[k] = 4;
				k++;
			}
			else if (s[i] == '$') {
				precedence[k] = 3;
				k++;
			}
			if (!stk.empty()) {
				a = stk.top();
			}
			if (stk.empty()) {
				stk.push(s[i]);
				continue;
			}
			if (s[i] == '(') {
				stk.push(s[i]);
				continue;
			}
			else if (s[i] == ')') {
				while (a != '(') {
					precedence[k - 1] = NULL;
					k--;
					result += stk.top();
					result += ' ';
					stk.pop();
					precedence[k - 1] = 0;
					k--;
					a = stk.top();
					flag++;
				}
				stk.pop();
				precedence[k - 1] = NULL;
				k--;
				flag = 0;
				continue;
			}
			else if (precedence[k - 2] < precedence[k - 1]) {
				stk.push(s[i]);
				continue;
			}
			else if (precedence[k - 2] > precedence[k - 1] && precedence[k - 2] != 4) {
				int c = k;
				int temp = k;
				while (precedence[c - 2] >= precedence[k - 1] && !stk.empty() && a != '(') {
					if (stk.top() == '(') {
						break;
					}
					result += stk.top();
					result += ' ';
					stk.pop();
					c--;
					precedence[c - 1] = NULL;
					flag++;
				}
				k = temp - flag;
				stk.push(s[i]);
				precedence[k - 1] = precedence[temp - 1];
				precedence[temp - 1] = NULL;
				flag = 0;
				continue;
			}
			else if (precedence[k - 2] == precedence[k - 1]) {
				int c = k;
				int temp = k;
				while (precedence[k - 2] == precedence[k - 1] && !stk.empty()) {
					result += stk.top();
					result += ' ';
					stk.pop();
					c--;
					precedence[c - 1] = NULL;
					flag++;

				}
				k = temp - flag;
				stk.push(s[i]);
				precedence[k - 1] = precedence[temp - 1];
				precedence[temp - 1] = NULL;
				flag = 0;
				continue;
			}
			else {
				stk.push(s[i]);
				continue;
			}
		}
		int temp = i;
		p = i;
		while (s[p] < 58 && s[p]>47) {
			result += s[p];
			p++;
			flag++;
		}
		if (flag != 0) {
			i = temp + flag - 1;
			result += ' ';
			flag = 0;
			continue;
		}
	}
	while (!stk.empty()) {
		result += stk.top();
		result += ' ';
		stk.pop();
	}
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
				continue;
			}
			num2 -= num1;
			k.push(to_string(num2));
		}

	}
	return stoi(k.top());
}