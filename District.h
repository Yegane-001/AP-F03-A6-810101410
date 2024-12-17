#ifndef DISTRICT_H
#define DISTRICT_H

#include <iostream>
#include <vector>
#include <string>

class District {
public:
    std::string name;
    std::vector<std::string> neighbors;

    District(); // سازنده پیش‌فرض
    District(const std::string& districtName); // سازنده با نام

    virtual void print() const; // متد مجازی برای نمایش اطلاعات

    virtual ~District() = default; // مخرب پیش‌فرض
    
};

#endif // DISTRICT_H