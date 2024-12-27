#include "Utaste.h"
#include "User.h"
#include "Restaurant.h"
#include "District.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
using namespace std;
const string GET = "GET";
const string PUT = "PUT";
const string DELETE = "DELETE";
const string POST = "POST";
const string SIGNUP = "signup";
const string USERNAME = "username";
const string BAD_REQUEST = "Bad Request";
const string PASSWORD = "password";
const string LOGIN = "login";
const string LOGOUT = "logout";
const string OK = "OK";
const string PERMISSION_DENIED = "Permission Denied";
const string NOT_FOUND = "Not Found";
const string EMPTY = "Empty";
const string DISTRICTS = "districts"; 
const string DISTRICT = "district";
const string SET_LOCATION = "setlocation"; 
const string RESTAURANTS = "restaurants";
const string RESTAURANT_DETAIL = "restaurant_detail";
const string RESTAURANT_NAME = "restaurant_name";
const string RESERVES = "reserves";
const string RESERVE = "reserve";
const string RESERVE_ID = "reserve_id";
const string TABLE_ID = "table_id";
const string FOOD_NAME = "food_name";
const string START_TIME = "start_time";
const string END_TIME = "end_time";
const string FOODS = "foods";
const string MY_DISTRICT = "my_district";
const int LOGIN_STATE = 2;
const int LOGOUT_STATE = 3;
const int TWO_CHARACTER = 2;
const int ZERO = 0;
const int ONE = 1;
const char Double_quotation = '"';
const char CAMA = ',';
const string SPACE = " ";


Utaste::Utaste(const vector<District>& districts, const vector<Restaurant>& restaurants) : districts(districts), restaurants(restaurants) {}

vector<string> Utaste::getNearbyDistricts(const string& districtName) {
    vector<string> result;
    auto it = find_if(districts.begin(), districts.end(), [&](const District& d) {
        return d.district_name == districtName;
    });
    if (it != districts.end()) {
        result = it->neighbors;
    }
    return result;
}

void Utaste::addReservation(const Reserve& reservation) { 
    reservations.push_back(reservation); 
}

void  Utaste::add_deletedReservation(const Reserve& deleted) {
    deleted_reserves.push_back(deleted);
}

void Utaste::handle_input() {
    string method;
    while(getline(cin, method)) {
        if(method.find(GET) == ZERO)
            handle_get(method);
        else if(method.find(PUT) == ZERO)
            handle_put(method);
        else if(method.find(DELETE) == ZERO)
            handle_delete(method);
        else if(method.find(POST) == ZERO)
            handle_post(method);
        else {
            cout << BAD_REQUEST << endl;
        }
    }
}


User* Utaste::find_user(const string& username) {
    for (auto& user : users) {
        if (user.get_username() == username) {
            return &user;
        }
    }
    return nullptr;
}

