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

vector<Restaurant> readDiscounts(vector<Restaurant>& restaurants, const string& discountsFile) {
    ifstream file(discountsFile);
    if (!file.is_open()) {
        cerr << "Could not open discounts file." << endl;
        return restaurants;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string restaurantName, total_price_discount, first_order_discount, food_discounts;

        getline(ss, restaurantName, ',');

        auto it = find_if(restaurants.begin(), restaurants.end(), [&restaurantName](const Restaurant& r) {
            return r.restaurantName == restaurantName;
        });

        if (it == restaurants.end()) continue;

        getline(ss, total_price_discount, ',');
        getline(ss, first_order_discount, ',');
        getline(ss, food_discounts, ',');

        if (!total_price_discount.empty()) {
            stringstream tp_stream(total_price_discount);
            string type;
            int minimum = 0, value = 0;
            getline(tp_stream, type, ';');
            tp_stream >> minimum;       
            tp_stream.ignore(1, ';');  
            tp_stream >> value; 

            Discount* totalPriceDiscount = new Total_Price_Discount(type, value, minimum);
            it->discounts.push_back(totalPriceDiscount);
        }

        if (!first_order_discount.empty()) {
            stringstream fo_stream(first_order_discount);
            string type;
            int value = 0;
            getline(fo_stream, type, ';');
            fo_stream >> value;            

            Discount* firstOrderDiscount = new First_Order_Discount(type, value);
            it->discounts.push_back(firstOrderDiscount);
        }

        if (!food_discounts.empty()) {
            stringstream fd_stream(food_discounts);
            string food_discount;
            while (getline(fd_stream, food_discount, '/')) {
                stringstream food_stream(food_discount);
                string type_food, food_name;
                int value = 0;

                getline(food_stream, type_food, ';');
                getline(food_stream, food_name, ':');
                food_stream >> value;               

                Discount* foodDiscount = new Food_Discount(type_food, value, food_name);
                it->discounts.push_back(foodDiscount);
            }
        }
    }

    file.close();
    for (auto& restaurant : restaurants) {
        restaurant.discounts.erase(
            remove_if(restaurant.discounts.begin(), restaurant.discounts.end(),
                      [](Discount* discount) {
                          return discount->get_type() == "none";
                      }),
            restaurant.discounts.end());
    }

    return restaurants;
}
