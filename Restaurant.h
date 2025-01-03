#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "District.h"
#include "Discount.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

class Restaurant : public District {
public:
    string restaurantName;
    vector<pair<string, int>> foods; 
    int openingTime, closingTime, numTables;
    Restaurant();
    Restaurant(const string& districtName, const string& rName);

    void print() const override; 

    ~Restaurant();
    vector<Discount*> discounts; 
};

#endif