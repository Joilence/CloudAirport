//
// Created by Jonathan Yang on 05/10/2016.
//

#include "RandomHelper.h"
#include <cstdlib>
#include <memory>

RandomHelper::RandomHelper(double lr, double tr) :
        landing_rate_(lr),
        takeoff_rate_(tr),
        min_fuel_(-1),
        max_fuel_(-1) {}

int RandomHelper::NewPlaneComing() {
    return getNewPlane(landing_rate_);
}

int RandomHelper::NewPlaneLeaving() {
    return getNewPlane(takeoff_rate_);
}

int RandomHelper::GetRandomFuel() {
    return (rand() % (max_fuel_ - min_fuel_ + 1)) + min_fuel_;
}

double RandomHelper::GetRate() {
    return rand() / static_cast<double>(RAND_MAX);
}

int RandomHelper::getNewPlane(double rate) {
    if (rate <= 0) {
        return 0;
    } else if (0 < rate && rate <= 1) {
        return (rate > (rand() % (max_fuel_ - min_fuel_ + 1)) + min_fuel_);
    } else if (1 < rate && rate <= 10) {
        int max = rate + rate * 0.5;
        int min = rate - rate * 0.5;
        return rate > (rand() % (max - min + 1)) + min;
    } else {
        int max = rate + rate * 0.3;
        int min = rate - rate * 0.3;
        return rate > (rand() % (max - min + 1)) + min;
    }
}

int RandomHelper::getMaxFuel() {
    return max_fuel_;
}

int RandomHelper::getMinFuel() {
    return min_fuel_;
}

double RandomHelper::getLandRate() {
    return landing_rate_;
}

double RandomHelper::getTakeoffRate() {
    return takeoff_rate_;
}

void RandomHelper::setMaxFuel(int maxf) {
    max_fuel_ = maxf;
}

void RandomHelper::setMinFuel(int minf) {
    min_fuel_ = minf;
}

void RandomHelper::setLandRate(int lr) {
    landing_rate_ = lr;
}

void RandomHelper::setTakeoffRate(int tr) {
    takeoff_rate_ = tr;
}
