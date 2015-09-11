#ifndef _BINK_EXPORTS_
#define _BINK_EXPORTS_

#define BINK_SURFACE_32          3

struct BINK 
{
	uInt Width;
	uInt Height;
};

#ifdef _M_IX86

#define	BINK_DLL_NAME							"binkw32.dll"
#define	BINK_OPEN_FUNC_NAME						"_BinkOpen@8"
#define	BINK_GET_RECTS_FUNC_NAME				"_BinkGetRects@8"
#define	BINK_SET_SOUND_TRACK_FUNC_NAME			"_BinkSetSoundTrack@8"
#define	BINK_GOTO_FUNC_NAME						"_BinkGoto@12"
#define	BINK_OPEN_DIRECT_SOUND_FUNC_NAME		"_BinkOpenDirectSound@4"
#define	BINK_SET_SOUND_SYSTEM_FUNC_NAME			"_BinkSetSoundSystem@8"
#define	BINK_SET_SOUND_ON_OFF_FUNC_NAME			"_BinkSetSoundOnOff@8"
#define	BINK_OPEN_MILES_FUNC_NAME				"_BinkOpenMiles@4"
#define	BINK_GET_SUMMARY_FUNC_NAME				"_BinkGetSummary@8"
#define	BINK_GET_KEY_FRAME_FUNC_NAME			"_BinkGetKeyFrame@12"
#define	BINK_GET_REALTIME_FUNC_NAME				"_BinkGetRealtime@12"
#define	BINK_GET_TRACK_ID_FUNC_NAME				"_BinkGetTrackID@8"
#define	BINK_SET_VOLUME_G1_FUNC_NAME			"_BinkSetVolume@8"
#define	BINK_SET_VOLUME_G2_FUNC_NAME			"_BinkSetVolume@12"
#define	BINK_CLOSE_FUNC_NAME					"_BinkClose@4"
#define	BINK_WAIT_FUNC_NAME						"_BinkWait@4"
#define	BINK_REGISTER_FRAME_BUFFERS_FUNC_NAME	"_BinkRegisterFrameBuffers@8"
#define	BINK_DO_FRAME_FUNC_NAME					"_BinkDoFrame@4"
#define	BINK_SHOULD_SKIP_FUNC_NAME				"_BinkShouldSkip@4"
#define	BINK_NEXT_FRAME_FUNC_NAME				"_BinkNextFrame@4"
#define	BINK_GET_FRAME_BUFFERS_INFO_FUNC_NAME	"_BinkGetFrameBuffersInfo@8"
#define	BINK_PAUSE_FUNC_NAME					"_BinkPause@8"
#define	BINK_COPY_TO_BUFFER_FUNC_NAME			"_BinkCopyToBuffer@28"
#define	BINK_COPY_TO_BUFFER_RECT_FUNC_NAME		"_BinkCopyToBufferRect@44"
#define	BINK_GET_ERROR_FUNC_NAME				"_BinkGetError@0"

#else

