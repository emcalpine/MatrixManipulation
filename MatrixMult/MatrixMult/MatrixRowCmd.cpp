#include <iostream>
#include <sstream>
#include <cstdlib>
#include "matrix.h"

using namespace std;

void display(Matrix m);

int main()
{

	Matrix myMat;
	string control;
	bool done = false;
	int rows;
	int cols;

	//init matrix;
	cout << "rows:" << endl;
	cin >> rows;
	cout << "cols:" << endl;
	cin >> cols;

	myMat = Matrix(rows, cols);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float val;
			cin >> val;
			myMat.setNumber(r, c, val);
		}
	}

	while (!done)
	{
		display(myMat);

		cout << endl;
		getline(cin, control);
		control += " ";


		//parse control
		string curArgVal = "";
		string operation = "";
		int curArg = 0;
		float arg1;
		float arg2;
		float arg3 = -1.0;
		for (unsigned int i = 0; i < control.length(); i++)
		{
			if (control.at(i) != ' ' && control.at(i) != '\n')
				curArgVal += control.at(i);
			else
			{
				const char* val = curArgVal.c_str();
				switch (curArg)
				{
				case 0:
					operation = curArgVal;
					break;
				case 1:
					arg1 = atof(val);
					break;
				case 2:
					arg2 = atoi(val);
					break;
				case 3:
					arg3 = atoi(val);
				}
				curArg++;
				curArgVal = "";
			}
		}
		if (operation == "swap")
		{
			myMat.rowSwap(arg1, arg2);
		}
		else if (operation == "multiply")
		{
			if (arg3 == -1)
				myMat.rowMult(arg1, arg2);
			else
				myMat.rowMult(arg1, arg2, arg3);
		}
		else if (operation == "quit")
		{
			done = true;
		}
		else
		{
			cout << "\n syntax: \n [operation] [arg1] [arg2] [arg3]\n";
			cout << "opeartions:\n";
			cout << "\tswap:\n\t\trow1\n\t\trow2\n";
			cout << "\tmultiply: (m*r1) / r2+(m*r1)\n\t\tmultiplier\n\t\trow1\n\t\t[row2]\n";
			cout << "\tquit\n\n";
		}

	}
}

void display(Matrix m)
{
	for (int i = 0; i < m.getNumRows(); i++)
	{
		cout << "|\t";
		for (int j = 0; j < m.getNumCols(); j++)
		{
			cout << m.getNumber(i, j) << "\t";
		}
		cout << "|" << endl;
	}
}