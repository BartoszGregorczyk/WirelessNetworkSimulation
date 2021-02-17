#include "chanell_listening_event.h"
#include "difs_waiting_time_event.h"
#include <iostream>

ChanellListeningEvent::ChanellListeningEvent(size_t time, WirelessNetwork* wireless_network,  EventList* event_list, int id)
	:Event(time,wireless_network),event_list_(event_list), transmitter_id_(id)
{
}

void ChanellListeningEvent::Execute()
{
	//--------------------------------------------------Nasluchiwanie kanalu co 0.5 ms-------------------------------------------------------
	bool chanell_status = wireless_network_pointer_->GetChannel()->GetChannelStatus(); // zmienna okreslajaca czy kanal zajety
	if (!wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->empty())
	{
		if (chanell_status) //czy kanal wolny
		{
			//------------------------------------------------zaplanowanie zdarzenia odczekania czasu DIFS---------------------------------
			event_list_->push(new DifsWaitingTimeEvent(time_ + waiting_for_channel_, wireless_network_pointer_, event_list_, transmitter_id_));
			//logger.Info("Waiting for a channel... ");
			//cout << "TX: " << transmitter_id_ << " \n";
			//------------------------------------------------------------------------------------------------------------------------------
		}
		else //kanal zajety
		{
			int waiting_time_ = 0;	//zerowanie oczekiwania na kanal (nalezy zliczac od poczatku, poniewaz kanal jest zajety)
			wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetWaitingTime(waiting_time_);
			//logger.Info("Channel is busy! \n");
			event_list_->push(new ChanellListeningEvent(time_ + waiting_for_channel_, wireless_network_pointer_, event_list_, transmitter_id_)); //Kanal zajety wiec planowanie zdarzenia nasluchiwania kanalu
		}
	}
	else wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetListening(false);
}
