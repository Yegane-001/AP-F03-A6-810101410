#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "District.h"
#include <vector>
#include <string>
using namespace std;

class Restaurant : public District {
public:
    string restaurantName;
    vector<std::pair<std::string, int>> foods; 
    int openingTime, closingTime, numTables;

    Restaurant();
    Restaurant(const std::string& districtName, const std::string& rName);

    void print() const override; 

    ~Restaurant() = default;
};

#endif