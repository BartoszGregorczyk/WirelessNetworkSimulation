#ifndef CRP_RETRANSMISSION_TIME_EVENT_H
#define CRP_RETRANSMISSION_TIME_EVENT_H


//-----------------------------------------Ta klasa prawdopodobnie niepotrzebna--------------------------------------------------

#include "event.h"
#include "channel.h"
#include "wireless_network.h"
#include <functional>
#include "transmitter.h"

class CrpRetransmissionTimeEvent : Event
{
public:
	CrpRetransmissionTimeEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list);
	~CrpRetransmissionTimeEvent();
	void Execute() override;						//metoda wykonujaca zdarzenie

private:
	EventList* event_list_ = nullptr;				//wskaznik na liste zdarzen 
	double r_;										//losowa liczba z przedzialu <0,(2^r-1)>
	double crp_;									//=R*CTP
};



#endif // !CRP_RETRANSMISSION_TIME_EVENT_H

