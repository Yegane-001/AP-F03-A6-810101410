#include "Utaste.h"
#include <iostream>
#include <sstream>
using namespace std;
const string GET = "GET";
const string PUT = "PUT";
const string DELETE = "DELETE";
const string POST = "POST";

void Utaste::handle_input() {
    string method;
    while(getline(cin,method)) {
    if(method.find(GET)==0)
        handle_get();
    else if(method.find(PUT)==0)
       handle_put();
    else if(method.find(DELETE)==0)
       handle_delete();
    else if(method.find(POST)==0)
        handle_post(method);
    else {
        cout<<"Bad Request"<<endl;
    }
       
    }
}

void Utaste::handle_post(const string method) {
    int state;
     std::string command, secondOrder;
    std::istringstream iss(method);
    iss >> command >> secondOrder;
    
    if (secondOrder == "signup") {
         std::string username, password;
        std::string word;
    
    while (iss >> word) {
        if (word == "username") {
            iss >> word;
            username = word.substr(1, word.size() - 2); // Remove the quotes
        } else if (word == "password") {
            iss >> word;
            password = word.substr(1, word.size() - 2); // Remove the quotes
        }
    }

    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    }

   

}
