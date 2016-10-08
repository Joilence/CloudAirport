//
// Created by Jonathan Yang on 05/10/2016.
//

#include "WaitingQueue.h"
#include <queue>
#include <list>
#include "Plane.h"
#include "Logger.h"

using std::list;

WaitingQueue::WaitingQueue(int max_size) : max_queue_size_(max_size) {
    m_logger_ = Logger::GetLogger();
}

bool WaitingQueue::AppendPlanes(int f) {
    if (queue_.size() <= max_queue_size_) {
        queue_.push_back(Plane(f));
        return true;
    }
    else {
        RejectPlane(Plane(f));
        return false;
    }
}

bool WaitingQueue::isEmpty() const {
    return queue_.empty();
}

int WaitingQueue::getMaxQueueSize() {
    return max_queue_size_;
}

void WaitingQueue::setMaxQueueSize(int max_size) {
    max_queue_size_ = max_size;
}

LandingQueue::LandingQueue(int max_size) : WaitingQueue(max_size) {}

void LandingQueue::RejectPlane(const Plane &p) {
    m_logger_->PlaneRejectedToLand(p);
}

void LandingQueue::Land() {
    m_logger_->PlaneLanded(queue_.front());
    m_logger_->logAverageLandWaitingTime(queue_.front().getStartTime());
    queue_.pop_front();
}

bool LandingQueue::IsPlaneCrash() {
    for (auto plane : queue_) {
        if (plane.GetFuel() <= 0) return true;
    }
    return false;
}

TakeoffQueue::TakeoffQueue(int max_size) : WaitingQueue(max_size) {}

void TakeoffQueue::RejectPlane(const Plane &p) {
    m_logger_->PlaneRejectedToTakeoff(p);
}

void TakeoffQueue::Takeoff() {
    m_logger_->PlaneTookoff(queue_.front());
    m_logger_->logAverageTakeoffWaitingTime(queue_.front().getStartTime());
    queue_.pop_front();
}
