#include "User.h"
#include <iostream>
#include <sstream>
using namespace std;

User::User(const string& u, const string& p) : username(u), password(p), state(1) {}

string User::get_username() {
    return username;
}

string User::get_password() {
    return password;
}

int User::get_state() {
    return state;
}

void User::set_state(int new_state) {
    state = new_state;
}

string User::get_location() { 
    return location;
} 

void User::set_location(const string& loc) { 
    location = loc;
}
