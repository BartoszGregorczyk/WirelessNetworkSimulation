#ifndef PACKAGE_H
#define PACKAGE_H

//Klasa reprezentujaca pakiet. Przekazywany od nadajnika do odbiornika
class Package
{
public:
	Package( unsigned long int package_id, size_t time_of_appearance);
	~Package();
	unsigned long int GetPackageId();						//Pobranie ID pakietu
	int GetNumberOfPacketTransmission();					//Pobierz liczbe transmisji pakietu
	void SetNumberOfPacketTransmission(int number);			//ustaw liczbe transmisji pakietu
	void SetCtpkTime(int ctpk);								//ustawia czas transmisji pakietu (wykorzystane do tworzenia czasu crp)
	int GetCtpkTime();										//pobiera czas ctp
	size_t GetTimeOfAppearance();							//pobiera czas pojawienia sie pakietu

private:
	unsigned long int id_package_;							// okresla ID pakietu
	int nr_of_packet_transmissions_;						// liczba transmisji pakietu
	int* ptr_nr_of_packet_transmissions = &nr_of_packet_transmissions_;
	int ctpk_time_;											// czas transmisji pakietu
	size_t time_of_appearance_;								// czas pojawienia sie pakietu
};

#endif

