#ifndef USER_H
#define USER_H
using namespace std;
#include <string>

class User {
private:
    string username;
    string password;
    string location;
    int state;
public:
    User(const string& u,const string& p);
    string get_username() const;
    string get_password() const;
    int get_state() const;
    void set_state(int new_state);
    string get_location(); 
    void set_location(const string& loc);

};

#endif