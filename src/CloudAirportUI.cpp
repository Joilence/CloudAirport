//
// Created by Jonathan Yang on 05/10/2016.
//

#include "CloudAirportUI.h"
#include "Airport.h"
#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

CloudAirportUI::CloudAirportUI() {
    m_airport_ = nullptr;
    quit_ = false;
}

CloudAirportUI::~CloudAirportUI() {
    cout << "Good Bye!~" << endl;
}

void CloudAirportUI::Start() {
    cout << "------------ Cloud Airport ------------" << endl
         << "cr  - create new airport" << endl
         << "sb  - show base data" << endl
         << "ss  - show statistics" << endl
         << "sl  - show log for a particular time" << endl
         << "sal - show all log" << endl
         << "sq  - show all queues" << endl
         << "r   - run for one time unit" << endl
         << "rp  - run for a period of time" << endl
         << "q   - quit" << endl
         << "---------------------------------------" << endl;
    cout << "CA > ";
}

void CloudAirportUI::OperationLoop() {
    Start();
    while (!quit_) {
        string cmd;
        cin >> cmd;
        ExcuteOperation(cmd);
        cout << "CA > ";
    }
}

void CloudAirportUI::ExcuteOperation(string cmd) {
    if (cmd == "cr") {
        CreateNewAirport();
    } else if (cmd == "sb") {
        ShowBaseData();
    } else if (cmd == "ss") {
        ShowStatistcis();
    } else if (cmd == "r") {
        RunAirportForOneTime();
    } else if (cmd == "rp") {
        RunAirportForPeriod();
    } else if (cmd == "q") {
        quit_ = true;
    } else if (cmd == "sl") {
        ShowLogForParticularTime();
    } else if (cmd == "sal") {
        ShowAllLogs();
    } else {
        cout << "ERROR: Command Not Found!" << endl;
    }
}

void CloudAirportUI::CreateNewAirport() {
    int pl, pt, ol, ot, minf, maxf, max_size;
    double lr, tr;
    bool cf;
    cout << "Please input base data: \n"
         << "Runways usually for planes' landing: ";
    cin >> pl;
    cout << "Runways usually for planes' taking off: ";
    cin >> pt;
    cout << "Runways always (only) for planes' landing: ";
    cin >> ol;
    cout << "Runways always (only) for planes' taking off: ";
    cin >> ot;
    cout << "Land rate: ";
    cin >> lr;
    cout << "Take off rate: ";
    cin >> tr;
    cout << "Max size of waiting queue: ";
    cin >> max_size;
    cout << "Do you wanna consider fuel situation of landing plane?\n"
         << "(1 for Yes/ 0 for No) ";
    cin >> cf;
    m_airport_.reset(new Airport(pl, pt, pl ,ot, lr, tr, max_size));
    if (cf) {
        cout << "Input max fuel of landing plane: ";
        cin >> maxf;
        cout << "Input min fuel of landing plane: ";
        cin >> minf;

        m_airport_->setFuelConsidering(true);
        m_airport_->setMaxFuel(maxf);
        m_airport_->setMinFuel(minf);
    }
}

void CloudAirportUI::ShowBaseData() {
    if (!checkAirport()) return;
    int pl = m_airport_->getPrimaryLanding();
    int pt = m_airport_->getPrimaryTakeoff();
    int ol = m_airport_->getOnlyLanding();
    int ot = m_airport_->getOnlyTakeoff();
    double lr = m_airport_->getLandRate();
    double tr = m_airport_-> getTakeoffRate();
    int max_size = m_airport_->getMaxQueueSize();
    cout << "Runways usually for planes' landing: " << pl << endl
         << "Runways usually for planes' taking off: " << pt << endl
         << "Runways always (only) for planes' landing: " << ol << endl
         << "Runways always (only) for planes' taking off: " << ot << endl
         << "Land rate ( > 0): " << lr << endl
         << "Take off rate: ( > 0)" << tr << endl
         << "Max size of waiting queue: " << max_size << endl;
    if (m_airport_->getFuelConsidering()) {
        int maxf = m_airport_->getMaxFuel();
        int minf = m_airport_->getMinFuel();
        cout << "Input max fuel of landing plane: " <<maxf << endl
             << "Input min fuel of landing plane: " <<minf << endl;
    }
}

void CloudAirportUI::ShowStatistcis() {
    if (!checkAirport()) return;
    auto stat = Logger::getStatistics();
    if (stat.size() == 6) {
        cout << "Sum of planes took off: " << stat[0] << endl
             << "Sum of planes landed:  " << stat[1] << endl
             << "Sum of planes been rejected to takeoff: " << stat[2] << endl
             << "Sum of planes been rejected to land: " << stat[3] << endl
             << "Average waiting time for land: " << stat[4] << endl
             << "Average waiting time for takeoff: " << stat[5] << endl;
    } else {
        cout << "Logger is not prepared!" << endl;
    }
}

void CloudAirportUI::ShowLogForParticularTime() {
    if (!checkAirport()) return;
    cout << "Input the particular time you wanna check: ";
    int time;
    cin >> time;
    auto log = m_airport_->getParticularLog(time);
    cout << log;
    cout << endl;
}

void CloudAirportUI::ShowAllLogs() {
    if (!checkAirport()) return;
    auto logs = m_airport_->getAllLogs();
    for (string log : logs) {
        cout << log;
    }
    cout << endl;
}

void CloudAirportUI::RunAirportForOneTime() {
    if (!checkAirport()) return;
    m_airport_->PassOneTimeUnit();
}

void CloudAirportUI::RunAirportForPeriod() {
    if (!checkAirport()) return;
    cout << "Please input a number represent the time intervals you wanna pass: " << endl;
    cout << "> ";
    int period;
    cin >> period;
    while (period--) {
        RunAirportForOneTime();
    }
}

bool CloudAirportUI::checkAirport() {
    if (m_airport_ == nullptr) {
        cout << "You have to create a new Airport!" << endl;
        return false;
    }
    return true;
}
