#include "Utaste.h"
#include <iostream>
#include <sstream>
const string GET = "GET";
const string PUT = "PUT";
const string DELETE = "DELETE";
const string POST = "POST";

void Utaste::handle_input() {
    string command;
    while(getline(cin,command)) {
    if(command.find(GET)==0)
        handle_get();
    else if(command.find(PUT)==0)
       handle_put();
    else if(command.find(DELETE)==0)
       handle_delete();
    else if(command.find(POST)==0)
        handle_post();
    else {
        cout<<"Bad Request"<<endl;
    }
       
    }
}