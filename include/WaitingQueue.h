//
// Created by Jonathan Yang on 05/10/2016.
//

#ifndef CLOUDAIRPORT_WAITING_QUEUE_H
#define CLOUDAIRPORT_WAITING_QUEUE_H

#include <queue>
#include <list>
#include "Plane.h"
#include "Logger.h"

using std::list;

class WaitingQueue {
public:
    WaitingQueue(int max_size);


    bool AppendPlanes(int f);

    virtual void RejectPlane(const Plane& p) = 0;

    bool isEmpty() const;

    int getMaxQueueSize();

    void setMaxQueueSize(int max_size);

protected:
    int max_queue_size_;
    list<Plane> queue_;
    std::shared_ptr<Logger> m_logger_;
};

class LandingQueue: public WaitingQueue {
public:
    LandingQueue(int max_size);

    void RejectPlane(const Plane& p);

    void Land();

    bool IsPlaneCrash();
};

class TakeoffQueue: public WaitingQueue {
public:
    TakeoffQueue(int max_size);

    void RejectPlane(const Plane& p);;

    void Takeoff();
};

#endif //CLOUDAIRPORT_WAITING_QUEUE_H
