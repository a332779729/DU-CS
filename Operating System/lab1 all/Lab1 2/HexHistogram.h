/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HexHistogram.h
 * Author: cheng
 *
 * Created on April 9, 2019, 1:54 AM
 */

// HexHistogram.h

#ifndef HEXHISTOGRAM_H
#define HEXHISTOGRAM_H

#include <cstdint>		// uint32_t, uint64_t
#include <string>
#include <vector>

class HexHistogram {
private:
        std::string data;
        std::vector<std::string> lines;
        std::vector<uint64_t> linesSum;
        std::vector<uint32_t> allItems;
        std::vector<uint32_t> uniqueItems;
        std::vector<uint32_t> uniqueItemsCount;

        uint32_t valueCount;
	uint32_t uniqueValueCount;
	uint64_t maxLineSum;
public:
	HexHistogram(std::string filename);
	~HexHistogram();
        /**
   * find the every value count can be same
   * functionName    get_value_count
   * @return         return every value Count which can be same
   */
	uint32_t get_value_count();
        /**
   * find the unique value count
   * functionName    get_unique_value_count()
   * @return         return the every unique Value Count
   */
	uint32_t get_unique_value_count();
        /**
   * find the max line sum
   * functionName    get_max_line_sum()
   * @return         which one is the max Line Sum
   */
	uint64_t get_max_line_sum();
        /**
   * print all things in histogram 
   * functionName    print()
   */
	void print();
};

#endif


