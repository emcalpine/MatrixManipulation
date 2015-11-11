#include <iostream>
#include <sstream>
#include <cstdlib>
#include "matrix.h"

using namespace std;

const float ERROR = 0.000005;

void display(Matrix m);
void newMat(Matrix* &a, int i);
void addOneMat(Matrix* &a, int n);

int main()
{

	Matrix* ary;
	string control;
	bool done = false;
	int curMat = 0;
	int numMats = 1;

	//init array
	ary = new Matrix[numMats];
	cout << "Starting with 1 matrix\n";
	newMat(ary, curMat);	//init first matrix


	while (!done)
	{
		display(ary[curMat]);

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
		//************************
		//	Parse command
		//************************
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

		//****************************
		//	Operation switch
		//****************************
		if (operation == "swap")
		{
			ary[curMat].rowSwap(arg1, arg2);
		}
		else if (operation == "rm")
		{
			if (arg3 == -1)
				ary[curMat].rowMult(arg1, arg2);
			else
				ary[curMat].rowMult(arg1, arg2, arg3);
		}
		else if (operation == "mult")
		{
			//bounds check for 2 source matricies
			if (arg1 >= 0 && arg1 < numMats && arg2 >= 0 && arg2 < numMats)
			{
				//check bounds for dest
				if (arg3 >= 0 && arg3 < numMats)
					ary[(int)arg3] = ary[(int)arg1].smartMultiply(ary[(int)arg2]);
				else if (abs(arg3-numMats) < ERROR)
				{
					addOneMat(ary, numMats++);
					ary[(int)arg3] = ary[(int)arg1].smartMultiply(ary[(int)arg2]);
				}
				else
					cout << "\n\n***** Invalid desitnation index *****\n\n";
			}
		}
		else if (operation == "create")
		{
			//bounds check
			if (arg1 >= 0 && arg1 < numMats)
			{
				newMat(ary, (int)arg1);
			}
			else if (abs(arg1-numMats) < ERROR)	//arg1 == numMats
			{
				addOneMat(ary, numMats);
				newMat(ary, numMats);
				numMats++;
			}
		}
		else if (operation == "switch")
		{
			//switch to valid index, else stay same
			curMat = (arg1 >= 0 && arg1 < numMats) ? arg1 : curMat;
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
			cout << "\trm: (m*r1) / r2+(m*r1)\n\t\tmultiplier\n\t\trow1\n\t\t[row2]\n";
			cout << "\tmult\n\t\tmatrix 1\n\t\tmatrix2\n\t\tdestination index\n";
			cout << "\tcreate\n\t\tindex\n";
			cout << "\tswitch\n\t\tindex\n";
			cout << "\tquit\n\n";
		}

	}

	delete[] ary;
}

// Print out matrix
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

//**************************
//	create new matrix at index i
//**************************
void newMat(Matrix* &a, int i)
{
	int rows;
	int cols;

	cout << "rows:" << endl;
	cin >> rows;
	cout << "cols:" << endl;
	cin >> cols;

	//error checking
	rows = (rows >0) ? rows : 1;
	cols = (cols > 0) ? cols : 1;

	a[i] = Matrix(rows, cols);

	//init values
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float val;
			cin >> val;
			a[i].setNumber(r, c, val);
		}
	}

}

//<param> n current size
void addOneMat(Matrix* &a, int n)
{
	Matrix* temp = new Matrix[n + 1];
	for (int i = 0; i < n; i++)
	{
		temp[i] = a[i];
	}
	delete[] a;
	a = temp;
}