#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Discount {
protected:
    string type;
    int value;

public:
    Discount(string t, int v);
    string get_type();
    int get_value();
    virtual int calc_final_price(int price, int previous_price) = 0;
    virtual int discount_amount_applied(int price, int previous_price) = 0;
};

class Food_Discount : public Discount {
private:
    string food_name;

public:
    Food_Discount(string t, int v, string f_n);
    string get_food_name();
    int calc_final_price(int price, int previous_price) override;
    int discount_amount_applied(int price, int previous_price) override;
};

class First_Order_Discount : public Discount {
public:
    First_Order_Discount(string t, int v);
    int calc_final_price(int price, int previous_price) override;
    int discount_amount_applied(int price, int previous_price) override;
};

class Total_Price_Discount : public Discount {
    private:
    int minimum_price;

    public:
    Total_Price_Discount(string t, int v, int m_p);
    int calc_final_price(int price, int previous_price) override;
    int discount_amount_applied(int price, int previous_price) override;
};

#endif
