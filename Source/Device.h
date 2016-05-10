#pragma once

#define NOMINMAX
#include "openvr.h"
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"

#include "RigidTransform.h"

typedef unsigned long ulong;
typedef unsigned int u_int;




class Device
{
public:
	Device();
	~Device();
	inline virtual void SetUp(u_int index, int* framecount, CActor* player, vr::IVRSystem* hmd) { index_ = index; hmd_ = hmd; framecount_ = framecount; Update(); player_ = player; };
	virtual void Update();

	//transforms
	RigidTransform GetTransform() { Update(); transform_.UpdateTransform(pose_.mDeviceToAbsoluteTracking);  return transform_; };
	Vector3 GetVelocity() { Update(); return Vector3(pose_.vVelocity.v[0], pose_.vVelocity.v[1], -pose_.vVelocity.v[2]); }
	Vector3 GetAngularVelocity() { Update(); return Vector3(-pose_.vAngularVelocity.v[0], -pose_.vAngularVelocity.v[1], pose_.vAngularVelocity.v[2]); }
	Vector3 GetVectorFromOtherDevice(Device *b) { return b->GetTransform().pos - this->transform_.pos; };

	vr::VRControllerState_t GetState() { Update(); return state_; }
	vr::VRControllerState_t GetPrevState() { Update(); return prev_state_; }
	vr::TrackedDevicePose_t GetPose() { Update(); return pose_; }

	//Getters and Setters
	inline void SetIndex(u_int index) { index_ = index; };
	inline u_int GetIndex() { return index_; };
	inline void SetValid(bool valid) { valid_ = valid; };
	inline bool GetValid() { return valid_; };
	

protected:
	float Max(float a, float b) { return a < b; };

	vr::IVRSystem* hmd_;
	u_int index_;
	bool valid_, connected_, has_tracking_, out_of_range_, callibrating_, uninitalized_;
	vr::VRControllerState_t state_, prev_state_;
	vr::TrackedDevicePose_t pose_;
	RigidTransform transform_;
	int prev_framecount_;
	int* framecount_;

	vr::ETrackingUniverseOrigin tracking_space_ = vr::TrackingUniverseStanding;


	CActor* player_; //pointer to player within the game (set on init)



};


