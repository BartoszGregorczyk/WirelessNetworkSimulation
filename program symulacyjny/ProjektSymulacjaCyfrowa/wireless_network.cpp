#include "wireless_network.h"
#include <iostream>
WirelessNetwork::WirelessNetwork()
{
	for(int i=0;i<k_tranmitter_;i++)
	{
		auto n_transmitter_ = new Transmitter(i);
		transmitters_.push_back(n_transmitter_);

	}
	number_of_retransmissions_ = 0;
	channel=new Channel();
	actual_number_of_received_packages_ = 0;
	lambda_ = 0.05;
}

WirelessNetwork::~WirelessNetwork()
= default;

vector<Transmitter*> *WirelessNetwork::GetTranmitters()
{
	return ptr_t;
}

Channel *WirelessNetwork::GetChannel()
{
	return channel;
}


void WirelessNetwork::SetTerKernel(int& kernel)
{
	ter_kernel_ = kernel;
}

double WirelessNetwork::GetTerKernel()
{
	return ter_kernel_;
}

void WirelessNetwork::ImportNumbersToFile(std::vector<double>& numbers, std::string filename)
{
	std::ofstream output_file("./" + filename);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(numbers.begin(), numbers.end(), output_iterator);
}

void WirelessNetwork::InitializeTerGenerator()
{
	ter_generator_ = new Generators(ter_kernel_);
}

Generators* WirelessNetwork::GetTerGenerator()
{
	return ter_generator_;
}

void WirelessNetwork::SetStartSimTime(int start_from_the_package)
{
	start_from_the_package_ = start_from_the_package;
}

int WirelessNetwork::GetStartSimTime()
{
	return start_from_the_package_;
}


void WirelessNetwork::SetPacketDelayTimes(size_t time)
{
	packet_delay_times.push_back(time);
}

vector<size_t>* WirelessNetwork::GetPacketDelayTimes()
{
	return ptr_packet_delay_times;
}


void WirelessNetwork::SaveAverageNumberOfRetransmission()
{
	static size_t package_id = 0;
	++package_id;
	double average = 0;

	if (GetNumberOfAllPackages() == 0)
		average = (double)GetNumberOfRetransmissions();
	else
		average = (double)GetNumberOfRetransmissions() / GetNumberOfAllPackages();

	ofstream save_average_number_of_retransmission("AverageNumberOfRetransmission.txt", ios_base::app);
	save_average_number_of_retransmission << "package: " + to_string(package_id)
		+ " average: " + to_string(average) << endl;
	save_average_number_of_retransmission.close();

}


int WirelessNetwork::GetNumberOfAllPackages()
{
	int tx_sum = 0;
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += (transmitters_.at(i)->GetNrofSucces() + transmitters_.at(i)->GetNrOfFail());
	}
	return sum;
}

int WirelessNetwork::GetNumberOfRetransmissions()
{
	return number_of_retransmissions_;
}

void WirelessNetwork::SetNumberOfRetransmissions()
{
	++number_of_retransmissions_;
}

void WirelessNetwork::SetActualNumberOfReceivedPackages()
{
	++actual_number_of_received_packages_;
}

int WirelessNetwork::GetActualNumberOfReceivedPackages()
{
	return actual_number_of_received_packages_;
}

void WirelessNetwork::SetPacketWaitingTime(size_t time)
{
	packet_waiting_time_.push_back(time);
}

vector<size_t>* WirelessNetwork::GetPacketWaitingTime()
{
	return ptr_packet_waiting_time_;
}

int WirelessNetwork::GetNumberOfTransmitters()
{
	return k_tranmitter_;
}

void WirelessNetwork::SetLambda(double lambda)
{
	lambda_ = lambda;
}

double WirelessNetwork::GetLambda()
{
	return lambda_;
}

















