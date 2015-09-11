#include "PreCompiled.h"

#define NUM_ROOM_PRESETS 23
XAUDIO2FX_REVERB_I3DL2_PARAMETERS ROOM_PRESET_PARAMS[NUM_ROOM_PRESETS] =
{
    XAUDIO2FX_I3DL2_PRESET_GENERIC,
    XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
    XAUDIO2FX_I3DL2_PRESET_ROOM,
    XAUDIO2FX_I3DL2_PRESET_BATHROOM,
    XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
    XAUDIO2FX_I3DL2_PRESET_STONEROOM,
    XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
    XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
    XAUDIO2FX_I3DL2_PRESET_CAVE,
    XAUDIO2FX_I3DL2_PRESET_ARENA,
    XAUDIO2FX_I3DL2_PRESET_HANGAR,
    XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
    XAUDIO2FX_I3DL2_PRESET_HALLWAY,
    XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
    XAUDIO2FX_I3DL2_PRESET_ALLEY,
	XAUDIO2FX_I3DL2_PRESET_FOREST,
    XAUDIO2FX_I3DL2_PRESET_CITY,
    XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
    XAUDIO2FX_I3DL2_PRESET_QUARRY,
    XAUDIO2FX_I3DL2_PRESET_PLAIN,
    XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
    XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
    XAUDIO2FX_I3DL2_PRESET_UNDERWATER
};

// Missed
//ENVIRONMENT_DRUGGED,
//ENVIRONMENT_DIZZY,
//ENVIRONMENT_PSYCHOTIC,

// Types

struct M3D_Object
{
	uInt junk;
	int type;
};

struct M3D_Listener
{
	M3D_Object			Obj;

	float					X;
	float					Y;
	float					Z;
	float					X_face;
	float					Y_face;
	float					Z_face;
	float					X_up;
	float					Y_up;
	float					Z_up;
	float					dX_per_ms;
	float					dY_per_ms;
	float					dZ_per_ms;

	HTIMER				AutoUpdatePosTimer;

	IXAudio2MasteringVoice* pMasterVoice;
	X3DAUDIO_LISTENER		X3DListener;
};

struct M3D_Source
{
	M3D_Object				Obj;
	uInt					Status;

	WAVEFORMATEX			Format;
	BYTE*					pOrgData;
	DWORD					OrgLen;

	float					X;
	float					Y;
	float					Z;
	float					X_face;
	float					Y_face;
	float					Z_face;
	float					X_up;
	float					Y_up;
	float					Z_up;
	float					dX_per_ms;
	float					dY_per_ms;
	float					dZ_per_ms;

	int						playback_rate;
	G32						volume;

	int						loop_start_offset;
	int						loop_end_offset;
	uInt					loops;

	float					max_dist;
	float					min_dist;

	float					inner_angle;
	float					outer_angle;
	int						outer_volume;

	HTIMER					AutoUpdatePosTimer;

	M3D_SAMPLE				EOS_client;
	MSS_SAMPLE_CALLBACK		EOS_cb;

	float					occlusion; // Low-pass
	float					obstruction; // Volume

	float					effects_level;

	IXAudio2SourceVoice*	pSourceVoice;
	XAUDIO2_BUFFER			Buffer;

	IUnknown*				pReverbEffect;
	IXAudio2SubmixVoice*	pSubmixVoice;
};

#define MAX_SAMPLES_COUNT 64

// Data

#ifdef LOG
FILE* Log = NULL;
#endif

CRITICAL_SECTION M3D_CS;
static int	M3D_RefCount = 0;
static char M3D_LastError[256] = { "\0" };

static float ReverbVolume = 1.0f;

static IXAudio2*				pXAudio2 = NULL;
static XAUDIO2_DEVICE_DETAILS	deviceDetails;
static IXAudio2MasteringVoice*	pMasterVoice = NULL;

static X3DAUDIO_HANDLE		X3DAudioInstance;
static X3DAUDIO_LISTENER	X3DAudioListener;
static X3DAUDIO_DSP_SETTINGS X3DDSPSettings;

static M3D_Listener	Listener;
static M3D_Source*	Samples = NULL;

static int Current_EAX_room_type = 0;

// Implementation

class XAudio2Callback : public IXAudio2VoiceCallback
{
public:
	STDMETHOD_(void, OnBufferEnd)(void* pBufferContext)    
	{
		M3D_Source* Result = (M3D_Source*)pBufferContext;

		EnterCriticalSection(&M3D_CS);
		Result->Status = SMP_DONE;
		if(Result->EOS_cb)
			Result->EOS_cb(Result->EOS_client);
		LeaveCriticalSection(&M3D_CS);
	}

    //Unused methods are stubs
    STDMETHOD_(void, OnVoiceProcessingPassEnd()) {};
    STDMETHOD_(void, OnVoiceProcessingPassStart)(UINT32 SamplesRequired) {};
    STDMETHOD_(void, OnBufferStart)(void * pBufferContext) {};
    STDMETHOD_(void, OnVoiceError)(void * pBufferContext, HRESULT Error) {};
	STDMETHOD_(void, OnLoopEnd)(void * pBufferContext) {};
	STDMETHOD_(void, OnStreamEnd)(void) {};
};

XAudio2Callback Callback;

