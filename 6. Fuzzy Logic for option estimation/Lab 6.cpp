#include<bits/stdc++.h>
using namespace std;

float min(vector<float> a)
{
	float min=INT_MAX;
	for (int i=0; i<a.size();i++)
	{
		if (a[i]<min)
		min =a[i];
	}
	return min;
}
float max(vector<float>a)
{
	float max=0;
	for (int i=0; i<a.size();i++)
	{
		if(a[i]>max)
		max= a[i];
	}
	return max;
}
int main()
{
	float r1[3][3] = { {0.62,0.32,0.33}, {0.36,0.82,0.35},{0.18,0.31,0.76}};
	float r2[3][3] = { {0.12,0.31,1.0}, {0.22,0.61,0.56}, {0.82, 0.45, 0.43}};
	float b[3][3] =  { {0.4, .33, 0}, {0, 0.66, .1818}, {0, 0.33, .36}};
	float a,a1;
	float  mid[3][3];
	vector<float >temp, temp1, temp2, temp3;
	for (int i=0;i<3;i++)
	{
		for(int k=0;k<3;k++)
		{
		
			for (int j=0;j<3; j++)
			{
				temp.push_back(r1[i][j]);
				temp.push_back(r2[j][k]);
				a= min(temp);
				temp1.push_back(a);
				temp.pop_back();
				temp.pop_back();
    		}
			a1= max(temp1);
			temp2.push_back(a1);
			temp1.pop_back();
			temp1.pop_back();
			temp1.pop_back();
		}
	}		

cout<<endl;
mid[0][0]=temp2[0]; mid[0][1]=temp2[1]; mid[0][2]=temp2[2];
mid[1][0]=temp2[3]; mid[1][1]=temp2[4]; mid[1][2]=temp2[5];
mid[2][0]=temp2[6]; mid[2][1]=temp2[7]; mid[2][2]=temp2[8];

for (int i=0;i<3;i++)
	{
		for(int k=0;k<3;k++)
		{
			for (int j=0;j<3; j++)
			{
				temp.push_back(b[i][j]);
				temp.push_back(mid[j][k]);
				a= min(temp);
				temp1.push_back(a);
				temp.pop_back();
				temp.pop_back();
	    	}
			a1= max(temp1);
			temp3.push_back(a1);
			temp1.pop_back();
			temp1.pop_back();
			temp1.pop_back();
		}
	}

int boy;
float choice = 0;
for (int i=0;i<temp3.size();i++)
{
	//cout << temp3[i]<<"\t";
	if (temp3[i] > choice) {
	    choice = temp3[i];
	    boy = (i / 3) + 1;
	}
}
//cout<< endl;
cout << "Choice is Boy: " << boy << " with value " << choice << endl;
}
