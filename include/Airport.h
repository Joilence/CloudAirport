//
// Created by Jonathan Yang on 05/10/2016.
//

#ifndef CLOUDAIRPORT_AIRPORT_H
#define CLOUDAIRPORT_AIRPORT_H

#include <cstdlib>
#include <string>
#include "Plane.h"
#include "Logger.h"
#include "WaitingQueue.h"
#include "RandomHelper.h"

using std::string;
using std::vector;

class Airport {
public:

    // Constructor
    // TODO: make constructor smaller
    Airport(int pl, int pt, int ol, int ot, double lr, double tr, int max_queue_size);


    void PassOneTimeUnit();

    void OperateOnce();

    void Rountine();

    // Getter and Setter
    // Level 1
    int getPrimaryTakeoff() const;

    int getPrimaryLanding() const;

    int getOnlyTakeoff() const;

    int getOnlyLanding() const;

    bool getFuelConsidering() const;

    void setPrimaryTakeoff(int pt);

    void setPrimaryLanding(int pl);

    void setOnlyTakeoff(int ot);

    void setOnlyLanding(int ol);

    void setFuelConsidering(bool cf);

    // Level 2

    int getMaxFuel();

    int getMinFuel();

    double getLandRate();

    double getTakeoffRate();

    int getMaxQueueSize();

    void setMaxFuel(int maxf);

    void setMinFuel(int minf);

    void setLandRate(int lr);

    void setTakeoffRate(int tr);

    void setMaxQueueSize(int max_size);

    // Logs

    string getParticularLog(int time);

    vector<string> getAllLogs();

    static int Time;

private:
    int primary_takeoff_;
    int primary_landing_;
    int only_takeoff_;
    int only_landing_;

    LandingQueue landing_queue_;
    TakeoffQueue takeoff_queue_;

    bool check_fuel_;

    std::shared_ptr<Logger> m_logger_;
    RandomHelper random_;
};

#endif //CLOUDAIRPORT_AIRPORT_H