void UpdateSample(M3D_Source* sample)
{
	if(sample->pSourceVoice)
	{
		X3DAUDIO_EMITTER X3DEmitter;
		memset(&X3DEmitter, 0, sizeof(X3DAUDIO_EMITTER));

		X3DEmitter.ChannelCount = 1;

		X3DEmitter.Position.x = sample->X;
		X3DEmitter.Position.y = sample->Y;
		X3DEmitter.Position.z = sample->Z;

		X3DEmitter.OrientFront.x = sample->X_face;
		X3DEmitter.OrientFront.y = sample->Y_face;
		X3DEmitter.OrientFront.z = sample->Z_face;

		X3DEmitter.OrientTop.x = sample->X_up;
		X3DEmitter.OrientTop.y = sample->Y_up;
		X3DEmitter.OrientTop.z = sample->Z_up;

		X3DEmitter.Velocity.x = sample->dX_per_ms * 1000.0f;
		X3DEmitter.Velocity.y = sample->dY_per_ms * 1000.0f;
		X3DEmitter.Velocity.z = sample->dZ_per_ms * 1000.0f;

		X3DEmitter.CurveDistanceScaler = sample->min_dist;

		X3DAUDIO_CONE Cone;
		memset(&Cone, 0, sizeof(X3DAUDIO_CONE));
		X3DEmitter.pCone = &Cone;
		X3DEmitter.pCone->InnerAngle = (sample->inner_angle / 180.0f) * X3DAUDIO_PI;
		X3DEmitter.pCone->OuterAngle = (sample->outer_angle / 180.0f) * X3DAUDIO_PI;
		if(X3DEmitter.pCone->OuterAngle < X3DEmitter.pCone->InnerAngle)
			X3DEmitter.pCone->OuterAngle = X3DEmitter.pCone->InnerAngle;
		X3DEmitter.pCone->InnerVolume = 1.0f;
		X3DEmitter.pCone->OuterVolume = (float)sample->outer_volume / G32_SCALE;
		X3DEmitter.pCone->InnerLPF = 1.0f;
		X3DEmitter.pCone->OuterLPF = (float)sample->outer_volume / G32_SCALE;
		X3DEmitter.pCone->InnerReverb = 1.0f;
		X3DEmitter.pCone->OuterReverb = (float)sample->outer_volume / G32_SCALE;

		X3DAUDIO_DISTANCE_CURVE_POINT ReverbCurvePoints[2];
		ReverbCurvePoints[0].Distance = 0.0f;
		ReverbCurvePoints[0].DSPSetting = 1.0f;
		ReverbCurvePoints[1].Distance = 1.0f;
		ReverbCurvePoints[1].DSPSetting = 1.0f;
		X3DAUDIO_DISTANCE_CURVE ReverbCurve;
		ReverbCurve.PointCount = 2;
		ReverbCurve.pPoints = ReverbCurvePoints;
		X3DEmitter.pReverbCurve = &ReverbCurve;

		X3DAudioCalculate(X3DAudioInstance, &Listener.X3DListener, &X3DEmitter, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB | X3DAUDIO_CALCULATE_LPF_REVERB, &X3DDSPSettings);

		sample->pSourceVoice->SetOutputMatrix(pMasterVoice, 1, X3DDSPSettings.DstChannelCount, X3DDSPSettings.pMatrixCoefficients);
		if(sample->pSubmixVoice)
		{
			X3DDSPSettings.ReverbLevel *= ReverbVolume;
			sample->pSourceVoice->SetOutputMatrix(sample->pSubmixVoice, 1, 1, &X3DDSPSettings.ReverbLevel);
		}

		float FreqRatioScale = 1.0f;
		if(sample->playback_rate && sample->Format.nSamplesPerSec)
			FreqRatioScale = ((float)sample->playback_rate / (float)sample->Format.nSamplesPerSec);
		sample->pSourceVoice->SetFrequencyRatio(FreqRatioScale * X3DDSPSettings.DopplerFactor);

		float VolumeScale = 1.0f;
		if(sample->obstruction <= 1.0f)
			VolumeScale -= sample->obstruction;

		sample->pSourceVoice->SetVolume((float)sample->volume / G32_SCALE * VolumeScale);

		float LowPassScale = 1.0f;
		if(sample->occlusion <= 1.0f)
			LowPassScale -= sample->occlusion;

		XAUDIO2_FILTER_PARAMETERS FilterParametersDirect = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI/6.0f * X3DDSPSettings.LPFDirectCoefficient) * LowPassScale, 1.0f };
		sample->pSourceVoice->SetOutputFilterParameters(pMasterVoice, &FilterParametersDirect);

		if(sample->pSubmixVoice)
		{
			XAUDIO2_FILTER_PARAMETERS FilterParametersReverb = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI/6.0f * X3DDSPSettings.LPFReverbCoefficient) * LowPassScale, 1.0f };
			sample->pSourceVoice->SetOutputFilterParameters(sample->pSubmixVoice, &FilterParametersReverb);
		}
	}
}

double Log2( double n )  
{  
	return log( n ) / log( 2.0 );  
}

int CalcRoom(double a1, double a2, double a3)
{
	double v4 = 0.0f;
	if(a1 + 0.0001 < a3)
	{
		if(a2 - 0.0001 > a3)
		{
			v4 = a2;
			if (a3 != 0.0)
				v4 = a3;
			return (int)(0.3010299956639812 * Log2((a1 + a2) / v4) * -2000.0);
		}
		else
			return 0;
	}
	return -10000;
}

void UpdateReverb(M3D_Source* Sample)
{
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2 = ROOM_PRESET_PARAMS[Current_EAX_room_type];
	I3DL2.Room = CalcRoom(0.0, 1.0, Sample->effects_level);

	XAUDIO2FX_REVERB_PARAMETERS native;
	ReverbConvertI3DL2ToNative(&I3DL2, &native);
	
	Sample->pSubmixVoice->SetEffectParameters(0, &native, sizeof(native));
}

