#ifndef GENERATE_PACKET_EVENT
#define GENERATE_PACKET_EVENT

#include "event.h"
#include "wireless_network.h"
#include <functional>
#include "transmitter.h"
#include "logger.h"
#include "generators.h"

//Klasa okreslajaca zdarzenie wygenerowania pakietu
class GeneratePacketEvent : public Event
{
public:
	GeneratePacketEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id);
	void Execute() override;						
	int GetId() override { return transmitter_id_; };

private:
	EventList* event_list_ = nullptr;				
	const size_t waiting_for_channel = 5;			//czas oczekiwania na kanal (0.5ms * 10)
	int transmitter_id_;								//id przekazywanego nadajnika
};


#endif // !GENERATE_PACKET_EVENT
