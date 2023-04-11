#ifndef Distribution_Factory_Singleton_H
#define Distribution_Factory_Singleton_H

#include <string>
#include <iostream>
#include "RandLib.h"
#include "DataAnalysis.h"
#include "Source.h"

class DistributionFactorySingleton {
private:
	static const unsigned int distributions_count = 4;
	DataAnalysis distributions[distributions_count] = {
		DataAnalysis { "Normal(0,1)", 100, -4, 4 },
		DataAnalysis { "LogNormal(0,1)", 100, -.1, 9.9 },
		DataAnalysis { "Beta(2,2,0,20)", 100, 0, 20 },
		DataAnalysis { "BetaPrime(5,1)", 100, 0, 1000 }
	};
	DistributionFactorySingleton() {

	};
public:
	static DistributionFactorySingleton getDistributionFactory() { return DistributionFactorySingleton(); };
	int get_count() { return distributions_count; };
	std::string get_name(int i) { return distributions[i].name; };
	DataAnalysis get_data_analysis(int i) {
		//int sample_total = 10000;
		std::vector<double> data(10000);
		if (0 == i) {
			NormalRand X(0, 1);
			X.Sample(data);
		} else if (1 == i) {
			LogNormalRand X(0, 1);
			X.Sample(data);
		} else if (2 == i) {
			BetaRand X(2, 2, 0, 20);
			X.Sample(data);
		} else if (3 == i) {
			BetaPrimeRand X(5, 1);
			X.Sample(data);
		} else {
			std::cout << "Internal error: incorrect distribution index: " << i << std::endl;
		}

		DataAnalysis analysis = distributions[i];
		process_sample(data, analysis);
		return analysis;
	}

};

#endif
