#include "Reserve.h"
#include <iostream>
using namespace std;
#include "Reserve.h"
#include <iostream>

Reserve::Reserve(Restaurant& r, User& u, int id, int tbl, int start_time, int end_time, const vector<string>& foods)
    : restaurant(r), user(u), reserve_id(id), table(tbl), foodList(foods){
    reserved_time[start_time] = end_time;
}

int Reserve::get_reserveId() const {
    return reserve_id;
}

int Reserve::get_table() const {
    return table;
}

map<int, int> Reserve::get_reservedTime() const {
    return reserved_time;
}

const vector<string>& Reserve::get_foodList() const {
     return foodList; 
}

