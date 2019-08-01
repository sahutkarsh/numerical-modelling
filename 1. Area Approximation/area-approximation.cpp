#include <bits/stdc++.h>
using namespace std;

double compute_equation(vector<double> &coefficients, double x) { // Computes value of the equation
    double value = 0;
    int size = coefficients.size();
    for (int i=0;i<size;i++) {
        value = value + coefficients[i] * pow (x, size-i-1);
    }
    return value;
}

double compute_integral(vector<double> &coefficients, double lower, double upper) { // Computes value of the definite integral
    double value_lower = 0, value_upper = 0;
    int size = coefficients.size();
    for (int i=0;i<size;i++) {
        value_lower = value_lower + double(coefficients[i] * pow(lower, size-i)) / (size-i);
        value_upper = value_upper + double(coefficients[i] * pow(upper, size-i)) / (size-i);
    }
    return abs(value_upper-value_lower);
}

double trapezoidal(vector<double> &coefficients, double lower, double upper, int n) { // Computes area using trapezoidal method
    double h = (upper-lower)/n;
    double x;
    double area = compute_equation(coefficients, lower) + compute_equation(coefficients, upper);
    for(int i=1;i<n;i++) {
        x = lower + i * h;
        area = area + 2 * compute_equation(coefficients, x);
    }
    area = (h/2) * area;
    return area;
}

double simpson(vector<double> &coefficients, double lower, double upper, int n) { // Computes area using simpsons method
    double h = (upper-lower)/n;
    double x;
    double area = compute_equation(coefficients, lower) + compute_equation(coefficients, upper);
    double coeff = 4;
    for(int i=1;i<n;i++) {
        x = lower + i * h;
        if (i%2==1) coeff = 4;
        else coeff = 2;
        area = area + coeff * compute_equation(coefficients, x);
    }
    area = (h/3) * area;
    return area;
}


int main() {
	
    int degree, n_lower, n_upper;
    double lower, upper, temp;
    vector<double> coefficients;
	
	cout << "Enter degree of polynomial" << endl;
	cin >> degree;
	cout << "Enter coefficients" << endl;
	
	for(int i=0;i<=degree;i++) {
	    cin >> temp;
	    coefficients.push_back(temp);
	}
	
	cout << "Enter lower and upper limits for X" << endl;
	cin >> lower  >> upper;
	cout << "Enter lower and upper limits for n (number of segments) [Only even numbers]" << endl; // Only even values of n is allowed in simpson
	cin >> n_lower >> n_upper;
	
	for (int n=n_lower; n<=n_upper; n=n+2) { // Moves from lower to upper with a step of 2
	    cout << endl;
	    cout << "Number of segments: " << n << endl;
	    double integrated_area = compute_integral(coefficients, lower, upper);
    	double trapezoidal_area = trapezoidal(coefficients, lower, upper, n);
    	double simpson_area = simpson(coefficients, lower, upper, n);
    	double trapezoidal_error = abs(integrated_area - trapezoidal_area) * 100 / integrated_area;
    	double simpson_error = abs(integrated_area - simpson_area) * 100 / integrated_area;
    	cout << "Actual Area: " << integrated_area << endl;
    	cout << "Trapezoidal Rule Area: " << trapezoidal_area << " Error Percentage: " << trapezoidal_error << endl;
    	cout << "Simpson's Rule Area: " << simpson_area << " Error Percentage: " << simpson_error << endl;
	}
	return 0;
}