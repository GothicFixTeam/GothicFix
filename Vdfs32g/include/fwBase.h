/*
Copyright (c) 2006-2009 Advanced Micro Devices, Inc. All Rights Reserved.
This software is subject to the Apache v2.0 License.
*/

#ifndef    __FWBASE_H__
#define    __FWBASE_H__

#ifndef    OPT_PREFIX
#define    OPT_PREFIX 
#endif

#ifndef    OPT_LEVEL
#define    OPT_LEVEL SSE2
#endif

//#if      (OPT_LEVEL==1)
//#undef   OPT_LEVEL
//#define  OPT_LEVEL SSE2
//#endif


#if   defined  (OPT_F10H)
#define        CBL_OPTLEVEL CBL_GH
#elif defined  (OPT_SSE3)
#error         Not supposed to be using SSE3 code path anywhere!
#elif defined  (OPT_SSE2)
#define        CBL_OPTLEVEL CBL_SSE2
#else
#define        CBL_OPTLEVEL CBL_SSE2    // for fe only ATM. Find a better fix if using it anywhere else
#endif


//
// Types
//
typedef    signed char          Fw8s ;
typedef    signed short         Fw16s;
typedef    signed int           Fw32s;
typedef    signed long long     Fw64s;

typedef    unsigned char        Fw8u ;
typedef    unsigned short       Fw16u;
typedef    unsigned int         Fw32u;
typedef    unsigned long long   Fw64u;

typedef    float                Fw32f;
typedef    double               Fw64f;

//
// MAX/MIN Data Types constants
//
#define FW_MAX_8U	  CBL_U8_MAX 	
#define FW_MIN_8U   CBL_U8_MIN
#define FW_MAX_16U  CBL_U16_MAX 
#define FW_MIN_16U  CBL_U16_MIN
#define FW_MAX_32U  CBL_U32_MAX 
#define FW_MIN_32U  CBL_U32_MIN
#define FW_MAX_64U  CBL_U64_MAX 
#define FW_MIN_64U  CBL_U64_MIN	
                    
#define FW_MAX_8S   CBL_S8_MAX	
#define FW_MIN_8S   CBL_S8_MIN
#define FW_MAX_16S  CBL_S16_MAX	
#define FW_MIN_16S  CBL_S16_MIN
#define FW_MAX_32S  CBL_S32_MAX	
#define FW_MIN_32S  CBL_S32_MIN
#define FW_MAX_64S  CBL_S64_MAX	
#define FW_MIN_64S  CBL_S64_MIN	


typedef struct Fw16sc
{
    Fw16s    re;
    Fw16s    im;
}Fw16sc;

typedef struct Fw32sc
{
    Fw32s    re;
    Fw32s    im;
}Fw32sc;

typedef struct Fw64sc
{
    Fw64s    re;
    Fw64s    im;
}Fw64sc;

typedef struct Fw32fc
{
    Fw32f    re;
    Fw32f    im;
} Fw32fc;

typedef struct Fw64fc
{
    Fw64f    re;
    Fw64f    im;
} Fw64fc;

typedef struct 
{
    int x;
    int y;
} FwiPoint;

typedef struct
{
    int width;
    int height;
} FwiSize;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} FwiRect;

typedef enum 
{
    fwAxsHorizontal,
    fwAxsVertical,
    fwAxsBoth
} FwiAxis;

typedef enum _FwiBorderType
{
    fwBorderConst          = 0,
    fwBorderRepl           = 1,
    fwBorderWrap           = 2,
    fwBorderMirror         = 3,
    fwBorderMirrorR        = 4,
    fwBorderMirror2        = 5,
    fwBorderInMem          = 6,
    fwBorderInMemTop       = 0x0010,
    fwBorderInMemBottom    = 0x0020
} FwiBorderType;

typedef enum  _FwiMaskSize 
{
    fwMskSize1x3 = 13,
    fwMskSize1x5 = 15,
    fwMskSize3x1 = 31,
    fwMskSize3x3 = 33,
    fwMskSize5x1 = 51,
    fwMskSize5x5 = 55
} FwiMaskSize;

//
// Enumerated Types
//

typedef enum 
{
    fwFalse = 0,    // No-Normalize sequence of coefficients 
    fwTrue          // Normalize sequence of coefficients 
} FwBool;


