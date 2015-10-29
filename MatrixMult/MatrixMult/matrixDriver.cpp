/* Eric McAlpine
 * Matrix Multiplier
 *
 *
 *
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <string.h>
#include <cctype>
#include "Matrix.h"

using namespace std;

const int SIZE=5000;		//size of matricies

int main(){
	//variable dictionary
	clock_t stopWatch;
	Matrix src1(SIZE, SIZE);
	Matrix src2(SIZE, SIZE);
	double sTime;
	srand(time(NULL));


	//set base matricies to random values
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			src1.setNumber(i, j, rand());
			src2.setNumber(i, j, rand());
		}
	}
	
	//*******************naiveMultiply
	/*stopWatch=clock();//sets clock
	Matrix naive=src1.naiveMultiply(src2);//multiply/store in new matrix
	nTime=(double)((clock()-stopWatch)/CLOCKS_PER_SEC);//reads clock
	cout<<nTime<<endl;//shows output as soon as done*/
						//easier to keep track of progress


	src1.setTileSize(2048);
	//*******************tileMultiply
	stopWatch=clock();
	Matrix tile=src1.tileMultiply(src2);
	sTime=(double)((clock()-stopWatch)/CLOCKS_PER_SEC);
	cout<<sTime<<endl;


	//*******************smartMultiply
	stopWatch=clock();
	Matrix smart=src1.smartMultiply(src2);
	sTime=(double)((clock()-stopWatch)/CLOCKS_PER_SEC);
	cout<<sTime<<endl;


	//*******************invertedMultiply
	/*stopWatch=clock();
	src2.invert();			//inverts the 2nd array
	Matrix inverted=src1.invertedMultiply(src2);//multiplies
	src2.invert();			//un-inverts the array (back to normal)
	iTime=(double)((clock()-stopWatch)/CLOCKS_PER_SEC); //also to be fair to other algorithms
	cout<<iTime<<endl;*/

	if(smart.equals(tile))
		cout<<"tile result equal to smart result"<<endl;
	else
		cout<<"tile result not equal to smart result"<<endl;
	/*if(naive.equals(inverted))
		cout<<"naive result equal to inverted result"<<endl;
	else
		cout<<"naive result not equal to inverted result"<<endl;*/


	return 0;
}