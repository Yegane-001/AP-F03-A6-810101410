#include "Restaurant.h"

using namespace std;

Restaurant::Restaurant() = default;

Restaurant::Restaurant(const string& districtName, const string& rName)
    : District(districtName), restaurantName(rName) {}

void Restaurant::print() const {
    cout << "Restaurant: " << restaurantName << ", District: " << district_name << endl;
    cout << "Foods: ";
    for (const auto& food : foods) {
        cout << food.first << ":" << food.second << " ";
    }
    cout << "\nOpening: " << openingTime << ", Closing: " << closingTime 
         << ", Tables: " << numTables << endl;
}