void Utaste::handle_post(const string method) {
    try {
        string command, action;
        istringstream iss(method);
        iss >> command >> action;

        if (action != SIGNUP && action != LOGIN && action != LOGOUT && action != RESERVE) {
            throw BAD_REQUEST;
        }

        string username, password;
        string word;
        if (action == SIGNUP || action == LOGIN) {
            bool hasUsername = false, hasPassword = false;
            while (iss >> word) {
                if (word == USERNAME) {
                    iss >> word;
                    if (word.size() < TWO_CHARACTER || word.front() != Double_quotation || word.back() != Double_quotation) {
                        throw BAD_REQUEST;
                    }
                    username = word.substr(ONE, word.size() - TWO_CHARACTER);
                    if (username.empty()) {
                        throw BAD_REQUEST;
                    }
                    hasUsername = true;
                } else if (word == PASSWORD) {
                    iss >> word;
                    if (word.size() < TWO_CHARACTER || word.front() != Double_quotation || word.back() != Double_quotation) {
                        throw BAD_REQUEST;
                    }
                    password = word.substr(ONE, word.size() - TWO_CHARACTER);
                    if (password.empty()) {
                        throw BAD_REQUEST;
                    }
                    hasPassword = true;
                }
            }
            if (!hasUsername || !hasPassword) {
                throw BAD_REQUEST;
            }
        }

        if (action == SIGNUP) {
            if (find_user(username) != nullptr) {
                cout << BAD_REQUEST << endl;
            } 
            else if (current_user!=nullptr)
            {
                cout << PERMISSION_DENIED <<endl;
            }
            else {
                User new_user(username, password);
                users.push_back(new_user);
                current_user = find_user(username);
                current_user->set_state(LOGIN_STATE);
                cout << OK << endl;
            }

        } else if (action == LOGIN) {
            if (users.empty()) { 
                cout << NOT_FOUND << endl;
                return;
            }

            User* user = find_user(username);
            if (user == nullptr) {
                cout << NOT_FOUND << endl;
            } else if (user->get_password() != password) {
                cout << PERMISSION_DENIED << endl;
            } else if (current_user != nullptr) {
                cout << PERMISSION_DENIED << endl;
            } else {
                current_user = user;
                current_user->set_state(LOGIN_STATE);
                cout << OK << endl;
            }

        } else if (action == LOGOUT) {
            if (current_user == nullptr) {
                cout << PERMISSION_DENIED << endl;
            } else {
                current_user->set_state(LOGOUT_STATE);
                current_user = nullptr;
                cout << OK << endl;
            }
        } 
        
        else if (action == RESERVE) {
            if (current_user == nullptr || current_user->get_state() != LOGIN_STATE) {
                cout << PERMISSION_DENIED << endl;
                return;
            }
            string restaurantName, tableId, startTime, endTime, foods;

            bool hasRestaurantName = false;
            bool hasTableId = false;
            bool hasStartTime = false;
            bool hasEndTime = false;
            bool hasFoods = false;

            while (iss >> word) {
                if (word == RESTAURANT_NAME) {
                    hasRestaurantName = true;
                    iss >> ws;
                    getline(iss, restaurantName, Double_quotation);
                    getline(iss, restaurantName, Double_quotation);
                } else if (word == TABLE_ID) {
                    hasTableId = true;
                    iss >> ws;
                    getline(iss, tableId, Double_quotation);
                    getline(iss, tableId, Double_quotation);
                } else if (word == START_TIME) {
                    hasStartTime = true;
                    iss >> ws;
                    getline(iss, startTime, Double_quotation);
                    getline(iss, startTime, Double_quotation);
                } else if (word == END_TIME) {
                    hasEndTime = true;
                    iss >> ws;
                    getline(iss, endTime, Double_quotation);
                    getline(iss, endTime, Double_quotation);
                } else if (word == FOODS) {
                    bool hasFoods = true;
                    iss >> ws; 
                    getline(iss, foods, Double_quotation);
                    getline(iss, foods, Double_quotation);
                }
            }

            if (!hasRestaurantName || !hasTableId || !hasStartTime || !hasEndTime) {
                throw string(BAD_REQUEST);
            }

            int start_time, end_time, table_id;
            start_time = stoi(startTime);
            end_time = stoi(endTime);
            table_id = stoi(tableId);
            auto restaurant_it = find_if(restaurants.begin(), restaurants.end(), [&](const Restaurant& r) {
                return r.restaurantName == restaurantName;
            });

            if (restaurant_it == restaurants.end()) throw string(NOT_FOUND);
            Restaurant& restaurant = *restaurant_it;
            if (start_time < 1 || end_time > 24 || start_time < restaurant.openingTime || end_time > restaurant.closingTime) {
                throw string(PERMISSION_DENIED);
            }
            if (table_id < 1 || table_id > restaurant.numTables) {
                throw string(NOT_FOUND);
            }
            vector<string> foodList;
            if (!foods.empty()) {
                istringstream foodStream(foods);
                string foodItem;
                while (getline(foodStream, foodItem, CAMA)) {
                    foodList.push_back(foodItem);
                }

                for (const auto& food : foodList) {
                    auto food_it = find_if(restaurant.foods.begin(), restaurant.foods.end(), [&](const pair<string, int>& f) {
                        return f.first == food;
                    });
                    if (food_it == restaurant.foods.end()) {
                        throw string(NOT_FOUND);
                    }
                }
            }

            for (const auto& res : reservations) {
                if (res.restaurant.restaurantName == restaurantName && res.get_table() == table_id) {
                    for (const auto& time : res.get_reservedTime()) {
                        if ((start_time >= time.first && start_time < time.second) ||
                            (end_time > time.first && end_time <= time.second)) {
                            throw string(PERMISSION_DENIED);
                        }
                    }
                }

                if (res.user.get_username() == current_user->get_username()) {
                    for (const auto& time : res.get_reservedTime()) {
                        if ((start_time >= time.first && start_time < time.second) ||
                            (end_time > time.first && end_time <= time.second)) {
                            throw string(PERMISSION_DENIED);
                        }
                    }
                }
            }
            int reserve_id = 1;
            for (const auto& res : reservations) {
                if (res.restaurant.restaurantName == restaurantName) {
                    reserve_id++;
                }
            }
            for (const auto& res2 : deleted_reserves) {
                if (res2.restaurant.restaurantName == restaurantName) {
                    reserve_id++;
                }
            }
            
            
            Reserve new_reserve(restaurant, *current_user, reserve_id, table_id, start_time, end_time, foodList);
            int total_price = 0;
            map<int, int> reserved_time;
            for (int hour = start_time; hour <= end_time; ++hour) {
                reserved_time[hour] = table_id;
            }
            new_reserve.get_reservedTime() = reserved_time;

            for (const auto& food : foodList) {
                auto food_it = find_if(restaurant.foods.begin(), restaurant.foods.end(), [&](const pair<string, int>& f) {
                    return f.first == food;
                });
                if (food_it != restaurant.foods.end()) {
                    total_price += food_it->second;
                }
            }

            addReservation(new_reserve);

            cout << "Reserve ID: " << reserve_id << endl;
            cout << "Table " << table_id << " for " << start_time << " to " << end_time << " in " << restaurantName << endl;
            cout << "Price: " << total_price << endl;
        }

    } 
    
    catch (const string& err) {
        cout << err << endl;
    }
}




