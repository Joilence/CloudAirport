//
// Created by Jonathan Yang on 05/10/2016.
//

#ifndef CLOUDAIRPORT_LOGGER_H
#define CLOUDAIRPORT_LOGGER_H

#include "Plane.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Logger {
public:

    // Time Interval
    void NewLog(int time);

    void SaveLog();

    // Operation Log
    void PlaneRejectedToLand(const Plane& p);

    void PlaneRejectedToTakeoff(const Plane& p);

    void PlaneTookoff(const Plane& p);

    void PlaneLanded(const Plane& p);

    static std::shared_ptr<Logger> GetLogger();

    static vector<int> getStatistics();

    string getParticularLog(int time);

    vector<string> getAllLogs();

    void logAverageLandWaitingTime(int start_time);

    void logAverageTakeoffWaitingTime(int start_time);

private:

    Logger();

    vector<string> log;

    int time_;

    int sum_of_tookoff_;
    int sum_of_landed_;
    int sum_of_rejected_land_;
    int sum_of_rejected_takeoff_;

    int average_land_wait_;
    int average_takeoff_wait_;

    static std::shared_ptr<Logger> logger;

    string buffer;
};

#endif //CLOUDAIRPORT_LOGGER_H
