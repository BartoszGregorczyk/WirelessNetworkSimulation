#include "receiving_the_package_event.h"
#include "generate_packet_event.h"
#include "ack_status_event.h"
#include "chanell_listening_event.h"
#include <iostream>

ReceivingThePackageEvent::ReceivingThePackageEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, int id)
	:Event(time, wireless_network), event_list_(event_list), transmitter_id_(id)
{
}

//od tego momentu cos nie dziala poprzednie zdarzenia raczej ok

void ReceivingThePackageEvent::Execute()
{
	bool flag = false; //zmienna pomocnicza, wykorzystana w petli poszukiwania wektora
	int i = 0;		   //iterator w petli while

	//logger.Info("Received a package! TX: ");
	//cout << transmitter_id_ << " \n";

	//cout << "number of current transmission: " << wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->size() << "\n";
	int ter_rnd = wireless_network_pointer_->GetTerGenerator()->RndZeroOne(0.8); //1-brak bledu 0-blad
	wireless_network_pointer_->ter_numbers.push_back(ter_rnd);

	if (wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->size() > 1) //jesli nadaje wiecej niz 1 nadajnik - ustawia kolizje
	{
		wireless_network_pointer_->GetChannel()->SetCollission(true);
		//cout << "USTAWIONO KOLIZJE\n";
	}

	for (int i = 0; i < wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->size(); i++)
	{
		Transmitter* tx = wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->at(i);
		//std::cout << "CURRENT TX ID: " << tx->GetTransmitterId() << "\n";
		//wireless_network_pointer_->SetCollisionTransmitters(tx);
		//wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->pop_back();
	}

	if ((wireless_network_pointer_->GetChannel()->IsCollision())==true || ter_rnd==0)
	{
		//cout << "ERROR LOOP \n";
		if (wireless_network_pointer_->GetChannel()->IsCollision()==true)
		{
			//logger.Info("COLLISION! \n");
			//cout << "COLLISION FOR TX: " << transmitter_id_ << "\n";
			wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetAck(false);

			while(flag==false)
			{
				if (transmitter_id_ == wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->at(i)->GetTransmitterId())
				{
					//cout << "POP TX: " << wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->at(i)->GetTransmitterId() << "\n";
					wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->erase(wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->begin() + i);
					flag = true;
				}
				++i;
			}
		}
		else if (ter_rnd == 0)
		{
			//----------------------------procedura w przypadku wystapienia bledu TER-----------------------------------------------
			wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetAck(false);	// ustaw status ACK w transmiterze na brak
			//cout << "TER ERROR ! TX: ";
			//cout << transmitter_id_ << " \n";
			wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->pop_back();
			//-----------------------------------------------------------------------------------------------------------------------
		}

		if (wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->empty())
		{
			//cout << "Unset Collission...\n";
			wireless_network_pointer_->GetChannel()->SetCollission(false);
			wireless_network_pointer_->GetChannel()->SetChannelStatus(true);
		}
		event_list_->push(new AckStatusEvent(time_ + 10, wireless_network_pointer_, event_list_, transmitter_id_));	//zaplanuj zdarzenie odbioru ACK
	}
	
	else //brak kolizji i bledu ter
	{
			wireless_network_pointer_->GetChannel()->GetCurrentTranmission()->pop_back();
			wireless_network_pointer_->GetTranmitters()->at(transmitter_id_)->SetAck(true);  // ustaw status ACK w transmiterze 
			event_list_->push(new AckStatusEvent(time_ + 10, wireless_network_pointer_, event_list_, transmitter_id_));	//zaplanuj zdarzenie odbioru ACK
	}
} 

