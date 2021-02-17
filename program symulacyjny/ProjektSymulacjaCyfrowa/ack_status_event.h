#ifndef ACK_STATUS_EVENT_H
#define ACK_STATUS_EVENT_H

#include "event.h"
#include "wireless_network.h"
#include <functional>
#include "transmitter.h"
#include "channel.h"
#include "transmitter.h"
#include "channel.h"
#include <vector>

//Klasa okreslajaca zdarzenie odebrania pakietu ACK
class AckStatusEvent : public Event
{
public:
	AckStatusEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id);
	void Execute() override;						
	
private:
	EventList* event_list_ = nullptr;				
	const int lr_ = 10;								//max liczba retransmisji
	int transmitter_id_;								//id przekazywanego nadajnika
};


#endif // !ACK_STATUS_EVENT_H

