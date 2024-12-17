#include "Utaste.h"
#include "User.h"
#include <iostream>
#include <sstream>
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

void Utaste::handle_input() {
    string method;
    while(getline(cin, method)) {
        if(method.find(GET) == 0)
            handle_get();
        else if(method.find(PUT) == 0)
            handle_put();
        else if(method.find(DELETE) == 0)
            handle_delete();
        else if(method.find(POST) == 0)
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
    string command, secondOrder;
    istringstream iss(method);
    iss >> command >> secondOrder;

    if (secondOrder == SIGNUP) {
        string username, password;
        string word;

        while (iss >> word) {
            if (word == USERNAME) {
                iss >> word;
                username = word.substr(1, word.size() - 2);
            } else if (word == PASSWORD) {
                iss >> word;
                password = word.substr(1, word.size() - 2);
            }
        }

        if (find_user(username) != nullptr) {
            cout << BAD_REQUEST << endl;
        } else {
            User new_user(username, password);
            users.push_back(new_user);
            cout << OK << endl;
        }

    } else if (secondOrder == LOGIN) {
        string username, password;
        string word;

        while (iss >> word) {
            if (word == USERNAME) {
                iss >> word;
                username = word.substr(1, word.size() - 2);
            } else if (word == PASSWORD) {
                iss >> word;
                password = word.substr(1, word.size() - 2);
            }
        }

        if (users.empty()) {  // بررسی اینکه هیچ کاربری ثبت‌نام نکرده است
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
            current_user->set_state(2); // حالت لاگین
            cout << OK << endl;
        }

    } else if (secondOrder == LOGOUT) {
        if (current_user == nullptr) {
            cout << PERMISSION_DENIED << endl;
        } else {
            current_user->set_state(3); // حالت خروج
            current_user = nullptr;
            cout << OK << endl;
        }
    }
}

void Utaste::handle_get() {}
void Utaste::handle_delete() {}
void Utaste::handle_put() {}
