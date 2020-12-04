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
	s.erase(remove(s.begin(), s.end(), ' '), s.end()); //remove spaces

	string const delims = "-+/*";
	size_t nMatchedPos, pos = 0;
	stack<char> S;
	int i = 0;
	int weight[100] = { -1 };
	int flag = 0;
	string result;
	while ((nMatchedPos = s.find_first_not_of(delims, pos)) != string::npos) { //Find non-matching character in string from the end and return position of character

		pos = s.find_first_of(delims, nMatchedPos + 1);//s.find_first_of(delims, pos) finds the first occurrence of one of the characters in delims
		string stringNumber = s.substr(nMatchedPos, pos - nMatchedPos);//Substract characters starting by  un-matched character (2) to matched character (+) in s string

		if (s[nMatchedPos] == '(') {
			S.push(s[nMatchedPos]);
			stringNumber = s.substr(nMatchedPos + 1, pos - nMatchedPos - 1);
			result = result + " " + stringNumber;
			flag = 1;
		}
		else if (s[nMatchedPos + 1] == ')') {
			result = result +" "+ s[nMatchedPos];
			while (S.top() != '(') {
				result = result + " " + S.top();
				S.pop();
			}
			S.pop();
			flag = 1;
		}
		else {
			result = result +" "+ stringNumber;
		}
		if (pos < s.length()) {
			switch (s[pos])
			{
			case '+':
				weight[i] = 1;
				break;
			case '-':
				weight[i] = 1;
				break;
			case '*':
				weight[i] = 2;
				break;
			case '/':
				weight[i] = 2;
				break;
			case '$':
				weight[i] = 3;
				break;
			default:
				weight[i] = 0;
			}
			if (s[pos])
			{
				int k = i;
				while (!S.empty() && S.top() != '(' && i > 0 && weight[i - 1] >= weight[i])
				{
					result = result +" "+ S.top();
					S.pop();
					//weight[k] = 0;
					k--;//k azaltmak ne işe yarıyor
				}
				S.push(s[pos]);
			}
			i++;//Ne işe yarıyor?
		}
		else {
			while (!S.empty()) {
				result = result + " " + S.top();
				S.pop();
			}
		}

		// If character is operator, pop two elements from stack, perform operation and push the result back.

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





} // end-EvaluatePostfixExpression
/*
	s.erase(remove(s.nMatchedPosin(), s.end(), ' '), s.end());
	stack<char> k;
	k.push('0');
	int i = 0;
	string const delims{ "-+/*()" };
	size_t beg, pos = 0;
	string stringNumber;
	string nums;
	int weight[100];
	string result;

	while ((beg = s.find_first_not_of(delims, pos)) != string::npos) {
		pos = s.find_first_of(delims, beg + 1);
		stringNumber = s.substr(beg, pos - beg);
		switch (s[pos])
		{
		case '+':
		case '-':
			weight[i] = 1;
		case '*':
		case '/':
			weight[i] = 2;
		case ')':
			weight[i] = 3;
		case '0':
			weight[i] = 4;
		}
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
			while (k.top() != '0' && k.top() != '(' &&weight[i-1]>weight[i])
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

	return result;
*/






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