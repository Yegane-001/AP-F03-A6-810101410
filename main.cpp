#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Utaste.h"
#include "District.h"
#include "Restaurant.h"
#include "Readfiles.h"
#include "Discount.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <districts_file> <restaurants_file> <discounts_file>" << endl;
        return 1;
    }

    string districtsFile = argv[1];
    string restaurantsFile = argv[2];
    string discountsFile = argv[3];
    vector<District> districts = readDistricts(districtsFile);
    vector<Restaurant> restaurants = readRestaurants(restaurantsFile);
    restaurants = readDiscounts(restaurants, discountsFile);

    /*for (const auto& restaurant : restaurants) {
        restaurant.print();
        cout << "Discounts:\n";
        for (const auto& discount : restaurant.discounts) {
            cout << "Type: " << discount->get_type() << ", Value: " << discount->get_value() << "\n";
        }
    }*/
  
    Utaste utaste(districts,restaurants);
    utaste.handle_input();

    return 0;
}

