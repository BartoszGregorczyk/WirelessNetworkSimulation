#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <queue>
#include <vector>
#include "logger.h"

class Channel;
class Package;
class WirelessNetwork;
//Klasa abstrakcyjna okreslajaca zdarzenie
class Event
{
public:
	 typedef std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>> EventList; //kolejka priorytetowa zdarzen
	 Event(size_t time, WirelessNetwork* wireless_network_ptr);
	~Event();
	virtual void Execute() = 0;						
	long double get_time() { return time_; }		
	virtual int GetId() { return NULL; };

protected:
	size_t  time_;									//aktualny czas symulacji
	Logger logger;
	WirelessNetwork* wireless_network_pointer_;		//wskaznik na siec, w ktorej odbywa sie symulacja
};



#endif // !EVENT_H