void UpdateAllSamples(void)
{
	Listener.X3DListener.Position.x = Listener.X;
	Listener.X3DListener.Position.y = Listener.Y;
	Listener.X3DListener.Position.z = Listener.Z;

	Listener.X3DListener.OrientFront.x = Listener.X_face;
	Listener.X3DListener.OrientFront.y = Listener.Y_face;
	Listener.X3DListener.OrientFront.z = Listener.Z_face;

	Listener.X3DListener.OrientTop.x = Listener.X_up;
	Listener.X3DListener.OrientTop.y = Listener.Y_up;
	Listener.X3DListener.OrientTop.z = Listener.Z_up;

	Listener.X3DListener.Velocity.x = Listener.dX_per_ms * 1000.0f;
	Listener.X3DListener.Velocity.y = Listener.dY_per_ms * 1000.0f;
	Listener.X3DListener.Velocity.z = Listener.dZ_per_ms * 1000.0f;

	if(Samples)
	{
		for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
			UpdateSample(&Samples[i]);
	}
}

uInt __stdcall M3D_3D_sample_query_attribute(M3D_SAMPLE samp, M3D_ATTRIB index)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_sample_query_attribute(%d, %d)\n", samp, index);
#endif

	return 0;
}

int __stdcall M3D_3D_set_sample_preference(M3D_SAMPLE samp, M3D_ATTRIB preference, void const * value)
{
#ifdef _LOG
	fprintf(Log, "M3D_3D_set_sample_preference(%d, %d, %d)\n", samp, preference, value);
#endif

	return -1;
}

static int SpeakerType = 0;

void __stdcall M3D_set_3D_speaker_type(int speaker_type)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_speaker_type(%d)\n", speaker_type);
#endif

	SpeakerType = speaker_type;
}

int __stdcall M3D_3D_speaker_type(void)
{
#ifdef LOG
	fprintf(Log, "%d M3D_3D_speaker_type\n", SpeakerType);
#endif

	return SpeakerType;
}

// Audio Services

uInt __stdcall PROVIDER_query_attribute(M3D_ATTRIB index)
{
#ifdef LOG
	fprintf(Log, "PROVIDER_query_attribute(%d)\n", index);
#endif

	switch(index)
	{
	case PROVIDER_NAME:
		return (uInt)"DirectSound3D Hardware Support";
		break;
	case PROVIDER_VERSION:
		return 0x102;
		break;
	case 0: // Maximum supported samples
		return MAX_SAMPLES_COUNT;
		break;
	}
	return 0;
}

M3D_RESULT __stdcall M3D_startup(void)
{
	if(!M3D_RefCount++)
	{
		CoInitializeEx(0, COINIT_MULTITHREADED);
#ifdef LOG
		Log = fopen("M3D.log", "w");
#endif
		InitializeCriticalSection(&M3D_CS);
		M3D_LastError[0] = '\0';
		return M3D_NOERR;
	}
	strcpy(M3D_LastError, "Already started");
	return M3D_ALREADY_STARTED;
}

const char* __stdcall M3D_error(void)
{
#ifdef LOG
	fprintf(Log, "%s M3D_error\n", M3D_LastError);
#endif
	return (strlen(M3D_LastError) > 0) ? M3D_LastError : NULL;
}

M3D_RESULT __stdcall M3D_shutdown(void)
{
	if(M3D_RefCount)
	{
		if(!--M3D_RefCount)
		{
			M3D_activate(FALSE);

			DeleteCriticalSection(&M3D_CS);
#ifdef LOG
			fclose(Log);
			Log = NULL;
#endif
			CoUninitialize();
		}
		M3D_LastError[0] = '\0';
		return M3D_NOERR;
	}
	strcpy(M3D_LastError, "Not initialized");
	return M3D_NOT_INIT;
}

int __stdcall M3D_set_provider_preference(M3D_ATTRIB preference, void const* value)
{
#ifdef LOG
	fprintf(Log, "M3D_set_provider_preference(%d)\n", preference);
#endif
	return -1;
}

void SetSampleDefaults(M3D_Source* sample)
{
	sample->Status = SMP_FREE;
	sample->Obj.type = 1;

	sample->Z_face = 1.0f;
	sample->Y_up = 1.0f;

	sample->min_dist = 1.0f;

	sample->inner_angle = 360.0f;

	sample->effects_level = 0.0f;

	//sample->volume = AIL_get_preference(DIG_DEFAULT_VOLUME);
}