void Utaste::handle_get(const string method) {
    try {
        string command, secondOrder, argName, argValue;
        istringstream iss(method);
        iss >> command >> secondOrder;

        if (current_user == nullptr || current_user->get_state() != LOGIN_STATE) {
            cout << PERMISSION_DENIED << endl;
            return;
        }

        if (secondOrder != DISTRICTS && secondOrder != RESTAURANTS && secondOrder != RESTAURANT_DETAIL && secondOrder != RESERVES) {
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
                    if (word.size() < TWO_CHARACTER || word.front() != Double_quotation || word.back() != Double_quotation) {
                        break;
                    }
                    districtName = word.substr(ONE, word.size() - TWO_CHARACTER);
                    if (districtName.empty()) {
                        break; 
                    }
                    districtFilter = true;
                    break;
                }
            }

            if (districtFilter) {
                auto it = find_if(districts.begin(), districts.end(), [&](const District& d) {
                    return d.district_name == districtName;
                });
                if (it != districts.end()) {
                    it->print();
                } else {
                    cout << NOT_FOUND << endl;
                }
            } else {
                sort(districts.begin(), districts.end(), [](const District& a, const District& b) {
                    return a.district_name < b.district_name;
                });
                for (const auto& district : districts) {
                    district.print();
                }
            }
        } 

       else if (secondOrder == RESTAURANTS) {
            if (current_user->get_location().empty()) {
                cout << NOT_FOUND << endl;
                return;
            }

            string userDistrict = current_user->get_location();
            string foodName;
            bool foodFilter = false;

            string word;
            while (iss >> word) {
                if (word == FOOD_NAME) {
                    iss >> ws;
                    getline(iss, word);
                    size_t start = word.find(Double_quotation);
                    size_t end = word.rfind(Double_quotation);
                    if (start == string::npos || end == string::npos || start == end) {
                        throw string(BAD_REQUEST);
                    }
                    foodName = word.substr(start + ONE, end - start - ONE);
                    if (foodName.empty()) {
                        throw string(BAD_REQUEST);
                    }
                    foodFilter = true;
                    break;
                }
            }

            set<string> printedRestaurants;

            auto filterAndPrintRestaurants = [&](const vector<Restaurant>& restaurants) {
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
                    if (printedRestaurants.find(restaurant.restaurantName) == printedRestaurants.end()) {
                        filteredRestaurants.push_back(restaurant);
                    }
                }

                sort(filteredRestaurants.begin(), filteredRestaurants.end(), [](const Restaurant& a, const Restaurant& b) {
                    return a.restaurantName < b.restaurantName;
                });

                for (const auto& restaurant : filteredRestaurants) {
                    cout << restaurant.restaurantName << " (" << restaurant.district_name << ")" << endl;
                    printedRestaurants.insert(restaurant.restaurantName);
                }
            };
            

            vector<Restaurant> userDistrictRestaurants;
            for (const auto& restaurant : restaurants) {
                if (restaurant.district_name == userDistrict) {
                    userDistrictRestaurants.push_back(restaurant);
                }
            }
            filterAndPrintRestaurants(userDistrictRestaurants);

            auto printNearbyRestaurants = [&](const vector<string>& nearbyDistricts) {
                for (const auto& neighbor : nearbyDistricts) {
                    vector<Restaurant> neighborRestaurants;
                    for (const auto& restaurant : restaurants) {
                        if (restaurant.district_name == neighbor) {
                            neighborRestaurants.push_back(restaurant);
                        }
                    }
                    filterAndPrintRestaurants(neighborRestaurants);
                }
            };

            vector<string> nearbyDistricts = getNearbyDistricts(userDistrict);
            printNearbyRestaurants(nearbyDistricts);

            for (const auto& neighbor : nearbyDistricts) {
                vector<string> secondDegreeDistricts = getNearbyDistricts(neighbor);
                printNearbyRestaurants(secondDegreeDistricts);
            }

            vector<Restaurant> remainingRestaurants;
            for (const auto& restaurant : restaurants) {
                if (restaurant.district_name != userDistrict &&
                    find(nearbyDistricts.begin(), nearbyDistricts.end(), restaurant.district_name) == nearbyDistricts.end()) {
                    bool inSecondDegree = false;
                    for (const auto& neighbor : nearbyDistricts) {
                        vector<string> secondDegreeDistricts = getNearbyDistricts(neighbor);
                        if (find(secondDegreeDistricts.begin(), secondDegreeDistricts.end(), restaurant.district_name) != secondDegreeDistricts.end()) {
                            inSecondDegree = true;
                            break;
                        }
                    }
                    if (!inSecondDegree) {
                        remainingRestaurants.push_back(restaurant);
                    }
                }
            }
            filterAndPrintRestaurants(remainingRestaurants);
        }

        else if(secondOrder == RESTAURANT_DETAIL) {
            if (current_user == nullptr) {
                cout << PERMISSION_DENIED << endl;
                return;
            }
            string word;
            string restaurantName;

            while (iss >> word) {
                if (word == RESTAURANT_NAME) {
                    iss >> ws;
                    getline(iss, restaurantName, Double_quotation);
                    getline(iss, restaurantName, Double_quotation);
                    if (restaurantName.empty()) {
                        throw string(BAD_REQUEST);
                    }
                    break;
                }
            }

        if (restaurantName.empty()) {
            throw string(BAD_REQUEST);
        }

        auto restaurant_it = find_if(restaurants.begin(), restaurants.end(), [&](const Restaurant& r) {
            return r.restaurantName == restaurantName;
        });

        if (restaurant_it == restaurants.end()) throw string(NOT_FOUND);

        const Restaurant& restaurant = *restaurant_it;

        cout << "Name: " << restaurant.restaurantName << endl;
        cout << "District: " << restaurant.district_name << endl;
        cout << "Time: " << restaurant.openingTime << "-" << restaurant.closingTime << endl;
        cout << "Menu: ";
        vector<pair<string, int>> sortedMenu(restaurant.foods.begin(), restaurant.foods.end());
        sort(sortedMenu.begin(), sortedMenu.end());
        for (size_t i = 0; i < sortedMenu.size(); ++i) {
            cout << sortedMenu[i].first << "(" << sortedMenu[i].second << ")";
            if (i != sortedMenu.size() - 1) {
                cout << " ,";
            }
        }
        cout << endl;

        for (int i = 1; i <= restaurant.numTables; ++i) {
            cout << i << ": ";
            vector<pair<int, int>> tableReservations;
            for (const auto& res : reservations) {
                if (res.restaurant.restaurantName == restaurant.restaurantName && res.get_table() == i) {
                    for (const auto& time : res.get_reservedTime()) {
                        tableReservations.push_back({time.first, time.second});
                    }
                }
            }
            sort(tableReservations.begin(), tableReservations.end());
            for (size_t j = 0; j < tableReservations.size(); ++j) {
                if (j > 0) {
                    cout << ", ";
                }
                cout << "(" << tableReservations[j].first << "-" << tableReservations[j].second << ")";
            }
            cout << endl;
        }

        }

        else if (secondOrder == RESERVES) {
            string word, restaurantName, reserveIdStr;
            int reserveId = 0;
            bool hasRestaurantName = false, hasReserveId = false;

            while (iss >> word) {
                if (word == RESTAURANT_NAME) {
                    iss >> ws;
                    getline(iss, restaurantName, Double_quotation);
                    getline(iss, restaurantName, Double_quotation);
                    hasRestaurantName = true;
                } else if (word == RESERVE_ID) {
                    if (!hasRestaurantName) throw string(BAD_REQUEST);
                    iss >> ws;
                    getline(iss, reserveIdStr, Double_quotation);
                    getline(iss, reserveIdStr, Double_quotation);
                    reserveId = stoi(reserveIdStr);
                    hasReserveId = true;
                }
            }

            if (hasRestaurantName) {
                auto restaurant_it = find_if(restaurants.begin(), restaurants.end(), [&](const Restaurant& r) {
                    return r.restaurantName == restaurantName;
                });
                if (restaurant_it == restaurants.end()) throw string(NOT_FOUND);
            }

            vector<Reserve> userReserves;
            bool reserveFound = false;

            for (const auto& res : reservations) {
                if (res.user.get_username() == current_user->get_username()) {
                    if (hasRestaurantName && res.restaurant.restaurantName != restaurantName) continue;
                    if (hasReserveId && res.get_reserveId() != reserveId) continue;
                    userReserves.push_back(res);
                }
                if (hasReserveId && res.restaurant.restaurantName == restaurantName && res.get_reserveId() == reserveId) {
                    reserveFound = true;
                }
            }

            if (hasReserveId && !reserveFound) throw string(NOT_FOUND);
            if (hasReserveId && userReserves.empty()) throw string(PERMISSION_DENIED);
            if (userReserves.empty()) throw string("Empty");

            sort(userReserves.begin(), userReserves.end(), [](const Reserve& a, const Reserve& b) {
                return a.get_reservedTime().begin()->first < b.get_reservedTime().begin()->first;
            });

            for (const auto& res : userReserves) {
                cout << res.get_reserveId() << ": " << res.restaurant.restaurantName << SPACE
                     << res.get_table() << SPACE
                     << res.get_reservedTime().begin()->first << "-" << res.get_reservedTime().rbegin()->second;

                const auto& foodList = res.get_foodList();
                if (!foodList.empty()) {
                    cout << SPACE;
                    map<string, int> foodCount;
                    for (const auto& food : foodList) {
                        foodCount[food]++;
                    }
                    for (auto it = foodCount.begin(); it != foodCount.end(); ++it) {
                        cout << it->first << " (" << it->second << ")";
                        if (next(it) != foodCount.end()) cout << SPACE;
                    }
                }
                cout << endl;
            }
        }
    } 
    catch (const string& err) {
        cout << err << endl;
    }
}




