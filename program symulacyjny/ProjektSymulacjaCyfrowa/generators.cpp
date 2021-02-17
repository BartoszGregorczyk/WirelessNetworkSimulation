#include "Generators.h"

Generators::Generators(int kernel) :kernel_(kernel)
{
}

Generators::~Generators()
{
}

double Generators::Rnd()
{
	int h = floor(kernel_ / Q_);
	kernel_ = A_ * (kernel_ - Q_ * h) - R_ * h;
	if (kernel_ < 0)
		kernel_ = kernel_ + static_cast<int>(M_);
	return kernel_ / M_;
}

int Generators::Rnd(double min, double max)
{
	return Rnd() * (max - min) + min;
}

int Generators::RndExp(double lambda)
{
	double k = Rnd();
	return -(1.0 / lambda) * log(k);
}

int Generators::RndZeroOne(double p)
{
	double k = Rnd();
	if (k < p)
		return 1;
	else
		return 0;
}

void Generators::ImportKernelsToFile(std::vector<int> &kernels, std::string filename)
{
	std::ofstream output_file("./"+ filename);
	std::ostream_iterator<int> output_iterator(output_file, "\n");
	std::copy(kernels.begin(), kernels.end(), output_iterator);
}

void Generators::GenerateKernels(int number_of_rands, std::vector<int> &kernels)
{
	for (int j = 0; j < number_of_rands; ++j)
	{
		for (int i = 1; i < 100000; ++i)
		{
			Rnd();
		}
		kernels.push_back(kernel_);

	}
}

void Generators::GenerateKernels(int &kernel)
{
	for (int i = 1; i < 100000; ++i)
	{
		Rnd();
	}
	kernel = kernel_;
	
}

void Generators::ImportKernelsToFile(int &kernel, std::string filename)
{
	std::ofstream save_file("./" + filename);
	save_file << kernel;
}



