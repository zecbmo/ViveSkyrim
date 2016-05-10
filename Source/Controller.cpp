#include "Controller.h"

Controller::Controller()
{
	hair_trigger_delta_ = 0.1f; //trigger deadzone
	prev_framecount_ = -1;

	
}
void Controller::SetUp(u_int index, int* framecount, CActor* player, vr::IVRSystem* hmd)
{ 
	index_ = index; 
	hmd_ = hmd; 
	framecount_ = framecount; 
	Update(); 
	player_ = player; 

	hand_object_ = ObjectReference::PlaceAtMe((TESObjectREFR*)player_, Game::GetFormById(DEFAULT_GLOVE), 1, false, false);
};

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
			if (prev_state_.ulButtonPressed != state_.ulButtonPressed)
			{
				int breakpoint = 0;
			}
			UpdateHairTrigger();
		}
	}

	
}



void Controller::UpdateHairTrigger()
{
	hair_trigger_prev_state_ = hair_trigger_state_;
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
	u_int axisId = (u_int)buttonId - (u_int)vr::k_EButton_Axis0;
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
void Controller::TriggerHapticPulse(u_int duration_micro_sec, vr::EVRButtonId buttonId)
{
	if (hmd_ != NULL)
	{
		u_int axisId = (u_int)buttonId - (u_int)vr::k_EButton_Axis0;
		hmd_->TriggerHapticPulse(index_, axisId, (char)duration_micro_sec);
	}
}
void Controller::UpdateHandPosition(Device* hmd)
{
	Update();
	//get player body position
	body_pos;
	TESObjectREFR* player_obj = (TESObjectREFR*)player_;
	body_pos.x = ObjectReference::GetPositionX(player_obj);
	body_pos.y = ObjectReference::GetPositionY(player_obj);
	body_pos.z = ObjectReference::GetPositionZ(player_obj);

	//Get vector/Distance from hand to HMD
	offset = GetVectorFromOtherDevice(hmd);
	offset.ConvertToSkyrimSystem();
	//Object position to be set at player position + this vectore
	in_game_pos = body_pos + offset;

	//NB: may need to scale for skyrim settings
	//may need to base this off HMD position rather than player (different player heights)


	

	ObjectReference::SetMotionType(hand_object_, 4, true);

	ObjectReference::SetPosition(hand_object_,
		in_game_pos.x,
		in_game_pos.y,
		in_game_pos.z);

	//ObjectReference::TranslateTo(hand_object_, 
	//	in_game_pos.x,
	//	in_game_pos.y,
	//	in_game_pos.z, 
	//	0,
	//	0, 
	//	0, 
	//	5000, 
	//	2000);
}