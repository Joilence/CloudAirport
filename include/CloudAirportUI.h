//
// Created by Jonathan Yang on 05/10/2016.
//

#ifndef CLOUDAIRPORT_CLOUDAIRPORTUI_H
#define CLOUDAIRPORT_CLOUDAIRPORTUI_H

#include "Airport.h"
#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class CloudAirportUI {
public:
    // Constructor
    CloudAirportUI();

    ~CloudAirportUI();

    void Start();

    void OperationLoop();

    void ExcuteOperation(string cmd);;

    void CreateNewAirport();

    void ShowBaseData();

    void ShowStatistcis();

    void ShowLogForParticularTime();

    void ShowAllLogs();

    void RunAirportForOneTime();

    void RunAirportForPeriod();

    bool checkAirport();

private:
    bool quit_;
    std::shared_ptr<Airport> m_airport_;
};

#endif //CLOUDAIRPORT_CLOUDAIRPORTUI_H