M3D_RESULT __stdcall M3D_activate(int enable)
{
	if(enable)
	{
		if(pXAudio2)
			return M3D_ALREADY_STARTED;

		char ReverbVolumeText[256];
		if(!GothicReadIniString("PARAMETERS", "ReverbVolume", "3.0", ReverbVolumeText, 256, "SystemPack.ini"))
			GothicWriteIniString("PARAMETERS", "ReverbVolume", "3.0", "SystemPack.ini");
		ReverbVolume = (float)atof(ReverbVolumeText);

		HRESULT hResult = S_OK;
		if(FAILED(hResult = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		{
#ifdef LOG
			fprintf(Log, "M3D_activate XAudio2Create failed %d\n", hResult);
#endif
			return M3D_NOT_INIT;
		}

		memset(&deviceDetails, 0, sizeof(XAUDIO2_DEVICE_DETAILS));
		if(FAILED(hResult = pXAudio2->GetDeviceDetails(0, &deviceDetails)))
		{
			pXAudio2->Release();
			pXAudio2 = NULL;
#ifdef LOG
			fprintf(Log, "M3D_activate GetDeviceDetails failed %d\n", hResult);
#endif
			return M3D_NOT_INIT;
		}

		UINT32 SampleRate = MIN(MAX(deviceDetails.OutputFormat.Format.nSamplesPerSec, XAUDIO2FX_REVERB_MIN_FRAMERATE), XAUDIO2FX_REVERB_MAX_FRAMERATE);
		if(FAILED(hResult = pXAudio2->CreateMasteringVoice(&pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, SampleRate)))
		{
			pXAudio2->Release();
			pXAudio2 = NULL;
#ifdef LOG
			fprintf(Log, "M3D_activate CreateMasteringVoice failed %d\n", hResult);
#endif
			return M3D_NOT_INIT;
		}

		X3DAudioInitialize(deviceDetails.OutputFormat.dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, X3DAudioInstance);
		
		memset(&Listener, 0, sizeof(M3D_Listener));
		Listener.pMasterVoice = pMasterVoice;
		Listener.Z_face = 1.0f;
		Listener.Y_up = 1.0f;
		UpdateAllSamples();

		X3DDSPSettings.SrcChannelCount = 1;
		X3DDSPSettings.DstChannelCount = deviceDetails.OutputFormat.Format.nChannels;
		X3DDSPSettings.pMatrixCoefficients = new FLOAT32[deviceDetails.OutputFormat.Format.nChannels];
		memset(X3DDSPSettings.pMatrixCoefficients, 0, sizeof(FLOAT32) * deviceDetails.OutputFormat.Format.nChannels);

		Samples = new M3D_Source[MAX_SAMPLES_COUNT];
		memset(Samples, 0, sizeof(M3D_Source) * MAX_SAMPLES_COUNT);
		for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
		{
			SetSampleDefaults(&Samples[i]);
			if(FAILED(hResult = XAudio2CreateReverb(&Samples[i].pReverbEffect)))
			{
				pMasterVoice->DestroyVoice();
				pMasterVoice = NULL;
				pXAudio2->Release();
				pXAudio2 = NULL;
#ifdef LOG
				fprintf(Log, "M3D_activate XAudio2CreateReverb failed %d\n", hResult);
#endif
				return M3D_NOT_INIT;
			}

			XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { Samples[i].pReverbEffect, TRUE, 1 } };
			XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

			if(FAILED(hResult = pXAudio2->CreateSubmixVoice(&Samples[i].pSubmixVoice, 1, SampleRate, 0, 0, NULL, Samples[i].pReverbEffect ? &effectChain : NULL)))
			{
				Samples[i].pReverbEffect->Release();
				Samples[i].pReverbEffect = NULL;
				pMasterVoice->DestroyVoice();
				pMasterVoice = NULL;
				pXAudio2->Release();
				pXAudio2 = NULL;
#ifdef LOG
				fprintf(Log, "M3D_activate CreateSubmixVoice(%d) failed %d\n", deviceDetails.OutputFormat.Format.nSamplesPerSec, hResult);
#endif
				return M3D_NOT_INIT;
			}

			XAUDIO2FX_REVERB_PARAMETERS native;
			ReverbConvertI3DL2ToNative( &ROOM_PRESET_PARAMS[Current_EAX_room_type], &native );
			Samples[i].pSubmixVoice->SetEffectParameters(0, &native, sizeof(native));
		}
	}
	else
	{
		if(!pXAudio2)
			return M3D_NOT_INIT;

		if(Samples)
		{
			for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
			{
				M3D_end_3D_sample((M3D_SAMPLE)&Samples[i]);

				if(Samples[i].pSubmixVoice)
				{
					Samples[i].pSubmixVoice->DestroyVoice();
					Samples[i].pSubmixVoice = NULL;
				}

				if(Samples[i].pReverbEffect)
				{
					Samples[i].pReverbEffect->Release();
					Samples[i].pReverbEffect = NULL;
				}
			}

			delete[] Samples;
			Samples = NULL;
		}

		if(pMasterVoice)
		{
			pMasterVoice->DestroyVoice();
			pMasterVoice = NULL;
		}
		if(X3DDSPSettings.pMatrixCoefficients)
		{
			delete[] X3DDSPSettings.pMatrixCoefficients;
			X3DDSPSettings.pMatrixCoefficients = NULL;
		}
		if(pXAudio2)
		{
			pXAudio2->Release();
			pXAudio2 = NULL;
		}
	}
#ifdef LOG
	fprintf(Log, "M3D_activate(%d) ok\n", enable);
#endif
	return M3D_NOERR;
}

M3D_SAMPLE __stdcall M3D_allocate_3D_sample_handle(void)
{
	if(pMasterVoice)
	{
		M3D_Source* Result = NULL;
		EnterCriticalSection(&M3D_CS);
		for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
		{
			if(Samples[i].Status == SMP_FREE)
			{
				Result = &Samples[i];
				Result->Status = SMP_DONE;
				break;
			}
		}
		LeaveCriticalSection(&M3D_CS);

#ifdef LOG
		fprintf(Log, "%d M3D_allocate_3D_sample_handle()\n", Result);
#endif

		return (M3D_OBJECT*)Result;
	}
#ifdef LOG
	fprintf(Log, "NULL M3D_allocate_3D_sample_handle()\n");
#endif
	return NULL;
}

int __stdcall M3D_active_3D_sample_count(void)
{
	int Res = 0;
	EnterCriticalSection(&M3D_CS);
	for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
	{
		if(Samples[i].Status != SMP_FREE)
			Res++;
	}
	LeaveCriticalSection(&M3D_CS);

#ifdef LOG
	fprintf(Log, "%d M3D_active_3D_sample_count\n", Res);
#endif
	return Res;
}

void __stdcall M3D_release_3D_sample_handle(M3D_SAMPLE samp)
{
#ifdef LOG
	fprintf(Log, "M3D_release_3D_sample_handle(%d)\n", samp);
#endif

	if(((M3D_Object*)samp)->type)
	{
		M3D_Source* Result = (M3D_Source*)samp;

		M3D_end_3D_sample(samp);

		memset(Result, 0, ((unsigned char*)&Result->pReverbEffect - (unsigned char*)Result));
		SetSampleDefaults(Result);
	}
}

M3D_OBJECT* __stdcall M3D_3D_open_listener(void)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_open_listener\n");
#endif
	return (M3D_OBJECT*)&Listener;
}

