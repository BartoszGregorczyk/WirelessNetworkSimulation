#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include <queue>
#include "transmitter.h"

class WirelessNetwork;

//Klasa reprezentujaca kanal transmisyjny/ lacznik pomiedzy stacja nadawcza a odbiorcza
class Channel
{
public:
	Channel();
	~Channel();
	bool IsCollision();									// Czy wystapila kolizja True - tak False - nie
	void SetChannelStatus(bool status);					// Ustawia status kanalu 
	bool GetChannelStatus();							// pobiera status kanalu
	std::vector<Transmitter*>* GetCurrentTranmission(); // pobiera wektor aktualnie nadajacych nadajnikow
	void SetCurrentTransmission(Transmitter* tx);		// ustawia wektor aktualnie nadajacych nadajnikow
	void SetCollission(bool set);						// ustawia status kolizji

private:
	bool is_collision_;	  // Okresla czy wsytapila kolizja True - kolizja False - brak kolizji
	bool channel_free_;	  // zmienna okreslajaca czy kanal wolny TRUE -> wolny FALSE -> zajety
	std::vector<Transmitter*> current_transmitters;	//wektor zajetosci kanalu (posiada informacje o identyfikatorach nadajnikow aktualnie nadajacych)
	std::vector<Transmitter*>* ptr_current_transmitters = &current_transmitters; //wskaznij na wektor zajetosci kanalu
};


#endif

