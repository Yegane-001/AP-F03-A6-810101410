void Utaste::handle_get(const string method) {
    try {
        string command, secondOrder, argName, argValue;
        istringstream iss(method);
        iss >> command >> secondOrder;

        if (current_user == nullptr || current_user->get_state() != 2) {
            cout << PERMISSION_DENIED << endl;
            return;
        }

        if (secondOrder != DISTRICTS && secondOrder != "restaurants" && secondOrder != "restaurant_detail" && secondOrder != "reserves") {
            throw string(BAD_REQUEST);
        }

        if (secondOrder == DISTRICTS) {
            if (districts.empty()) {
                cout << EMPTY << endl;
                return;
            }

            string word;
            bool districtFilter = false;
            string districtName;
            while (iss >> word) {
                if (word == DISTRICT) {
                    iss >> word;
                    if (word.size() < 2 || word.front() != '"' || word.back() != '"') {
                        break;
                    }
                    districtName = word.substr(1, word.size() - 2);
                    if (districtName.empty()) {
                        break; 
                    }
                    districtFilter = true;
                    break;
                }
            }

            if (districtFilter) {
                auto it = find_if(districts.begin(), districts.end(), [&](const District& d) {
                    return d.name == districtName;
                });
                if (it != districts.end()) {
                    it->print();
                } else {
                    cout << NOT_FOUND << endl;
                }
            } else {
                sort(districts.begin(), districts.end(), [](const District& a, const District& b) {
                    return a.name < b.name;
                });
                for (const auto& district : districts) {
                    district.print();
                }
            }
        } else if (secondOrder == "restaurants") {
            if (current_user->get_location().empty()) {
                cout << NOT_FOUND << endl;
                return;
            }

            string userDistrict = current_user->get_location();
            string foodName;
            bool foodFilter = false;

            string word;
            while (iss >> word) {
                if (word == "food_name") {
                    iss >> ws; // Ignore leading whitespace
                    getline(iss, word);
                    size_t start = word.find('"');
                    size_t end = word.rfind('"');
                    if (start == string::npos || end == string::npos || start == end) {
                        throw string(BAD_REQUEST);
                    }
                    foodName = word.substr(start + 1, end - start - 1);
                    if (foodName.empty()) {
                        throw string(BAD_REQUEST);
                    }
                    foodFilter = true;
                    break;
                }
            }

            vector<Restaurant> filteredRestaurants;
            for (const auto& restaurant : restaurants) {
                if (foodFilter) {
                    bool found = false;
                    for (const auto& food : restaurant.foods) {
                        if (food.first == foodName) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) continue;
                }
                filteredRestaurants.push_back(restaurant);
            }

            if (filteredRestaurants.empty()) {
                cout << EMPTY << endl;
                return;
            }

            vector<string> nearbyDistricts = getNearbyDistricts(userDistrict);

            sort(filteredRestaurants.begin(), filteredRestaurants.end(), [&](const Restaurant& a, const Restaurant& b) {
                if (a.name == b.name) return a.restaurantName < b.restaurantName;
                auto itA = find(nearbyDistricts.begin(), nearbyDistricts.end(), a.name);
                auto itB = find(nearbyDistricts.begin(), nearbyDistricts.end(), b.name);
                return itA < itB;
            });

            for (const auto& restaurant : filteredRestaurants) {
                cout << restaurant.restaurantName << " (" << restaurant.name << ")" << endl;
            }
        }

        // برای دستورات دیگر مانند "restaurant_detail" و "reserves" می‌توانید کد مشابهی اضافه کنید

    } catch (const string& err) {
        cout << err << endl;
    }
}
