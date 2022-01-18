/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// Scheduler.cpp

#include "Scheduler.h"

using namespace std;

Scheduler::Scheduler(uint32_t blockDuration, uint32_t timeSlice)
{
    currentTime = 0;
    currentRunProcess = nullptr;
    this->blockDuration = blockDuration;
    this->timeSlice = timeSlice;
    totalCountProcesses = 0;
}

Scheduler::~Scheduler()
{
    for (auto p : arrivalList)
        delete p;
    arrivalList.clear();
}

/**
 * insert_arrival_process       insert arrival processes
 *
 * @param name            name of processes priority arrivalTime totalTime
 * @param priority         priority of processes
 * @param arrivalTime       arrivalTime of processes
 * @param totalTime         total time of processes
 * @param blockInterval         blockInterval time of processes
 *
 * @return                 0
 */
int Scheduler::insert_arrival_process(string name, uint32_t priority,
        uint32_t arrivalTime, uint32_t totalTime, uint32_t blockInterval)
{
    auto aProcess = new Process();
    if (aProcess == nullptr) {
        return -1;
    }

    aProcess->name = name;
    aProcess->priority = priority;
    aProcess->arrivalTime = arrivalTime;
    aProcess->endedTime = 0;
    aProcess->totalTime = totalTime;
    aProcess->lastTotalTime = totalTime;
    aProcess->blockInterval = blockInterval;
    aProcess->lastBlockInterval = blockInterval;
    aProcess->blockingTime = 0;
    aProcess->isFetched = false;
    aProcess->isTerminated = false;

    arrivalList.push_back(aProcess);
    totalCountProcesses += 1;
    return 0;
}

//this is a show arrivalList function
/**
 * show_arrivalList              show arrivalList of process
 *
 * @return                 0
 */
int Scheduler::show_arrivalList()
{
    if (arrivalList.size() == 0)
        return 0;
    cout << "n\tpri \tarr \t"
        << "tot \tlastT\t"
        << "bki \tlastBki \tlastBt"
        << endl;
    for (auto p : arrivalList) {
        cout << p->name << '\t' << p->priority << '\t'
            << p->arrivalTime << '\t' << p->totalTime << '\t'
            << p->lastTotalTime << '\t' << p->blockInterval << '\t'
            << p->lastBlockInterval << '\t' << p->blockingTime
            << endl;
    }
    return 0;
}

/**
 * fetch_process_from_arrivalList_to_readyList_by_time              fetch process from arrivalList to readyList by time
 *
 * @return                 0
 */
int Scheduler::fetch_process_from_arrivalList_to_readyList_by_time()
{
    for (auto p : arrivalList) {
        if (p->arrivalTime <= currentTime &&
                p->isFetched == false &&
                p->isTerminated == false) {
            p->isFetched = true;
            readyList[p->priority].push_back(p);
        }
    }
    return 0;
}

/**
 * show_readyList      show readyList
 *
 * @return                 0
 */
int Scheduler::show_readyList()
{
    for (auto i = 9; i >= 0; i--) {
        cout << "Lv " << i << ": ";
        for (auto p : readyList[i]) {
            cout << p->name << " ";
        }
        cout << endl;
    }
    return 0;
}

/**
 * choose_a_process_to_run      choose a process to run
 *
 * @return                 if we choose a process then return 0 otherwise 1
 */
int Scheduler::choose_a_process_to_run()
{
    Process *choosedProcess = nullptr;
    for (auto i = 9; i >= 0; i--) {
        if (readyList[i].size() > 0) {
            choosedProcess = readyList[i][0];
            readyList[i].erase(readyList[i].begin());
            break;
        }
    }
    if (choosedProcess != nullptr) {
        currentRunProcess = choosedProcess;
        return 0;
    } else {
        if (blockList.size() > 0) {
            // Find the minimum blocking time from processes
            // and free the choosed process
            uint32_t timeRun = blockList[0]->blockingTime;
            for (auto p : blockList) {
                if (p->blockingTime < timeRun)
                    timeRun = p->blockingTime;
            }
            for(auto p : arrivalList) {
                if(p->isFetched == false && p ->arrivalTime - currentTime < timeRun)
                    timeRun = p -> arrivalTime - currentTime;
            }
            cout <<" " << currentTime << '\t'
                << "(IDLE)\t"
                << timeRun << '\t'
                << 'I' << endl;
            change_current_time(timeRun);
            // Choose the process again
            for (auto i = 9; i >= 0; i--) {
                if (readyList[i].size() > 0) {
                    choosedProcess = readyList[i][0];
                    readyList[i].erase(readyList[i].begin());
                    break;
                }
            }
            currentRunProcess = choosedProcess;
            return 0;
        } else {
            // Calculate average turnaround time
            auto avgTurnTime = 0.0;
            for (auto p : arrivalList) {
                avgTurnTime += (p->endedTime - p->arrivalTime);
            }
            avgTurnTime /= arrivalList.size();
            // Scheduling all processes
            cout <<" "<< currentTime << '\t'
                << "(END)\t" << avgTurnTime
                << endl;
            return 1;
        }
    }
}

/**
 * change_current_time       change current time
 *
 * @param timePassed            time pass of scheduler
 *
 * @return                 0
 */
int Scheduler::change_current_time(uint32_t timePassed)
{
    // Rebuild block list
    vector<Process *> tmpBlockList;
    for (auto p : blockList) {
        if (p->blockingTime <= timePassed) {
            p->blockingTime = 0;
            p->lastBlockInterval = p->blockInterval;
            readyList[p->priority].push_back(p);
        } else {
            p->blockingTime -= timePassed;
            tmpBlockList.push_back(p);
        }
    }
    blockList.clear();
    for (auto p : tmpBlockList)
        blockList.push_back(p);

    if (currentRunProcess != nullptr) {
        currentRunProcess->lastTotalTime -= timePassed;
        currentRunProcess->lastBlockInterval -= timePassed;
    }
    currentTime += timePassed;
    return 0;
}

#define GOTO_TERMINATE 'T'
#define GOTO_BLOCK 'B'
#define GOTO_NEXTPROCESS 'S'

/**
 * run_choosed_process       run choosed process
 * @return                 0
 */
int Scheduler::run_choosed_process()
{
    uint32_t runTime = timeSlice;
    char direct = GOTO_NEXTPROCESS;

    if (currentRunProcess == nullptr) {
        //cout << "SOMETHING WRONG???" << endl;
        return 1;
    }

    runTime = min(timeSlice, currentRunProcess->lastTotalTime);
    runTime = min(runTime, currentRunProcess->lastBlockInterval);
    if (runTime == currentRunProcess->lastTotalTime) {
        direct = GOTO_TERMINATE;
    } else if (runTime == currentRunProcess->lastBlockInterval) {
        direct = GOTO_BLOCK;
    }

    // Now, let this process run
    cout <<" "<< currentTime << '\t'
        << currentRunProcess->name << '\t'
        << runTime << '\t'
        << direct << endl;
    change_current_time(runTime);

    if (direct == GOTO_NEXTPROCESS) {
        readyList[currentRunProcess->priority].push_back(currentRunProcess);
        currentRunProcess = nullptr;
    } else if (direct == GOTO_BLOCK) {
        blockList.push_back(currentRunProcess);
        currentRunProcess->blockingTime = blockDuration;
        currentRunProcess = nullptr;
    } else if (direct == GOTO_TERMINATE) {
        // cout << currentRunProcess->name << " terminated." << endl;
        currentRunProcess->endedTime = currentTime;
        currentRunProcess = nullptr;
    }

    return 0;
}
