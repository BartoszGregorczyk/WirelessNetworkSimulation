#ifndef GENERATORS_H
#define GENERATORS_H

#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <ostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>

//Klasa generujaca rozklady losowe
class Generators
{
public:
	Generators(int kernel);
	virtual ~Generators();

	double Rnd();			
	int Rnd(double min, double max);
	int RndExp(double lambda);
	int RndZeroOne(double p);
	void ImportKernelsToFile(std::vector<int> &kernels, std::string filename);
	void GenerateKernels(int number_of_rands, std::vector<int> &kernels);
	void GenerateKernels(int &kernel);
	void ImportKernelsToFile(int &kernel, std::string filename);
	int get_kernel() { return kernel_; };

private:
	
	const double M_ = 2147483647;
	static const int A_ = 16807.0;
	static const int Q_ = 127773.0;
	static const int R_ = 2836;
	int kernel_;
};




#endif // !GENERATORS_H

