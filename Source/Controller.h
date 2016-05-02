#pragma once

#include "openvr.h"
#include "Vectors.h"
#include <algorithm> 
typedef unsigned long ulong;
typedef unsigned int uint;


struct ButtonMask
{
	const ulong System = (1ul << (int)vr::k_EButton_System); // reserved
	const ulong ApplicationMenu = (1ul << (int)vr::k_EButton_ApplicationMenu);
	const ulong Grip = (1ul << (int)vr::k_EButton_Grip);
	const ulong Axis0 = (1ul << (int)vr::k_EButton_Axis0);
	const ulong Axis1 = (1ul << (int)vr::k_EButton_Axis1);
	const ulong Axis2 = (1ul << (int)vr::k_EButton_Axis2);
	const ulong Axis3 = (1ul << (int)vr::k_EButton_Axis3);
	const ulong Axis4 = (1ul << (int)vr::k_EButton_Axis4);
	const ulong Touchpad = (1ul << (int)vr::k_EButton_SteamVR_Touchpad);
	const ulong Trigger = (1ul << (int)vr::k_EButton_SteamVR_Trigger);
};

class Controller
{
public:
	Controller();
	~Controller();
	inline void ControllerSetUp(uint index, int* framecount, vr::IVRSystem* hmd) { index_ = index; hmd_ = hmd; framecount_ = framecount; };
	void Update();
	

	

	/// These values are only accurate for the last controller state change (e.g. trigger release), and by definition, will always lag behind
	// the predicted visual poses that drive SteamVR_TrackedObjects since they are sync'd to the input timestamp that caused them to update.
	 //SteamVR_Utils.RigidTransform transform{ get{ Update(); return new SteamVR_Utils.RigidTransform(pose.mDeviceToAbsoluteTracking); } }
	// Vector3 velocity{ get{ Update(); return new Vector3(pose.vVelocity.v0, pose.vVelocity.v1, -pose.vVelocity.v2); } }
	// Vector3 angularVelocity{ get{ Update(); return new Vector3(-pose.vAngularVelocity.v0, -pose.vAngularVelocity.v1, pose.vAngularVelocity.v2); } }

	// VRControllerState_t GetState() { Update(); return state; }
	 //VRControllerState_t GetPrevState() { Update(); return prevState; }
	 //TrackedDevicePose_t GetPose() { Update(); return pose; }

	//Controller Input
	bool GetPress(ulong buttonMask) { Update(); return (state_.ulButtonPressed & buttonMask) != 0; }
	bool GetPressDown(ulong buttonMask) { Update(); return (state_.ulButtonPressed & buttonMask) != 0 && (prev_state_.ulButtonPressed & buttonMask) == 0; }
	bool GetPressUp(ulong buttonMask) { Update(); return (state_.ulButtonPressed & buttonMask) == 0 && (prev_state_.ulButtonPressed & buttonMask) != 0; }

	bool GetPress(vr::EVRButtonId buttonId) { return GetPress(1ul << (int)buttonId); }
	bool GetPressDown(vr::EVRButtonId buttonId) { return GetPressDown(1ul << (int)buttonId); }
	bool GetPressUp(vr::EVRButtonId buttonId) { return GetPressUp(1ul << (int)buttonId); }

	bool GetTouch(ulong buttonMask) { Update(); return (state_.ulButtonTouched & buttonMask) != 0; }
	bool GetTouchDown(ulong buttonMask) { Update(); return (state_.ulButtonTouched & buttonMask) != 0 && (prev_state_.ulButtonTouched & buttonMask) == 0; }
	bool GetTouchUp(ulong buttonMask) { Update(); return (state_.ulButtonTouched & buttonMask) == 0 && (prev_state_.ulButtonTouched & buttonMask) != 0; }

	bool GetTouch(vr::EVRButtonId buttonId) { return GetTouch(1ul << (int)buttonId); }
	bool GetTouchDown(vr::EVRButtonId buttonId) { return GetTouchDown(1ul << (int)buttonId); }
	bool GetTouchUp(vr::EVRButtonId buttonId) { return GetTouchUp(1ul << (int)buttonId); }


	//Trigger
	void UpdateHairTrigger();
	bool GetHairTrigger() { Update(); return hair_trigger_state_; }
	bool GetHairTriggerDown() { Update(); return hair_trigger_state_ && !hair_trigger_prev_state_; }
	bool GetHairTriggerUp() { Update(); return !hair_trigger_state_ && hair_trigger_prev_state_; }

	//mostly for touchpad
	Vector2 GetAxis(vr::EVRButtonId buttonId = vr::k_EButton_SteamVR_Touchpad);

	//Getters and Setters
	inline void SetIndex(uint index) { index_ = index; };
	inline uint GetIndex() { return index_; };
	inline void SetValid(bool valid) { valid_ = valid; };
	inline bool GetValid() { return valid_; };
	void TriggerHapticPulse(uint duration_micro_sec = 500, vr::EVRButtonId buttonId = vr::k_EButton_SteamVR_Touchpad);

private:
	float Max(float a, float b) { return a < b; };

	vr::IVRSystem* hmd_;
	uint index_;
	bool valid_, connected_, has_tracking_, out_of_range_, callibrating_, uninitalized_;
	vr::VRControllerState_t state_, prev_state_;
	vr::TrackedDevicePose_t pose_;
	int prev_framecount_;
	int* framecount_;

	vr::ETrackingUniverseOrigin tracking_space_ = vr::TrackingUniverseStanding;

	float hair_trigger_delta_;
	float hair_trigger_limit_;
	bool hair_trigger_state_, hair_trigger_prev_state_;


};


