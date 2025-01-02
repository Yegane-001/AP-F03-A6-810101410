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
    string get_type();
    int get_value();
    virtual int calc_final_price(int previous_price) = 0;

};

#endif