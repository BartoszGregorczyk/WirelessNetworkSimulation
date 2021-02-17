#ifndef TRANSMITTER_H
#define TRANSMITTER_H
#include <queue>
#include "package.h"
#include "logger.h"
#include "generators.h"
#include <vector>

//Klasa reprezentujaca nadajnik. Protokol dostepu zgodnie z CSMA-1 persient.
class Transmitter
{
public:
	Transmitter(int id);
	~Transmitter();

	void GeneratePackage(size_t time_of_appearance);					//Metoda generujaca pakiety
	void SetNrOfRetransmissionSucces(int retransmissions);				//Ustawia liczbe retransmisji
	std::vector<int>* GetNrOfRetransmissionSucces();					//Pobiera liczbe retransmisji
	void StartTransmission(Transmitter* tx);							//metoda odpowiedzialna za rozpoczecie transmisji
	std::queue<Package*> *GetPackages();	//metoda pobierajaca wskaznik na bufor pakietow
	int GetTransmitterId();					//metoda pobierajaca ID nadajnika
	bool GetAck();							//pobranie ACK, True - > otrzymano False -> nie otrzymano
	void SetAck(bool status);				//Ustawienie ACK 
	double GetWaitingTime();				// pobiera zmienna oczekiwania czasu wolnego kanalu
	void SetWaitingTime(int time);			// ustawia zmienna oczekiwania czasu wolnego kanalu
	void SetListening(bool listening);		// Ustawia czy nadajnik nasluchuje
	bool getListening();					// Pobiera czy nadajnik nasluchuje
	void SetNrOfSucces();					// Ustawia liczbe pomyslnie przeslanych pakietow
	long int GetNrofSucces();				// Pobiera liczbe pomyslnie przeslanych pakietow
	void SetNrOfFail();						// Ustawia liczbe blednych pakietow
	long int GetNrOfFail();					// Pobiera liczbe blednych pakietow

	//-----------------metody odpowiedzialne za generacje rozkladow------------------------------------------
	void SetCgpkKernel(double &kernel);
	double GetCgpkKernel();

	void InitializeCgpkGenerator();
	Generators* GetCgpkGenerator();

	void SetCtpkKernel(double& kernel);
	double GetCtpkKernel();

	void InitializeCtpkGenerator();
	Generators* GetCtpkGenerator();

	void SetRKernel(double& kernel);
	double GetRKernel();

	void InitializeRGenerator();
	Generators* GetRGenerator();
//--------------------------------------------------------------------------------------------------------------
	
private:
	
	std::queue<Package*> packages_; // kolejka pakietow
	std::queue<Package*>* ptr = &packages_;
	int transmitter_id_;			// ID nadajnika
	long int nr_of_succes_;			// liczba bezblednych transmisji 
	long int nr_of_fail_;			// liczba blednych transmisji    
	bool ack;						// zmienna informujaca czy otrzymano ACK True -> otrzymano
	Logger* logger;					
	double cgpk_kernel_;			// ziarno dla generatora cgpk
	double ctpk_kernel_;			// ziarno dla generatora ctpk
	double r_kernel_;				// ziarno dla generatora r
	Generators* cgpk_generator_;	// generator rozkladu wykladniczego cgpk
	Generators* ctpk_generator_;	// generator rozkladu jednostajnego ctpk
	Generators* r_generator_;		// generator rozkladu jednostajnego r
	int waiting_time_;				// zmienna pomocnicza do odczekiwania czasu wolnego kanalu
	bool isListening_;				// zmienna okreslajaca czy nadajnik nasluchuje
	std::vector<int> number_of_retransmission_succes_; //liczba pomyslnych retransmisji
	std::vector<int>* ptr_number_of_retransmission_succes_=&number_of_retransmission_succes_;
};




#endif

