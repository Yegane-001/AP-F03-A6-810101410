#ifndef USER_H
#define USER_H
using namespace std;
#include <string>

class User {
private:
    string username;
    string password;
public:
    string get_username();
    string get_password();

};

#endif