//
// Created by Jonathan Yang on 05/10/2016.
//

#include "Plane.h"
#include <string>

using std::string;


int Plane::PlaneNum = 0;

Plane::Plane(int sc, int f) {
    start_clock_ = sc;
    id_ = ++PlaneNum;
    fuel_ = f;
}

int Plane::GetFuel() const {
    return fuel_;
}

string Plane::ToString() const {
    return string("Plane " + std::to_string(id_));
}

int Plane::getStartTime() {
    return start_clock_;
}
