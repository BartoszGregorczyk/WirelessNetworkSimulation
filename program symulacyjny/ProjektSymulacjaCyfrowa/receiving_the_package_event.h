#ifndef RECEIVING_THE_PACKAGE_EVENT_H
#define RECEIVING_THE_PACKAGE_EVENT_H

#include "event.h"
#include "wireless_network.h"
#include <functional>
#include "transmitter.h"
#include "package.h"
#include "transmitter.h"
#include "channel.h"

//Klasa okreslajaca zdarzenie odebrania pakietu
class ReceivingThePackageEvent : public Event
{
public:
	ReceivingThePackageEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id);
	int GetId() override { return transmitter_id_; };
	void Execute() override;						

private:
	EventList* event_list_ = nullptr;				
	int transmitter_id_;								//id przekazywanego nadajnika
};


#endif // !RECEIVING_THE_PACKAGE_EVENT_H

