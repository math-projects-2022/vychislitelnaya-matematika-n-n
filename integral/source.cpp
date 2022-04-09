#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

double f(double x)
{
	return (
		cos(x)*sin(x)
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
		result1 += f(a + 2*i * ((b - a) / n));
	}
	result1 *= 2;
	for (int i = 1; i <= ((n / 2.0)); i++)
	{
		result2 += f(a + (2*i-1) * ((b - a) / n));
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

	double result = 0;
	double a = 0, b = 0, pg = 0;
	double n = 1000;
	
	int ch = out;
	do {
		cout << "\n\n��� ��������� �������?" << endl
			 << par << " - �������� ��������� ��������������" << endl
			 << rect << " - ��������� �������� ����� ����� ��������������� (c�������� �������)" << endl
			 << trap << " - ��������� �������� ����� ����� �������� (c�������� �������)" << endl
			 << simp << " - ��������� �������� ����� ����� �������� (������� ������)" << endl
			 << out << " - �����" << endl;

		cout << "����: "; cin >> ch;

		switch (ch)
		{
		case par:
			cout << "������� ������ ������: ";
			cin >> a;
			cout << "\n������� ������� ������: ";
			cin >> b;
			cout << "\n������� ������������ ��������� (������ ����� - ������ �����������): ";
			cin >> n;
			break;

		case trap:
			result = trapf(a, b, n, pg);
			cout << "\n" << "���������  = " << result;
			cout << "\n" << "����������� �" << pg;
			break;

		case rect:
			result = rectf(a, b, n, pg);
			cout << "\n" << "���������: " << result;
			cout << "\n" << "�����������: �" << pg;
			break;

		case simp:
			result = simpf(a, b, n, pg);
			cout << "\n" << "���������: " << result;
			cout << "\n" << "�����������: �" << pg;
			break;

		default: ch = out; break;
		}

	} while (ch != out);

	return 0;
}