#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat A=imread("abc.png",0);
int m=31,n=31;
int m1=(m-1)/2,n1=(n-1)/2;
double sigma=2;

/*bool Valid(Mat img,int x,int y)
{
	if(x-m1<0 || x+m1>=img.cols || y-n1<0 || y+n1>=img.rows)
		return false;
	else
		return true;
}*/

double gaussian(int x,double sigma)
{
	double r=pow((x/sigma),2);
	double value= (r-1)*exp(-1*r/2);///(1.414*3.14*pow(sigma,3));
	return -1*value;
}

void **getTemplate(double **matrix,double sigma)
{
	int i,j;
	double a;
	for(i=0;i<m;i++){
		a=gaussian(m1-i,sigma);
		for(j=0;j<n;j++){
			matrix[j][i]=a;
		}
	}
}

/*void print_matrix(double **matrix)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<matrix[j][i]<<" ";
		}
		cout<<endl;
	}
}*/

void gaussian_visualization(double **matrix)
{
	Mat visual(n,m,CV_8UC1,Scalar(0));
	int i,j;
	double max=0,ratio,min=9999;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(matrix[j][i]>max)
				max=matrix[j][i];
			if(matrix[j][i]<min)
				min=matrix[j][i];
		}
	}
	max-=min;
	ratio=(double)255/max;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			matrix[j][i]-=min;
			matrix[j][i]*=255/max;
			visual.at<uchar>(j,i)=matrix[j][i];
		}
	}
	cout<<"Max:"<<max<<endl<<"Min:"<<min<<endl;

	//imshow("gaussian",visual);
	//waitKey(0);

}

double sum_of_kernel(double **matrix)
{
	int i,j;
	double sum=0;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			sum+=matrix[j][i];
		}
	}

	return sum;
}

void apply_kernel(Mat img,double **matrix)
{
	int i,j,x,y;
	double sum=0;
	double sum_kernel=sum_of_kernel(matrix);


	for(i=m1;i<img.cols-m1;i++)
	{
		for(j=n1;j<img.rows-n1;j++)
		{
			for(x=0;x<m;x++)
			{
				for(y=0;y<n;y++)
				{
					sum+=matrix[y][x]*img.at<uchar>(j-n1+y,i-m1+x);
				}
			}
			if(sum<0)
				sum=0;
			img.at<uchar>(j,i)=sum/sum_kernel;
			sum=0;
		}
	}

}


int main()
{

	double **matrix;
	int i,j;

	matrix=new double*[n];
	for(i=0;i<n;i++)
	{
		matrix[i]=new double[m];
	}

	getTemplate(matrix,sigma);
	//print_matrix(matrix);
	gaussian_visualization(matrix);
	apply_kernel(A,matrix);

	imshow("a",A);
	waitKey(0);

	return 0;



}