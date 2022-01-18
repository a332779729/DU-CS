/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// HexHistogram.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "HexHistogram.h"

using namespace std;

HexHistogram::HexHistogram(std::string filename)
{
	ifstream file(filename);
	if (file.is_open()) {
		stringstream strStream;
		strStream << file.rdbuf();
		data = strStream.str();
		file.close();
	} else {
		string errorInfo;
		errorInfo.append("Error: open(): ").append(filename);
		throw std::runtime_error(errorInfo);
	}
}

HexHistogram::~HexHistogram()
{
	// Do nothing
}

  /**
   * find the every value count can be same
   * functionName    get_value_count
   * @return         return every value Count which can be same
   */
uint32_t HexHistogram::get_value_count()
{
	string line;
	uint32_t num = 0;
	uint64_t sum = 0;
	istringstream f(data);

	while (getline(f, line)) { h
		lines.push_back(line);
		istringstream iLine(line);
		while (iLine >> hex >> num) {
				sum += num;
				allItems.push_back(num);
		}
		linesSum.push_back(sum);
			sum = 0;
		}

	valueCount = allItems.size();
	return valueCount;
}
/**
   * find the unique value count
   * functionName    get_unique_value_count()
   * @return         return the every unique Value Count
   */
uint32_t HexHistogram::get_unique_value_count()
{
	sort(allItems.begin(), allItems.end());
	for (auto &item : allItems) {
		if (uniqueItems.size() == 0 || uniqueItems.back() != item) {
			uniqueItems.push_back(item);
			uniqueItemsCount.push_back(1);
		} else if (uniqueItems.back() == item) {
			uniqueItemsCount[uniqueItems.size() - 1] += 1;
		}
	}
	uniqueValueCount = uniqueItems.size();
	return uniqueValueCount;
}

/**
   * find the max line sum
   * functionName    get_max_line_sum()
   * @return         which one is the max Line Sum
   */
uint64_t HexHistogram::get_max_line_sum()
{
	uint64_t maxSum = 0;
	for (auto i = 0; i < linesSum.size(); i++) {
		if (maxSum < linesSum[i])
			maxSum = linesSum[i];
	}

	maxLineSum = maxSum;
	return maxLineSum;
}

/**
   * print all things in histogram 
   * functionName    print()
   */
void HexHistogram::print()
{
        cout << "Count of values read: " << hex << setw(8) << setfill('0') << valueCount << endl;
	cout << "Count of unique values read: " << hex << setw(8) << setfill('0') << uniqueValueCount << endl;
	cout << "Maximum line sum: " << hex << setw(16) << setfill('0') << maxLineSum << endl;
	for (auto i = 0; i < uniqueItems.size(); i++) {
		cout << hex << setfill('0') << setw(8) << uniqueItems[i] << ": ";
		cout << hex << setfill('0') << setw(8) << uniqueItemsCount[i] << endl;
	}
	cout << "Done." << endl;
}
