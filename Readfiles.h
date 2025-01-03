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
using namespace std;

vector<Restaurant> readRestaurants(const string& filePath);
vector<District> readDistricts(const string& filePath);
vector<pair<string, vector<Discount*>>> readDiscounts(string filename);

#endif