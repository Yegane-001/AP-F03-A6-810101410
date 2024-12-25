#ifndef DISTRICT_H
#define DISTRICT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class District {
public:
    string name;
    vector<string> neighbors;

    District();
    District(const string& districtName); 

    virtual void print() const;

    virtual ~District() = default;
    
};

#endif