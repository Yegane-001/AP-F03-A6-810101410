#include "District.h"

using namespace std;

// سازنده پیش‌فرض
District::District() = default;

// سازنده با پارامتر نام
District::District(const string& districtName) : name(districtName) {}

// متد نمایش اطلاعات محله
void District::print() const {
    cout << "District: " << name << " Neighbors: ";
    for (const auto& neighbor : neighbors) {
        cout << neighbor << " ";
    }
    cout << endl;
}