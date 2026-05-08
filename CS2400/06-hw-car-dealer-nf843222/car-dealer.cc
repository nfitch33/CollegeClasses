/**
 *   @file: car-dealer.cc
 * @author: Nathaniel Fitch
 *   @date: 11/09/2023
 *  @brief: The following project allows the user to get an estimated price for a car of their choosing, along with additional costs
 *          from any additional options they want for their car.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

ifstream inStream;
ofstream outStream;

void optionMenu(const vector<string> prices, const vector<string> options);
void displayMenu();
char pickCar(int &carPRICE);
void addOption(const vector<string> prices, const vector<string> options, vector<string> &chosen, vector<int> &price);
void addMenu(const vector<string> prices, const vector<string> options);
void removeOption(vector<string> &chosen, vector<int> &price);
void removeMenu(vector<string> &chosen, vector<int> &price);
int totalTEST(vector<int> price);
void cancelOrder(vector<string> &chosen, vector<int> &prices, int &carPRICE, char &car);
vector<string> prices;
vector<string> options;
vector<string> chosen;
vector<int> price;
int carPRICE;

int main(int argc, char const *argv[]) {
    int total;
    string consumer;
    string line = "";
    string placeholder = "";
    char character;
    char car;
    string newLine = "";
    inStream.open(argv[1]);
    while(inStream){
        getline(inStream, line);
        for (size_t x = 0; x < line.length(); x++){
           character = line.at(x);
           if (character == ' '){
                prices.push_back(newLine);
                newLine = line.substr(x + 1, line.length());
                x = line.length();
           }
           else {
           newLine = newLine + character;
           }
        }
        options.push_back(newLine);
        line = "";
        newLine = "";
        car = '0';
    }
    while (consumer != "6"){
        if (car == '0'){
        cout << "NO CAR SELECTED: ";
        }
        else {
            cout << "Current Car: " << car;
        }
        total = totalTEST(price);
        cout << " Total is: $" << total + carPRICE << " ";
        if (chosen.size() == 0){
            cout << "No options selected" << endl;
        }
        else if (chosen.size() == 1){
            cout << chosen.at(0);
        }
        else {
        for (size_t x = 0; x < chosen.size() - 1; x++){
                cout << chosen.at(x) << ", ";
            }
            int x = chosen.size();
            x--;
            cout << chosen.at(x);
        }
        cout << endl;
        displayMenu();
        cin >> consumer;
        if (consumer > "6" || consumer < "1"){
            cout << "Number must be 1-6" << endl;
        }
        else if(consumer == "1"){
            cout << "Select a model (E, L, X)" << endl;
            car = pickCar(carPRICE);
            cout << endl;
        }
        else if (consumer == "2"){
            cout << endl;
            optionMenu(prices, options);
        }
        else if (consumer == "3"){
            cout << endl;
            addOption(prices, options, chosen, price);
        }
        else if (consumer == "4"){
            cout << endl;
            removeOption(chosen, price);
        }
        else if (consumer == "5"){
            cout << endl;
            cancelOrder(chosen, price, carPRICE, car);
        }
        cout << "------------------------" << endl;
    }
    return 0;

}
void optionMenu(const vector<string> prices, const vector<string> options){
    for(size_t x = 0; x < prices.size(); x++){
        cout << left;
        cout << setw(20);
        if (x % 3 == 0){
            cout << endl;
            cout << left << options.at(x) << left << "($" << prices.at(x) << ") ";
        }
        else{
            cout << left << options.at(x) << "($" << prices.at(x) << ") ";
        }
    }
    cout << endl;
    cout << endl;
}
void addMenu(const vector<string> prices, const vector<string> options){
 for(size_t x = 0; x < prices.size(); x++){
        cout << right;
        if (x % 3 == 0){
            cout << endl;
            cout << right << x + 1 << ". " << options.at(x) << left << "($" << prices.at(x) << ") ";
        }
        else{
            cout << right << setw(20) << x + 1 << ". " << options.at(x) << "($" << prices.at(x) << ") ";
        }
    }
    cout << endl;
    cout << endl;
}
void displayMenu(){
    cout << "1. Select Car type: " << endl;
    cout << "2. List all options: " << endl;
    cout << "3. Add an option: " << endl;
    cout << "4. Remove an option: " << endl;
    cout << "5. Cancel an order: " << endl;
    cout << "6. Exit Program: " << endl;
}
char pickCar(int &carPRICE){
    char car;
    int placeholder = 0;
    cout << "Select from E, L, or X, (E: $10000)(L: $12000)(X: $15000): ";
    cin >> car;
    cout << endl;
    if (car == 'E' || car == 'e'){
        car = 'E';
        carPRICE = 10000;
        return car;
    }
    else if (car == 'L' || car == 'l'){
        car = 'L';
        carPRICE = 12000;
        return car;
    }
    else if (car == 'X' || car == 'x'){
        car = 'X';
        carPRICE = 18000;
        return car;
    }
    else{
        car = ' ';
        pickCar(placeholder);
        return car;
    }
}
void addOption(const vector<string> prices, const vector<string> options, vector<string> &chosen, vector<int> &price){
    int input;
    string container;
    addMenu(prices, options);
    cout << "Choose between 1-" << options.size() - 1 << endl;
    cout << "Which option would you like to add: ";
    cin >> input;
    if (input > options.size()){
        cout << "Not an option" << endl;
    }
    else if(input > options.size() - 1){
        cout << "Not an option, out of range" << endl;
    }
    else {
        input--;
        chosen.push_back(options.at(input));
        container = prices.at(input);
        int cal = stoi(container);
        price.push_back(cal);
        
    }
}
void removeOption(vector<string> &chosen, vector<int> &price){
    if (chosen.size() == 0){
        cout << "Nothing to remove" << endl;
    }
    else if (chosen.size() == 1){
        chosen.erase(chosen.begin());
        price.erase(price.begin());
    }
    else{
    int input;
    string container;
    removeMenu(chosen, price);
    cout << endl;
    cout << "Number 1-" << chosen.size() << endl;
    cout << "Choose which to remove: ";
    cin >> input;
    if (input < 1){
        cout << "No option removed" << endl;
    }
    else if (input > chosen.size()){
        cout << "No option removed, out of range" << endl;
    }
    else {
        input--;
        chosen.erase(chosen.begin() + input);
        price.erase(price.begin() + input);
    }
    }
}
void removeMenu(vector<string> &chosen, vector<int> &price){
    if (chosen.size() == 0){
        cout << "No options selected" << endl;
    }
    else{
        for (size_t x = 0; x < chosen.size(); x++){
            cout << x + 1 << ". " << chosen.at(x) << " ($" << price.at(x) << ")" << endl;
        }
    }
}
int totalTEST(vector<int> price){
    int total = 0;
    int container;
    if (price.size() == 0){
        total = 0;
        return total;
    }
    else {
        for(size_t x = 0; x < price.size(); x++){
            container = price.at(x);
            total = total + container;
        }
        return total;
    }
}
void cancelOrder(vector<string> &chosen, vector<int> &prices, int &carPRICE, char &car){
    car = ' ';
    carPRICE = 0;
    while (chosen.size() > 0){
        chosen.erase(chosen.begin());
        price.erase(price.begin());
    }
}
/// main