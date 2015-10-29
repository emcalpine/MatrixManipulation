/*  Eric McAlpine
 *	header file for a matrix object
 *	I was also going to overload the * operator, but
 *	syntactic problems were encountered, and frustration won
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <string.h>

class Matrix{
private:
	float* ary;
	float marginOfError;
	int size, rows, cols;
	int tileSize;
	void multiplyATile(const Matrix& mat2, Matrix& dest, int rStart, int rEnd, int cStart, int cEnd, int qStart, int qEnd);
public:
	Matrix(); //constructor
	Matrix(int rows, int cols); //size argumented constructors
	Matrix(const Matrix& mat2);
	Matrix& Matrix::operator=(const Matrix& mat2);
	~Matrix();

	int getNumRows();
	int getNumCols();

	void invert(); //flips rows/cols  (makes multiplication easy)
	void setNumber(int r, int c, float val);
	void setMarginOfError(float newMoe);
	void setTileSize(int size);
	float getNumber(int r, int c);
	Matrix tileMultiply(const Matrix& mat2);
	Matrix naiveMultiply(const Matrix& mat2);
	Matrix smartMultiply(const Matrix& mat2);
	Matrix invertedMultiply(const Matrix& mat2);
	bool equals(const Matrix& mat2);

	void rowSwap(int r1, int r2);
	void rowMult(float coef, int r1);
	void rowMult(float coef, int r1, int r2);

};
#endif