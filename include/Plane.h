//
// Created by Jonathan Yang on 05/10/2016.
//

#ifndef CLOUDAIRPORT_PLANE_H
#define CLOUDAIRPORT_PLANE_H

#include <string>

using std::string;

class Plane {
public:
    Plane(int sc, int f = -1);

    int GetFuel() const;

    string ToString() const;

    int getStartTime();

private:
    static int PlaneNum;

    int id_;
    int fuel_;
    int start_clock_;
};

#endif //CLOUDAIRPORT_PLANE_H
