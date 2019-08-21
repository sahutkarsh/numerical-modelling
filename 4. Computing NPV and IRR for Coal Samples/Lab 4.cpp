#include <bits/stdc++.h>
using namespace std;

class Coal {
    public:
        double operating[100], capital[100], revenue[100];
        double tax_rate, discount;
        
        double compute_npv(int size, double rate, bool derivative=false) {
            double num, den, num_der, den_der, gross, tax, net, npv=0.0, npv_der=0.0;
            for (int i=0; i<size; i++) {
                gross = revenue[i] - operating[i];
                tax = tax_rate * gross;
                net = gross - tax;
                num = net - capital[i];
                num_der = -i * num;
                den = pow(1+rate, i);
                den_der = pow(1+rate, i+1);
                npv += (num / den);
                npv_der += (num_der / den_der);
            }
            if (derivative) return npv_der;
            else return npv;
        }
        
        double compute_irr(int size) {
            double irr = 0.2, npv, npv_der, error;
            while(true) {
                npv = compute_npv(size, irr);
                npv_der = compute_npv(size, irr, true);
                error = (npv / npv_der);
                if (abs(error)  < 0.01) break;
                else irr -= error;
            }
            return irr;
        }
};

int main() {
    int size;
    Coal sample;
    
    cout << "Enter number of years" << endl;
    cin >> size;
    cout << "Enter Operating Cost over the years" << endl;
    for (int i=0; i<size; i++) cin >> sample.operating[i];
    cout << "Enter Capital Cost over the years" << endl;
    for (int i=0; i<size; i++) cin >> sample.capital[i];
    cout << "Enter Revenue over the years" << endl;
    for (int i=0; i<size; i++) cin >> sample.revenue[i];
    cout << "Enter Tax Rate" << endl;
    cin >> sample.tax_rate;
    cout << "Enter Discount Rate" << endl;
    cin >> sample.discount;
    double npv = sample.compute_npv(size, sample.discount);
    double irr = sample.compute_irr(size);
    cout << "NPV: " << npv << endl;
    cout << "IRR: " << irr << endl;
    return 0;
}