#include <iostream>
#include <string>
#include <sstream>
#include <stack>

int precedence(char c)
{
	if (c == '+' || c == '-') return 1;
	else if (c == '*' || c == '/') return 2;
	else if (c == '^') return 3;
	else return 0;
}

bool isoperator(char c)
{
	return 
		c == '+' || 
		c == '*' || 
		c == '/' || 
		c == '-' || 
		c == '(' || 
		c == ')' || 
		c == '^';
}

std::string toPostfix(std::string &exp)
{
	std::string postfix;
	std::stack<char> stack;
	for (char c : exp)
	{
		if (c == ' ')
			continue;
		else if (c == '.')
			postfix += c;
		else if (std::isdigit(c))
			postfix += c;
		else if (isoperator(c))
		{
			postfix += ' ';
			while (!stack.empty() && precedence(stack.top()) >= precedence(c)) 
			{

				postfix += stack.top();
				postfix += ' ';
				stack.pop();
			}
			stack.push(c);
		}
	}
	
	while (!stack.empty())
	{
		postfix += ' ';
		postfix += stack.top();
		stack.pop();
	}

	return postfix;
}

float calc(float n1, float n2, char op)
{
	switch(op)
	{
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		return n1 / n2;
	default:
		return 0.0f;
		break;
	}
}

float eval(std::string &exp)
{
	std::stringstream ss(toPostfix(exp));
	std::string token = "";
	std::stack<float> stack;
	while (ss >> token)
	{
		if (std::isdigit(token[0]))
			stack.push(std::stof(token));
		else if (isoperator(token[0]))
		{
			float num2 = stack.top();
			stack.pop();
			float num1 = stack.top();
			stack.pop();
			stack.push(calc(num1, num2, token[0]));
		}
	}
	return stack.top();
}

int main(int argc, char* argv[])
{
	if (argc < 3) 
	{
		std::cerr << "Usage: " << "-<mode> <expression>" << std::endl;
		return 1;
	}

	std::string mode = argv[1];
	std::string expression = argv[2];

	if (mode == "-e")
	{
		float res = eval(expression);
		std::cout << "Result: " << res << "\n";
	}

	return 0;
}