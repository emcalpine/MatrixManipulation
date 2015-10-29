/*	Eric McAlpine
 *	Matrix object implementation file
 */


#include <cstdlib>
#include <string.h>
#include "matrix.h"

using namespace std;

Matrix::Matrix(){	//no-arg constructor
	rows=10;
	cols=10;
	size=100;
	marginOfError=0.00005;
	ary=new float[size];
}

Matrix::Matrix(int newRows, int newCols){
	rows=newRows;
	cols=newCols;
	marginOfError=0.00005;
	if(newRows<1)		//check for proper size
		rows=1;
	if(newCols<1)
		cols=1;
	size=rows*cols;		//assign size
	ary=new float[size];	//create array
}

//deconstructor
Matrix::~Matrix(){
	delete [] ary;
}


//copy constructor
Matrix::Matrix(const Matrix& mat2){
	this->rows=mat2.rows;
	this->cols=mat2.cols;
	this->size=mat2.size;
	this->marginOfError=mat2.marginOfError;
	this->ary= new float[this->size];
	for(int i=0; i<size; i++)
		this->ary[i]=mat2.ary[i];
}

//assignment operator overload
Matrix& Matrix::operator=(const Matrix& mat2){
	if(!(this == &mat2)){
		this->rows=mat2.rows;			//assign automatic variables
		this->cols=mat2.cols;
		this->size=mat2.size;
		this->marginOfError=mat2.marginOfError;
		delete [] this->ary;
		this->ary=new float [this->size];	//copy over dynamic array
		for(int a=0; a<this->size; a++)
			this->ary[a]=mat2.ary[a];
	}
	return *this;
}



void Matrix::setTileSize(int size){
	if(size>0)
		tileSize=size;
	else
		tileSize=1;
}

void Matrix::setNumber(int r, int c, float val){
	if(r>=0 && c>=0 && r<rows && c<cols)	//check for valid address
		ary[r*cols+c]=val;		//dont care about the value (their problem)

}

void Matrix::setMarginOfError(float newMoE){
	if(newMoE>0)
		marginOfError=newMoE;
	else
		marginOfError=-newMoE;
}

float Matrix::getNumber(int r, int c){
	return ary[r*cols+c];
}


Matrix Matrix::naiveMultiply(const Matrix& mat2){//***********naiveMultiply
	Matrix temp= Matrix(this->rows, mat2.cols);
	for(int r=0; r<this->rows; r++){
		for(int c=0; c<mat2.cols; c++){
			temp.ary[r*temp.cols+c]=0.0;
			for(int k=0; k<this->cols; k++)
				temp.ary[r*temp.cols+c]+=this->ary[r*this->cols+k]*mat2.ary[k*mat2.cols+c];
		}
	}
	return temp;
}

Matrix Matrix::smartMultiply(const Matrix& mat2){//**************smartMultiply
	Matrix temp= Matrix(this->rows, mat2.cols);
	for(int r=0; r<this->rows; r++)		//seperate loop to assign values
		for(int c=0; c<mat2.cols; c++)
			temp.ary[r*temp.cols+c]=0.0;
	for(int r=0; r<this->rows; r++){
		for(int k=0; k<this->cols; k++){		//flips the inner-most loops
			for(int c=0; c<mat2.cols; c++){		//uses cache more efficiently (less memory access)
				temp.ary[r*temp.cols+c]+=this->ary[r*this->cols+k]*mat2.ary[k*mat2.cols+c];
			}
		}
	}
	return temp;
}

Matrix Matrix::invertedMultiply(const Matrix& mat2){//***********inverted swap, same as naive swap
	Matrix temp= Matrix (this->rows, mat2.rows);//		but built for 2nd matrix inverted
	for(int r=0; r<this->rows; r++){
		for(int c=0; c<mat2.cols; c++){					//                        ||
			temp.ary[r*temp.cols+c]=0.0;				//                        ||
			for(int k=0; k<this->cols; k++){			//the c/k for the 2nd ary \/ are swapped
				temp.ary[r*temp.cols+c]+=this->ary[r*this->cols+k]*mat2.ary[c*mat2.cols+k];
			}
		}
	}
	return temp;
}

Matrix Matrix::tileMultiply(const Matrix& mat2){
	Matrix temp= Matrix(this->rows, mat2.cols);
	for(int i=0; i<(this->rows*mat2.cols); i++)//zero out destination
		temp.ary[i]=0.0;
	int rStart, rEnd, cStart, cEnd, qStart, qEnd;
	for(rStart=0; rStart<this->rows; rStart+=tileSize){
		rEnd=rStart+tileSize-1;
		if(rEnd>=this->rows)//double check bounds
			rEnd=this->rows-1;
		for(qStart=0; qStart<this->cols; qStart+=tileSize){
			qEnd=qStart+tileSize-1;
			if(qEnd>=this->cols)//bounds check
				qEnd=this->cols-1;
			for(cStart=0;cStart<mat2.cols;cStart+=tileSize){
				cEnd=cStart+tileSize-1;
				if(cEnd>=mat2.cols)//bounds check
					cEnd=mat2.cols-1;
				multiplyATile(mat2,temp,rStart,rEnd,cStart,cEnd,qStart,qEnd);
			}//c
		}//q
	}//r
	return temp;
}

void Matrix::multiplyATile(const Matrix& mat2, Matrix& dest, int rStart, int rEnd, int cStart, int cEnd, int qStart, int qEnd){
	int r,c,q;
	for(r=rStart; r<=rEnd; r++){
		for(q=qStart; q<=qEnd; q++){
			for(c=cStart; c<=cEnd; c++){
				dest.ary[r*dest.cols+c]+=this->ary[r*this->cols+q]*mat2.ary[q*mat2.cols+c];
			}
		}
	}
	return;
}

bool Matrix::equals(const Matrix& mat2){
	bool diff=true;		//assume they are the same
	if(this->size!=mat2.size || this->rows!=mat2.rows || this->cols!=mat2.cols)
		return false;		//if sizes are different, no need to compare elements
	for(int i=0; i<this->size; i++){
		if((this->ary[i]-mat2.ary[i])>marginOfError)	//if there is a difference
			diff=false;					//assumption is wrong
	}
	return diff;
}

void Matrix::invert(){
	Matrix temp=Matrix(rows,cols);			//temporary location for data
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			temp.ary[j*rows+i]=this->ary[i*cols+j];		//put array in order
		}
	}
	for(int i=0; i<rows*cols; i++)
		this->ary[i]=temp.ary[i];		//copy data back
	int temp1=rows;
	rows=cols;
	cols=temp1;
}

void Matrix::rowSwap(int r1, int r2)
{
	float temp;
	for (int i = 0; i < cols; i++)
	{
		temp = ary[r1*cols + i];
		ary[r1*cols + i] = ary[r2*cols + i];
		ary[r2*cols + i] = temp;
	}
}

void Matrix::rowMult(float coef, int r1)
{
	for (int i = 0; i < cols; i++)
	{
		ary[r1*cols + i] *= coef;
	}
}

void Matrix::rowMult(float coef, int r1, int r2)
{
	for (int i = 0; i < cols; i++)
	{
		ary[r2*cols + i] += ary[r1*cols +i] * coef;
	}
}

int Matrix::getNumRows()
{
	return rows;
}

int Matrix::getNumCols()
{
	return cols;
}