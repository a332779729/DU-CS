#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#include "SimplePriorityQueue.h"
using namespace std;


template <typename T>
class SimplePriorityQueue {
  // use vector to simulate it.
private:
  std::vector<T> underline_array;

public:
  SimplePriorityQueue(){};
  ~SimplePriorityQueue(){};
  void insert(T& e) {
//  underline_array.push_back(e); // (arriveTime, priority): (1, 3), (2, 2), (4, 1), (3, 1) <- (5, 1)
    bool insert_flag = false;
    for (auto it = underline_array.begin(); it != underline_array.end(); it++) {
      if (!(*it < e)) {
        underline_array.insert(it, e);
        insert_flag = true;
        break;
      }
    }
    if (!insert_flag)
      underline_array.push_back(e);

  }
  T pop() {
    T e = underline_array.back();
    underline_array.pop_back();
    return e;
  }
  bool is_empty() {
    return underline_array.empty();
  }

  int size() {
    return underline_array.size();
  }

  void show() {
    for (int i = 0; i < size(); i ++) {
      cout << underline_array[i].vehicleID << endl;
    }
  }
};


class vehicle {
public:
  string vehicleID;
  int arriveTime, refuelPriority;

  vehicle(){}
  vehicle(string& _id, int at, int rp):vehicleID(_id), arriveTime(at), refuelPriority(rp){}
  // if priority is equal, then the vehicle who has less arrivetime will place front
  bool operator<(vehicle& v) {
    if (refuelPriority == v.refuelPriority) return arriveTime > v.arriveTime; // (2, 2) < (5, 1) < (4, 1)
    return refuelPriority > v.refuelPriority; //
  }
  void show(ostream& out, int t) {
    out << "\"" << vehicleID << "\"" << "," << arriveTime << "," << t << endl;
//    cout << vehicleID << "," << arriveTime << "," << t << " " << refuelPriority << endl;
  }
};

template <typename T>
class Station {
private:
  int num;
  vector<T> pumps;
  int index;
  int time;
public:
  Station(int _num) {
    num = _num;
    pumps.resize(_num);
    index = -1;
  }
  void push(T& e, int t) {
    index += 1;
    pumps[index] = e;
    time = t;
  }
  void pop() {
    index = -1;
  }

  bool empty() {
    if (index == -1) return true;
    return false;
  }

};

void simulation(const char * input, const char * output) {
  std::ifstream file(input, std::ifstream::in);
  std::ofstream result(output, std::ofstream::out);
  int fuel_num = 2;
  file >> fuel_num;
  Station<vehicle> station(fuel_num);

  string vehicleID;
  int arriveTime, refuelPriority;

  vector<vehicle> all_vehicles;
  int ct = 0;
  while (!file.eof()) {
    file >> vehicleID >> arriveTime >> refuelPriority;
    all_vehicles.push_back(vehicle(vehicleID, arriveTime, refuelPriority));
  }
  int vehicles_num = all_vehicles.size();
  int currentTime = 0; // simulation by a step
  SimplePriorityQueue<vehicle> pq;

  int p = 0;
  int avaiable = fuel_num;
  while (true) {
    avaiable = fuel_num;
//    cout << "current time:     " << currentTime << endl;
    if (!station.empty()) {
      station.pop();
    }
    while (p < vehicles_num) {
      if (currentTime == all_vehicles[p].arriveTime) {
        pq.insert(all_vehicles[p]);
        p++;
      }
      else
        break;
    }
    if (!pq.is_empty()) {
      while(avaiable--) {
        if (!pq.is_empty()) {
          vehicle e = pq.pop();
          e.show(result, currentTime);
          station.push(e, currentTime);
        }
      }
    }

    currentTime ++;

    if (p >= vehicles_num and pq.is_empty() and station.empty()) {
      break;
    }
  }

  file.close();
  result.close();
}

int main() {
  simulation("./Data/sample.txt", "./Data/sample.txt.csv");
  simulation("./Data/vehicle_3_25.txt", "./Data/vehicle_3_25.txt.csv");
  simulation("./Data/vehicle_5_25.txt", "./Data/vehicle_5_25.txt.csv");
  simulation("./Data/vehicle_5_100.txt", "./Data/vehicle_5_100.txt.csv");
  return 0;
}