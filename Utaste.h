#ifndef UTASTE_H
#define UTASTE_H
using namespace std;
#include <string>
#include <vector>
#include "User.h"
#include "District.h"

class Utaste {
private:
    vector<User> users;
    User* current_user = nullptr;
    vector<District> districts;

public:
    Utaste(const vector<District>& districts);
    void handle_input();
    void handle_get(const string command);
    void handle_put(const string command);
    void handle_delete();
    void handle_post(const string command);
    User* find_user(const string& username);
};

#endif
