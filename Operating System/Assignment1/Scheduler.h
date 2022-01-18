/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scheduler.h
 * Author: cheng shuhan
 *
 * Created on May 8, 2019, 9:47 PM
 */

// Scheduler.h
#ifndef __scheduler_h__
#define __scheduler_h__

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Process {
        uint32_t priority;
        uint32_t arrivalTime;
        uint32_t endedTime;
        uint32_t totalTime;
        uint32_t lastTotalTime;
        uint32_t blockInterval;
        uint32_t lastBlockInterval;
        uint32_t blockingTime;
        bool isFetched;
        bool isTerminated;
        string name;
};

class Scheduler {
    private:
        vector<Process *> arrivalList;
        vector<Process *> readyList[10];
        vector<Process *> blockList;
        Process *currentRunProcess;
        uint32_t currentTime;
        uint32_t blockDuration;
        uint32_t timeSlice;
        uint32_t totalCountProcesses;
    public:
        Scheduler(uint32_t blockDuration, uint32_t timeSlice);
        ~Scheduler();
        // Disallow copy/move
        Scheduler(const Scheduler &other) = delete;
        Scheduler(Scheduler &&other) = delete;
        Scheduler &operator=(const Scheduler &other) = delete;
        Scheduler &operator=(Scheduler &&other) = delete;
    
        int change_current_time(uint32_t timePassed);
        int insert_arrival_process(string name, uint32_t priority,
                uint32_t arrivalTime, uint32_t totalTime,
                uint32_t blockInterval);
        int show_arrivalList();
        int fetch_process_from_arrivalList_to_readyList_by_time();
        int show_readyList();
        int choose_a_process_to_run();
        int run_choosed_process();
        int run();
};

#endif
