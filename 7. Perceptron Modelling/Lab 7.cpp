#include <bits/stdc++.h>
using namespace std;

class Perceptron {
    public:
        float wx, wy, wb, grad_x, grad_y, grad_b;
        int i = 0;
        
        float compute_grad(vector<pair<float, float>> &train, vector<int> &targets, vector<float> &param) {
            int n = train.size(), i=0;
            float grad = 0.0, hx, y_hat;
            for (auto itr = train.begin(); itr != train.end(); itr++) {
                hx = wx * (itr->first) + wy * (itr->second) + wb;
                y_hat = 1 / (1 + exp(-1.0 * hx));
                grad += (y_hat - targets[i]) * param[i];
                i += 1;
            }
            grad /= n;
            return grad;
        }
        void train(vector<pair<float, float>> &train, vector<int> &targets) {
            int epochs = 50;
            float lr = 0.0001;
            vector<float> x, y, b;
            for (auto itr = train.begin(); itr != train.end(); itr++) {
                x.push_back(itr->first);
                y.push_back(itr->second);
                b.push_back(1);
            }
            for (int i=0; i<epochs; i++) {
                grad_x = compute_grad(train, targets, x);
                grad_y = compute_grad(train, targets, y);
                grad_b = compute_grad(train, targets, b);
                wx -= (lr * grad_x);
                wy -= (lr * grad_y);
                wb -= (lr * grad_b);
            }
        }
        vector<int> predict(vector<pair<float,float>> &test) {
            vector<int> pred;
            float y_hat;
            for (auto itr = test.begin(); itr != test.end(); itr++) {
                y_hat = wx * (itr->first) + wy * (itr->second) + wb;
                if (y_hat <= 0.5) pred.push_back(0);
                else pred.push_back(1);
            }
            return pred;
        }
};

float accuracy_score(vector<int> targets, vector<int> pred) {
    int n = targets.size(), t = 0;
    for (int i=0; i<n; i++) {
        if (targets[i] == pred[i]) {
            t += 1;
        }
    }
    float acc = (t*1.0)/n;
    return acc;
}

void print_data(vector<pair<float,float>> &data) {
    cout << "Data: " << endl;
    for (auto itr = data.begin(); itr != data.end(); itr++) {
        cout << itr->first << " " << itr->second << endl;
    }
    cout << endl;
}

float random(float lower, float upper) {
    double r = rand();
    double num = lower + (r / RAND_MAX) * (upper - lower);
    return num;
}

void generate_data(float m, float c, vector<pair<float,float>> &train, vector<pair<float,float>> &test, vector<int> &targets_train, vector<int> &targets_test, int size, float test_size) {
    int n_test = size * test_size;
    int n_train = size - n_test;
    float tol = 5;
    float x, y, distortion;
    for (int i=0; i<(n_train/2); i++) {
        x = 100 * random(0,1);
        y = m * x + c;
        distortion = random(0, tol);
        train.push_back(make_pair(x, y+distortion));
        train.push_back(make_pair(x, y-distortion));
        targets_train.push_back(1);
        targets_train.push_back(0);
    }
    for (int i=0; i<(n_test/2); i++) {
        x = 100 * random(0,1);
        y = m * x + c;
        distortion = random(0, tol);
        test.push_back(make_pair(x, y+distortion));
        test.push_back(make_pair(x, y-distortion));
        targets_test.push_back(1);
        targets_test.push_back(0);
    }
}

int main() {
    srand(0);
    float m, c;
    cout << "Enter m and c for the equation y = mx + c" << endl;
    cin >> m >> c;
    cout << "Equation: y = " << m << "x + " << c << endl;
    vector<pair<float,float>> train, test;
    vector<int> targets_train, targets_test;
    generate_data(m, c, train, test, targets_train, targets_test, 1000, 0.3);
    Perceptron model;
    model.wx = -1.0 * m + random(0,0.1);
    model.wy = 1 + random(0, 0.1);
    model.wb = -1.0 * c + random(0,0.1);
    model.train(train, targets_train);
    vector<int> predictions = model.predict(test);
    float accuracy = accuracy_score(targets_test, predictions) * 100;
    cout << "Accuracy: " << accuracy << " %" << endl;
    cout << "Boundary Modelled: ";
    cout << model.wy << "y = " << (-1 * model.wx) << "x + " << (-1 * model.wb) << endl;
    return 0;
}