void __stdcall M3D_3D_close_listener(M3D_OBJECT* listener)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_close_listener(%d)\n", listener);
#endif
}

M3D_OBJECT* __stdcall M3D_3D_open_object(void)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_open_object\n");
#endif
	return NULL;
}

void __stdcall M3D_3D_close_object(M3D_OBJECT* obj)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_close_object(%d)\n", obj);
#endif
}

void __stdcall M3D_start_3D_sample(M3D_SAMPLE samp)
{
#ifdef LOG
	fprintf(Log, "M3D_start_3D_sample(%d)\n", samp);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->pSourceVoice && Result->Buffer.pAudioData)
	{
		Result->Buffer.LoopBegin = Result->loop_start_offset / Result->Format.nBlockAlign;
		Result->Buffer.LoopLength = (Result->loop_end_offset > 0) ? Result->loop_end_offset / Result->Format.nBlockAlign : 0;
		Result->Buffer.LoopCount = (Result->loops > 0) ? Result->loops - 1 : XAUDIO2_LOOP_INFINITE;

		Result->pSourceVoice->SubmitSourceBuffer(&Result->Buffer);
		UpdateSample(Result);
		Result->pSourceVoice->Start();

		EnterCriticalSection(&M3D_CS);
		Result->Status = SMP_PLAYING;
		LeaveCriticalSection(&M3D_CS);
	}
}

void __stdcall M3D_stop_3D_sample(M3D_SAMPLE samp)
{
#ifdef LOG
	fprintf(Log, "M3D_stop_3D_sample(%d)\n", samp);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->pSourceVoice)
	{
		Result->pSourceVoice->Stop();
		EnterCriticalSection(&M3D_CS);
		Result->Status = SMP_STOPPED;
		LeaveCriticalSection(&M3D_CS);
	}
}

void __stdcall M3D_resume_3D_sample(M3D_SAMPLE samp)
{
#ifdef LOG
	fprintf(Log, "M3D_resume_3D_sample(%d)\n", samp);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->pSourceVoice && Result->Buffer.pAudioData)
	{
		UpdateSample(Result);
		Result->pSourceVoice->Start();

		EnterCriticalSection(&M3D_CS);
		Result->Status = SMP_PLAYING;
		LeaveCriticalSection(&M3D_CS);
	}
}

void __stdcall M3D_end_3D_sample(M3D_SAMPLE samp)
{
#ifdef LOG
	fprintf(Log, "M3D_end_3D_sample(%d)\n", samp);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
		if(Result->pSourceVoice)
		{
			Result->pSourceVoice->Stop();
			Result->pSourceVoice->DestroyVoice();
			Result->pSourceVoice = NULL;
		}

		Result->pOrgData = NULL;
		Result->OrgLen = 0;
		memset(&Result->Format, 0, sizeof(WAVEFORMATEX));
		memset(&Result->Buffer, 0, sizeof(XAUDIO2_BUFFER));

		EnterCriticalSection(&M3D_CS);
		Result->Status = SMP_DONE;
		LeaveCriticalSection(&M3D_CS);
	}
}

uInt __stdcall M3D_3D_sample_status(M3D_SAMPLE samp)
{
	M3D_Source* Result = (M3D_Source*)samp;

	if(!Result->Obj.type)
	{
#ifdef LOG
		fprintf(Log, "0 M3D_3D_sample_status(%d)\n", samp);
#endif
		return 0;
	}

	EnterCriticalSection(&M3D_CS);
	uInt Res = Result->Status;
	LeaveCriticalSection(&M3D_CS);

#ifdef LOG
	fprintf(Log, "%d M3D_3D_sample_status(%d)\n", Res, samp);
#endif

	return Res;
}

