//
// Created by Jonathan Yang on 05/10/2016.
//

#include "Airport.h"
#include <cstdlib>
#include <string>
#include "Plane.h"
#include "Logger.h"
#include "WaitingQueue.h"
#include "RandomHelper.h"

using std::string;


int Airport::Time = 0;

Airport::Airport(int pl, int pt, int ol, int ot, double lr, double tr, int max_queue_size) :
        primary_landing_(pl),
        primary_takeoff_(pt),
        only_landing_(ol),
        only_takeoff_(ot),
        random_(RandomHelper(lr, tr)),
        check_fuel_(false),
        landing_queue_(LandingQueue(max_queue_size)),
        takeoff_queue_(TakeoffQueue(max_queue_size)) {
    m_logger_ = Logger::GetLogger();
}

void Airport::PassOneTimeUnit() {
    Rountine();
    if (landing_queue_.IsPlaneCrash()) {}
    OperateOnce();
}

void Airport::OperateOnce() {
    int primary_takeoff = primary_takeoff_;
    int primary_landing = primary_landing_;
    int only_takeoff = primary_takeoff_;
    int only_landing = only_landing_;
    while (only_landing != 0 && !landing_queue_.isEmpty()) {
        landing_queue_.Land();
        --only_landing;
    }
    while (primary_landing != 0 && !landing_queue_.isEmpty()) {
        landing_queue_.Land();
        --primary_landing;
    }
    while (only_takeoff != 0 && !takeoff_queue_.isEmpty()) {
        takeoff_queue_.Takeoff();
        --only_takeoff;
    }
    while (primary_takeoff != 0 && !takeoff_queue_.isEmpty()) {
        takeoff_queue_.Takeoff();
        --primary_takeoff;
    }
    while (primary_takeoff != 0 && takeoff_queue_.isEmpty() && !landing_queue_.isEmpty()) {
        landing_queue_.Land();
        --primary_takeoff;
    }
    while (primary_landing != 0 && landing_queue_.isEmpty() && !takeoff_queue_.isEmpty()) {
        takeoff_queue_.Takeoff();
        --primary_landing;
    }

    m_logger_->SaveLog();
}

void Airport::Rountine() {
    ++Time;

    m_logger_->NewLog(Time);

    int coming_plane = random_.NewPlaneComing();
    while (coming_plane--) {
        if (check_fuel_) {
            landing_queue_.AppendPlanes(random_.GetRandomFuel());
        } else {
            landing_queue_.AppendPlanes();
        }
    }

    int leaving_plane = random_.NewPlaneLeaving();
    while (leaving_plane--) {
        if (check_fuel_) {
            takeoff_queue_.AppendPlanes(random_.GetRandomFuel());
        } else {
            takeoff_queue_.AppendPlanes();
        }
    }
}

int Airport::getPrimaryTakeoff() const {
    return primary_takeoff_;
}

int Airport::getPrimaryLanding() const {
    return primary_landing_;
}

int Airport::getOnlyTakeoff() const {
    return only_takeoff_;
}

int Airport::getOnlyLanding() const {
    return only_landing_;
}

bool Airport::getFuelConsidering() const {
    return check_fuel_;
}

void Airport::setPrimaryTakeoff(int pt) {
    primary_takeoff_ = pt;
}

void Airport::setPrimaryLanding(int pl) {
    primary_landing_ = pl;
}

void Airport::setOnlyTakeoff(int ot) {
    only_takeoff_ = ot;
}

void Airport::setOnlyLanding(int ol) {
    only_landing_ = ol;
}

void Airport::setFuelConsidering(bool cf) {
    check_fuel_ = cf;
}

int Airport::getMaxFuel() {
    return random_.getMaxFuel();
}

int Airport::getMinFuel() {
    return random_.getMinFuel();
}

double Airport::getLandRate() {
    return random_.getLandRate();
}

double Airport::getTakeoffRate() {
    return random_.getTakeoffRate();
}

int Airport::getMaxQueueSize() {
    return landing_queue_.getMaxQueueSize();
}

void Airport::setMaxFuel(int maxf) {
    random_.setMaxFuel(maxf);
}

void Airport::setMinFuel(int minf) {
    random_.setMinFuel(minf);
}

void Airport::setLandRate(int lr) {
    random_.setLandRate(lr);
}

void Airport::setTakeoffRate(int tr) {
    random_.setTakeoffRate(tr);
}

void Airport::setMaxQueueSize(int max_size) {
    landing_queue_.setMaxQueueSize(max_size);
    takeoff_queue_.setMaxQueueSize(max_size);
}

string Airport::getParticularLog(int time) {
    return m_logger_->getParticularLog(time);
}

vector<string> Airport::getAllLogs() {
    return m_logger_->getAllLogs();
}

