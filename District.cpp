#include "District.h"

using namespace std;

District::District() = default;

District::District(const string& districtName) : district_name(districtName) {}

void District::print() const {
    cout << district_name << ": ";
    for (size_t i = 0; i < neighbors.size(); ++i) {
        cout << neighbors[i];
        if (i < neighbors.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

    

