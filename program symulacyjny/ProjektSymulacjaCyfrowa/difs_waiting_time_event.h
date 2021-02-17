#ifndef DIFS_WAITING_TIME_EVENT
#define DIFS_WAITING_TIME_EVENT

#include "event.h"
#include "channel.h"
#include "wireless_network.h"
#include "transmitter.h"

//Klasa okreslajaca zdarzenie odczekiwania czasu DIFS w celu rozpoczecia transmisji
class DifsWaitingTimeEvent : public Event
{
public:
	DifsWaitingTimeEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id);
	void Execute() override;						//metoda wykonujaca zdarzenie
	int GetId() override { return transmitter_id_; };

private:
	EventList* event_list_ = nullptr;				
	const int difs_time_ = 30;						// czas w jakim kanal musi byc wolny w celu rozpoczecia transmisji [ms](3ms *10)
	const size_t waiting_for_channel_ = 5;			// czas oczekiwania na kanal (0.5ms * 10)
	int transmitter_id_;							// id przekazywanego nadajnika
};


#endif // !DIFS_WAITING_TIME_EVENT

