#include "Utaste.h"
#include "User.h"
#include <iostream>
#include <sstream>
#include <algorithm>
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
const string DISTRICTS = "districts"; 
const string DISTRICT = "district";
const string EMPTY = "empty";
const int LOGIN_STATE = 2;
const int LOGOUT_STATE = 3;
const int TWO_CHARACTER = 2;
const int ZERO = 0;
const int ONE = 1;

Utaste::Utaste(const vector<District>& districts) : districts(districts) {}

void Utaste::handle_input() {
    string method;
    while(getline(cin, method)) {
        if(method.find(GET) == ZERO)
            handle_get(method);
        else if(method.find(PUT) == ZERO)
            handle_put(method);
        else if(method.find(DELETE) == ZERO)
            handle_delete();
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
        string command, secondOrder;
        istringstream iss(method);
        iss >> command >> secondOrder;

        if (secondOrder != SIGNUP && secondOrder != LOGIN && secondOrder != LOGOUT) {
            throw NOT_FOUND;
        }

        string username, password;
        string word;
        if (secondOrder == SIGNUP || secondOrder == LOGIN) {
            bool hasUsername = false, hasPassword = false;
            while (iss >> word) {
                if (word == USERNAME) {
                    iss >> word;
                    if (word.size() < TWO_CHARACTER || word.front() != '"' || word.back() != '"') {
                        throw BAD_REQUEST;
                    }
                    username = word.substr(ONE, word.size() - TWO_CHARACTER);
                    if (username.empty()) {
                        throw BAD_REQUEST;
                    }
                    hasUsername = true;
                } else if (word == PASSWORD) {
                    iss >> word;
                    if (word.size() < TWO_CHARACTER || word.front() != '"' || word.back() != '"') {
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

        if (secondOrder == SIGNUP) {
            if (find_user(username) != nullptr) {
                cout << BAD_REQUEST << endl;
            } else {
                User new_user(username, password);
                users.push_back(new_user);
                cout << OK << endl;
            }

        } else if (secondOrder == LOGIN) {
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

        } else if (secondOrder == LOGOUT) {
            if (current_user == nullptr) {
                cout << PERMISSION_DENIED << endl;
            } else {
                current_user->set_state(LOGOUT_STATE);
                current_user = nullptr;
                cout << OK << endl;
            }
        }
    } catch (const string& err) {
        cout << err << endl;
    }
}


void Utaste::handle_get(const string method) {
    try {
        string command, secondOrder, argName, argValue;
        istringstream iss(method);
        iss >> command >> secondOrder;

        if (secondOrder != DISTRICTS) {
            throw BAD_REQUEST;
        }

        if (current_user == nullptr || current_user->get_state() != LOGIN_STATE) {
            cout << PERMISSION_DENIED << endl;
            return;
        }

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
                if (word.size() < TWO_CHARACTER || word.front() != '"' || word.back() != '"') {
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
    } catch (const string& err) {
        cout << err << endl;
    }
}


void Utaste::handle_delete() {}
void Utaste::handle_put(const string method) {
    try {
        string command, secondOrder;
        istringstream iss(method);
        iss >> command >> secondOrder;

        if (secondOrder != "my_district") {
            throw string(BAD_REQUEST);
        }

        if (current_user == nullptr || current_user->get_state() != 2) {
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
                remainingStream >> ws; // Ignore leading whitespace
                getline(remainingStream, word);
                size_t start = word.find('"');
                size_t end = word.rfind('"');
                if (start == string::npos || end == string::npos || start == end) {
                    throw string(BAD_REQUEST);
                }
                district = word.substr(start + 1, end - start - 1);
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
            return d.name == district;
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



