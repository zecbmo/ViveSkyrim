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
#include <string>
//#include <openvr_capi.h>
//#include <openvr_driver.h>

#define CONFIG_FILE "horsespawner.ini" //using default names from template
#define SCR_NAME "Horse spawner"

//Globals




vr::IVRSystem* InitHMD()
{
	
	
	vr::EVRInitError eError = vr::VRInitError_None;
	vr::IVRSystem* hmd = vr::VR_Init(&eError, vr::VRApplication_Other);
	
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
	
	return hmd;

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
std::string GetTrackedDeviceString(vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *peError = NULL)
{
	uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, NULL, 0, peError);
	if (unRequiredBufferLen == 0)
		return "";

	char *pchBuffer = new char[unRequiredBufferLen];
	unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, pchBuffer, unRequiredBufferLen, peError);
	std::string sResult = pchBuffer;
	delete[] pchBuffer;
	return sResult;
}

void main()
{
	BYTE key = IniReadInt(CONFIG_FILE, "main", "key", 0);
	PrintNote("[%s] not started, press '%s' to use", SCR_NAME, GetKeyName(key).c_str());
	
	
	vr::IVRSystem *hmd = NULL;
	hmd = InitHMD();	

	
	std::string driver_string = "No Display";
	driver_string = GetTrackedDeviceString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_TrackingSystemName_String);
	PrintNote("HMD: %s", driver_string.c_str());

	

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
			if (hmd == NULL)
			{
				PrintNote("Head set is null");
			}
			else
			{
				PrintNote("Headset pointer set %s", hmd);
			}
		}	

		Wait(0); // In order to switch between script threads Wait() must be called anyway		
	}

	vr::VR_Shutdown();
}

