#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(int argc, char** argv) {
    double mean = 0.0;
    std::vector<double> list;
    char done = 'n';
    double x = 0.0; // Used for putting numbers into vector
    double y = 0.0; // Used as a placeholder to keep adding numbers
    double z = 0.0; // Used as a placeholder for adding all squared numbers before square root
    double a = 0.0; // Placeholder for after square root
    while(done != 'y'){
        cout << "What number are you adding?" << endl;
        cin >> x;
        list.push_back(x);
        y = y + x;
        cout << "Are you finished?" << endl;
        cout << "y/n" << endl;
        cin >> done;
    }
    mean = y / list.size();
    cout << "MEAN IS " << fixed << setprecision(3) << mean << endl;
    for(size_t i = 0; i < list.size(); i++){ 
        z = z + (pow((list[i]-mean), 2));
    }
    a = sqrt(z/(list.size() - 1));
    cout << "STD IS " << fixed << setprecision(3) << a << endl;
}

// BOOK: DATA STRUCTURES USING C++ - D.D. Malik PAGE 260
//
// STD is SQUARE ROOT OF (SUMATION of (NUMBER - MEAN)^2 / N)       /// NOTE IT IS N-1 WHEN IS FOR SAMPLE

// 5 4, The information on Ai art and Ai imaging was very clear and interesting to learn about. The only reason I put a 4 on understanding the material, was because there were three different occasions where information couldn't be stated as to why it was a bad idea to have Ai art. For example, one was the 80 hour work project for the Ai image editing for an award. If it was Ai couldn't they have just googled it and got the image? But instead it was 80 hours. It was just hard to see how it took 80 hours to get that picture, but then if you ask how that time was spent there wasnt an answer. It makes the argument seem invalid. Other than that, it was a perfectly fine presentation.