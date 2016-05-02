#include "Controller.h"

Controller::Controller()
{
	hair_trigger_delta_ = 0.1; //trigger deadzone
	prev_framecount_ = -1;
}

Controller::~Controller()
{
}


void Controller::Update()
{
	//update the contoller pose/state when called. 
	if (*framecount_ != prev_framecount_)
	{
		prev_framecount_ = *framecount_;
		prev_state_ = state_;
		if (hmd_ != NULL)
		{
			valid_ = hmd_->GetControllerStateWithPose(tracking_space_, index_, &state_, &pose_);
			UpdateHairTrigger();
		}
	}
}

void Controller::UpdateHairTrigger()
{
	hair_trigger_prev_state_= hair_trigger_state_;
	float value = state_.rAxis[1].x;
	if (hair_trigger_state_)
	{
		if (value < hair_trigger_limit_ - hair_trigger_delta_ || value <= 0.0f)
			hair_trigger_state_ = false;
	}
	else
	{
		if (value > hair_trigger_limit_ + hair_trigger_delta_ || value >= 1.0f)
			hair_trigger_state_ = true;
	}
	hair_trigger_limit_ = hair_trigger_state_ ? std::max(hair_trigger_limit_, value) : std::min(hair_trigger_limit_, value);
}


Vector2 Controller::GetAxis(vr::EVRButtonId buttonId)
{
	Update();
	Vector2 axis_value;
	uint axisId = (uint)buttonId - (uint)vr::k_EButton_Axis0;
	switch (axisId)
	{
		case 0: axis_value = Vector2(state_.rAxis[0].x, state_.rAxis[0].y); break;
		case 1: axis_value = Vector2(state_.rAxis[1].x, state_.rAxis[1].y); break;
		case 2: axis_value = Vector2(state_.rAxis[2].x, state_.rAxis[2].y); break;
		case 3: axis_value = Vector2(state_.rAxis[3].x, state_.rAxis[3].y); break;
		case 4: axis_value = Vector2(state_.rAxis[4].x, state_.rAxis[4].y); break;
	}
	return axis_value;

}
void Controller::TriggerHapticPulse(uint duration_micro_sec, vr::EVRButtonId buttonId )
{
	if (hmd_ != NULL)
	{
		uint axisId = (uint)buttonId - (uint)vr::k_EButton_Axis0;
		hmd_->TriggerHapticPulse(index_, axisId, (char)duration_micro_sec);
	}
}