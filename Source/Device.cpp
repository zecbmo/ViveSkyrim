#include "Device.h"
Device::Device()
{
	prev_framecount_ = -1;
}

Device::~Device()
{
}


void Device::Update()
{
	//update the contoller pose/state when called. 
	if (*framecount_ != prev_framecount_)
	{
		prev_framecount_ = *framecount_;
		prev_state_ = state_;
		if (hmd_ != NULL)
		{
			valid_ = hmd_->GetControllerStateWithPose(tracking_space_, index_, &state_, &pose_);
			if (prev_state_.ulButtonPressed != state_.ulButtonPressed)
			{
				int breakpoint = 0;
			}
		}
	}
}

