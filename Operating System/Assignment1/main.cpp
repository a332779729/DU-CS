/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cheng shuhan
 *
 * Created on May 8, 2019, 9:46 PM
 */

// main.cpp

#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./main in.txt blockDuration timeSlice" << endl;
        return 1;
    }
    cout << argv[2]  << ' ' << argv[3] << endl;
    auto myScheduler = new Scheduler(atoi(argv[2]), atoi(argv[3]));
    ifstream infile(argv[1]);
    if (infile.is_open()) {
        string line, name;
        uint32_t priority, arrivalTime, totalTime, blockInterval;
        while (getline(infile, line)) {
            stringstream lineStream(line);
            lineStream >> name >> priority >> arrivalTime
                >> totalTime >> blockInterval;
            myScheduler->insert_arrival_process(name, priority,
                    arrivalTime, totalTime, blockInterval);
        }
    } else {
        cout << "File open error!" << endl;
        return 2;
    }
    infile.close();
    //myScheduler->show_arrivalList();
    while(true) {
        myScheduler->fetch_process_from_arrivalList_to_readyList_by_time();
        if (myScheduler->choose_a_process_to_run() == 0) {
            myScheduler->run_choosed_process();
        } else {
            break;
        }
    }

    delete myScheduler;
    return 0;
}
