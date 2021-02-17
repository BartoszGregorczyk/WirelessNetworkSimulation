#include <iostream>
#include "channel.h"
#include "package.h"
#include "simulator.h"
#include "transmitter.h"
#include "wireless_network.h"
#include "event.h"
#include "generate_packet_event.h"
#include "difs_waiting_time_event.h"
#include "chanell_listening_event.h"
#include "ack_status_event.h"
#include "receiving_the_package_event.h"
#include "logger.h"
#include "generators.h"
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
	auto wn = new WirelessNetwork(); //utworzenie przykladowej sieci
	auto logger = new Logger();

	//---------------------------generacja ziaren--------------------------------
  //potrzebuje ziaren :
  //CGP ->  10(nadajniki)*10(symulacje) = 100 ziaren
  //CTP ->  10(nadajniki)*10(symulacje) = 100 ziaren
  //R ->    10(nadajniki)*10(symulacje) = 100 ziaren
  //TER ->  1 ziarno

  //lacznie 301 ziaren
	int seed = 123;
	auto generator = Generators(seed);
	vector<int> cgpk_kernels;
	vector<int> ctpk_kernels;
	vector<int> r_kernels;
	int ter_kernel;
	cout << "Kernels Generating...\n";
	//---------------------------------generowanie ziaren dla CGP ---------------
	generator.GenerateKernels(100, cgpk_kernels);
	generator.ImportKernelsToFile(cgpk_kernels, "cgpk_kernels.txt");
	//---------------------------------------------------------------------------

	//---------------------------------generowanie ziaren dla CTP ---------------
	generator.GenerateKernels(100, ctpk_kernels);
	generator.ImportKernelsToFile(ctpk_kernels, "ctpk_kernels.txt");
	//---------------------------------------------------------------------------

	//---------------------------------generowanie ziaren dla R -----------------
	generator.GenerateKernels(100, r_kernels);
	generator.ImportKernelsToFile(r_kernels, "r_kernels.txt");
	//---------------------------------------------------------------------------

	//-----------------------------generowanie ziaren dla TER -------------------
	generator.GenerateKernels(ter_kernel);
	generator.ImportKernelsToFile(ter_kernel, "ter_kernel.txt");
	//---------------------------------------------------------------------------


	int nr_of_simulation = 1;
	int sim_loop_iterator;
	cout << "Enter Simulation number 1-10: \n";
	cin >> nr_of_simulation;
	cout << "\n";
	switch (nr_of_simulation)
	{
	case 1:
		sim_loop_iterator = 0;
		break;
	case 2:
		sim_loop_iterator = 10;
		break;
	case 3:
		sim_loop_iterator = 20;
		break;
	case 4:
		sim_loop_iterator = 30;
		break;
	case 5:
		sim_loop_iterator = 40;
		break;
	case 6:
		sim_loop_iterator = 50;
		break;
	case 7:
		sim_loop_iterator = 60;
		break;
	case 8:
		sim_loop_iterator = 70;
		break;
	case 9:
		sim_loop_iterator = 80;
		break;
	case 10:
		sim_loop_iterator = 90;
		break;
	default:
		sim_loop_iterator = 0;
		break;
	}

	//Ustawienie ziaren  oraz utworzenie generatora dla ka¿dego transmittera------
	int j = 0;
	for (int i = sim_loop_iterator; i < (sim_loop_iterator+10); i++)
	{
		double kernel_cgpk = cgpk_kernels.at(i);
		wn->GetTranmitters()->at(j)->SetCgpkKernel(kernel_cgpk);
		wn->GetTranmitters()->at(j)->InitializeCgpkGenerator();
	
		double kernel_ctpk = ctpk_kernels.at(i);
		wn->GetTranmitters()->at(j)->SetCtpkKernel(kernel_ctpk);
		wn->GetTranmitters()->at(j)->InitializeCtpkGenerator();
	
		double kernel_r = r_kernels.at(i);
		wn->GetTranmitters()->at(j)->SetRKernel(kernel_r);
		wn->GetTranmitters()->at(j)->InitializeRGenerator();
		j++;
	}
	wn->SetTerKernel(ter_kernel);
	wn->InitializeTerGenerator();


	//---------------------------------------------------------------------------
	int sim_time = 500;
	double lambda = 0.05;
	int start_from_the_package = 0;
	cout << "Enter the number of quantum simulation time ----- 1 quantum == 0.1ms \n";
	cin >> sim_time;
	cout << "\n";
	cout << "Enter the moment of the end of the initial phase (from which package): \n";
	cin >> start_from_the_package;
	cout << "\n";
	cout << "Enter the lambda parameter: \n";
	cin >> lambda;
	cout << "\n";
	Simulator simulator = Simulator(wn);
	wn->SetStartSimTime(start_from_the_package);
	wn->SetLambda(lambda);
	simulator.M2(sim_time); //czas *10

	//--------------------zapis wygenerowanych wartosci---------------------------
	vector<double> numbers_cgpk = wn->cgpk_numbers;
	vector<double> numbers_ctpk = wn->ctpk_numbers;
	vector<double> numbers_r = wn->r_numbers;
	vector<double> numbers_ter = wn->ter_numbers;

	wn->ImportNumbersToFile(numbers_cgpk, "cgpk_numbers.txt");
	wn->ImportNumbersToFile(numbers_ctpk, "ctpk_numbers.txt");
	wn->ImportNumbersToFile(numbers_r, "r_numbers.txt");
	wn->ImportNumbersToFile(numbers_ter, "ter_numbers.txt");
	//-----------------------------------------------------------------------------

	simulator.GetStats();

	 

	return 0;
}