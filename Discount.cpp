#include "Discount.h"

const string PERCENT = "percent";
const string AMOUNT = "amount";
const int HUNDRED = 100;

Discount::Discount(string t, int v) : type(t), value(v) {}

string Discount::get_type() const{
    return type;
}

int Discount::get_value() const{
    return value;
}

Food_Discount::Food_Discount(string t, int v, string f_n) : Discount(t, v), food_name(f_n) {}

string Food_Discount::get_food_name() {
    return food_name;
}

int Food_Discount::calc_final_price(int price, int previous_price) {
    return previous_price - (type == PERCENT ? (value / HUNDRED) * price : value);
}

int Food_Discount::discount_amount_applied(int price, int previous_price) {
    return (type == PERCENT ? (value / HUNDRED) * price : value);
}

First_Order_Discount::First_Order_Discount(string t, int v) : Discount(t, v) {}

int First_Order_Discount::calc_final_price(int price, int previous_price) {
    return previous_price - (type == PERCENT ? (value / HUNDRED) * previous_price : value);
}

int First_Order_Discount::discount_amount_applied(int price, int previous_price) {
    return (type == PERCENT ? (value / HUNDRED) * previous_price : value);
}

Total_Price_Discount::Total_Price_Discount(string t, int v, int m_p) : Discount(t, v), minimum_price(m_p) {}

int Total_Price_Discount::get_minimum_price() {
    return minimum_price;
}

int Total_Price_Discount::calc_final_price(int price, int previous_price) {
    return previous_price - (type == PERCENT ? (value / HUNDRED) * previous_price : value);
}

int Total_Price_Discount::discount_amount_applied(int price, int previous_price) {
    return (type == PERCENT ? (value / HUNDRED) * previous_price : value);
}
