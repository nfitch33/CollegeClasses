//C-- Product Page, We Making stuff, Making Bread

#include <iostream>

class Product //Car Parts
{
public:
//Constructor
    Product(/*double p = 0.0,*/ int a = 0){/*p = price;*/ a = amt;}
    
//Setter Functions

    // void set_price(double item_price);
    void set_amt(int item_amt) {amt = item_amt;}

//Getter Functions

    // double get_price();
    int get_amt() {return amt;}

//Virtual Functions
    virtual void input(std::istream& ins);
    virtual void output(std::ostream& outs);
protected:
    // double price; 
    int amt; //stock amount
};

// price is in child class -- NOTE