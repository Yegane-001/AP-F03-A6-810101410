#ifndef UTASTE_H
#define UTASTE_H
using namespace std;
#include <string>
#include <vector>
#include "User.h"

class Utaste {
private:
    vector<User> users;
    User* current_user = nullptr;

public:
    void handle_input();
    void handle_get();
    void handle_put();
    void handle_delete();
    void handle_post(const string command);
    User* find_user(const string& username);
};

#endif
