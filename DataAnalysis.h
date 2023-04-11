#ifndef DataAnalysis_H
#define DataAnalysis_H

struct DataAnalysis {
	string name;
	int histogramSteps;
	int histogramHeight;
	ListDataType histogramMin;
	ListDataType histogramMax;
	ListDataType min;
	ListDataType max;
	ListDataType mean;
	ListDataType sigma;
	std::vector<ListDataType> histogram;
};

#endif //DataAnalysis_H
