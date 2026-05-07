#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

// If you have Boost installed, uncomment this line:
// #include <boost/math/distributions/students_t.hpp>

using namespace std;

int main() {
    double mean = 0.0;
    vector<double> list;
    char done = 'n';
    double x = 0.0; // User input
    double y = 0.0; // Sum of values
    double z = 0.0; // Sum of squared differences
    double sd = 0.0; // Standard deviation
    double mu = 0.0; // Null hypothesis mean

    // Collect values
    while(done != 'y'){
        cout << "What number are you adding?" << endl;
        cin >> x;
        list.push_back(x);
        y += x;
        cout << "Are you finished? (y/n)" << endl;
        cin >> done;
    }

    // Calculate mean
    mean = y / list.size();
    cout << "MEAN IS " << fixed << setprecision(3) << mean << endl;

    // Calculate standard deviation (sample)
    for(size_t i = 0; i < list.size(); i++){ 
        z += pow((list[i] - mean), 2);
    }
    sd = sqrt(z / (list.size() - 1));
    cout << "STD IS " << fixed << setprecision(3) << sd << endl;

    // Ask for population mean (null hypothesis)
    cout << "Enter the population mean (null hypothesis): ";
    cin >> mu;

    // t-statistic
    double se = sd / sqrt(list.size()); // Standard error
    double t = (mean - mu) / se;
    int df = list.size() - 1; // Degrees of freedom

    cout << "T-STATISTIC IS " << fixed << setprecision(3) << t << endl;
    cout << "Degrees of Freedom: " << df << endl;

    // --- P-VALUE CALCULATION ---

    // Option 1: Using Boost (uncomment if using Boost)
    /*
    boost::math::students_t dist(df);
    double p = 2 * (1 - boost::math::cdf(dist, fabs(t)));
    cout << "P-VALUE IS " << fixed << setprecision(6) << p << endl;
    */

    // Option 2: Approximate using standard normal (less accurate for small n)
    // Only recommended for n > 30
    double p_approx = 2 * (1 - 0.5 * erfc(-fabs(t) / sqrt(2))); // Two-tailed
    cout << "APPROXIMATE P-VALUE (Z-based) IS " << fixed << setprecision(6) << p_approx << endl;

    return 0;
}
