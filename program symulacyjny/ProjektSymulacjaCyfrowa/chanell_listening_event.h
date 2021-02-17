#ifndef CHANELL_LISTENING_EVENT
#define CHANELL_LISTENING_EVENT

#include "event.h"
#include "channel.h"
#include "wireless_network.h"
#include <functional>
#include "transmitter.h"
#include "logger.h"

class Channel;
class WirelessNetwork;
//Klasa okreslajaca zdarzenie nasluchiwania kanalu
class ChanellListeningEvent : public Event
{
public:
	ChanellListeningEvent(size_t time, WirelessNetwork* wireless_network,  EventList* event_list, int id);
	void Execute() override;						
	int GetId() override { return transmitter_id_; };
private:
	EventList* event_list_ = nullptr;				
	const int waiting_for_channel_ = 5;				//czas oczekiwania na kanal (0.5ms * 10)
	int transmitter_id_;							//id przekazywanego nadajnika
};



#endif // !CHANELL_LISTENING_EVENT

