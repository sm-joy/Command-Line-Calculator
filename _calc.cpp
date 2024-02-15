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

inline bool isoperator(char c)
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
		else
		{
			std::cerr << "Invalid Argument\n";
			return "error";
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
	std::string postfixed = toPostfix(exp);
	if (postfixed != "Error")
	{
		std::stringstream ss(postfixed);
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
	else
	{
		std::cout << "Invalid Argument\n";
		return 0;
	}
}

long long factorial(int n)
{
	if (n == 0 || n == 1) return 1;
	else return n * factorial(n - 1);
}


int main(int argc, char* argv[])
{


	if (argc < 2)
	{
		std::cerr << "Usage: " << "-<mode> <expression>\n\nType [_calc -h] or [_calc -help]" << "\n";
		return -1;
	}

	if (argv[1] == "-h")
	{
		std::cout << "";
	}
	else if (argv[1] == "-fac")
	{
		if (argc < 3)
		{
			std::cerr << "Invalid Argument" << "\n";
			return -1;
		}
		else
		{
			std::string number = argv[2];
			int num = std::stoi(number);
			if (num < 0)
			{
				std::cerr << "Invalid Argument\n";
				return -1;
			}
			else
			{
				long long res = factorial(num);
				std::cout << "Result: " << res << "\n";
			}
		}
	}
	else if (argv[1] == "-e")
	{
		std::string expression = argv[2];
		float res = eval(expression);
		if (res == static_cast<int>(res))
			std::cout << "Result: " << static_cast<int>(res) << "\n";
		else
			std::cout << "Result: " << res << "\n";
	}

	return 0;
}