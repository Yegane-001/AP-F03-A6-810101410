#include "Readfiles.h"

vector<District> readDistricts(const string& filePath) {
    vector<District> districts;
    ifstream file(filePath);
    string line, token;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return districts;
    }

    getline(file, line);
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

vector<Restaurant> readRestaurants(const string& filePath) {

    vector<Restaurant> restaurants;
    ifstream file(filePath);
    string line, token;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return restaurants;
    }

    getline(file, line);
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

vector<pair<string, vector<Discount*>>> readDiscounts(string filename) {
    ifstream file(filename);
    vector<pair<string, vector<Discount*>>> restaurant_discounts;

    if (!file.is_open()) {
        throw runtime_error("Could not open discounts file.");
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string restaurant_name, total_price_discount, first_order_discount, food_discounts;
        getline(ss, restaurant_name, ',');
        getline(ss, total_price_discount, ',');
        getline(ss, first_order_discount, ',');
        getline(ss, food_discounts, ',');

        vector<Discount*> discounts;

        if (total_price_discount != "none") {
            stringstream tp_stream(total_price_discount);
            string type;
            int minimum, value;
            getline(tp_stream, type, ';');
            tp_stream >> minimum >> value;
            discounts.push_back(new Total_Price_Discount(type, value, minimum));
        }

        if (first_order_discount != "none") {
            stringstream fo_stream(first_order_discount);
            string type;
            int value;
            getline(fo_stream, type, ';');
            fo_stream >> value;
            discounts.push_back(new First_Order_Discount(type, value));
        }

        if (food_discounts != "none") {
            stringstream fd_stream(food_discounts);
            string token;
            while (getline(fd_stream, token, '/')) {
                stringstream food_stream(token);
                string type, food_name;
                int value;
                getline(food_stream, type, ':');
                getline(food_stream, food_name, ':');
                food_stream >> value;
                discounts.push_back(new Food_Discount(type, value, food_name));
            }
        }

        restaurant_discounts.push_back({restaurant_name, discounts});
    }

    file.close();
    return restaurant_discounts;
}
