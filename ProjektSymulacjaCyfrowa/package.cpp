#include "package.h"

Package::Package(unsigned long int package_id, size_t time_of_appearance)
{
	id_package_ = package_id;
	nr_of_packet_transmissions_ = 0;
	time_of_appearance_ = time_of_appearance;
}

Package::~Package()
{
}

unsigned long Package::GetPackageId()
{
	return id_package_;
}

int Package::GetNumberOfPacketTransmission()
{
	return nr_of_packet_transmissions_;
}

void Package::SetNumberOfPacketTransmission(int number)
{
	nr_of_packet_transmissions_ = number;
}

void Package::SetCtpkTime(int ctpk)
{
	ctpk_time_ = ctpk;
}

int Package::GetCtpkTime()
{
	return ctpk_time_;
}

size_t Package::GetTimeOfAppearance()
{
	return time_of_appearance_;
}