//! FwCpuType
typedef enum
{
    fwCpuUnknown  = 0,
    fwCpuSSE      = 0x40,
    fwCpuSSE2,
    fwCpuSSE3,
    fwCpuFamily10h
}FwCpuType;

typedef struct 
{
    int   major;
    int   minor;
    int   majorBuild;
    int   build;
    char  targetCpu[4];
    const char* Name;
    const char* Version; 
    const char* BuildDate;
} FwLibraryVersion;


//! FwStatus value enumeration
typedef enum 
{
     /* errors */
    fwStsNotSupportedModeErr           = -9999,
    fwStsCpuNotSupportedErr            = -9998,

    fwStsSizeMatchMatrixErr            = -204 ,
    fwStsCountMatrixErr                = -203 ,
    fwStsRoiShiftMatrixErr             = -202 ,

    fwStsResizeNoOperationErr          = -201 ,
    fwStsSrcDataErr                    = -200 ,
    fwStsMaxLenHuffCodeErr             = -199 ,
    fwStsCodeLenTableErr               = -198 ,
    fwStsFreqTableErr                  = -197 ,

    fwStsIncompleteContextErr          = -196 ,

    fwStsSingularErr                   = -195 ,
    fwStsSparseErr                     = -194 ,
    fwStsBitOffsetErr                  = -193 ,
    fwStsQPErr                         = -192 ,
    fwStsVLCErr                        = -191 ,
    fwStsRegExpOptionsErr              = -190 ,
    fwStsRegExpErr                     = -189 ,
    fwStsRegExpMatchLimitErr           = -188 ,
    fwStsRegExpQuantifierErr           = -187 ,
    fwStsRegExpGroupingErr             = -186 ,
    fwStsRegExpBackRefErr              = -185 ,
    fwStsRegExpChClassErr              = -184 ,
    fwStsRegExpMetaChErr               = -183 ,

    fwStsStrideMatrixErr               = -182 ,

    fwStsCTRSizeErr                    = -181 ,

    fwStsJPEG2KCodeBlockIsNotAttached  = -180 ,
    fwStsNotPosDefErr                  = -179 ,

    fwStsMessageErr                    = -177 ,
    fwStsOutOfECErr                    = -173 ,
    fwStsECCInvalidFlagErr             = -172 ,

    fwStsMP3FrameHeaderErr             = -171 ,
    fwStsMP3SideInfoErr                = -170 ,

    fwStsBlockStepErr                  = -169 ,
    fwStsMBStepErr                     = -168 ,

    fwStsAacPrgNumErr                  = -167 ,
    fwStsAacSectCbErr                  = -166 ,
    fwStsAacSfValErr                   = -164 ,
    fwStsAacCoefValErr                 = -163 ,
    fwStsAacMaxSfbErr                  = -162 ,
    fwStsAacPredSfbErr                 = -161 ,
    fwStsAacPlsDataErr                 = -160 ,
    fwStsAacGainCtrErr                 = -159 ,
    fwStsAacSectErr                    = -158 ,
    fwStsAacTnsNumFiltErr              = -157 ,
    fwStsAacTnsLenErr                  = -156 ,
    fwStsAacTnsOrderErr                = -155 ,
    fwStsAacTnsCoefResErr              = -154 ,
    fwStsAacTnsCoefErr                 = -153 ,
    fwStsAacTnsDirectErr               = -152 ,
    fwStsAacTnsProfileErr              = -151 ,
    fwStsAacErr                        = -150 ,
    fwStsAacBitOffsetErr               = -149 ,
    fwStsAacAdtsSyncWordErr            = -148 ,
    fwStsAacSmplRateIdxErr             = -147 ,
    fwStsAacWinLenErr                  = -146 ,
    fwStsAacWinGrpErr                  = -145 ,
    fwStsAacWinSeqErr                  = -144 ,
    fwStsAacComWinErr                  = -143 ,
    fwStsAacStereoMaskErr              = -142 ,
    fwStsAacChanErr                    = -141 ,
    fwStsAacMonoStereoErr              = -140 ,
    fwStsAacStereoLayerErr             = -139 ,
    fwStsAacMonoLayerErr               = -138 ,
    fwStsAacScalableErr                = -137 ,
    fwStsAacObjTypeErr                 = -136 ,
    fwStsAacWinShapeErr                = -135 ,
    fwStsAacPcmModeErr                 = -134 ,
    fwStsVLCUsrTblHeaderErr            = -133 ,
    fwStsVLCUsrTblUnsupportedFmtErr    = -132 ,
    fwStsVLCUsrTblEscAlgTypeErr        = -131 ,
    fwStsVLCUsrTblEscCodeLengthErr     = -130 ,
    fwStsVLCUsrTblCodeLengthErr        = -129 ,
    fwStsVLCInternalTblErr             = -128 ,
    fwStsVLCInputDataErr               = -127 ,
    fwStsVLCAACEscCodeLengthErr        = -126 ,
    fwStsNoiseRangeErr                 = -125 ,
    fwStsUnderRunErr                   = -124 ,
    fwStsPaddingErr                    = -123 ,
    fwStsCFBSizeErr                    = -122 ,
    fwStsPaddingSchemeErr              = -121 ,
    fwStsLengthErr                     = -119 ,
    fwStsBadModulusErr                 = -118 ,
    fwStsLPCCalcErr                    = -117 ,
    fwStsRCCalcErr                     = -116 ,
    fwStsIncorrectLSPErr               = -115 ,
    fwStsNoRootFoundErr                = -114 ,
    fwStsJPEG2KBadPassNumber           = -113 ,
    fwStsJPEG2KDamagedCodeBlock        = -112 ,
    fwStsH263CBPYCodeErr               = -111 ,
    fwStsH263MCBPCInterCodeErr         = -110 ,
    fwStsH263MCBPCIntraCodeErr         = -109 ,
    fwStsNotEvenStepErr                = -108 ,
    fwStsHistoNofLevelsErr             = -107 ,
    fwStsLUTNofLevelsErr               = -106 ,
    fwStsMP4BitOffsetErr               = -105 ,
    fwStsMP4QPErr                      = -104 ,
    fwStsMP4BlockIdxErr                = -103 ,
    fwStsMP4BlockTypeErr               = -102 ,
    fwStsMP4MVCodeErr                  = -101 ,
    fwStsMP4VLCCodeErr                 = -100 ,
    fwStsMP4DCCodeErr                  = -99  ,
    fwStsMP4FcodeErr                   = -98  ,
    fwStsMP4AlignErr                   = -97  ,
    fwStsMP4TempDiffErr                = -96  ,
    fwStsMP4BlockSizeErr               = -95  ,
    fwStsMP4ZeroBABErr                 = -94  ,
    fwStsMP4PredDirErr                 = -93  ,
    fwStsMP4BitsPerPixelErr            = -92  ,
    fwStsMP4VideoCompModeErr           = -91  ,
    fwStsMP4LinearModeErr              = -90  ,
    fwStsH263PredModeErr               = -83  ,
    fwStsH263BlockStepErr              = -82  ,
    fwStsH263MBStepErr                 = -81  ,
    fwStsH263FrameWidthErr             = -80  ,
    fwStsH263FrameHeightErr            = -79  ,
    fwStsH263ExpandPelsErr             = -78  ,
    fwStsH263PlaneStepErr              = -77  ,
    fwStsH263QuantErr                  = -76  ,
    fwStsH263MVCodeErr                 = -75  ,
    fwStsH263VLCCodeErr                = -74  ,
    fwStsH263DCCodeErr                 = -73  ,
    fwStsH263ZigzagLenErr              = -72  ,
    fwStsFBankFreqErr                  = -71  ,
    fwStsFBankFlagErr                  = -70  ,
    fwStsFBankErr                      = -69  ,
    fwStsNegOccErr                     = -67  ,
    fwStsCdbkFlagErr                   = -66  ,
    fwStsSVDCnvgErr                    = -65  ,
    fwStsJPEGHuffTableErr              = -64  ,
    fwStsJPEGDCTRangeErr               = -63  ,
    fwStsJPEGOutOfBufErr               = -62  ,
    fwStsDrawTextErr                   = -61  ,
    fwStsChannelOrderErr               = -60  ,
    fwStsZeroMaskValuesErr             = -59  ,
    fwStsQuadErr                       = -58  ,
    fwStsRectErr                       = -57  ,
    fwStsCoeffErr                      = -56  ,
    fwStsNoiseValErr                   = -55  ,
    fwStsDitherLevelsErr               = -54  ,
    fwStsNumChannelsErr                = -53  ,
    fwStsCOIErr                        = -52  ,
    fwStsDivisorErr                    = -51  ,
    fwStsAlphaTypeErr                  = -50  ,
    fwStsGammaRangeErr                 = -49  ,
    fwStsGrayCoefSumErr                = -48  ,
    fwStsChannelErr                    = -47  ,
    fwStsToneMagnErr                   = -46  ,
    fwStsToneFreqErr                   = -45  ,
    fwStsTonePhaseErr                  = -44  ,
    fwStsTrnglMagnErr                  = -43  ,
    fwStsTrnglFreqErr                  = -42  ,
    fwStsTrnglPhaseErr                 = -41  ,
    fwStsTrnglAsymErr                  = -40  ,
    fwStsHugeWinErr                    = -39  ,
    fwStsJaehneErr                     = -38  ,
    fwStsStrideErr                     = -37  ,
    fwStsEpsValErr                     = -36  ,
    fwStsWtOffsetErr                   = -35  ,
    fwStsAnchorErr                     = -34  ,
    fwStsMaskSizeErr                   = -33  ,
    fwStsShiftErr                      = -32  ,
    fwStsSampleFactorErr               = -31  ,
    fwStsSamplePhaseErr                = -30  ,
    fwStsFIRMRFactorErr                = -29  ,
    fwStsFIRMRPhaseErr                 = -28  ,
    fwStsRelFreqErr                    = -27  ,
    fwStsFIRLenErr                     = -26  ,
    fwStsIIROrderErr                   = -25  ,
    fwStsDlyLineIndexErr               = -24  ,
    fwStsResizeFactorErr               = -23  ,
    fwStsInterpolationErr              = -22  ,
    fwStsMirrorFlipErr                 = -21  ,
    fwStsMoment00ZeroErr               = -20  ,
    fwStsThreshNegLevelErr             = -19  ,
    fwStsThresholdErr                  = -18  ,
    fwStsContextMatchErr               = -17  ,
    fwStsStepErr                       = -14  ,
    fwStsScaleRangeErr                 = -13  ,
    fwStsDataTypeErr                   = -12  ,
    fwStsOutOfRangeErr                 = -11  ,
    fwStsDivByZeroErr                  = -10  ,
    fwStsMemAllocErr                   = -9   ,
    fwStsNullPtrErr                    = -8   ,
    fwStsRangeErr                      = -7   ,
    fwStsSizeErr                       = -6   ,
    fwStsBadArgErr                     = -5   ,
    fwStsNoMemErr                      = -4   ,
    fwStsSAReservedErr3                = -3   ,
    fwStsErr                           = -2   ,
    fwStsSAReservedErr1                = -1   ,

     // no errors                      
    fwStsNoErr                         =  0   ,

     // warnings                       
    fwStsNoOperation                   = 1    ,
    fwStsMisalignedBuf                 = 2    ,
    fwStsSqrtNegArg                    = 3    ,
    fwStsInvZero                       = 4    ,
    fwStsEvenMedianMaskSize            = 5    ,
    fwStsDivByZero                     = 6    ,
    fwStsLnZeroArg                     = 7    ,
    fwStsLnNegArg                      = 8    ,
    fwStsNanArg                        = 9    ,
    fwStsJPEGMarker                    = 10   ,
    fwStsResFloor                      = 11   ,
    fwStsOverflow                      = 12   ,
    fwStsLSFLow                        = 13   ,
    fwStsLSFHigh                       = 14   ,
    fwStsLSFLowAndHigh                 = 15   ,
    fwStsZeroOcc                       = 16   ,
    fwStsUnderflow                     = 17   ,
    fwStsSingularity                   = 18   ,
    fwStsDomain                        = 19   ,
    fwStsCpuMismatch                   = 21   ,
    fwStsNoFwFunctionFound            = 22   ,
    fwStsDllNotFoundBestUsed           = 23   ,
    fwStsNoOperationInDll              = 24   ,
    fwStsInsufficientEntropy           = 25   ,
    fwStsOvermuchStrings               = 26   ,
    fwStsOverlongString                = 27   ,
    fwStsAffineQuadChanged             = 28   ,
    fwStsWrongIntersectROI             = 29   ,
    fwStsWrongIntersectQuad            = 30   ,
    fwStsSmallerCodebook               = 31   ,
    fwStsSrcSizeLessExpected           = 32   ,
    fwStsDstSizeLessExpected           = 33   ,
    fwStsStreamEnd                     = 34   ,
    fwStsDoubleSize                    = 35   ,
    fwStsNotSupportedCpu               = 36   ,
    fwStsUnknownCacheSize              = 37   ,
    fwStsJPEGMarkerWarn                = 38
} FwStatus;

