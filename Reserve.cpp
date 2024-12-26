#include "Reserve.h"
#include <iostream>
using namespace std;

// سازنده کلاس
#include "Reserve.h"
#include <iostream>

Reserve::Reserve(Restaurant& r, User& u, int id, int tbl, int start_time, int end_time)
    : restaurant(r), user(u), reserve_id(id), table(tbl) {
    reserved_time[start_time] = end_time;
}


// متد دریافت شناسه رزرو
int Reserve::get_reserveId() const {
    return reserve_id;
}

// متد دریافت شماره میز
int Reserve::get_table() const {
    return table;
}

// متد دریافت زمان‌های رزرو
map<int, int> Reserve::get_reservedTime() const {
    return reserved_time;
}

// متد چاپ جزئیات رزرو
/*void Reserve::printReservationDetails() const {
    cout << "Reservation Details:" << endl;
    cout << "Reserve ID: " << reserve_id << endl;
    cout << "User: " << user.get_username() << endl;
    cout << "Restaurant: " << restaurant.restaurantName << endl;
    cout << "Table: " << table << endl;
    cout << "Reserved Time: ";
    for (const auto& time : reserved_time) {
        cout << time.first << ":" << time.second << " ";
    }
    cout << endl;
}*/
