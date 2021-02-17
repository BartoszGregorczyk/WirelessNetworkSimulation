#include "event.h"



Event::Event(size_t time, WirelessNetwork* wireless_network) :
	time_(time), wireless_network_pointer_(wireless_network)
{

}

Event::~Event()
{
}