void Utaste::handle_delete(const string method) {
    try {
        string command, action;
        istringstream iss(method);
        iss >> command >> action;

        if (current_user == nullptr) {
            throw string(PERMISSION_DENIED);
        }

        if (action != RESERVE) {
            throw string(BAD_REQUEST);
        }

        string word, restaurantName, reserveIdStr;
        int reserveId = ZERO;
        bool hasRestaurantName = false, hasReserveId = false;

        while (iss >> word) {
            if (word == RESTAURANT_NAME) {
                iss >> ws;
                getline(iss, restaurantName, Double_quotation);
                getline(iss, restaurantName, Double_quotation);
                hasRestaurantName = true;
            } else if (word == RESERVE_ID) {
                iss >> ws;
                getline(iss, reserveIdStr, Double_quotation);
                getline(iss, reserveIdStr, Double_quotation);
                reserveId = stoi(reserveIdStr);
                hasReserveId = true;
            }
        }

        if (!hasRestaurantName || !hasReserveId) {
            throw string(BAD_REQUEST);
        }

        auto restaurant_it = find_if(restaurants.begin(), restaurants.end(), [&](const Restaurant& r) {
            return r.restaurantName == restaurantName;
        });

        if (restaurant_it == restaurants.end()) {
            throw string(NOT_FOUND);
        }

        auto reserve_it = find_if(reservations.begin(), reservations.end(), [&](const Reserve& res) {
            return res.restaurant.restaurantName == restaurantName && res.get_reserveId() == reserveId;
        });

        if (reserve_it == reservations.end()) {
            throw string(NOT_FOUND);
        }

        if (reserve_it->user.get_username() != current_user->get_username()) {
            throw string(PERMISSION_DENIED);
        }
        add_deletedReservation(*reserve_it);
        reservations.erase(reserve_it);
        cout << OK << endl;

    } catch (const string& err) {
        cout << err << endl;
    }
}

