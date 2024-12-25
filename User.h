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
    string get_username();
    string get_password();
    int get_state();
    void set_state(int new_state);
    string get_location(); 
    void set_location(const string& loc);

};

#endif