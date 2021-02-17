#include "difs_waiting_time_event.h"
#include "chanell_listening_event.h"
#include "receiving_the_package_event.h"
#include <iostream>


DifsWaitingTimeEvent::DifsWaitingTimeEvent(size_t time, WirelessNetwork* wireless_network,  EventList* event_list, int id)
	:Event(time, wireless_network), event_list_(event_list), transmitter_id_(id)
{
}

void DifsWaitingTimeEvent::Execute()
{
	bool channel_status = wireless_network_pointer_->GetChannel()->GetChannelStatus();							//pobierz stan kanalu wolny/zajety
	int  w_time = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetWaitingTime();			//pobierz czas oczekiwania na kanal
	w_time = w_time + waiting_for_channel_;																		//zwieksz czas oczekiwania na kanal (poniewaz w planowaniu zdarzenia uwzgledniono jednostke czasu)
	int ctpk = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetCtpkGenerator()->Rnd(1, 10) * 10; //generuj czas wysylania pakietu (od 1 do 100 kwantow czasu)
	wireless_network_pointer_->ctpk_numbers.push_back(ctpk);
	static size_t start_transmission_time = 0;	//zmienna pomocnicza do wyznaczania kolizji

	if (!wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->empty()) //sprawdzenie warunku, czy aby na pewno nadajnik nie ma pustego bufora(zabezpieczenie)
	{
		if (channel_status)							
		{
			if (w_time > difs_time_)				//jesli czas oczekiwania jest wiekszy od DIFS...
			{
				Transmitter* tx = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_);
				start_transmission_time = time_;	//przypisuje do zmiennej pomocniczej aktualny czas
				wireless_network_pointer_->GetChannel()->SetChannelStatus(false);								//Ustaw kanal jako zajety
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetWaitingTime(0);			//wyzeruj zmienna waiting_time
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->StartTransmission(tx);			//rozpoczecie transmisji
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front()->SetCtpkTime(ctpk);	//ustawia czas ctpk dla pakietu
				wireless_network_pointer_->GetChannel()->SetCurrentTransmission(wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)); //Dodanie do wektora zajetosci nadajnika, który aktualnie nadaje
				//cout << "Getting Transmitter TEST: " << wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->back()->GetTransmitterId() << "\n";
				event_list_->push(new ReceivingThePackageEvent(time_ + ctpk, wireless_network_pointer_, event_list_, transmitter_id_));	//zaplanuj zdarzenie odebrania pakietu 
				//cout << "CTPK: " << ctpk << "\n";
				Package* package = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front();
				size_t appearance_time = package->GetTimeOfAppearance();
				size_t waiting_packet_time = time_ - appearance_time;
				wireless_network_pointer_->SetPacketWaitingTime(waiting_packet_time);
			}
			else //nie minal czas konieczny do odczekania
			{
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetWaitingTime(w_time);							   //Ustaw czas oczekiwania 
				event_list_->push(new ChanellListeningEvent(time_ , wireless_network_pointer_, event_list_, transmitter_id_));		   //za krotki czas wolnego kanalu
				//logger.Info("Channel isn't free more than 3ms... Waiting time is: ");
				//std::cout << (double)w_time/10  << " [ms] TX: " << transmitter_id_ << " \n";
			}
		}
		else    //kanal zajety
		{
			if (w_time > difs_time_ && start_transmission_time == time_)
			{
				//-------------------------------------------------realizacja kolizji------------------------------------------------------------------
				wireless_network_pointer_->GetChannel()->SetCurrentTransmission(wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)); //Dodanie do wektora zajetosci nadajnika, który aktualnie nadaje
				//cout << "It will be a collission! "<<transmitter_id<<"\n";
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetWaitingTime(0);				//wyzeruj zmienna waiting_time
				Transmitter* tx = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_);
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->StartTransmission(tx);				//rozpoczecie transmisji
				//cout << "Getting Transmitter TEST: " << wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->back()->GetTransmitterId() << "\n";
				event_list_->push(new ReceivingThePackageEvent(time_ + ctpk, wireless_network_pointer_, event_list_, transmitter_id_));	//zaplanuj zdarzenie odebrania pakietu 
				Package* package = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front();
				size_t appearance_time = package->GetTimeOfAppearance();
				size_t waiting_packet_time = time_ - appearance_time;
				wireless_network_pointer_->SetPacketWaitingTime(waiting_packet_time);
				//---------------------------------------------------------------------------------------------------------------------------------------
			}
			else
			{
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetWaitingTime(0);				//wyzeruj zmienna waiting_time
				event_list_->push(new ChanellListeningEvent(time_ , wireless_network_pointer_, event_list_, transmitter_id_)); //kanal zajety wiec od poczatku nasluchuj kanal
				//logger.Info("Channel is busy now... \n ");
			}
		}
	}
	else wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetListening(false); //NAdajnik juz nie nasluchuje
}

