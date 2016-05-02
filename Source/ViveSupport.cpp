/*
HORSE SPAWNER SCRIPT PLUGIN EXAMPLE

THIS FILE IS A PART OF THE SKYRIM DRAGON SCRIPT PROJECT
(C) Alexander Blade 2011
http://Alexander.SannyBuilder.com
*/

#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include <math.h>
#include <openvr.h>
//#include <openvr_capi.h>
//#include <openvr_driver.h>

#define CONFIG_FILE "horsespawner.ini" //using default names from template
#define SCR_NAME "Horse spawner"

void InitHMD(vr::IVRSystem* hmd)
{
	vr::EVRInitError eError = vr::VRInitError_None;
	hmd = vr::VR_Init(&eError, vr::VRApplication_Other);

	if (eError != vr::VRInitError_None)
	{
		PrintNote("Error: %s", eError);
	}
	else
	{
		PrintNote("HMD succesfully initialized");
	}
	//extra chech for my own sanity
	if (hmd == nullptr)
	{
		PrintNote("NULL POINTER HMD");
	}
	else
	{
		PrintNote("HMD pointer set");
	}

	

}
void CheckTrackedDevices(vr::IVRSystem* hmd)
{
	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++)
	{
		vr::ETrackedDeviceClass temp = hmd->GetTrackedDeviceClass(i);


		if (temp == vr::TrackedDeviceClass_Invalid)
		{
			PrintNote("device %d: TrackedDeviceClass_Invalid", i);
		}
		if (temp == vr::TrackedDeviceClass_HMD)
		{
			PrintNote("device %d: TrackedDeviceClass_HMD", i);
		}
		if (temp == vr::TrackedDeviceClass_Controller)
		{
			PrintNote("device %d: TrackedDeviceClass_Controller", i);
		}
		if (temp == vr::TrackedDeviceClass_TrackingReference)
		{
			PrintNote("device %d: TrackedDeviceClass_TrackingReference", i);
		}
		if (temp == vr::TrackedDeviceClass_Other)
		{
			PrintNote("device %d: TrackedDeviceClass_Other", i);
		}

	}

}
void main()
{
	BYTE key = IniReadInt(CONFIG_FILE, "main", "key", 0);
	PrintNote("[%s] not started, press '%s' to use", SCR_NAME, GetKeyName(key).c_str());
	
	vr::IVRSystem* hmd;
	InitHMD(hmd);	

	//vr::TrackedDeviceClass right_controller;
	//vr::TrackedDeviceIndex_t right_controller = hmd->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_RightHand);
	//vr::TrackedDeviceIndex_t left_controller = hmd->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_LeftHand);
	
	vr::VRControllerState_t right_state;

	while (TRUE)
	{
		if (GetKeyPressed(key))
		{
			//CheckTrackedDevices(hmd);
			bool temp = hmd->IsInputFocusCapturedByAnotherProcess();
			if (temp == true)
			{
				PrintNote("Funciton working t");
			}
			else
			{
				PrintNote("Funciton working f");
			}
		}	

		Wait(0); // In order to switch between script threads Wait() must be called anyway		
	}

	vr::VR_Shutdown();
}

