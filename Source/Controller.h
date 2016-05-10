#pragma once

#include "Device.h"

#define DEFAULT_GLOVE (0x000B145B) //mythic dawn gloves 



class Controller : public Device
{
public:
	Controller();
	~Controller() {};
	void Update();
	inline void SetUp(u_int index, int* framecount, CActor* player, vr::IVRSystem* hmd);

	//controller input
	bool GetPress(vr::EVRButtonId buttonId) { Update(); return (state_.ulButtonPressed& vr::ButtonMaskFromId(buttonId)) != 0; }
	bool GetPressDown(vr::EVRButtonId buttonId) { Update(); return (state_.ulButtonPressed& vr::ButtonMaskFromId(buttonId)) != 0 && (prev_state_.ulButtonPressed & vr::ButtonMaskFromId(buttonId)) == 0; }
	bool GetPressUp(vr::EVRButtonId buttonId) { Update(); return (state_.ulButtonPressed& vr::ButtonMaskFromId(buttonId)) == 0 && (prev_state_.ulButtonPressed & vr::ButtonMaskFromId(buttonId)) != 0; }

	bool GetTouch(vr::EVRButtonId buttonId) { Update(); return (state_.ulButtonTouched& vr::ButtonMaskFromId(buttonId)) != 0; }
	bool GetTouchDown(vr::EVRButtonId buttonId) { Update(); return (state_.ulButtonTouched& vr::ButtonMaskFromId(buttonId)) != 0 && (prev_state_.ulButtonTouched & vr::ButtonMaskFromId(buttonId)) == 0; }
	bool GetTouchUp(vr::EVRButtonId buttonId) { Update(); return (state_.ulButtonTouched& vr::ButtonMaskFromId(buttonId)) == 0 && (prev_state_.ulButtonTouched & vr::ButtonMaskFromId(buttonId)) != 0; }

	//Trigger
	void UpdateHairTrigger();
	bool GetHairTrigger() { Update(); return hair_trigger_state_; }
	bool GetHairTriggerDown() { Update(); return hair_trigger_state_ && !hair_trigger_prev_state_; }
	bool GetHairTriggerUp() { Update(); return !hair_trigger_state_ && hair_trigger_prev_state_; }

	//mostly for touchpad
	Vector2 GetAxis(vr::EVRButtonId buttonId = vr::k_EButton_SteamVR_Touchpad);
	void TriggerHapticPulse(u_int duration_micro_sec = 500, vr::EVRButtonId buttonId = vr::k_EButton_SteamVR_Touchpad);

	//translating tracking to in game
	void UpdateHandPosition(Device* hmd);

	Vector3 body_pos, offset, in_game_pos;

private:
	

	float hair_trigger_delta_;
	float hair_trigger_limit_; //trigger dead zone
	bool hair_trigger_state_, hair_trigger_prev_state_;

	TESObjectREFR *hand_object_;  //reference to object currently held / will be a glove if nothing is held
	
};