#define fwStsOk fwStsNoErr

// comparison
typedef enum 
{
    fwCmpLess     ,
    fwCmpLessEq   ,
    fwCmpEq       ,
    fwCmpGreaterEq,
    fwCmpGreater
} FwCmpOp;

// suggested algorithm
typedef enum 
{
    fwAlgHintNone,
    fwAlgHintFast,
    fwAlgHintAccurate
} FwHintAlgorithm;



// Round mode
typedef enum 
{
    fwRndZero,
    fwRndNear
} FwRoundMode;


//------------------------------------------------------
//            PLATFORM SPECIFIC
//------------------------------------------------------

#define STDCALL

//------------------------------------------------------

typedef void(*WorkFn)(void*);

#ifdef __cplusplus
extern "C" {
#endif


////////////////////////////////////////////////////////////////
//                        GetLibVersion
////////////////////////////////////////////////////////////////

const FwLibraryVersion* STDCALL fwGetLibVersion ();

////////////////////////////////////////////////////////////////
//                        GetStatusString
////////////////////////////////////////////////////////////////

const char * STDCALL fwGetStatusString( FwStatus StsCode );

////////////////////////////////////////////////////////////////
//                        GetCpuType
////////////////////////////////////////////////////////////////

FwCpuType   STDCALL fwGetCpuType();

////////////////////////////////////////////////////////////////
//                        GetCpuClocks
////////////////////////////////////////////////////////////////

Fw64u       STDCALL fwGetCpuClocks();

////////////////////////////////////////////////////////////////
//                        StaticInit
////////////////////////////////////////////////////////////////

FwStatus    STDCALL fwStaticInit();

////////////////////////////////////////////////////////////////
//                        StaticInitCpu
////////////////////////////////////////////////////////////////

FwStatus    STDCALL fwStaticInitCpu( FwCpuType cpu );

////////////////////////////////////////////////////////////////
//                        SetNumThreads
////////////////////////////////////////////////////////////////

FwStatus    STDCALL fwSetNumThreads( unsigned int numThr );

////////////////////////////////////////////////////////////////
//                        GetNumThreads
////////////////////////////////////////////////////////////////

Fw32u       STDCALL fwGetNumThreads();

////////////////////////////////////////////////////////////////
//                        Malloc
////////////////////////////////////////////////////////////////

void *       STDCALL fwMalloc( int length );

////////////////////////////////////////////////////////////////
//                        Free
////////////////////////////////////////////////////////////////

void         STDCALL fwFree( void * ptr );

////////////////////////////////////////////////////////////////
//                        AlignPtr
////////////////////////////////////////////////////////////////

void *       STDCALL fwAlignPtr( void *ptr, int alignBytes);

// Internal Functions


////////////////////////////////////////////////////////////////
//                        SetNumThreads_local
////////////////////////////////////////////////////////////////

FwStatus    STDCALL fwSetNumThreads_local( unsigned int numThr );

////////////////////////////////////////////////////////////////
//                        Run
////////////////////////////////////////////////////////////////

void         STDCALL fwRun( WorkFn workFn, void* param );

////////////////////////////////////////////////////////////////
//                        Wait
////////////////////////////////////////////////////////////////

void         STDCALL fwWait();

////////////////////////////////////////////////////////////////
//                        GetInitType
////////////////////////////////////////////////////////////////

int          STDCALL fwGetInitType();

////////////////////////////////////////////////////////////////
//                        BaseData
////////////////////////////////////////////////////////////////

void *       STDCALL fwBaseData();

#ifdef __cplusplus
}
#endif



#endif // __FWBASE_H__

