#include "Discount.h"

const string PERCENT = "percent";
const string AMOUNT = "amount";
const int HUDRED = 100;
const int ZERO = 0;

Discount::Discount(string t, int v): type(t), value(v) {}

string Discount::get_type() {
    return type;
}

int Discount::get_value() {
    return value;
}

Food_Discount::Food_Discount(string t, int v, string f_n) : Discount(t, v), food_name(f_n) {}

int Food_Discount::calc_final_price(int price, int previous_price) {
    if (type == PERCENT) {
        return previous_price - (value / HUDRED) * price;
    } else if (type == AMOUNT) {
        return previous_price - value;
    }
    return previous_price;
}

int Food_Discount::discount_amount_applied(int price, int previous_price) {
    if (type == PERCENT) {
        return (value / HUDRED) * price;
    } else if (type == AMOUNT) {
        return value;
    }
    return ZERO;
}

First_Order_Discount::First_Order_Discount(string t, int v) : Discount(t, v) {}

int First_Order_Discount::calc_final_price(int price, int previous_price) {
    if (type == AMOUNT) {
        return previous_price - value;
    } else if (type == PERCENT) {
        return previous_price - (value / HUDRED) * previous_price;
    }
    return previous_price;
}

int First_Order_Discount::discount_amount_applied(int price, int previous_price) {
    if (type == PERCENT) {
        return (value / HUDRED) * previous_price;
    } else if (type == AMOUNT) {
        return value;
    }
    return ZERO;
}

Total_Price_Discount::Total_Price_Discount(string t, int v, int m_p) : Discount(t, v), minimum_price(m_p) {}

int Total_Price_Discount::calc_final_price(int price, int previous_price) {
    if(previous_price < minimum_price) {
        return previous_price;
    }
    else {
        if (type == AMOUNT) {
        return previous_price - value;
        } else if (type == PERCENT) {
            return previous_price - (value / HUDRED) * previous_price;
        }
        return previous_price;
    }
}

int Total_Price_Discount::discount_amount_applied(int price, int previous_price) {
    if(previous_price < minimum_price) {
        return ZERO;
    }
    else {
        if (type == AMOUNT) {
        return value;
        } else if (type == PERCENT) {
            return (value / HUDRED) * previous_price;
        }
        return ZERO;
    }
}