#include <bits/stdc++.h>
using namespace std;

void logarithm(vector<double> &vect) { //Applies log over a vector
    for(int i=0; i<vect.size(); i++) vect[i] = log(vect[i]);
}

vector<double> regression (vector<double> &x, vector<double> &y) { // Regression to compute the best fit line using least square method
    vector<double> coefficients;
    int size = x.size();
    double numerator=0.0, denominator=0.0, slope, intercept;
    double x_avg = accumulate(x.begin(), x.end(), 0.0) / size;
    double y_avg = accumulate(y.begin(), y.end(), 0.0) / size;
    for (int i=0; i<size; i++) {
        numerator += (x[i] - x_avg) * (y[i] - y_avg);
        denominator += pow((x[i] - x_avg), 2);
    }
    slope = numerator / denominator;
    intercept = y_avg - slope * x_avg;
    coefficients.push_back(slope);
    coefficients.push_back(intercept);
    return coefficients;
}

double compute_derivative(vector<double> &coefficients, double x) { // Derivative of a polynomial
    double degree, value=0;
    degree = coefficients.size() - 1;
    for(int i=degree; i>=0; i--) value += i * coefficients[i] * pow(x, i-1);
    return value;
}

double compute_polynomial(vector<double> &coefficients, double x) { // Value of a polynomial
    double degree, value=0;
    degree = coefficients.size() - 1;
    for(int i=degree; i>=0; i--) value += coefficients[i] * pow(x, i);
    return value;
}

double newton_raphson(vector<double> &coefficients) { // Newton Raphson method to compute roots of the polynomial
    double error, root=50.0;
    while (true) {
        root = root - (compute_polynomial(coefficients, root) / compute_derivative (coefficients, root));
        error = abs(compute_polynomial(coefficients, root));
        if (error < 0.01) break;
    }
    return root;
}

vector<double> formulate_cubic(double S1, double h, double FOS, double density, double D, double w_g) { // Compute coefficients of the cubic
    vector<double> coefficients;
    double sp_wt = density / 100;
    coefficients.push_back(-1 * FOS * sp_wt * D * pow(w_g, 2));
    coefficients.push_back(-2 * FOS * sp_wt * D * w_g);
    coefficients.push_back(0.64 * S1 - FOS * sp_wt * D);
    coefficients.push_back(0.36 * S1 / h);
    return coefficients;
}

int main () {
    int N;
    double temp_size, temp_strength, k, a, S1, h, FOS, density, w_p;
    vector <double> size, strength, best_fit_line, coefficients;
    cout << "Enter the length of the Size-Strength Table" << endl;
    cin >> N;
    cout << "Enter rows of the table: Size (mm) and Strength (MPa)" << endl;
    
    for (int i=0;i<N;i++) {
        cin >> temp_size >> temp_strength;
        size.push_back(temp_size);
        strength.push_back(temp_strength);
    }
    
    cout << "Enter the pillar height (metres)" << endl;
    cin >> h;
    cout << "Enter the density of overburden (Te/m3)" << endl;
    cin >> density;
    cout << "Enter the desired Factor of Safety" << endl;
    cin >> FOS;
    
	// ln(strength) = ln(k) - a * ln (size)
    logarithm(size);
    logarithm(strength);
    
	// Regression
    best_fit_line = regression(size, strength);
    a = -1 * best_fit_line[0];
    k = exp(best_fit_line[1]);
    S1 = k * pow(1000, -a);
    
	// Computing width of the pillar
    cout << endl;
    cout << showpoint << setprecision(5);
    for (double D=200; D<=400; D+=50) {
        for (double w_g=4; w_g<=6; w_g+=0.5) {
            coefficients = formulate_cubic(S1, h, FOS, density, D, w_g);
            w_p = newton_raphson(coefficients);
            cout << "Depth: " << D << "m " << "Gallery Width: " << w_g << "m ";
            cout << "Pillar Width: " << w_p << "m " << endl;
        }
    }
    return 0;
}