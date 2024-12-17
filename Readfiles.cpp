#include "Readfiles.h"

vector<District> readDistricts(const string& filePath) {
    vector<District> districts;
    ifstream file(filePath);
    string line, token;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return districts;
    }

    getline(file, line); // خواندن هدر
    while (getline(file, line)) {
        stringstream ss(line);
        string name, neighbor;

        getline(ss, name, ',');
        District d(name);

        while (getline(ss, neighbor, ';')) {
            d.neighbors.push_back(neighbor);
        }
        districts.push_back(d);
    }
    return districts;
}

// تابع برای خواندن فایل رستوران‌ها
vector<Restaurant> readRestaurants(const string& filePath) {
    vector<Restaurant> restaurants;
    ifstream file(filePath);
    string line, token;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return restaurants;
    }

    getline(file, line); // خواندن هدر
    while (getline(file, line)) {
        stringstream ss(line);
        string rName, districtName, foodsStr;

        getline(ss, rName, ',');
        getline(ss, districtName, ',');

        Restaurant r(districtName, rName);

        getline(ss, foodsStr, ',');
        stringstream foodStream(foodsStr);
        string foodToken;

        while (getline(foodStream, foodToken, ';')) {
            string foodName = foodToken.substr(0, foodToken.find(':'));
            int price = stoi(foodToken.substr(foodToken.find(':') + 1));
            r.foods.emplace_back(foodName, price);
        }

        ss >> r.openingTime;
        ss.ignore();
        ss >> r.closingTime;
        ss.ignore();
        ss >> r.numTables;

        restaurants.push_back(r);
    }
    return restaurants;
}