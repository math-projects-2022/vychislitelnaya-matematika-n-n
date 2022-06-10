#include <iostream>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <random>

using namespace std;

double f2(double x, double y)
{
	return x + y;              //заменяемая функция для дифференциального уравнения
}

double f(double x)
{
	return (
		cos(x) * sin(x)        //заменяемая функция для интеграла
		);
}

double trapf(double& a, double& b, double& n, double& pg)
{
	static double result = ((f(a) / 2.0) * ((1.0 / n) * (b - a))) + ((f(b) / 2.0) * ((1.0 / n) * (b - a)));
	for (int i = 1; i < n; i++)
	{
		result += f((b - a) * (i / n) + a) * ((1 / n) * (b - a));
	}

	pg = (b - a) / n;
	return result;
}

double rectf(double& a, double& b, double& n, double& pg)
{
	static double result = 0;
	for (int i = 0; i < n; i++)
	{
		result += f(a + i * ((b - a) / n)) * ((b - a) / n);
	}

	pg = (b - a) / n;
	return result;
}

double simpf(double& a, double& b, double& n, double& pg)
{
	static double result = f(a) + f(b), result1 = 0, result2 = 0;
	for (int i = 1; i <= ((n / 2.0) - 1); i++)
	{
		result1 += f(a + 2 * i * ((b - a) / n));
	}
	result1 *= 2;
	for (int i = 1; i <= ((n / 2.0)); i++)
	{
		result2 += f(a + (2 * i - 1) * ((b - a) / n));
	}
	result2 *= 4;
	result += result1 + result2;
	result *= ((b - a) / n) / 3.0;

	pg = (b - a) / n;
	return result;
}

enum
{
	par,
	rect,
	trap,
	simp,
	out
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int zxc;
	cout << "Посчитать интеграл - 1" << endl;
	cout << "Посчитать дифференциальное уравнение - 2" << endl;
	cin >> zxc;
	if (zxc != 1 and zxc != 2) // and - и
		zxc = rand() % 2 + 1;

	switch (zxc)
	{
	case 1:
	{
		double result = 0;
		double a = 0, b = 0, pg = 0;
		double n = 1000;

		int ch = out;
		do {
			cout << "\n\nЧто требуется сделать?" << endl
				<< par << " - изменить параметры интегрирования" << endl
				<< rect << " - посчитать интеграл через метод прямоугольников (cоставная формула)" << endl
				<< trap << " - посчитать интеграл через метод трапеций (cоставная формула)" << endl
				<< simp << " - посчитать интеграл через метод Симпсона (формула Котеса)" << endl
				<< out << " - выход" << endl;

			cout << "Ввод: "; cin >> ch;

			switch (ch)
			{
			case par:
				cout << "Введите нижний предел: ";
				cin >> a;
				cout << "\nВведите верхний предел: ";
				cin >> b;
				cout << "\nВведите количествово разбиений (больше число - меньше погрешность): ";
				cin >> n;
				break;

			case trap:
				result = trapf(a, b, n, pg);
				cout << "\n" << "Результат  = " << result;
				cout << "\n" << "Погрешность ±" << pg;
				break;

			case rect:
				result = rectf(a, b, n, pg);
				cout << "\n" << "Результат: " << result;
				cout << "\n" << "Погрешность: ±" << pg;
				break;

			case simp:
				result = simpf(a, b, n, pg);
				cout << "\n" << "Результат: " << result;
				cout << "\n" << "Погрешность: ±" << pg;
				break;

			default: ch = out; break;
			}

		} while (ch != out);
		break;
	}
	case 2:
	{
		float x0, y0, xn, h, yn, slope;
		int i, n;

		cout << "Введите начальное условие" << endl;
		cout << "x0 = ";
		cin >> x0;
		cout << "y0 = ";
		cin >> y0;
		cout << "Введите расчетную точку xn = ";
		cin >> xn;
		cout << "Введите количество шагов: ";
		cin >> n;

		h = (xn - x0) / n;

		cout << "\nx0\ty0\tslope\tyn\n";
		cout << "------------------------------\n";

		for (i = 0; i < n; i++)
		{
			slope = f2(x0, y0);
			yn = y0 + h * slope;
			cout << x0 << "\t" << y0 << "\t" << slope << "\t" << yn << endl;
			y0 = yn;
			x0 = x0 + h;
		}

		cout << "\nЗначение y при x = " << xn << ": " << yn << endl;
		break;
	}
	}
	system("pause");
	return 0;
}