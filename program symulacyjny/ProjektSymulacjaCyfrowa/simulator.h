#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include "wireless_network.h"
#include "event.h"
#include "generate_packet_event.h"
#include "difs_waiting_time_event.h"
#include "crp_retransmission_time_event.h"
#include "chanell_listening_event.h"
#include "ack_status_event.h"
#include "receiving_the_package_event.h"


//Klasa zawierajaca czas systemowy oraz liste zdarzen.
class Simulator
{
public:
	explicit Simulator(WirelessNetwork* wireless_network);
	void M2(int time);    //glowna metoda symulacyjna zawarta w niej petla symulacji
	void StepByStepMode();//tryb wyswietlania
	void GetStats();


private:

	size_t clock_ = 0;
	WirelessNetwork* wireless_network_ = nullptr;

};

#endif
