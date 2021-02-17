#ifndef WIRELESS_NETWORK_H
#define WIRELESS_NETWORK_H

#include "transmitter.h"
#include "channel.h"
#include <vector>
#include <queue>
#include"generators.h"
#include "event.h"

using namespace std;
//Klasa, ktora gromadzi wszystkie pozostale elementy systemu telekomunikacyjnego.
class WirelessNetwork
{
public:
	
	WirelessNetwork();
	~WirelessNetwork();

	vector<Transmitter*> *GetTranmitters();					//metoda umozliwiajaca pobranie wskaznika na wektor nadajnikow
	Channel *GetChannel();									//metoda zwracajaca kanal

	void SetTerKernel(int& kernel);							//ustawia ziarno dla TER
	double GetTerKernel();									//pobiera ziarno dla TER

	void ImportNumbersToFile(std::vector<double>& numbers, std::string filename);	//zapis wygenerowanych liczb do pliku
	void InitializeTerGenerator();							//inicjacja generatora TER
	Generators* GetTerGenerator();							//pobranie generatora TER


	//---------------------------wygenerowane wartosci-----------
	vector<double> cgpk_numbers;
	vector<double> ctpk_numbers;
	vector<double> r_numbers;
	vector<double> ter_numbers;
	//-----------------------------------------------------------

	void SetStartSimTime(int start_from_the_package); // Ustawia moment od ktorego maja byc zbierane statystyki
	int GetStartSimTime();							  // Pobiera moment od ktorego maja byc zbierane statystyki
	void SetPacketDelayTimes(size_t time);			  // Ustawia opoznienie pakietu
	vector<size_t> *GetPacketDelayTimes();			  // Pobiera opoznienie pakietu
	void SaveAverageNumberOfRetransmission();		  // Zapis sredniej liczby retransmisji od numeru pakietu
	int GetNumberOfAllPackages();					  // Pobiera wszystkie pakiety (bledne i poprawne)
	int GetNumberOfRetransmissions();				  // Pobiera liczbe retransmisji
	void SetNumberOfRetransmissions();				  // Ustawia liczbe retransmisji
	void SetActualNumberOfReceivedPackages();		  // Ustawia aktualna liczbe otrzymanych pakietow
	int GetActualNumberOfReceivedPackages();		  // Pobiera aktualna liczbe otrzymanych pakietow
	void SetPacketWaitingTime(size_t time);			  // Ustawia czas oczekiwania pakietu od jego wygenerowania do opuszczenia
	vector<size_t>* GetPacketWaitingTime();			  // Pobiera czas oczekiwania pakietu
	int GetNumberOfTransmitters();
	void SetLambda(double lambda);
	double GetLambda();

private:

	vector<Transmitter*> transmitters_;				// wektor stacji nadawczych
	vector<Transmitter*>* ptr_t = &transmitters_;	// wskaznik na wektor stacji nadawczych
	const int k_tranmitter_=10;						// liczba nadajnikow
	Channel* channel;								// kanal transmisyjny
	double ter_kernel_;								// ziarno dla generatora TER
	Generators* ter_generator_;						// Generator TER
	int start_from_the_package_;					// Moment rozpoczecia zbierania statystyk symulacji
	vector<size_t> packet_delay_times;				// Wektor opoznien pakietow
	vector<size_t>* ptr_packet_delay_times = &packet_delay_times;	//wskaznik na wektor opoznien pakietow
	int number_of_retransmissions_;									//liczba retransmisji
	int actual_number_of_received_packages_;						//aktualna liczba odebranych pakietow
	vector<size_t> packet_waiting_time_;							//wektor oczekiwania pakietow
	vector<size_t>* ptr_packet_waiting_time_ = &packet_waiting_time_;//wskaznik na wektor oczekiwania pakietow
	double lambda_;
};

#endif
