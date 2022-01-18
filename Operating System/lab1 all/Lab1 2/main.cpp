/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cheng
 *
 * Created on April 8, 2019, 1:43 AM
 */

// main.cpp

#include <iostream>
#include <string>
#include "HexHistogram.h"

using namespace std;

int main(int argc, char **argv)
{
	string filename;
	if (argc > 1) {
		filename.append(argv[1]);
	} else
        {
		return -1;
	}

	try {
		auto hh = new HexHistogram(filename);

		hh->get_value_count();
		hh->get_unique_value_count();
		hh->get_max_line_sum();
		hh->print();

		delete hh;
                
	} catch (exception &e) {
		cout << "Exception: " << e.what() << endl;
		return -2;
	}
	return 0;
}