int __stdcall M3D_set_3D_sample_data(M3D_SAMPLE samp, M3D_SOUNDINFO const* info)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_data(%d, %d)\n", samp, info->data_ptr);
#endif

	M3D_Source* Result = (M3D_Source*)samp;

	if(!Result->Obj.type)
	{
#ifdef LOG
		fprintf(Log, "0 M3D_set_3D_sample_data(%d)\n", samp);
#endif
		return 0;
	}

	M3D_end_3D_sample(samp);

	if((info->format != 1) || info->channels != 1)
	{
#ifdef LOG
		fprintf(Log, "0 M3D_set_3D_sample_data(%d)\n", samp);
#endif
		return 0;
	}

	int AlreadyPlaying = 0;
	EnterCriticalSection(&M3D_CS);
	for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
	{
		if(Samples[i].Status == SMP_PLAYING)
		{
			if(Samples[i].pOrgData == (BYTE*)info->data_ptr)
			{
				AlreadyPlaying++;
			}
		}
	}
	LeaveCriticalSection(&M3D_CS);

	if(AlreadyPlaying > 3)
	{
#ifdef LOG
		fprintf(Log, "0 M3D_set_3D_sample_data(%d)\n", samp);
#endif
		return 0;
	}

	Result->Format.wFormatTag = WAVE_FORMAT_PCM;
	Result->Format.nChannels = (WORD)info->channels;
	Result->Format.nSamplesPerSec = info->rate;
	Result->Format.cbSize = 0;
	Result->Format.wBitsPerSample = 16;
	Result->Format.nBlockAlign = (Result->Format.wBitsPerSample / 8) * Result->Format.nChannels;
	Result->Format.nAvgBytesPerSec = Result->Format.nSamplesPerSec * Result->Format.nBlockAlign;

	XAUDIO2_SEND_DESCRIPTOR sendDescriptors[2];
    sendDescriptors[0].Flags = XAUDIO2_SEND_USEFILTER;
    sendDescriptors[0].pOutputVoice = pMasterVoice;
    sendDescriptors[1].Flags = XAUDIO2_SEND_USEFILTER;
    sendDescriptors[1].pOutputVoice = Result->pSubmixVoice;
    const XAUDIO2_VOICE_SENDS sendList = { 2, sendDescriptors };

	if(FAILED(pXAudio2->CreateSourceVoice(&Result->pSourceVoice, (WAVEFORMATEX*)&Result->Format, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &Callback, Result->pSubmixVoice ? &sendList : NULL)))
	{
		memset(&Result->Format, 0, sizeof(WAVEFORMATEX));
#ifdef LOG
		fprintf(Log, "0 M3D_set_3D_sample_data(%d)\n", samp);
#endif
		return 0;
	}

	Result->pOrgData = (BYTE*)info->data_ptr;
	Result->OrgLen = info->data_len;

	Result->Buffer.pAudioData = (BYTE*)info->data_ptr;
	Result->Buffer.AudioBytes = info->data_len;
	Result->Buffer.pContext = Result;

	EnterCriticalSection(&M3D_CS);
	Result->Status = SMP_STOPPED;
	LeaveCriticalSection(&M3D_CS);

#ifdef LOG
	fprintf(Log, "1 M3D_set_3D_sample_data(%d)\n", samp);
#endif
	return 1;
}

// Set / Get

void __stdcall M3D_set_3D_sample_volume(M3D_SAMPLE samp, G32 volume)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_volume(%d, %f)\n", samp, volume);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
		Result->volume = volume;
		UpdateSample(Result);
	}
}

G32 __stdcall M3D_3D_sample_volume(M3D_SAMPLE samp)
{
	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
#ifdef LOG
		fprintf(Log, "%f M3D_3D_sample_volume(%d)\n", (float)Result->volume, samp);
#endif

		return Result->volume;
	}
#ifdef LOG
	fprintf(Log, "0 M3D_3D_sample_volume(%d)\n", samp);
#endif
	return 0;
}

void __stdcall M3D_set_3D_sample_playback_rate(M3D_SAMPLE samp, int playback_rate)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_playback_rate(%d, %d)\n", samp, playback_rate);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->Buffer.pAudioData)
	{
		Result->playback_rate = playback_rate;
		UpdateSample(Result);
	}
}

int __stdcall M3D_3D_sample_playback_rate(M3D_SAMPLE samp)
{
	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
#ifdef LOG
		fprintf(Log, "%d M3D_3D_sample_playback_rate(%d)\n", Result->playback_rate, samp);
#endif
		return Result->playback_rate;
	}
#ifdef LOG
	fprintf(Log, "0 M3D_3D_sample_playback_rate(%d)\n", samp);
#endif
	return 0;
}

void __stdcall M3D_set_3D_sample_offset(M3D_SAMPLE samp, uInt offset)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_offset(%d, %d)\n", samp, offset);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->pOrgData)
	{
		Result->Buffer.pAudioData = &Result->pOrgData[offset];
		Result->Buffer.AudioBytes = Result->OrgLen - offset;
		// Works only if was called before start
	}
}

uInt __stdcall M3D_3D_sample_offset(M3D_SAMPLE samp)
{
	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->pOrgData)
	{
#ifdef LOG
		fprintf(Log, "%d M3D_3D_sample_offset(%d)\n", (uInt)(Result->Buffer.pAudioData - Result->pOrgData), samp);
#endif
		return (uInt)(Result->Buffer.pAudioData - Result->pOrgData);
	}
#ifdef LOG
	fprintf(Log, "0 M3D_3D_sample_offset(%d)\n", samp);
#endif
	return 0;
}

uInt __stdcall M3D_3D_sample_length(M3D_SAMPLE samp)
{
	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type && Result->OrgLen)
	{
#ifdef LOG
		fprintf(Log, "%d M3D_3D_sample_length(%d)\n", Result->OrgLen, samp);
#endif
		return (uInt)Result->OrgLen;
	}
#ifdef LOG
	fprintf(Log, "0 M3D_3D_sample_length(%d)\n", samp);
#endif
	return 0;
}

void __stdcall M3D_set_3D_sample_loop_count(M3D_SAMPLE samp, uInt loops)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_loop_count(%d, %d)\n", samp, loops);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
		Result->loops = loops;
		// Works only if was called before start
	}
}

uInt __stdcall M3D_3D_sample_loop_count(M3D_SAMPLE samp)
{
	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
#ifdef LOG
		fprintf(Log, "%d M3D_3D_sample_loop_count(%d)\n", Result->loops, samp);
#endif
		return Result->loops;
	}
#ifdef LOG
	fprintf(Log, "0 M3D_3D_sample_loop_count(%d)\n", samp);
#endif
	return 0;
}

