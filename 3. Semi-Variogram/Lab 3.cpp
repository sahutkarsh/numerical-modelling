#include <bits/stdc++.h>
using namespace std;

float horizontal(float **grade, int h, int m, int n) {
    float semi_var = 0;
    int n_pairs = 0;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n-h; j++) {
            if (grade[i][j]!=0 && grade[i][j+h]!=0) {
                semi_var += pow((grade[i][j] - grade[i][j+h]), 2);
                n_pairs += 1;
            }
        }
    }
    semi_var /= (2 * n_pairs);
    return semi_var;
}

float vertical(float **grade, int h, int m, int n) {
    float semi_var = 0;
    int n_pairs = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m-h; j++) {
            if (grade[j][i]!=0 && grade[j+h][i]!=0) {
                semi_var += pow((grade[j][i] - grade[j+h][i]), 2);
                n_pairs += 1;
            }
        }
    }
    semi_var /= (2 * n_pairs);
    return semi_var;
}

float diagonal(float **grade, int h, int m, int n) {
    float semi_var = 0;
    int n_pairs = 0;
    for (int i=0;i<m;i++) {
        int r = i, c = 0;
        while (r-h>=0 && c+h<n) {
            if(grade[r][c]!=0 && grade[r-h][c+h]!=0) {
                semi_var += pow((grade[r][c] - grade[r-h][c+h]),2);
                n_pairs += 1;
            }
            r -= 1;
            c += 1;
        }
    }
    for (int i=1;i<n;i++) {
        int r = m-1, c = i;
        while (r-h>=0 && c+h<n) {
            if(grade[r][c]!=0 && grade[r-h][c+h]!=0) {
                semi_var += pow((grade[r][c] - grade[r-h][c+h]),2);
                n_pairs += 1;
            }
            r -= 1;
            c += 1;
        }
    }
    semi_var /= (2 * n_pairs);
    return semi_var;
}

int main() {
    int m,n;
    cout << "Enter dimensions of the table" << endl;
    cin >> m >> n;
    float **grade;
    grade = new float*[m];
    for (int i=0; i<m; i++) grade[i] = new float[n];
    cout << "Enter rows of the table (0 for undefined points)" << endl;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) cin >> grade[i][j];
    }
    cout << endl;
    cout << "Semi-Variogram: Horizontal" << endl;
    for (int h=1; h<=5; h++) {
        cout << horizontal(grade,h,m,n) << " for h = " << (h*100) << " m" << endl;
    }
    cout << endl;
    cout << "Semi-Variogram: Vertical" << endl;
    for (int h=1; h<=5; h++) {
        cout << vertical(grade,h,m,n) << " for h = " << (h*100) << " m" << endl;
    }
    cout << endl;
    cout << "Semi-Variogram: Diagonal" << endl;
    for (int h=1; h<=5; h++) {
        cout << diagonal(grade,h,m,n) << " for h = " << (h*100*sqrt(2)) << " m" << endl;
    }
}