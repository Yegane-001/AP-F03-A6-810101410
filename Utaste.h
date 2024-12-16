#ifndef UTASTE_H
#define UTASTE_H
using namespace std;
#include <string>

class Utaste {
private:
    
public:
   void handle_input();
   void handle_get();
   void handle_put();
   void handle_delete();
   void handle_post(const string command);

};

#endif