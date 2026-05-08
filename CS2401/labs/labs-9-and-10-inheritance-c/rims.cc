/* MADE BY NATHANIEL FITCH */

#include <string>
#include <iostream>
#include <cctype>
#include "rims.h"

using namespace std;

void Rims::see_all_rims() const;
void Rims::see_all_sizes() const;
void Rims::see_all_colors() const;
void Rims::see_all_materials() const;
void Rims::input(std::istream& ins){
    if(&ins == &cin){
        cout << "What is the Rim type? ";
        cin >> type;
        cout << "What is the material? ";
        cin >> material;
        cout << "What color is it? ";
        cin >> color;
        cout << "What is the rim size? ";
        cin >> rim_size;
        cout << "What is the cost? ";
        cin >> price;
    }
    else{
        string tmp;
        getline(ins, type, '-');
        getline(ins, material, '-');
        getline(ins, color, '-');
        getline(ins, tmp, '-');
        rim_size = stoi(tmp);
        getline(ins, tmp, '-');
        price = stod(tmp);

    }
    string type;
    string material;
    string color;
    int rim_size;
}
void Rims::output(std::ostream& outs){
    outs << "Rim type: " << get_type() << endl;
    outs << "Rim material: " << get_material() << endl; 
    outs << "Rim color: " << get_color() << endl; 
    outs << "Rim size: " << get_size() << endl; 
    outs << "Rim price: " << get_price() << endl;
}
void Rims::get_all() const{
    cout << fixed << set_width(20) << "Rim type is: " << get_type() << endl;
    cout << fixed << set_width(20) << "Material type is: "<< get_material() << endl;
    cout << fixed << set_width(20) << "Color is: " << get_color() << endl;
    cout << fixed << set_width(20) << "Rim size is: " << get_size() << '"' << endl;
    cout << fixed << set_width(20) << "Price total is: " << get_price() << endl;
}
