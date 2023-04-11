#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING 1

#include <iostream>
#include <vector>
//#include "SDL.h"
#include "unittest.h"
#include "RandLib.h"

//typedef double ListDataType;
#include "ListDataType.h"

//Strategy Design pattern:

class ProcessDataStrategy {
    public:
	virtual void process(ListDataType data) = 0;
};

#include "LinkedList.h"

class DebugStrategy : public ProcessDataStrategy {
private:
	int i = 0;
public:
	virtual void process(ListDataType data) {
		std::cout << i << ":" << data << std::endl;
		i++;
	};
};

class DataAnalysisStrategy : public ProcessDataStrategy {
public:
	virtual ListDataType result() = 0;
};

class MinVal : public DataAnalysisStrategy {
private:
	ListDataType min = 0;
	bool firstRun = true;
public:
	virtual void process(ListDataType data) {
		if (firstRun || (min > data)) min = data;
		firstRun = false;
	};
	virtual ListDataType result() { return min; };
};

class MaxVal : public DataAnalysisStrategy {
private:
	ListDataType max = 0;
	bool firstRun = true;
public:
	virtual void process(ListDataType data) {
		if (firstRun || (max < data)) max = data;
		firstRun = false;
	};
	virtual ListDataType result() { return max; };
};

class MeanVal : public DataAnalysisStrategy {
private:
	ListDataType mean = 0;
	int n = 0;
public:
	virtual void process(ListDataType data) {
		mean += data;
		n++;
	};
	virtual ListDataType result() { return mean / n; };
};

class SigmaVal : public DataAnalysisStrategy {
private:
	ListDataType meanval = 0;
	ListDataType sum = 0;
	int n = 0;
public:
	SigmaVal(ListDataType _meanval) {meanval = _meanval; };
	virtual void process(ListDataType data) {
		sum += (data - meanval) * (data - meanval);
		n++;
	};
	virtual ListDataType result() {
		ListDataType dispersion = sum / (n - 1);
		return sqrt(dispersion); };
};

class HistogramSum : public ProcessDataStrategy {
private:
	int steps = 0;
	ListDataType min, max, histogram_scale;
	std::vector<ListDataType> box;
public:
	HistogramSum(ListDataType _min, ListDataType _max, int _steps)
		: steps {_steps},
		  min {_min},
		  max {_max}
		{
			histogram_scale = steps / (_max - _min);
			box.resize(steps);
		};
	virtual void process(ListDataType data) {
		int cell = round((data - min) * histogram_scale);
		if (cell >= 0 && cell < steps)
			box[cell]++;
	};
	std::vector<ListDataType> get_box() { return box; };
};

class TestLinkedListIteratorStrategy : public ProcessDataStrategy {
private:
	ListNode* cur_node;
	bool is_the_same_data = true;
public:
        TestLinkedListIteratorStrategy(ListNode* _cur_node)
		: cur_node {_cur_node}
		{};
	virtual void process(ListDataType data) {
		if (cur_node->data != data) is_the_same_data = false;
		cur_node = cur_node->next;
	};
	bool is_ok () { return is_the_same_data;};
};

class CompareLinkedListToVectorStrategy : public ProcessDataStrategy {
private:
	std::vector<ListDataType> vector;
	size_t counter;
	bool is_the_same_data;
public:
        CompareLinkedListToVectorStrategy(std::vector<ListDataType> _vector)
		: vector {_vector},
		  counter {0},
		  is_the_same_data {true}
		{};
	virtual void process(ListDataType data) {
		if (vector[counter] != data) is_the_same_data = false;
		counter++;
	};
	bool is_ok () { return is_the_same_data;};
};

bool is_the_same_content (LinkedList* list, std::vector<ListDataType> vector) {
	if (list->length() != vector.size()) return false;
	CompareLinkedListToVectorStrategy contentTest(vector);
	list->process(contentTest);
	return contentTest.is_ok();
}

