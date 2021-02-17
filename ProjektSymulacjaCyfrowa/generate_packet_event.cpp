#include "generate_packet_event.h"
#include "chanell_listening_event.h"
#include<iostream>
#include <cstdlib>
#include <ctime>


GeneratePacketEvent::GeneratePacketEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id)
	:Event(time, wireless_network), event_list_(event_list), transmitter_id_(id)
{
}


void GeneratePacketEvent::Execute()
{
	 				
	 double lambda = wireless_network_pointer_->GetLambda();
	 wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GeneratePackage(time_);	//wygenerowanie pakietu w nadajniku i umieszczenie go w buforze (otrzymuje on unikalne id)
	// logger.Info("packet generated for transmitter no: ");
	// std::cout <<  transmitter_id_<< "\n";

	 //----------------------------Generator odstepu czasu pomiedzy generowaniem pakietow---------------------------------------------
	 int cgpk=wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetCgpkGenerator()->RndExp(lambda)*10; //generacja czasu cgp (*10)
	 wireless_network_pointer_->cgpk_numbers.push_back(cgpk);
	// cout << "CGPK: "<<cgpk << "\n";
     //-------------------------------------------------------------------------------------------------------------------------------

	 //--------------------------------zaplanowanie zdarzenia generacji kolejnego pakietu---------------------------------------------
	 event_list_->push(new GeneratePacketEvent(time_ + cgpk, wireless_network_pointer_, event_list_, transmitter_id_)); 
	 //-------------------------------------------------------------------------------------------------------------------------------

	 //-----------------jesli w nadajniku czeka pakiet do wyslania zaplanuj nasluchiwanie kanalu--------------------------------------
	 if (wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->size()>0 && wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->getListening()==false) 
	 {
		 event_list_->push(new ChanellListeningEvent(time_ , wireless_network_pointer_, event_list_, transmitter_id_));
		 wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetListening(true); //nadajnik juz nasluchuje
	 }
	 //-------------------------------------------------------------------------------------------------------------------------------
}


