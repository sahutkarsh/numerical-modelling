#include <bits/stdc++.h>
using namespace std;

void print_matrix(vector<vector<double>> &matrix) {
    cout << endl << "Global Matrix: " << endl << endl;
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << matrix[i][j] << "\t\t\t";
        }
        cout << endl;
    }
}

void print_KMatrices(vector<vector<double>> &matrix) {
    cout << endl << endl;
    for (int i=0; i<matrix.size(); i++) {
        cout << "Matrix " << (i+1) << ":" << endl;
        cout << matrix[i][0] << "\t" << matrix[i][1] << endl;
        cout << matrix[i][2] << "\t" << matrix[i][3] << endl;
        cout << endl;
    }
    cout << endl;
}

double compute_equation(vector<double> &coefficients, double x, bool ex) {
    double value = 0;
    int size = coefficients.size();
    for (int i=0;i<size;i++) {
        double power_val = pow(x, size-i-1);
        if (ex && size-i-1 == 0) power_val = 0;
        if (ex) value += coefficients[i] * exp (power_val);
        else value += coefficients[i] * power_val;
    }
    return value;
}

double compute_element(vector<double> &coefficients, double x, bool ex, int type) {
    double value = compute_equation(coefficients, x, ex);
    if (type == 2) value *= x;
    else if (type == 3) value *= exp(x);
    else if (type == 4) value *= pow(x,2);
    return value;
}

double trapezoidal(vector<double> &coefficients, double lower, double upper, int n, bool ex, int type) {
    double h = (upper-lower)/n;
    double x;
    double area = compute_element(coefficients, lower, ex, type) + compute_element(coefficients, upper, ex, type);
    for(int i=1;i<n;i++) {
        x = lower + i * h;
        area += 2 * compute_element(coefficients, x, ex, type);
    }
    area *= (h/2);
    return area;
}

void build_global(vector<vector<double>> &matrices, vector<vector<double>> &global_matrix) {
    int n = matrices.size();
    for (int i=0; i<=n; i++) {
        vector<double> null;
        for (int j=0; j<=n; j++) null.push_back(0.0);
        global_matrix.push_back(null);
    }
    int row = 0, col = 0;
    for (row=0; row<n; row++) {
        global_matrix[row][col] += matrices[row][0];
        global_matrix[row][col+1] += matrices[row][1];
        global_matrix[row+1][col] += matrices[row][2];
        global_matrix[row+1][col+1] += matrices[row][3];
        col += 1;
    }
}

void compute_matrix(vector<vector<double>> &global_matrix, double length, int n, vector<double> &coefficients, bool ex) {
    int itr = 100;
    double segment = length / n;
    double lower = 0, upper = segment;
    vector<vector<double>> matrices;
    for (int i=0; i<n; i++) {
        vector<double> matrix;
        matrix.push_back(trapezoidal(coefficients, lower, upper, itr, ex, 1));
        matrix.push_back(trapezoidal(coefficients, lower, upper, itr, ex, 2));
        matrix.push_back(trapezoidal(coefficients, lower, upper, itr, ex, 3));
        matrix.push_back(trapezoidal(coefficients, lower, upper, itr, ex, 4));
        matrices.push_back(matrix);
        lower += segment;
        upper += segment;
    }
    print_KMatrices(matrices);
    build_global(matrices, global_matrix);
    print_matrix(global_matrix);
}

int main() {
    int type, deg, n;
    double coeff, length;
    bool ex = false;
    vector<double> coefficients;
    vector<vector<double>> global_matrix;
    cout << "Enter Length of the Rod" << endl;
    cin >> length;
    cout << "Enter number of elements" << endl;
    cin >> n;
    cout << "Specify equation Type: Polynomial (Enter 0) / Exponential (Enter 1)" << endl;
    cin >> type;
    cout << "Enter Degree of the equation" << endl;
    cin >> deg;
    cout << "Enter Coefficients" << endl; 
    for (int i=0; i<=deg; i++) {
        cin >> coeff;
        coefficients.push_back(coeff);
    }
    if (type == 1) ex = true;
    compute_matrix(global_matrix, length, n, coefficients, ex);
    return 0;
}