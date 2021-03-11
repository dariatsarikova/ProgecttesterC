#include <iostream>

using namespace std;

void add(double x, double y)
{
	cout << x << "+" << y << "=" << x + y << endl;
}
void subtract(double x, double y)
{
	cout << x << "-" << y << "=" << x - y << endl;
}
void divide(double x, double y)
{
	if (y == 0)
	{
		cout << "not 0" << endl;
	}
	else 
		cout << x << "/" << y << "=" << x / y << endl;
}
void multipluy(double x, double y)
{
	cout << x << "*" << y << "=" << x * y << endl;
}

int main()
{
	char operation;
	double a, b;
	setlocale(LC_ALL, "rus");
	while (true)
	{
		cout << "введите знак операции (+, -, *, /)" << endl;
		cin >> operation;
		cout << "введите два числа" << endl;
		cin >> a >> b;
		if (operation == '+')
		{
			add(a, b); 
		}
		if (operation == '-')
		{
			subtract(a, b);
		}
		if (operation == '/')
		{

			divide(a, b);
		}
		if (operation == '*')
		{
			multipluy(a, b);
		}
	}
}


