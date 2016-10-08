//
// Created by Jonathan Yang on 05/10/2016.
//

#include "Logger.h"
#include "Plane.h"
#include "Airport.h"
#include <vector>
#include <string>

using std::vector;
using std::string;


std::shared_ptr<Logger> Logger::logger = nullptr;

void Logger::NewLog(int time) {
    buffer = "Time: " + std::to_string(time) + "\n";
    time_ = time;
}

void Logger::SaveLog() {
    log.push_back(buffer);
}

void Logger::PlaneRejectedToLand(const Plane &p) {
    buffer += p.ToString() + " is rejected to land.\n";
    ++sum_of_rejected_land_;
}

void Logger::PlaneRejectedToTakeoff(const Plane &p) {
    buffer += p.ToString() + " is rejected to take off.\n";
    ++sum_of_rejected_takeoff_;
}

void Logger::PlaneTookoff(const Plane &p) {
    buffer += p.ToString() + " takes off.\n";
    ++sum_of_tookoff_;
}

void Logger::PlaneLanded(const Plane &p) {
    buffer += p.ToString() + " lands.\n";
    ++sum_of_landed_;
}

std::shared_ptr<Logger> Logger::GetLogger() {
    if (Logger::logger == nullptr)
        Logger::logger.reset(new Logger());
    return Logger::logger;
}

vector<int> Logger::getStatistics() {
    auto logger = Logger::GetLogger();
    vector<int> stat = {
            logger->sum_of_tookoff_,
            logger->sum_of_landed_,
            logger->sum_of_rejected_takeoff_,
            logger->sum_of_rejected_land_,
            logger->average_takeoff_wait_,
            logger->average_land_wait_
    };
    return stat;
}

string Logger::getParticularLog(int time) {
    return (log.size() != 0) ? log[time + 1] : "ERROR: There's no log.";
}

vector<string> Logger::getAllLogs() {
    return log;
}

void Logger::logAverageLandWaitingTime(int start_time) {
    average_land_wait_ = (average_land_wait_ * (sum_of_landed_ - 1) + time_ - start_time) / sum_of_landed_;
}

void Logger::logAverageTakeoffWaitingTime(int start_time) {
    average_takeoff_wait_ = (average_takeoff_wait_ * (sum_of_tookoff_ - 1) + time_ - start_time) / sum_of_tookoff_;
}

Logger::Logger() {
    int sum_of_tookoff_ = 0;
    int sum_of_landed_ = 0;
    int sum_of_rejected_land_ = 0;
    int sum_of_rejected_takeoff_ = 0;
    int average_land_wait_;
    int average_takeoff_wait_ = 0;

    int time_ = 0;
}