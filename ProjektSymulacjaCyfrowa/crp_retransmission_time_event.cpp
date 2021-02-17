#include "crp_retransmission_time_event.h"

CrpRetransmissionTimeEvent::CrpRetransmissionTimeEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list)
	:Event(time, wireless_network), event_list_(event_list)
{
	r_ = 0;
	crp_ = 0;
}

CrpRetransmissionTimeEvent::~CrpRetransmissionTimeEvent()
{
}

void CrpRetransmissionTimeEvent::Execute()
{
	r_ = rand() % 1000;
	//crp_ = r_ * wireless_network_pointer_->GetChannel()->GetCurrentTransmitters()->front()->GetPackages()->front()->GetNumberOfPacketTransmission();
	//do zdarzenia chanell_listening_event
}
