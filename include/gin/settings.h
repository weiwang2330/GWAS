//
// Created by hclimente on 25/07/2017.
//

#ifndef GIN_SETTINGS_H
#define GIN_SETTINGS_H

#include "boost/program_options.hpp"
#include "gin/globals.h"

namespace po = boost::program_options;

class Settings
{
public:

	Settings(int argc, const char* const argv[]) {
		__parseOptions(argc, argv);
	}

	Settings(string pedBasename, string networkFilename, uint encoding, uint modelScore, uint associationScore, string output) {
		__pedBasename = pedBasename;
		__networkFilename = networkFilename;
		__encoding = encoding;
		__modelScore = modelScore;
		__associationScore = associationScore;
		__output = output;
	}

	void printHelp() {
		std::cout << __options() << "\n";
	}

	string pedBasename() { return __pedBasename; }
	uint encoding() { return __encoding; }
	string networkFilename() { return __networkFilename; }
	uint modelScore() { return __modelScore; }
	uint associationScore() { return __associationScore; }
	string output() { return __output; }
	bool flag() { return __flag; }

private:

	string __pedBasename;
	string __networkFilename;
	double __maf;
	string __output;
	int __pcs;
	int __seed;
	uint __associationScore;
	double __lambda;
	double __eta;
	bool __debug;
	uint __modelScore;
	int __depth;
	uint __encoding;

	bool __flag;

	po::options_description __options() {
		po::options_description desc("Allowed options");

		desc.add_options()
				("ped,p", po::value<string>(), "Plink genotype file.")
				("net,n", po::value<string>(), "Sparse network file.")
				("association_score,t", po::value<string>()->default_value("chi2"), "Association score.")
				("model_selection,x", po::value<string>()->default_value("cons"), "Metric to evaluate models.")
				// ("depth,y", po::value<int>()->default_value(3), "Depth of the grid search.")
				// ("maf,m", po::value<double>()->default_value(0.05), "Float minor allele frequency filter.")
				// ("lambda,l", po::value<double>()->default_value(-1), "Lambda parameter.")
				// ("eta,e", po::value<double>()->default_value(-1), "Eta parameter.")
				("ofile,o", po::value<string>()->default_value("results.txt"), "Output file.")
				("encoding,s", po::value<string>()->default_value("additive"), "Model of inheritance (additive, recessive, dominant or codominant).")
				// ("pc,c", po::value<int>()->default_value(0), "PC.")
				// ("seed,z", po::value<int>()->default_value(0), "Random state seed.")
				// ("debug,d", po::bool_switch()->default_value(false), "Debug flag (display extra information).")
				("help,h", "Produce this help message and exit.")
				;

		return desc;
	}

	void __parseOptions(int argc, const char* const argv[]) {

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, __options()), vm);
		po::notify(vm);

		if (vm.count("help")) {
			__flag = true;
		}

		__pedBasename = vm["ped"].as<string>();
		__networkFilename = vm["net"].as<string>();
		// __maf = vm["maf"].as<double>();
		__output = vm["ofile"].as<string>();
		string snp_encoding = vm["encoding"].as<string>();
		// __pcs = vm["pc"].as<int>();
		// __seed = vm["seed"].as<int>();
		string association_score_str = vm["association_score"].as<string>();
		// __lambda = vm["lambda"].as<double>();
		// __eta = vm["eta"].as<double>();
		// __debug = vm["debug"].as<bool>();
		string model_selection_str = vm["model_selection"].as<string>();
		// __depth = vm["depth"].as<int>();

		__encoding = 0;
		if(snp_encoding == "additive") {
			__encoding = 0;
		} else if(snp_encoding == "recessive") {
			__encoding = 1;
		} else if(snp_encoding == "dominant") {
			__encoding = 2;
		} else if(snp_encoding == "codominant") {
			__encoding = 3;
		} else {
			logging(ERROR,"Encoding does not exist!");
			__flag = true;
		}

		__associationScore = SKAT;
		if (association_score_str == "chi2")
			__associationScore = CHI2;

		__modelScore = CONSISTENCY;
		if (model_selection_str == "bic")
			__modelScore = BIC;

	}

};

#endif //GIN_SETTINGS_H
