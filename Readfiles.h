#ifndef READFILES_H
#define READFILES_H

#include "District.h"
#include "Restaurant.h"
#include "Discount.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype> 
using namespace std;

vector<Restaurant> readRestaurants(const string& filePath);
vector<District> readDistricts(const string& filePath);
vector<Restaurant> readDiscounts(vector<Restaurant>& restaurants, const string& discountsFile);

#endif