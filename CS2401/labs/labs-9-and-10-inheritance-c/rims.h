/* MADE BY NATHANIEL FITCH */
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

#include "Product.h"

class Rims:public Product
{
public:
    Rims(){type = "N/A", material = "N/A", color = "N/A", price = 0.00, size = 0;}
    Rims(string rim, string mat, string colors, double tprice, int num){type = rim, material = mat, color = colors, price = tprice, rim_size = num ;}
    void see_all_rims() const;
    void see_all_sizes() const;
    void see_all_colors() const;
    void see_all_materials() const;
    string get_type() const {return type;}
    string get_material() const {return material;}
    string get_color() const {return color;}
    double get_price() const {return price;}
    int get_size() const {return rim_size;}
    void get_all() const;
    void set_size(int num) {rim_size = num;}
    void set_material(string mat) {material = mat;}
    void set_type(string rim) {type = rim;}
    void set_color(string colors) {color = colors;}
    void input(std::istream& ins);
    void output(std::ostream& outs);
private:
    string type;
    string material;
    string color;
    double price;
    int rim_size;
};