void linkedlist_selftest_unittests() {
	unittest T = unittest("LinkedList self test");

	LinkedList test_list;
	T.ok(0 == test_list.length());

	test_list.append_item(1);
	T.ok(1 == test_list.length());
	test_list.append_item(5);
	T.ok(2 == test_list.length());
	test_list.append_item(9);
	T.ok(3 == test_list.length());
	test_list.add_item_after_position(6, 1);
	T.ok(4 == test_list.length());
	/*
	std::cout << "print: " << std::endl;
	test_list.print_list();
	std::cout << "print reverse: " << std::endl;
	test_list.print_reverse();
	*/
	T.ok(is_the_same_content(&test_list, std::vector<ListDataType> {1,6,5,9}));

	//std::cout << "print after deleting first element: " << std::endl;
	test_list.remove_item_at_position(0);
	T.ok(3 == test_list.length());
	//test_list.print_list();
	T.ok(is_the_same_content(&test_list, std::vector<ListDataType> {6,5,9}));


	//Adapter pattern, converting the linked list into vector:
	std::vector<ListDataType> converted_vector = test_list.convert_to_vector();
	T.ok(3 == converted_vector.size());
	/*
	std::cout << "print vector: " << std::endl;

	for (int i = 0; i < converted_vector.size(); i++) {
		std::cout << converted_vector[i] << " ";
	}
	std::cout << std::endl;
	*/
	//std::cout << "delete entire list then add 5: " << std::endl;
	test_list.remove_entire_list();
	T.ok(0 == test_list.length());
	test_list.append_item(5);
	T.ok(1 == test_list.length());
	T.ok(is_the_same_content(&test_list, std::vector<ListDataType> {5}));
	//test_list.print_list();

	//Adapter pattern, converting vector to linked list
	//std::cout << "replace list with vector values: " << std::endl;
	std::vector<ListDataType> input_vector = {1,2,3,4,5,6,7,8};
	test_list.replace_listnodes_with_vector_values(input_vector);
	T.ok(8 == test_list.length());
	T.ok(is_the_same_content(&test_list, std::vector<ListDataType> {1,2,3,4,5,6,7,8}));
	//test_list.print_list();

	// Iterator syntax test
	//for (ListDataType val: test_list) {};

	TestLinkedListIteratorStrategy iteratorTest(test_list.get_list_head());
	test_list.process(iteratorTest);
	T.ok(iteratorTest.is_ok());
	//DebugStrategy debugPrint;
	//test_list.process(debugPrint);
}

#include "DataAnalysis.h"

void print_data_analysis(DataAnalysis& analysis) {
	std::cout << analysis.name << ":" << std::endl;
	std::cout << "min   = " << analysis.min << std::endl;
	std::cout << "max   = " << analysis.max << std::endl;
	std::cout << "mean  = " << analysis.mean << std::endl;
	std::cout << "sigma = " << analysis.sigma << std::endl;
	std::cout << "histogram:" << std::endl;
	for (int height: analysis.histogram) {
		std::cout << height << "|";
	}
	std::cout << std::endl;
}

void process_sample (std::vector<double>& data, DataAnalysis& analysis) {
	LinkedList data_list;
	for (double val: data) data_list.append_item(val);
	MinVal minX;
	MaxVal maxX;
	MeanVal meanX;
	data_list.process(minX);
	data_list.process(maxX);
	data_list.process(meanX);
	SigmaVal sigmaX(meanX.result());
	data_list.process(sigmaX);
	HistogramSum histogramX(analysis.histogramMin, analysis.histogramMax, analysis.histogramSteps);
	data_list.process(histogramX);
	data_list.remove_entire_list();
	analysis.min = minX.result();
	analysis.max = maxX.result();
	analysis.mean = meanX.result();
	analysis.sigma = sigmaX.result();
	analysis.histogram = histogramX.get_box();
	int height = 0;
	for (int cell: analysis.histogram) {
		if (cell > height) height = cell;
	};
	analysis.histogramHeight = height;
	print_data_analysis(analysis);
}

DataAnalysis data_analysis() {
	//int sample_total = 10000;
	std::vector<double> data(10000);

	NormalRand X(0, 1);
	X.Sample(data);

	DataAnalysis analysis;
	analysis.name = "Normal(0,1)";
	analysis.histogramSteps = 100;
	analysis.histogramMin = -4;
	analysis.histogramMax = 4;
	process_sample(data, analysis);
	return analysis;
}
