#include "channel.h"
#include <vector>

Channel::Channel()
{
	is_collision_ = false;								
	channel_free_ = true;		
	
}

Channel::~Channel()
{
}

bool Channel::IsCollision()
{
	return is_collision_;
}

void Channel::SetChannelStatus(bool status)
{
	channel_free_ = status;
}

bool Channel::GetChannelStatus()
{
	return channel_free_;
}


std::vector<Transmitter*>* Channel::GetCurrentTranmission()
{
	return ptr_current_transmitters;
}

void Channel::SetCurrentTransmission(Transmitter* tx)
{
	current_transmitters.push_back(tx);
}


void Channel::SetCollission(bool set)
{
	is_collision_ = set;
}
















