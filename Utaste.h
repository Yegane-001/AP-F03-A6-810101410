#ifndef UTASTE_H
#define UTASTE_H
using namespace std;
#include <string>
#include <vector>
#include "User.h"
#include "District.h"
#include "Restaurant.h"
#include "Reserve.h"

class Utaste {
private:
    vector<User> users;
    User* current_user = nullptr;
    vector<District> districts;
    vector<Restaurant> restaurants;
    vector<Reserve> reservations;
    vector<Reserve> deleted_reserves;

public:
    Utaste(const vector<District>& districts, const vector<Restaurant>& restaurants);
    void handle_input();
    void handle_get(const string command);
    void handle_put(const string command);
    void handle_delete(const string command);
    void handle_post(const string command);
    User* find_user(const string& username);
    vector<string> getNearbyDistricts(const string& districtName);
    void addReservation(const Reserve& reservation);
    vector<Reserve> get_deletedReserves();
    void  add_deletedReservation(const Reserve& deleted);
};

#endif