void __stdcall M3D_set_3D_sample_loop_block(M3D_SAMPLE S, int loop_start_offset, int loop_end_offset)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_loop_block(%d, %d, %d)\n", S, loop_start_offset, loop_end_offset);
#endif

	M3D_Source* Result = (M3D_Source*)S;
	if(Result->Obj.type)
	{
		Result->loop_start_offset = loop_start_offset;
		Result->loop_end_offset = loop_end_offset;
		// Woks only if was called before start
	}
}

void __stdcall M3D_set_3D_sample_distances(M3D_SAMPLE samp, float max_dist, float min_dist)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_distances(%d, %f, %f)\n", samp, max_dist, min_dist);
#endif

	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
		Result->max_dist = max_dist;
		Result->min_dist = min_dist;
		UpdateSample(Result);
	}
}

void __stdcall M3D_3D_sample_distances(M3D_SAMPLE samp, float * max_dist, float * min_dist)
{
	M3D_Source* Result = (M3D_Source*)samp;
	if(Result->Obj.type)
	{
		*max_dist = Result->max_dist;
		*min_dist = Result->min_dist;
	}
}

void __stdcall M3D_set_3D_position(M3D_OBJECT* obj, float X, float Y, float Z)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		Result->X = X;
		Result->Y = Y;
		Result->Z = Z;

		UpdateSample(Result);
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			Listener.X = X;
			Listener.Y = Y;
			Listener.Z = Z;

			UpdateAllSamples();
		}
	}
}

void __stdcall M3D_3D_position(M3D_OBJECT* obj, float *X, float *Y, float *Z)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		*X = Result->X;
		*Y = Result->Y;
		*Z = Result->Z;
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			*X = Listener.X;
			*Y = Listener.Y;
			*Z = Listener.Z;
		}
	}
}

void __stdcall M3D_set_3D_velocity(M3D_OBJECT* obj, float dX_per_ms, float dY_per_ms, float dZ_per_ms, float magnitude)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		Result->dX_per_ms = dX_per_ms * magnitude;
		Result->dY_per_ms = dY_per_ms * magnitude;
		Result->dZ_per_ms = dZ_per_ms * magnitude;

		UpdateSample(Result);
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			Listener.dX_per_ms = dX_per_ms * magnitude;
			Listener.dY_per_ms = dY_per_ms * magnitude;
			Listener.dZ_per_ms = dZ_per_ms * magnitude;

			UpdateAllSamples();
		}
	}
}

void __stdcall M3D_set_3D_velocity_vector(M3D_OBJECT* obj, float dX_per_ms, float dY_per_ms, float dZ_per_ms)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		Result->dX_per_ms = dX_per_ms;
		Result->dY_per_ms = dY_per_ms;
		Result->dZ_per_ms = dZ_per_ms;

		UpdateSample(Result);
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			Listener.dX_per_ms = dX_per_ms;
			Listener.dY_per_ms = dY_per_ms;
			Listener.dZ_per_ms = dZ_per_ms;

			UpdateAllSamples();
		}
	}
}

void __stdcall M3D_3D_velocity(M3D_OBJECT* obj, float *dX_per_ms, float *dY_per_ms, float *dZ_per_ms)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		*dX_per_ms = Result->dX_per_ms;
		*dY_per_ms = Result->dY_per_ms;
		*dZ_per_ms = Result->dZ_per_ms;
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			*dX_per_ms = Listener.dX_per_ms;
			*dY_per_ms = Listener.dY_per_ms;
			*dZ_per_ms = Listener.dZ_per_ms;
		}
	}
}

void __stdcall M3D_set_3D_orientation(M3D_OBJECT* obj, float X_face, float Y_face, float Z_face, float X_up, float Y_up, float Z_up)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		Result->X_face = X_face;
		Result->Y_face = Y_face;
		Result->Z_face = Z_face;

		Result->X_up = X_up;
		Result->Y_up = Y_up;
		Result->Z_up = Z_up;

		UpdateSample(Result);
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			Listener.X_face = X_face;
			Listener.Y_face = Y_face;
			Listener.Z_face = Z_face;
			Listener.X_face = X_up;
			Listener.Y_face = Y_up;
			Listener.Z_face = Z_up;

			UpdateAllSamples();
		}
	}
}

void __stdcall M3D_3D_orientation(M3D_OBJECT*  obj, float *X_face, float *Y_face, float *Z_face, float *X_up, float *Y_up, float *Z_up)
{
	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		*X_face = Result->X_face;
		*Y_face = Result->Y_face;
		*Z_face = Result->Z_face;

		*X_up = Result->X_up;
		*Y_up = Result->Y_up;
		*Z_up = Result->Z_up;
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			*X_face = Listener.X_face;
			*Y_face = Listener.Y_face;
			*Z_face = Listener.Z_face;
			*X_up = Listener.X_face;
			*Y_up = Listener.Y_face;
			*Z_up = Listener.Z_face;
		}
	}
}

void __stdcall M3D_3D_update_position(M3D_OBJECT* obj, float dt_milliseconds)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_update_position(%d, %d)\n", obj, dt_milliseconds);
#endif

	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;

		Result->X += Result->dX_per_ms * dt_milliseconds;
		Result->Y += Result->dY_per_ms * dt_milliseconds;
		Result->Z += Result->dZ_per_ms * dt_milliseconds;
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			Listener.X += Listener.dX_per_ms * dt_milliseconds;
			Listener.Y += Listener.dY_per_ms * dt_milliseconds;
			Listener.Z += Listener.dZ_per_ms * dt_milliseconds;
		}
	}
}

