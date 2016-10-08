//
// Created by Jonathan Yang on 05/10/2016.
//

#ifndef CLOUDAIRPORT_RANDOMHELPER_H
#define CLOUDAIRPORT_RANDOMHELPER_H

#include <cstdlib>
#include <memory>

class RandomHelper {
public:
    RandomHelper(double lr, double tr);

    // External
    int NewPlaneComing();

    int NewPlaneLeaving();

    int GetRandomFuel();

    // Internal
    double GetRate();

    int getNewPlane(double rate);

    // Getter and Setter
    int getMaxFuel();

    int getMinFuel();

    double getLandRate();

    double getTakeoffRate();

    void setMaxFuel(int maxf);

    void setMinFuel(int minf);

    void setLandRate(int lr);

    void setTakeoffRate(int tr);

private:
    double landing_rate_;
    double takeoff_rate_;

    int max_fuel_;
    int min_fuel_;
};


#endif //CLOUDAIRPORT_RANDOMHELPER_H
