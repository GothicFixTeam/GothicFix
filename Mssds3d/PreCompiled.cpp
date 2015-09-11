#include "PreCompiled.h"

M3D_PROVIDER hProvider = NULL;

M3D_PROVIDER Register(void)
{
	M3D_PROVIDER Result = NULL;
	if(MssLoad() && (Result = RIB_provider_library_handle()))
	{
		// SampleServices

		int SampleServicesSize = 0;
		M3D_INTERFACE_ENTRY SampleServices[27];

		SampleServices[SampleServicesSize].type = M3D_ATTRIBUTE;
		SampleServices[SampleServicesSize].entry_name = "Reverb time";
		SampleServices[SampleServicesSize].token = 1;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_ATTRIBUTE;
		SampleServices[SampleServicesSize].entry_name = "Predelay time";
		SampleServices[SampleServicesSize].token = 2;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_ATTRIBUTE;
		SampleServices[SampleServicesSize].entry_name = "Damping";
		SampleServices[SampleServicesSize].token = 3;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_ATTRIBUTE;
		SampleServices[SampleServicesSize].entry_name = "Environment selection";
		SampleServices[SampleServicesSize].token = 4;
		SampleServices[SampleServicesSize++].subtype = M3D_DEC;

		SampleServices[SampleServicesSize].type = M3D_ATTRIBUTE;
		SampleServices[SampleServicesSize].entry_name = "Effect volume";
		SampleServices[SampleServicesSize].token = 5;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_ATTRIBUTE;
		SampleServices[SampleServicesSize].entry_name = "Reverb Quality";
		SampleServices[SampleServicesSize].token = 6;
		SampleServices[SampleServicesSize++].subtype = M3D_DEC;

		SampleServices[SampleServicesSize].type = M3D_PREFERENCE;
		SampleServices[SampleServicesSize].entry_name = "Reverb time";
		SampleServices[SampleServicesSize].token = 1;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_PREFERENCE;
		SampleServices[SampleServicesSize].entry_name = "Predelay time";
		SampleServices[SampleServicesSize].token = 2;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_PREFERENCE;
		SampleServices[SampleServicesSize].entry_name = "Damping";
		SampleServices[SampleServicesSize].token = 3;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_PREFERENCE;
		SampleServices[SampleServicesSize].entry_name = "Environment selection";
		SampleServices[SampleServicesSize].token = 4;
		SampleServices[SampleServicesSize++].subtype = M3D_DEC;

		SampleServices[SampleServicesSize].type = M3D_PREFERENCE;
		SampleServices[SampleServicesSize].entry_name = "Effect volume";
		SampleServices[SampleServicesSize].token = 5;
		SampleServices[SampleServicesSize++].subtype = M3D_FLOAT;

		SampleServices[SampleServicesSize].type = M3D_PREFERENCE;
		SampleServices[SampleServicesSize].entry_name = "Reverb Quality";
		SampleServices[SampleServicesSize].token = 6;
		SampleServices[SampleServicesSize++].subtype = M3D_DEC;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_room_type";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_room_type;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_room_type";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_room_type;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_sample_effects_level";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_sample_effects_level;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_sample_effects_level";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_sample_effects_level;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_EOS";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_EOS;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_sample_query_attribute";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_sample_query_attribute;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_set_sample_preference";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_set_sample_preference;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_speaker_type";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_speaker_type;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_speaker_type";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_speaker_type;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_sample_obstruction";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_sample_obstruction;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_sample_obstruction";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_sample_obstruction;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_sample_occlusion";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_sample_occlusion;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_sample_occlusion";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_sample_occlusion;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_set_3D_sample_cone";
		SampleServices[SampleServicesSize].token = (uInt)M3D_set_3D_sample_cone;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		SampleServices[SampleServicesSize].type = M3D_FUNCTION;
		SampleServices[SampleServicesSize].entry_name = "M3D_3D_sample_cone";
		SampleServices[SampleServicesSize].token = (uInt)M3D_3D_sample_cone;
		SampleServices[SampleServicesSize++].subtype = M3D_NONE;

		RIB_register_interface(Result, "MSS 3D sample services", SampleServicesSize, SampleServices);

		// AudioServices

		int AudioServicesSize = 0;
		M3D_INTERFACE_ENTRY AudioServices[43];

		AudioServices[AudioServicesSize].type = M3D_ATTRIBUTE;
		AudioServices[AudioServicesSize].entry_name = "Name";
		AudioServices[AudioServicesSize].token = PROVIDER_NAME;
		AudioServices[AudioServicesSize++].subtype = M3D_STRING;

		AudioServices[AudioServicesSize].type = M3D_ATTRIBUTE;
		AudioServices[AudioServicesSize].entry_name = "Version";
		AudioServices[AudioServicesSize].token = PROVIDER_VERSION;
		AudioServices[AudioServicesSize++].subtype = M3D_HEX;

		AudioServices[AudioServicesSize].type = M3D_ATTRIBUTE;
		AudioServices[AudioServicesSize].entry_name = "Maximum supported samples";
		AudioServices[AudioServicesSize].token = 0;
		AudioServices[AudioServicesSize++].subtype = M3D_DEC;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "PROVIDER_query_attribute";
		AudioServices[AudioServicesSize].token = (uInt)PROVIDER_query_attribute;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_startup";
		AudioServices[AudioServicesSize].token = (uInt)M3D_startup;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_error";
		AudioServices[AudioServicesSize].token = (uInt)M3D_error;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_shutdown";
		AudioServices[AudioServicesSize].token = (uInt)M3D_shutdown;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_provider_preference";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_provider_preference;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_activate";
		AudioServices[AudioServicesSize].token = (uInt)M3D_activate;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_allocate_3D_sample_handle";
		AudioServices[AudioServicesSize].token = (uInt)M3D_allocate_3D_sample_handle;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_release_3D_sample_handle";
		AudioServices[AudioServicesSize].token = (uInt)M3D_release_3D_sample_handle;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_start_3D_sample";
		AudioServices[AudioServicesSize].token = (uInt)M3D_start_3D_sample;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_stop_3D_sample";
		AudioServices[AudioServicesSize].token = (uInt)M3D_stop_3D_sample;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_resume_3D_sample";
		AudioServices[AudioServicesSize].token = (uInt)M3D_resume_3D_sample;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_end_3D_sample";
		AudioServices[AudioServicesSize].token = (uInt)M3D_end_3D_sample;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_data";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_data;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_volume";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_volume;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_playback_rate";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_playback_rate;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_offset";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_offset;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_loop_count";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_loop_count;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_loop_block";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_loop_block;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_status";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_status;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_volume";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_volume;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_playback_rate";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_playback_rate;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_offset";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_offset;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_length";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_length;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_loop_count";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_loop_count;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_sample_distances";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_sample_distances;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_sample_distances";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_sample_distances;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_active_3D_sample_count";
		AudioServices[AudioServicesSize].token = (uInt)M3D_active_3D_sample_count;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_open_listener";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_open_listener;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_close_listener";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_close_listener;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_open_object";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_open_object;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_close_object";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_close_object;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_position";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_position;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_velocity";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_velocity;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_velocity_vector";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_velocity_vector;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_set_3D_orientation";
		AudioServices[AudioServicesSize].token = (uInt)M3D_set_3D_orientation;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_position";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_position;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_velocity";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_velocity;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_orientation";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_orientation;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_update_position";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_update_position;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		AudioServices[AudioServicesSize].type = M3D_FUNCTION;
		AudioServices[AudioServicesSize].entry_name = "M3D_3D_auto_update_position";
		AudioServices[AudioServicesSize].token = (uInt)M3D_3D_auto_update_position;
		AudioServices[AudioServicesSize++].subtype = M3D_NONE;

		RIB_register_interface(Result, "MSS 3D audio services", AudioServicesSize, AudioServices);

		return Result;
	}
	return NULL;
}

void UnRegister(M3D_PROVIDER provider)
{
	if(hProvider)
		RIB_unregister_interface(hProvider, 0, 0, 0);
	MssFree();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			HMODULE hMss = GetModuleHandle(_T("Mss32.dll"));
			if(hMss && GetProcAddress(hMss, "_RIB_provider_library_handle@0"))
			{
				if(!(hProvider = Register()))
					return FALSE;
			}
		}
		break;
	case DLL_PROCESS_DETACH:
		UnRegister(hProvider);
		break;
	default:
		break;
	}
	return TRUE;
}

#ifdef _GOTHIC2

extern "C"
{

_declspec(dllexport) BOOL APIENTRY RIB_Main(HMODULE hModule, DWORD ul_reason_for_call)
{
	if(ul_reason_for_call)
		hProvider = Register();
	return TRUE;
}

}

#endif