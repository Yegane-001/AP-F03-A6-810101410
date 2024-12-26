#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Utaste.h"
#include "District.h"
#include "Restaurant.h"
#include "Readfiles.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <districts_file> <restaurants_file>" << endl;
        return 1;
    }
    string districtsFile = argv[1];
    string restaurantsFile = argv[2];
    vector<District> districts = readDistricts(districtsFile);
    vector<Restaurant> restaurants = readRestaurants(restaurantsFile);
    Utaste utaste(districts,restaurants);
    //cout << "\nRestaurants Data:\n";
    //for (const auto& r : restaurants) r.print();
    utaste.handle_input();

    return 0;
}