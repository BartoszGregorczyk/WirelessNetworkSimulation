#include "transmitter.h"
#include <iostream>

Transmitter::Transmitter(int id)
{
	transmitter_id_ = id;
	logger = new Logger();
	isListening_ = false;
	while (!packages_.empty())
	{
		packages_.pop();
	}
	waiting_time_ = 0;
	nr_of_fail_ = 0;
	nr_of_succes_ = 0;
}

Transmitter::~Transmitter()
{
	packages_.pop();
}

void Transmitter::GeneratePackage(size_t time_of_appearance)
{
	static size_t package_id = 0;
	++package_id;
	auto package_ = new Package(package_id,time_of_appearance);
	packages_.push(package_);
}

std::queue<Package*> *Transmitter::GetPackages()
{
	return ptr;
}


int Transmitter::GetTransmitterId()
{
	return transmitter_id_;
}

void Transmitter::StartTransmission(Transmitter* tx)
{
	//logger->Info("Start transmission of packet: ");
	//std::cout << tx->GetPackages()->front()->GetPackageId() << "\n";
	//std::cout << packages_.front()->GetPackageId() << "\n";
}

bool Transmitter::GetAck()
{
	return ack;
}

void Transmitter::SetAck(bool status)
{
	ack = status;
}


void Transmitter::SetCgpkKernel(double &kernel)
{
	cgpk_kernel_ = kernel;
}

double Transmitter::GetCgpkKernel()
{
	return cgpk_kernel_;
}

void Transmitter::InitializeCgpkGenerator()
{
	cgpk_generator_ = new Generators(cgpk_kernel_);
}

Generators* Transmitter::GetCgpkGenerator()
{
	return cgpk_generator_;
}

void Transmitter::SetCtpkKernel(double& kernel)
{
	ctpk_kernel_ = kernel;
}

double Transmitter::GetCtpkKernel()
{
	return ctpk_kernel_;
}
void Transmitter::InitializeCtpkGenerator()
{
	ctpk_generator_ = new Generators(ctpk_kernel_);
}

Generators* Transmitter::GetCtpkGenerator()
{
	return ctpk_generator_;
}

void Transmitter::SetRKernel(double& kernel)
{
	r_kernel_ = kernel;
}

double Transmitter::GetRKernel()
{
	return r_kernel_;
}

void Transmitter::InitializeRGenerator()
{
	r_generator_ = new Generators(r_kernel_);
}

Generators* Transmitter::GetRGenerator()
{
	return r_generator_;
}

void Transmitter::SetNrOfRetransmissionSucces(int retransmissions)
{
	number_of_retransmission_succes_.push_back(retransmissions);
}

std::vector<int>* Transmitter::GetNrOfRetransmissionSucces()
{
	return ptr_number_of_retransmission_succes_;
}

double Transmitter::GetWaitingTime()
{
	return waiting_time_;
}

void Transmitter::SetWaitingTime(int time)
{
	waiting_time_ = time;
}

void Transmitter::SetListening(bool listening)
{
	isListening_ = listening;
}

bool Transmitter::getListening()
{
	return isListening_;
}

void Transmitter::SetNrOfSucces()
{
	++nr_of_succes_;
}

long int Transmitter::GetNrofSucces()
{
	return nr_of_succes_;
}

void Transmitter::SetNrOfFail()
{
	++nr_of_fail_;
}

long int Transmitter::GetNrOfFail()
{
	return nr_of_fail_;
}







