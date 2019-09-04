#include<bits/stdc++.h>
using namespace std;

int sign[][3] = {
	{1,	0,	0},
	{1,	-1,	0},
	{1,	0,	-1},
	{1,	0,	0},
	{0,	1,	0},
	{0,	1,	0},
	{0,	-1,	1},
	{0,	0,  1},
	{0,	0,	1}
};
float k=0.024;
int l[] = {200,200,200,200,400,200,400,200,400};

float length = 4;
float width = 3.5;
float A = length*width;

float res[9] = {5.24, 5.24, 5.24, 5.24, 10.48, 5.24, 10.48, 5.24, 10.48};

float sum_hl(int dir_ar[], int size, int loop_no, float q[])
{
	float sum = 0;
	for(int i=0; i<size; i++)
	{
		sum = sum + res[dir_ar[i]]*q[dir_ar[i]]*abs(q[dir_ar[i]])*sign[dir_ar[i]][loop_no];
	}
	return -sum;
}
float d_sum_hl(int dir_ar[], int size, int loop_no, float q[])
{
	float sum=0;
	for(int i=0; i<size; i++)
	{
		sum = sum + res[dir_ar[i]]*abs(q[dir_ar[i]])*(sign[dir_ar[i]][loop_no])*(sign[dir_ar[i]][loop_no]);
	}
	return 2*sum;
}
float delta_q(int dir_ar[], int size, int loop_no, float q[])
{
	float sum;
	sum = sum_hl(dir_ar, size, loop_no, q)/d_sum_hl(dir_ar, size, loop_no, q);
	return sum;
}

int main()
{
	float q[] = {0.7, 0.2, 0, 0.2, 0.5, 0.471, 0.2, 0.671, 0.63};
	int dir_ar0[] = {0,1,2,3};
	int dir_ar1[] = {1,4,5,6};
	int dir_ar2[] = {2,6,7,8};
	int size = 4;
	int total_branch = 9;
	float dq0=1, dq1=1, dq2=1;
	do
	{
		dq0 = delta_q(dir_ar0, size, 0, q);
		dq1 = delta_q(dir_ar1, size, 1, q);
		dq2 = delta_q(dir_ar2, size, 2, q);
		for(int i=0; i<size; i++)
		{
			q[dir_ar0[i]] = q[dir_ar0[i]] + sign[dir_ar0[i]][0]*dq0;
			q[dir_ar1[i]] = q[dir_ar1[i]] + sign[dir_ar1[i]][1]*dq1;
			q[dir_ar2[i]] = q[dir_ar2[i]] + sign[dir_ar2[i]][2]*dq2;
		}
	}while(abs(dq0)>0.001 && abs(dq1)>0.001 && abs(dq2)>0.001);
	for(int i=0; i<total_branch; i++) cout << "Branch: " << i << ": " << q[i] << " (m3/s)" << endl;
}