void Utaste::handle_put(const string method) {
    try {
        string command, secondOrder;
        istringstream iss(method);
        iss >> command >> secondOrder;

        if (secondOrder != MY_DISTRICT) {
            throw string(BAD_REQUEST);
        }

        if (current_user == nullptr || current_user->get_state() != LOGIN_STATE) {
            cout << PERMISSION_DENIED << endl;
            return;
        }

        string remainingInput;
        getline(iss, remainingInput);
        istringstream remainingStream(remainingInput);
        
        string word, district;
        bool districtProvided = false;
        while (remainingStream >> word) {
            if (word == DISTRICT) {
                remainingStream >> ws;
                getline(remainingStream, word);
                size_t start = word.find(Double_quotation);
                size_t end = word.rfind(Double_quotation);
                if (start == string::npos || end == string::npos || start == end) {
                    throw string(BAD_REQUEST);
                }
                district = word.substr(start + ONE, end - start - ONE);
                if (district.empty()) {
                    throw string(BAD_REQUEST);
                }
                districtProvided = true;
                break;
            }
        }

        if (!districtProvided) {
            throw string(BAD_REQUEST);
        }

        auto it = find_if(districts.begin(), districts.end(), [&](const District& d) {
            return d.district_name == district;
        });

        if (it != districts.end()) {
            current_user->set_location(district);
            cout << OK << endl;
        } else {
            cout << NOT_FOUND << endl;
        }
    } catch (const string& err) {
        cout << err << endl;
    }
}



