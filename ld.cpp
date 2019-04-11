#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int m = 5, n = 7;                    //dimension of matrix m*n , m in x and n in y
int m1 = (m-1)/2 , n1 = (n-1)/2;
Mat img=imread("abc",1);


bool isvalid(Mat img,int x,int y)
{
	if(x-m1<0 || x+m1>=img.cols || y-n1<0 || y+n1>=img.rows)
		return false;
	else
		return true;
}

int main(){

	int **matrix,i;	

	matrix= new int*[n];

	for(i=0;i<n;i++)
	{
		matrix[i]=new int[m];
	}

	return 0;
}