#define	BINK_DLL_NAME							"binkw64.dll"
#define	BINK_OPEN_FUNC_NAME						"BinkOpen"
#define	BINK_GET_RECTS_FUNC_NAME				"BinkGetRects"
#define	BINK_SET_SOUND_TRACK_FUNC_NAME			"BinkSetSoundTrack"
#define	BINK_GOTO_FUNC_NAME						"BinkGoto"
#define	BINK_OPEN_DIRECT_SOUND_FUNC_NAME		"BinkOpenDirectSound"
#define	BINK_SET_SOUND_SYSTEM_FUNC_NAME			"BinkSetSoundSystem"
#define	BINK_GET_SUMMARY_FUNC_NAME				"BinkGetSummary"
#define	BINK_GET_KEY_FRAME_FUNC_NAME			"BinkGetKeyFrame"
#define	BINK_GET_REALTIME_FUNC_NAME				"BinkGetRealtime"
#define	BINK_GET_TRACK_ID_FUNC_NAME				"BinkGetTrackID"
#define	BINK_SET_VOLUME_FUNC_NAME				"BinkSetVolume"
#define	BINK_CLOSE_FUNC_NAME					"BinkClose"
#define	BINK_WAIT_FUNC_NAME						"BinkWait"
#define	BINK_REGISTER_FRAME_BUFFERS_FUNC_NAME	"BinkRegisterFrameBuffers"
#define	BINK_DO_FRAME_FUNC_NAME					"BinkDoFrame"
#define	BINK_SHOULD_SKIP_FUNC_NAME				"BinkShouldSkip"
#define	BINK_NEXT_FRAME_FUNC_NAME				"BinkNextFrame"
#define	BINK_GET_FRAME_BUFFERS_INFO_FUNC_NAME	"BinkGetFrameBuffersInfo"
#define	BINK_PAUSE_FUNC_NAME					"BinkPause"
#define	BINK_COPY_TO_BUFFER_FUNC_NAME			"BinkCopyToBuffer"
#define	BINK_COPY_TO_BUFFER_RECT_FUNC_NAME		"BinkCopyToBufferRect"
#define	BINK_GET_ERROR_FUNC_NAME				"BinkGetError"

#endif

typedef BINK*		(__stdcall* BinkOpenFuncPtr)(const char* name, uInt flags);
typedef int			(__stdcall* BinkGetRectsFuncPtr)(BINK* bnk, uInt flags);
typedef void		(__stdcall* BinkSetSoundTrackFuncPtr)(uInt total_tracks, uInt* tracks);
typedef void		(__stdcall* BinkGotoFuncPtr)(BINK* bnk, uInt frame, int flags);
typedef void*		(__stdcall* BinkOpenDirectSoundFuncPtr)(uInt param);
typedef int			(__stdcall* BinkSetSoundSystemFuncPtr)(void* open, uInt param);
typedef int			(__stdcall* BinkSetSoundOnOffFuncPtr)(BINK* bnk, int onoff);
typedef void*		(__stdcall* BinkOpenMilesFuncPtr)(uInt param);
typedef void		(__stdcall* BinkGetSummaryFuncPtr)(BINK* bnk, void* sum);
typedef uInt		(__stdcall* BinkGetKeyFrameFuncPtr)(BINK* bnk, uInt frame, int flags);
typedef void		(__stdcall* BinkGetRealtimeFuncPtr)(BINK* bink, void* run, uInt frames);
typedef uInt		(__stdcall* BinkGetTrackIDFuncPtr)(BINK* bnk, uInt trackindex);
typedef void		(__stdcall* BinkSetVolumeFuncG2Ptr)(BINK* bnk, uInt trackid, int volume);
typedef void		(__stdcall* BinkSetVolumeFuncG1Ptr)(BINK* bnk, int volume);
typedef void		(__stdcall* BinkCloseFuncPtr)(BINK* bnk);
typedef int			(__stdcall* BinkWaitFuncPtr)(BINK* bnk);
typedef void		(__stdcall* BinkRegisterFrameBuffersFuncPtr)(BINK* bink, void* fbset);
typedef int			(__stdcall* BinkDoFrameFuncPtr)(BINK* bnk);
typedef int			(__stdcall* BinkShouldSkipFuncPtr)(BINK* bink);
typedef void		(__stdcall* BinkNextFrameFuncPtr)(BINK* bnk);
typedef void		(__stdcall* BinkGetFrameBuffersInfoFuncPtr)(BINK* bink, void* fbset);
typedef int			(__stdcall* BinkPauseFuncPtr)(BINK* bnk, int pause);
typedef int			(__stdcall* BinkCopyToBufferFuncPtr)(BINK* bnk, void* dest, int destpitch, uInt destheight, uInt destx, uInt desty, uInt flags);
typedef int			(__stdcall* BinkCopyToBufferRectFuncPtr)(BINK* bnk,void* dest, int destpitch, uInt destheight, uInt destx, uInt desty, uInt srcx, uInt srcy, uInt srcw, uInt srch, uInt flags);
typedef const char*	(__stdcall* BinkGetErrorFuncPtr)(void);

#endif