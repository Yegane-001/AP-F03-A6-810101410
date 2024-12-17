#ifndef READFILES_H
#define READFILES_H

#include "District.h"
#include "Restaurant.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<Restaurant> readRestaurants(const string& filePath);
vector<District> readDistricts(const string& filePath);

#endif