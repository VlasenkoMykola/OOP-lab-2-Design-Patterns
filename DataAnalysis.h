#ifndef DataAnalysis_H
#define DataAnalysis_H

#include "ListDataType.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class DataAnalysis {
public:
	string name;
	int histogramSteps;
	ListDataType histogramMin;
	ListDataType histogramMax;
	int histogramHeight;
	ListDataType min;
	ListDataType max;
	ListDataType mean;
	ListDataType sigma;
	std::vector<ListDataType> histogram;
	DataAnalysis() {};
	DataAnalysis(string _name, int _histogramSteps, ListDataType _histogramMin, ListDataType _histogramMax):
	name {_name},
	histogramSteps {_histogramSteps},
	histogramMin {_histogramMin},
	histogramMax {_histogramMax}
	{};
	void print() const {
	    std::cout << name << ":" << std::endl;
	    std::cout << "min   = " << min << std::endl;
	    std::cout << "max   = " << max << std::endl;
	    std::cout << "mean  = " << mean << std::endl;
	    std::cout << "sigma = " << sigma << std::endl;
	    std::cout << "histogram:" << std::endl;
	    for (int height: histogram) {
		std::cout << height << "|";
	    }
	    std::cout << std::endl;
	};
	string toHTML() const {
	    return string("<html><head/><body><p>Distribution Info:<br/>name: ") + name + "<br/>min   = " + std::to_string(min) + "<br/>max   = " + std::to_string(max) + "<br/>mean  = " + std::to_string(mean) + "<br/>sigma = " + std::to_string(sigma) +  "</p><p><br/></p><p>Histogram Info:<br/>steps: " + std::to_string(histogramSteps) + "<br/>min displayed: " + std::to_string(histogramMin) + "<br/>max displayed: " + std::to_string(histogramMax) + "<br/>max height: " + std::to_string(histogramHeight) + "</p></body></html>";
	}
};

#endif //DataAnalysis_H
