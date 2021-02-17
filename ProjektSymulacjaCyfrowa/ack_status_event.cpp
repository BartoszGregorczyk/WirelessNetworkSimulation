#include "ack_status_event.h"
#include "chanell_listening_event.h"
#include "generate_packet_event.h"
#include <iostream>
#include<iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

AckStatusEvent::AckStatusEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id)
	:Event(time, wireless_network), event_list_(event_list), transmitter_id_(id)
{	
}

void AckStatusEvent::Execute()
{
	
	size_t additional_time = 5; //Okres nasluchiwania kanalu
	int start_phase = wireless_network_pointer_->GetStartSimTime();
	int when_start = wireless_network_pointer_->GetActualNumberOfReceivedPackages();
	bool IsMoreThanStartPhase = false;
	int number_of_retransmissions_ = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front()->GetNumberOfPacketTransmission();	//pobierz liczbe transmisji pakietu
	
	if (when_start>= start_phase)
	{
		IsMoreThanStartPhase = true;
	}
	else IsMoreThanStartPhase = false;
	//-------------------------------------------------
	//sprawdzenie czy nadajniki przekroczyly liczbe retransmisji oraz czy odebraly poprawnie pakiet ACK

			bool ack = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetAck();		
			
			
			if (ack==true) //sprawdzenie statusu ACK
			{
				//cout << "SUCCES! TX:  "<<transmitter_id_<<"\n";

				if (IsMoreThanStartPhase)
				{
					size_t appearance_time = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front()->GetTimeOfAppearance();
					size_t delay_time =  time_- appearance_time  ;
					//cout << "DELAY TIME: " << delay_time << "\n";
					wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetNrOfSucces();
					wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetNrOfRetransmissionSucces(number_of_retransmissions_);
					wireless_network_pointer_->SetPacketDelayTimes(delay_time);
					//wireless_network_pointer_->SaveAverageNumberOfRetransmission();

				}
				wireless_network_pointer_->SetActualNumberOfReceivedPackages();
				wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->pop();
				wireless_network_pointer_->GetChannel()->SetChannelStatus(true);
				if (wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->size()>0)
				{
					event_list_->push(new ChanellListeningEvent(time_ + additional_time, wireless_network_pointer_, event_list_, transmitter_id_));
				}
				else
				{
					wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetListening(false);
				}
			}
			else //nie odebrano ACK
			{

				if (number_of_retransmissions_ < 4) //sprawdzenie czy przekroczono liczbe retransmisji
				{
					
					wireless_network_pointer_->SetNumberOfRetransmissions();
					//cout << "RETRANSMISSION! TX:"<<transmitter_id_<<" \n";
					int temp_nr_retransmission = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front()->GetNumberOfPacketTransmission() + 1;
					wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front()->SetNumberOfPacketTransmission(temp_nr_retransmission);  //ustaw liczbe transmisji pakietu
					int ctpk = wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->front()->GetCtpkTime();
					int r= wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetRGenerator()->Rnd(0, pow(2,temp_nr_retransmission)-1)*10;
					wireless_network_pointer_->r_numbers.push_back(r);
					int crp_ = r * ctpk;
					//cout << "CRP: " << crp_ << "\n";
					event_list_->push(new ChanellListeningEvent(time_ + crp_, wireless_network_pointer_, event_list_,transmitter_id_));
					//wireless_network_pointer_->GetTranmitters()->at(transmitter_id)->SetListening(true);

				}
				else
				{
					//usun pakiet
					//cout << "ERROR...Delete Package! \n";
					if (IsMoreThanStartPhase)
					{
						wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetNrOfFail();
					}
					wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->pop();
					if (!wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->GetPackages()->empty())
					{
						//wireless_network_pointer_->GetTranmitters()->at(transmitter_id)->SetListening(true);
						event_list_->push(new ChanellListeningEvent(time_ + additional_time, wireless_network_pointer_, event_list_, transmitter_id_));
					}
					else wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetListening(false);

				}

			}
	}