void __stdcall M3D_set_3D_sample_cone(M3D_SAMPLE samp, float inner_angle, float outer_angle, int outer_volume)
{
	if(((M3D_Object*)samp)->type)
	{
		M3D_Source* Result = (M3D_Source*)samp;

		Result->inner_angle = inner_angle;
		Result->outer_angle = outer_angle;
		Result->outer_volume = outer_volume;

		UpdateSample(Result);
	}
}

void __stdcall M3D_3D_sample_cone(M3D_SAMPLE samp, float* inner_angle, float* outer_angle, int* outer_volume)
{
	if(((M3D_Object*)samp)->type)
	{
		M3D_Source* Result = (M3D_Source*)samp;

		*inner_angle = Result->inner_angle;
		*outer_angle = Result->outer_angle;
		*outer_volume = Result->outer_volume;
	}
}

void __stdcall M3D_3D_auto_update_position_callback(uInt user)
{
	M3D_3D_update_position((M3D_OBJECT*)user, 100);
}

void __stdcall M3D_3D_auto_update_position(M3D_OBJECT* obj, int enable)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_auto_update_position(%d, %d)\n", obj, enable);
#endif

	if(((M3D_Object*)obj)->type)
	{
		M3D_Source* Result = (M3D_Source*)obj;
		if(enable)
		{
			Result->AutoUpdatePosTimer = AIL_register_timer(M3D_3D_auto_update_position_callback);
			if(Result->AutoUpdatePosTimer)
			{
				AIL_set_timer_user(Result->AutoUpdatePosTimer, (uInt)obj);
				AIL_set_timer_frequency(Result->AutoUpdatePosTimer, 10);
				AIL_start_timer(Result->AutoUpdatePosTimer);
			}
		}
		else
		{
			if(Result->AutoUpdatePosTimer)
			{
				AIL_stop_timer(Result->AutoUpdatePosTimer);
				AIL_release_timer_handle(Result->AutoUpdatePosTimer);
				Result->AutoUpdatePosTimer = NULL;
			}
		}
	}
	else
	{
		if(obj == (M3D_OBJECT*)&Listener)
		{
			if(enable)
			{
				Listener.AutoUpdatePosTimer = AIL_register_timer(M3D_3D_auto_update_position_callback);
				if(Listener.AutoUpdatePosTimer)
				{
					AIL_set_timer_user(Listener.AutoUpdatePosTimer, (uInt)obj);
					AIL_set_timer_frequency(Listener.AutoUpdatePosTimer, 10);
					AIL_start_timer(Listener.AutoUpdatePosTimer);
				}
			}
			else
			{
				if(Listener.AutoUpdatePosTimer)
				{
					AIL_stop_timer(Listener.AutoUpdatePosTimer);
					AIL_release_timer_handle(Listener.AutoUpdatePosTimer);
					Listener.AutoUpdatePosTimer = NULL;
				}
			}
		}
	}
}

MSS_SAMPLE_CALLBACK __stdcall M3D_set_3D_EOS(M3D_SAMPLE client, M3D_SAMPLE samp, MSS_SAMPLE_CALLBACK cb)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_EOS(%d, %d, %d)\n", samp, client, cb);
#endif

	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
	{
		MSS_SAMPLE_CALLBACK Result = Sample->EOS_cb;
		Sample->EOS_client = client;
		Sample->EOS_cb = cb;
		return Result;
	}
	return NULL;
}

void __stdcall M3D_set_3D_sample_obstruction(M3D_SAMPLE samp, float obstruction)
{
	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
	{
		Sample->obstruction = obstruction;
		UpdateSample(Sample);
	}
}

float __stdcall M3D_3D_sample_obstruction(M3D_SAMPLE samp)
{
	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
		return Sample->obstruction;
	return 0.0f;
}

void __stdcall M3D_set_3D_sample_occlusion(M3D_SAMPLE samp, float occlusion)
{
	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
	{
		Sample->occlusion = occlusion;
		UpdateSample(Sample);
	}
}

float __stdcall M3D_3D_sample_occlusion(M3D_SAMPLE samp)
{
	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
		return Sample->occlusion;
	return 0.0f;
}

int __stdcall M3D_3D_room_type(void)
{
#ifdef LOG
	fprintf(Log, "%d M3D_3D_room_type\n", Current_EAX_room_type);
#endif
	return Current_EAX_room_type;
}

void __stdcall M3D_set_3D_room_type(int EAX_room_type)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_room_type(%d)\n", EAX_room_type);
#endif

	if((EAX_room_type < 0) && (EAX_room_type > NUM_ROOM_PRESETS))
		EAX_room_type = 0;
	Current_EAX_room_type = EAX_room_type;

	if(Samples)
	{
		for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
		{
			if(Samples[i].Status != SMP_FREE)
				UpdateReverb(&Samples[i]);
		}
	}
}

void __stdcall M3D_set_3D_sample_effects_level(M3D_SAMPLE samp, float effects_level)
{
#ifdef LOG
	fprintf(Log, "M3D_set_3D_sample_effects_level(%d, %f)\n", samp, effects_level);
#endif

	if(fabs(effects_level + 1.0f) < 0.0001f)
		effects_level = 1.0f;

	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
	{
		Sample->effects_level = effects_level;
		UpdateReverb(Sample);
	}
}

float __stdcall M3D_3D_sample_effects_level(M3D_SAMPLE samp)
{
#ifdef LOG
	fprintf(Log, "M3D_3D_sample_effects_level\n");
#endif

	M3D_Source* Sample = (M3D_Source*)samp;
	if(Sample->Obj.type)
		return Sample->effects_level;
	return 0.0f;
}