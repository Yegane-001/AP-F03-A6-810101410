#ifndef RESERVE_H
#define RESERVE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "User.h"
#include "Restaurant.h"
using namespace std;
class Reserve {
    private: 
        int reserve_id;
        int table;
        map<int,int> reserved_time;
    public:
        Restaurant restaurant;
        User user; 
        Reserve(Restaurant& r , User& u , int id , int tbl , int start_time , int end_time);
        int get_reserveId() const;
        int get_table() const;
        map<int,int> get_reservedTime() const;
};

#endif