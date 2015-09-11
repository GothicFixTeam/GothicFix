/*
Copyright (c) 2006-2009 Advanced Micro Devices, Inc. All Rights Reserved.
This software is subject to the Apache v2.0 License.
*/

#ifndef __FWIMAGE_H__
#define __FWIMAGE_H__

#include "fwBase.h"

typedef struct LUTSpec FwiLUTSpec;

//
// Enumerations
//
enum {
    FWI_INTER_NN       = 1,            // Nearest neighbor
    FWI_INTER_LINEAR   = 2,            // Linera Interpolation
    FWI_INTER_CUBIC    = 4,            // Bicubic Interpolation
    FWI_INTER_SUPER    = 8,            // Supersampling
    FWI_INTER_LANCZOS  = 16,           // 3-lobe Lanczos Interpolation
    FWI_SMOOTH_EDGE    = ( 1<<31 )     // Edge Smooth Feature
};
typedef enum {
    fwWinBartlett,
    fwWinBlackman,
    fwWinHamming,
    fwWinHann,
    fwWinRect,
    fwWinKaiser
} FwWinType;

typedef enum {
    fwAlphaOver,
    fwAlphaIn,
    fwAlphaOut,
    fwAlphaATop,
    fwAlphaXor,
    fwAlphaPlus,
    fwAlphaOverPremul,
    fwAlphaInPremul,
    fwAlphaOutPremul,
    fwAlphaATopPremul,
    fwAlphaXorPremul,
    fwAlphaPlusPremul
} FwiAlphaType;

typedef enum {
    fwDitherNone,
    fwDitherFS,
    fwDitherJJN,
    fwDitherStucki,
    fwDitherBayer
} FwiDitherType;

#ifdef __cplusplus
extern "C" {
#endif


////////////////////////////////////////////////////////////////
//                        GetLibVersion
////////////////////////////////////////////////////////////////


const FwLibraryVersion* STDCALL fwiGetLibVersion ();

////////////////////////////////////////////////////////////////
//                        Malloc
////////////////////////////////////////////////////////////////

Fw8u * STDCALL fwiMalloc_8u_C1             ( int widthPixels, int heightPixels, int *pStepBytes );
Fw8u * STDCALL fwiMalloc_8u_C2             ( int widthPixels, int heightPixels, int *pStepBytes );
Fw8u * STDCALL fwiMalloc_8u_C3             ( int widthPixels, int heightPixels, int *pStepBytes );
Fw8u * STDCALL fwiMalloc_8u_C4             ( int widthPixels, int heightPixels, int *pStepBytes );
Fw8u * STDCALL fwiMalloc_8u_AC4            ( int widthPixels, int heightPixels, int *pStepBytes );

Fw16u * STDCALL fwiMalloc_16u_C1           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16u * STDCALL fwiMalloc_16u_C2           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16u * STDCALL fwiMalloc_16u_C3           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16u * STDCALL fwiMalloc_16u_C4           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16u * STDCALL fwiMalloc_16u_AC4          ( int widthPixels, int heightPixels, int *pStepBytes );

Fw16s* STDCALL fwiMalloc_16s_C1           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16s* STDCALL fwiMalloc_16s_C2           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16s* STDCALL fwiMalloc_16s_C3           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16s* STDCALL fwiMalloc_16s_C4           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw16s* STDCALL fwiMalloc_16s_AC4          ( int widthPixels, int heightPixels, int *pStepBytes );

Fw32s* STDCALL fwiMalloc_32s_C1           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32s* STDCALL fwiMalloc_32s_C2           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32s* STDCALL fwiMalloc_32s_C3           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32s* STDCALL fwiMalloc_32s_C4           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32s* STDCALL fwiMalloc_32s_AC4          ( int widthPixels, int heightPixels, int *pStepBytes );

Fw32f* STDCALL fwiMalloc_32f_C1           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32f* STDCALL fwiMalloc_32f_C2           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32f* STDCALL fwiMalloc_32f_C3           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32f* STDCALL fwiMalloc_32f_C4           ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32f* STDCALL fwiMalloc_32f_AC4          ( int widthPixels, int heightPixels, int *pStepBytes );

Fw32sc* STDCALL fwiMalloc_32sc_C1         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32sc* STDCALL fwiMalloc_32sc_C2         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32sc* STDCALL fwiMalloc_32sc_C3         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32sc* STDCALL fwiMalloc_32sc_C4         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32sc* STDCALL fwiMalloc_32sc_AC4        ( int widthPixels, int heightPixels, int *pStepBytes );

Fw32fc* STDCALL fwiMalloc_32fc_C1         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32fc* STDCALL fwiMalloc_32fc_C2         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32fc* STDCALL fwiMalloc_32fc_C3         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32fc* STDCALL fwiMalloc_32fc_C4         ( int widthPixels, int heightPixels, int *pStepBytes );
Fw32fc* STDCALL fwiMalloc_32fc_AC4        ( int widthPixels, int heightPixels, int *pStepBytes );

////////////////////////////////////////////////////////////////
//                        Free
////////////////////////////////////////////////////////////////


void STDCALL fwiFree ( void *ptr );

////////////////////////////////////////////////////////////////
//                        Convert
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiConvert_8u16u_C1R     ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u16u_C3R     ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u16u_C4R     ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u16u_AC4R    ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_8u16s_C1R     ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u16s_C3R     ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u16s_C4R     ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u16s_AC4R    ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_8u32s_C1R     ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u32s_C3R     ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u32s_C4R     ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u32s_AC4R    ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_8s32s_C1R     ( const Fw8s  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8s32s_C3R     ( const Fw8s  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8s32s_C4R     ( const Fw8s  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8s32s_AC4R    ( const Fw8s  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_16u32s_C1R    ( const Fw16u *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u32s_C3R    ( const Fw16u *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u32s_C4R    ( const Fw16u *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u32s_AC4R   ( const Fw16u *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_8u32f_C1R     ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u32f_C3R     ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u32f_C4R     ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8u32f_AC4R    ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_8s32f_C1R     ( const Fw8s  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8s32f_C3R     ( const Fw8s  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8s32f_C4R     ( const Fw8s  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_8s32f_AC4R    ( const Fw8s  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_16u32f_C1R    ( const Fw16u *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u32f_C3R    ( const Fw16u *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u32f_C4R    ( const Fw16u *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u32f_AC4R   ( const Fw16u *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_16s32f_C1R    ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16s32f_C3R    ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16s32f_C4R    ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16s32f_AC4R   ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

//Reduced bit depth
FwStatus STDCALL fwiConvert_16u8u_C1R     ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u8u_C3R     ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u8u_C4R     ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16u8u_AC4R    ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_16s8u_C1R     ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16s8u_C3R     ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16s8u_C4R     ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_16s8u_AC4R    ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_32s8u_C1R     ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32s8u_C3R     ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32s8u_C4R     ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32s8u_AC4R    ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_32s8s_C1R     ( const Fw32s *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32s8s_C3R     ( const Fw32s *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32s8s_C4R     ( const Fw32s *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32s8s_AC4R    ( const Fw32s *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_32f8u_C1R     ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f8u_C3R     ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f8u_C4R     ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f8u_AC4R    ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_32f8s_C1R     ( const Fw32f *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f8s_C3R     ( const Fw32f *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f8s_C4R     ( const Fw32f *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f8s_AC4R    ( const Fw32f *pSrc, int srcStep, Fw8s  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_32f16s_C1R     ( const Fw32f *pSrc, int srcStep, Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f16s_C3R     ( const Fw32f *pSrc, int srcStep, Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f16s_C4R     ( const Fw32f *pSrc, int srcStep, Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f16s_AC4R    ( const Fw32f *pSrc, int srcStep, Fw16s  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiConvert_32f16u_C1R     ( const Fw32f *pSrc, int srcStep, Fw16u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f16u_C3R     ( const Fw32f *pSrc, int srcStep, Fw16u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f16u_C4R     ( const Fw32f *pSrc, int srcStep, Fw16u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiConvert_32f16u_AC4R    ( const Fw32f *pSrc, int srcStep, Fw16u  *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Copy
////////////////////////////////////////////////////////////////



FwStatus STDCALL fwiCopy_8u_C1R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C3R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C4R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_AC4R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C3AC4R        ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_AC4C3R        ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_8u_C3CR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C4CR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C3C1R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C4C1R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C1C3R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C1C4R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_16s_C1R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C3R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C4R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_AC4R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C3AC4R       ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_AC4C3R       ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_16s_C3CR         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C4CR         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C3C1R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C4C1R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C1C3R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C1C4R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_32s_C1R          ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C3R          ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C4R          ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_AC4R         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C3AC4R       ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_AC4C3R       ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_32s_C3CR         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C4CR         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C3C1R        ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C4C1R        ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C1C3R        ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C1C4R        ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_32f_C1R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C3R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C4R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_AC4R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C3AC4R       ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_AC4C3R       ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_32f_C3CR         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C4CR         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C3C1R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C4C1R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C1C3R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C1C4R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_8u_C3P3R         ( const Fw8u  *       pSrc   , int srcStep, Fw8u  * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_C4P4R         ( const Fw8u  *       pSrc   , int srcStep, Fw8u  * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_P3C3R         ( const Fw8u  * const pSrc[3], int srcStep, Fw8u  *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_8u_P4C4R         ( const Fw8u  * const pSrc[4], int srcStep, Fw8u  *       pDst   , int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_16s_C3P3R        ( const Fw16s *       pSrc   , int srcStep, Fw16s * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_C4P4R        ( const Fw16s *       pSrc   , int srcStep, Fw16s * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_P3C3R        ( const Fw16s * const pSrc[3], int srcStep, Fw16s *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_16s_P4C4R        ( const Fw16s * const pSrc[4], int srcStep, Fw16s *       pDst   , int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_32s_C3P3R        ( const Fw32s *       pSrc   , int srcStep, Fw32s * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_C4P4R        ( const Fw32s *       pSrc   , int srcStep, Fw32s * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_P3C3R        ( const Fw32s * const pSrc[3], int srcStep, Fw32s *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32s_P4C4R        ( const Fw32s * const pSrc[4], int srcStep, Fw32s *       pDst   , int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiCopy_32f_C3P3R        ( const Fw32f *       pSrc   , int srcStep, Fw32f * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_C4P4R        ( const Fw32f *       pSrc   , int srcStep, Fw32f * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_P3C3R        ( const Fw32f * const pSrc[3], int srcStep, Fw32f *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiCopy_32f_P4C4R        ( const Fw32f * const pSrc[4], int srcStep, Fw32f *       pDst   , int dstStep, FwiSize roiSize );


FwStatus STDCALL fwiCopy_8u_C1MR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_8u_C3MR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_8u_C4MR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_8u_AC4MR         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
                                                                                     
FwStatus STDCALL fwiCopy_16s_C1MR         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_16s_C3MR         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_16s_C4MR         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_16s_AC4MR        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );

FwStatus STDCALL fwiCopy_32s_C1MR         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_32s_C3MR         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_32s_C4MR         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_32s_AC4MR        ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );

FwStatus STDCALL fwiCopy_32f_C1MR         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_32f_C3MR         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_32f_C4MR         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );
FwStatus STDCALL fwiCopy_32f_AC4MR        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw8u *pMask, int maskStep );

////////////////////////////////////////////////////////////////
//                        Swap
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiSwapChannels_8u_C3R   ( const Fw8u  *pSrc,    int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_8u_AC4R  ( const Fw8u  *pSrc,    int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_16u_C3R  ( const Fw16u *pSrc,    int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_16u_AC4R ( const Fw16u *pSrc,    int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_32s_C3R  ( const Fw32s *pSrc,    int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_32s_AC4R ( const Fw32s *pSrc,    int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_32f_C3R  ( const Fw32f *pSrc,    int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_32f_AC4R ( const Fw32f *pSrc,    int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,const int dstOrder[3] );
FwStatus STDCALL fwiSwapChannels_8u_C3IR  (       Fw8u  *pSrcDst, int srcDstStep,                         FwiSize roiSize,const int dstOrder[3] );

////////////////////////////////////////////////////////////////
//                        ZigZag
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiZigzagFwd8x8_16s_C1   ( const Fw16s *pSrc, Fw16s *pDst );
FwStatus STDCALL fwiZigzagInv8x8_16s_C1   ( const Fw16s *pSrc, Fw16s *pDst );

////////////////////////////////////////////////////////////////
//                        Set
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiSet_8u_C1R            (       Fw8u  value,    Fw8u   *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_8u_C3R            ( const Fw8u  value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_8u_AC4R           ( const Fw8u  value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_8u_C4R            ( const Fw8u  value[4], Fw8u   *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_8u_C3CR           (       Fw8u  value,    Fw8u   *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_8u_C4CR           (       Fw8u  value,    Fw8u   *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiSet_16s_C1R           (       Fw16s value,    Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_16s_C3R           ( const Fw16s value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_16s_AC4R          ( const Fw16s value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_16s_C4R           ( const Fw16s value[4], Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_16s_C3CR          (       Fw16s value,    Fw16s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_16s_C4CR          (       Fw16s value,    Fw16s  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiSet_32s_C1R           (       Fw32s value,    Fw32s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32s_C3R           ( const Fw32s value[3], Fw32s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32s_AC4R          ( const Fw32s value[3], Fw32s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32s_C4R           ( const Fw32s value[4], Fw32s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32s_C3CR          (       Fw32s value,    Fw32s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32s_C4CR          (       Fw32s value,    Fw32s  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiSet_32f_C1R           (       Fw32f value,    Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32f_C3R           ( const Fw32f value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32f_AC4R          ( const Fw32f value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32f_C4R           ( const Fw32f value[4], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32f_C3CR          (       Fw32f value,    Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSet_32f_C4CR          (       Fw32f value,    Fw32f  *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiSet_8u_C1MR           (       Fw8u  value,    Fw8u   *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_8u_C3MR           ( const Fw8u  value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_8u_AC4MR          ( const Fw8u  value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_8u_C4MR           ( const Fw8u  value[4], Fw8u   *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );

FwStatus STDCALL fwiSet_16s_C1MR          (       Fw16s value,    Fw16s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_16s_C3MR          ( const Fw16s value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_16s_AC4MR         ( const Fw16s value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_16s_C4MR          ( const Fw16s value[4], Fw16s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );

FwStatus STDCALL fwiSet_32s_C1MR          (       Fw32s value,    Fw32s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_32s_C3MR          ( const Fw32s value[3], Fw32s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_32s_AC4MR         ( const Fw32s value[3], Fw32s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_32s_C4MR          ( const Fw32s value[4], Fw32s  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );

FwStatus STDCALL fwiSet_32f_C1MR          (       Fw32f value,    Fw32f  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_32f_C3MR          ( const Fw32f value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_32f_AC4MR         ( const Fw32f value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );
FwStatus STDCALL fwiSet_32f_C4MR          ( const Fw32f value[4], Fw32f  *pDst, int dstStep, FwiSize roiSize, const Fw8u  *pMask, int maskStep );

////////////////////////////////////////////////////////////////
//                        Scale
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiScale_8u16u_C1R       ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16u_C4R       ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16s_C1R       ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16s_C3R       ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16s_C4R       ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u16s_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u32s_C1R       ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u32s_C3R       ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u32s_C4R       ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiScale_8u32s_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize );

FwStatus STDCALL fwiScale_16u8u_C1R       ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16u8u_C3R       ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16u8u_C4R       ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16u8u_AC4R      ( const Fw16u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16s8u_C1R       ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16s8u_C3R       ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16s8u_C4R       ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_16s8u_AC4R      ( const Fw16s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_32s8u_C1R       ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_32s8u_C3R       ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_32s8u_C4R       ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );
FwStatus STDCALL fwiScale_32s8u_AC4R      ( const Fw32s *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwHintAlgorithm hint );

FwStatus STDCALL fwiScale_8u32f_C1R       ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_8u32f_C3R       ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_8u32f_C4R       ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_8u32f_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_32f8u_C1R       ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_32f8u_C3R       ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_32f8u_C4R       ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );
FwStatus STDCALL fwiScale_32f8u_AC4R      ( const Fw32f *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, Fw32f vMin, Fw32f vMax );

////////////////////////////////////////////////////////////////
//                        Abs
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiAbs_16s_C1IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_16s_C3IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_16s_C4IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_16s_AC4IR         ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_C1IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_C3IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_C4IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_AC4IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAbs_16s_C1R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_16s_C3R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_16s_C4R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_16s_AC4R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_C1R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_C3R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_C4R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbs_32f_AC4R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AbsDiff
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiAbsDiff_8u_C1R        ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbsDiff_16u_C1R       ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAbsDiff_32f_C1R       ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AbsDiffC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAbsDiffC_8u_C1R       ( const Fw8u  *pSrc, int srcStep,  Fw8u  *pDst, int dstStep, FwiSize roiSize, int    value );
FwStatus STDCALL fwiAbsDiffC_16u_C1R      ( const Fw16u *pSrc, int srcStep,  Fw16u *pDst, int dstStep, FwiSize roiSize, int    value );
FwStatus STDCALL fwiAbsDiffC_32f_C1R      ( const Fw32f *pSrc, int srcStep,  Fw32f *pDst, int dstStep, FwiSize roiSize, Fw32f value );

////////////////////////////////////////////////////////////////
//                        Add
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAdd_8u_C1IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_8u_C3IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_8u_C4IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_8u_AC4IRSfs       ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_C1IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_C3IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_C4IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_AC4IRSfs      ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16sc_C1IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16sc_C3IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16sc_AC4IRSfs     ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32sc_C1IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32sc_C3IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32sc_AC4IRSfs     ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32f_C1IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_C3IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_C4IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_AC4IR         ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32fc_C1IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32fc_C3IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32fc_AC4IR        ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_8u32f_C1IR        ( const Fw8u   *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_8s32f_C1IR        ( const Fw8s   *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_16u32f_C1IR       ( const Fw16u  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAdd_8u32f_C1IMR       ( const Fw8u   *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_8s32f_C1IMR       ( const Fw8s   *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_16u32f_C1IMR      ( const Fw16u  *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_C1IMR         ( const Fw32f  *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAdd_8u_C1RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_8u_C3RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_8u_C4RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_8u_AC4RSfs        ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_C1RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_C3RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_C4RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16s_AC4RSfs       ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16sc_C1RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16sc_C3RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_16sc_AC4RSfs      ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32sc_C1RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32sc_C3RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32sc_AC4RSfs      ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAdd_32f_C1R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_C3R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_C4R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32f_AC4R          ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32fc_C1R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32fc_C3R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAdd_32fc_AC4R         ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AddC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAddC_8u_C1IRSfs       (       Fw8u   value   , Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_8u_C3IRSfs       ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_8u_AC4IRSfs      ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_8u_C4IRSfs       ( const Fw8u   value[4], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_C1IRSfs      (       Fw16s  value   , Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_C3IRSfs      ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_AC4IRSfs     ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_C4IRSfs      ( const Fw16s  value[4], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16sc_C1IRSfs     (       Fw16sc value   , Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16sc_C3IRSfs     ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16sc_AC4IRSfs    ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32sc_C1IRSfs     (       Fw32sc value   , Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32sc_C3IRSfs     ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32sc_AC4IRSfs    ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32f_C1IR         (       Fw32f  value   , Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32f_C3IR         ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32f_AC4IR        ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32f_C4IR         ( const Fw32f  value[4], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32fc_C1IR        (       Fw32fc value   , Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32fc_C3IR        ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32fc_AC4IR       ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAddC_8u_C1RSfs        ( const Fw8u   *pSrc, int srcStep,       Fw8u   value   , Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_8u_C3RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_8u_AC4RSfs       ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_8u_C4RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[4], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_C1RSfs       ( const Fw16s  *pSrc, int srcStep,       Fw16s  value   , Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_C3RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_AC4RSfs      ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16s_C4RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[4], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16sc_C1RSfs      ( const Fw16sc *pSrc, int srcStep,       Fw16sc value   , Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16sc_C3RSfs      ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_16sc_AC4RSfs     ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32sc_C1RSfs      ( const Fw32sc *pSrc, int srcStep,       Fw32sc value   , Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32sc_C3RSfs      ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32sc_AC4RSfs     ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiAddC_32f_C1R          ( const Fw32f  *pSrc, int srcStep,       Fw32f  value   , Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32f_C3R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32f_AC4R         ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32f_C4R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[4], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32fc_C1R         ( const Fw32fc *pSrc, int srcStep,       Fw32fc value   , Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32fc_C3R         ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddC_32fc_AC4R        ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AddProduct
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAddProduct_8u32f_C1IR     ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddProduct_8s32f_C1IR     ( const Fw8s  *pSrc1, int src1Step, const Fw8s  *pSrc2, int src2Step, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddProduct_16u32f_C1IR    ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddProduct_32f_C1IR       ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAddProduct_8u32f_C1IMR    ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddProduct_8s32f_C1IMR    ( const Fw8s  *pSrc1, int src1Step, const Fw8s  *pSrc2, int src2Step, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddProduct_16u32f_C1IMR   ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddProduct_32f_C1IMR      ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AddSquare
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAddSquare_8u32f_C1IR      ( const Fw8u  *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddSquare_8s32f_C1IR      ( const Fw8s  *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddSquare_16u32f_C1IR     ( const Fw16u *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddSquare_32f_C1IR        ( const Fw32f *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAddSquare_8u32f_C1IMR     ( const Fw8u  *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddSquare_8s32f_C1IMR     ( const Fw8s  *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddSquare_16u32f_C1IMR    ( const Fw16u *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAddSquare_32f_C1IMR       ( const Fw32f *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AddWeighted
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAddWeighted_8u32f_C1IR    ( const Fw8u  *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );
FwStatus STDCALL fwiAddWeighted_8s32f_C1IR    ( const Fw8s  *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );
FwStatus STDCALL fwiAddWeighted_16u32f_C1IR   ( const Fw16u *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );
FwStatus STDCALL fwiAddWeighted_32f_C1IR      ( const Fw32f *pSrc, int srcStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );

FwStatus STDCALL fwiAddWeighted_8u32f_C1IMR   ( const Fw8u  *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );
FwStatus STDCALL fwiAddWeighted_8s32f_C1IMR   ( const Fw8s  *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );
FwStatus STDCALL fwiAddWeighted_16u32f_C1IMR  ( const Fw16u *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );
FwStatus STDCALL fwiAddWeighted_32f_C1IMR     ( const Fw32f *pSrc, int srcStep, const Fw8u *pMask, int maskStep, Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, Fw32f alpha );

////////////////////////////////////////////////////////////////
//                        Div
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiDiv_8u_C1IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_8u_C3IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16s_C1IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16s_C3IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16sc_C1IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16sc_C3IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16sc_AC4IRSfs     ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32sc_C1IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32sc_C3IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32sc_AC4IRSfs     ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32f_C1IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32f_C3IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32f_C4IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32f_AC4IR         ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32fc_C1IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32fc_C3IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32fc_AC4IR        ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiDiv_8u_C1RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_8u_C3RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16s_C1RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16s_C3RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16sc_C1RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16sc_C3RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_16sc_AC4RSfs      ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32sc_C1RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32sc_C3RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32sc_AC4RSfs      ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDiv_32f_C1R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32f_C3R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32f_C4R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32f_AC4R          ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32fc_C1R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32fc_C3R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDiv_32fc_AC4R         ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        DivC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiDivC_8u_C1IRSfs       (       Fw8u   value   , Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_8u_C3IRSfs       ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_8u_AC4IRSfs      ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16s_C1IRSfs      (       Fw16s  value   , Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16s_C3IRSfs      ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16s_AC4IRSfs     ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16sc_C1IRSfs     (       Fw16sc value   , Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16sc_C3IRSfs     ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16sc_AC4IRSfs    ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32sc_C1IRSfs     (       Fw32sc value   , Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32sc_C3IRSfs     ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32sc_AC4IRSfs    ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32f_C1IR         (       Fw32f  value   , Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32f_C3IR         ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32f_AC4IR        ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32fc_C1IR        (       Fw32fc value   , Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32fc_C3IR        ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32fc_AC4IR       ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiDivC_8u_C1RSfs        ( const Fw8u   *pSrc, int srcStep,       Fw8u   value   , Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_8u_C3RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_8u_AC4RSfs       ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16s_C1RSfs       ( const Fw16s  *pSrc, int srcStep,       Fw16s  value   , Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16s_C3RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16s_AC4RSfs      ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16sc_C1RSfs      ( const Fw16sc *pSrc, int srcStep,       Fw16sc value   , Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16sc_C3RSfs      ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_16sc_AC4RSfs     ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32sc_C1RSfs      ( const Fw32sc *pSrc, int srcStep,       Fw32sc value,    Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32sc_C3RSfs      ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32sc_AC4RSfs     ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiDivC_32f_C1R          ( const Fw32f  *pSrc, int srcStep,       Fw32f  value   , Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32f_C3R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32f_AC4R         ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32fc_C1R         ( const Fw32fc *pSrc, int srcStep,       Fw32fc value   , Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32fc_C3R         ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiDivC_32fc_AC4R        ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Exp
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiExp_8u_C1IRSfs        ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_8u_C3IRSfs        ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_16s_C1IRSfs       ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_16s_C3IRSfs       ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_32f_C1IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiExp_32f_C3IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiExp_8u_C1RSfs         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_8u_C3RSfs         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_16s_C1RSfs        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_16s_C3RSfs        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiExp_32f_C1R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiExp_32f_C3R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Ln
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiLn_8u_C1IRSfs         ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_8u_C3IRSfs         ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_16s_C1IRSfs        ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_16s_C3IRSfs        ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_32f_C1IR           ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLn_32f_C3IR           ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiLn_8u_C1RSfs          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_8u_C3RSfs          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_16s_C1RSfs         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_16s_C3RSfs         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiLn_32f_C1R            ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLn_32f_C3R            ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Mul
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiMul_8u_C1IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_8u_C3IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_8u_C4IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_8u_AC4IRSfs       ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_C1IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_C3IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_C4IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_AC4IRSfs      ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16sc_C1IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16sc_C3IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16sc_AC4IRSfs     ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32sc_C1IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32sc_C3IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32sc_AC4IRSfs     ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32f_C1IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32f_C3IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32f_C4IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32f_AC4IR         ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32fc_C1IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32fc_C3IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32fc_AC4IR        ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiMul_8u_C1RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_8u_C3RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_8u_C4RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_8u_AC4RSfs        ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_C1RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_C3RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_C4RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16s_AC4RSfs       ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16sc_C1RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16sc_C3RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_16sc_AC4RSfs      ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32sc_C1RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32sc_C3RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32sc_AC4RSfs      ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMul_32f_C1R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32f_C3R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32f_C4R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32f_AC4R          ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32fc_C1R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32fc_C3R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMul_32fc_AC4R         ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        MulC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiMulC_8u_C1IRSfs       (       Fw8u   value   , Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_8u_C3IRSfs       ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_8u_AC4IRSfs      ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_8u_C4IRSfs       ( const Fw8u   value[4], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_C1IRSfs      (       Fw16s  value   , Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_C3IRSfs      ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_AC4IRSfs     ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_C4IRSfs      ( const Fw16s  value[4], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16sc_C1IRSfs     (       Fw16sc value   , Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16sc_C3IRSfs     ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16sc_AC4IRSfs    ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32sc_C1IRSfs     (       Fw32sc value   , Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32sc_C3IRSfs     ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32sc_AC4IRSfs    ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32f_C1IR         (       Fw32f  value   , Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32f_C3IR         ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32f_AC4IR        ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32f_C4IR         ( const Fw32f  value[4], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32fc_C1IR        (       Fw32fc value   , Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32fc_C3IR        ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32fc_AC4IR       ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiMulC_8u_C1RSfs        ( const Fw8u   *pSrc, int srcStep,       Fw8u   value   , Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_8u_C3RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_8u_AC4RSfs       ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_8u_C4RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[4], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_C1RSfs       ( const Fw16s  *pSrc, int srcStep,       Fw16s  value   , Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_C3RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_AC4RSfs      ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16s_C4RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[4], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16sc_C1RSfs      ( const Fw16sc *pSrc, int srcStep,       Fw16sc value   , Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16sc_C3RSfs      ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_16sc_AC4RSfs     ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32sc_C1RSfs      ( const Fw32sc *pSrc, int srcStep,       Fw32sc value   , Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32sc_C3RSfs      ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32sc_AC4RSfs     ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiMulC_32f_C1R          ( const Fw32f  *pSrc, int srcStep,       Fw32f  value   , Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32f_C3R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32f_AC4R         ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32f_C4R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[4], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32fc_C1R         ( const Fw32fc *pSrc, int srcStep,       Fw32fc value   , Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32fc_C3R         ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulC_32fc_AC4R        ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        MulScale
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiMulScale_8u_C1IR      ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_8u_C3IR      ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_8u_C4IR      ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_8u_AC4IR     ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_C1IR     ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_C3IR     ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_C4IR     ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_AC4IR    ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiMulScale_8u_C1R       ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_8u_C3R       ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_8u_C4R       ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_8u_AC4R      ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_C1R      ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_C3R      ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_C4R      ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulScale_16u_AC4R     ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        MulCScale
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiMulCScale_8u_C1IR     (       Fw8u  value   , Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_8u_C3IR     ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_8u_AC4IR    ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_8u_C4IR     ( const Fw8u  value[4], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_C1IR    (       Fw16u value   , Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_C3IR    ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_AC4IR   ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_C4IR    ( const Fw16u value[4], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiMulCScale_8u_C1R      ( const Fw8u  *pSrc, int srcStep,       Fw8u  value   , Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_8u_C3R      ( const Fw8u  *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_8u_AC4R     ( const Fw8u  *pSrc, int srcStep, const Fw8u  value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_8u_C4R      ( const Fw8u  *pSrc, int srcStep, const Fw8u  value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_C1R     ( const Fw16u *pSrc, int srcStep,       Fw16u value   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_C3R     ( const Fw16u *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_AC4R    ( const Fw16u *pSrc, int srcStep, const Fw16u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiMulCScale_16u_C4R     ( const Fw16u *pSrc, int srcStep, const Fw16u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Sqr
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiSqr_8u_C1IRSfs        ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_8u_C3IRSfs        ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_8u_C4IRSfs        ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_8u_AC4IRSfs       ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_C1IRSfs       ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_C3IRSfs       ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_C4IRSfs       ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_AC4IRSfs      ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_C1IRSfs       ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_C3IRSfs       ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_C4IRSfs       ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_AC4IRSfs      ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_32f_C1IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqr_32f_C3IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqr_32f_C4IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqr_32f_AC4IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiSqr_8u_C1RSfs         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_8u_C3RSfs         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_8u_C4RSfs         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_8u_AC4RSfs        ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_C1RSfs        ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_C3RSfs        ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_C4RSfs        ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16u_AC4RSfs       ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_C1RSfs        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_C3RSfs        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_C4RSfs        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_16s_AC4RSfs       ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqr_32f_C1R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqr_32f_C3R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqr_32f_AC4R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Sqrt
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiSqrt_8u_C1IRSfs       ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_8u_C3IRSfs       ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_8u_AC4IRSfs      ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16s_C1IRSfs      ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16s_C3IRSfs      ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16s_AC4IRSfs     ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16u_C1IRSfs      ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16u_C3IRSfs      ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16u_AC4IRSfs     ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_32f_C1IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqrt_32f_C3IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqrt_32f_C4IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqrt_32f_AC4IR        ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiSqrt_8u_C1RSfs        ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_8u_C3RSfs        ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_8u_AC4RSfs       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16s_C1RSfs       ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16s_C3RSfs       ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16s_AC4RSfs      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16u_C1RSfs       ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16u_C3RSfs       ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_16u_AC4RSfs      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSqrt_32f_C1R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqrt_32f_C3R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSqrt_32f_AC4R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Sub
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiSub_8u_C1IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_8u_C3IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_8u_C4IRSfs        ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_8u_AC4IRSfs       ( const Fw8u   *pSrc, int srcStep, Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_C1IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_C3IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_C4IRSfs       ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_AC4IRSfs      ( const Fw16s  *pSrc, int srcStep, Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16sc_C1IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16sc_C3IRSfs      ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16sc_AC4IRSfs     ( const Fw16sc *pSrc, int srcStep, Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32sc_C1IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32sc_C3IRSfs      ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32sc_AC4IRSfs     ( const Fw32sc *pSrc, int srcStep, Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32f_C1IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32f_C3IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32f_C4IR          ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32f_AC4IR         ( const Fw32f  *pSrc, int srcStep, Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32fc_C1IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32fc_C3IR         ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32fc_AC4IR        ( const Fw32fc *pSrc, int srcStep, Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiSub_8u_C1RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_8u_C3RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_8u_C4RSfs         ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_8u_AC4RSfs        ( const Fw8u   *pSrc1, int src1Step, const Fw8u   *pSrc2, int src2Step, Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_C1RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_C3RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_C4RSfs        ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16s_AC4RSfs       ( const Fw16s  *pSrc1, int src1Step, const Fw16s  *pSrc2, int src2Step, Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16sc_C1RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16sc_C3RSfs       ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_16sc_AC4RSfs      ( const Fw16sc *pSrc1, int src1Step, const Fw16sc *pSrc2, int src2Step, Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32sc_C1RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32sc_C3RSfs       ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32sc_AC4RSfs      ( const Fw32sc *pSrc1, int src1Step, const Fw32sc *pSrc2, int src2Step, Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSub_32f_C1R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32f_C3R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32f_C4R           ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32f_AC4R          ( const Fw32f  *pSrc1, int src1Step, const Fw32f  *pSrc2, int src2Step, Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32fc_C1R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32fc_C3R          ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSub_32fc_AC4R         ( const Fw32fc *pSrc1, int src1Step, const Fw32fc *pSrc2, int src2Step, Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        SubC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiSubC_8u_C1IRSfs       (       Fw8u   value   , Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_8u_C3IRSfs       ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_8u_AC4IRSfs      ( const Fw8u   value[3], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_8u_C4IRSfs       ( const Fw8u   value[4], Fw8u   *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_C1IRSfs      (       Fw16s  value   , Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_C3IRSfs      ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_AC4IRSfs     ( const Fw16s  value[3], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_C4IRSfs      ( const Fw16s  value[4], Fw16s  *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16sc_C1IRSfs     (       Fw16sc value   , Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16sc_C3IRSfs     ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16sc_AC4IRSfs    ( const Fw16sc value[3], Fw16sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32sc_C1IRSfs     (       Fw32sc value   , Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32sc_C3IRSfs     ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32sc_AC4IRSfs    ( const Fw32sc value[3], Fw32sc *pSrcDst, int srcDstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32f_C1IR         (       Fw32f  value   , Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32f_C3IR         ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32f_AC4IR        ( const Fw32f  value[3], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32f_C4IR         ( const Fw32f  value[4], Fw32f  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32fc_C1IR        (       Fw32fc value   , Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32fc_C3IR        ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32fc_AC4IR       ( const Fw32fc value[3], Fw32fc *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiSubC_8u_C1RSfs        ( const Fw8u   *pSrc, int srcStep,       Fw8u   value   , Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_8u_C3RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_8u_AC4RSfs       ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[3], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_8u_C4RSfs        ( const Fw8u   *pSrc, int srcStep, const Fw8u   value[4], Fw8u   *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_C1RSfs       ( const Fw16s  *pSrc, int srcStep,       Fw16s  value   , Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_C3RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_AC4RSfs      ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[3], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16s_C4RSfs       ( const Fw16s  *pSrc, int srcStep, const Fw16s  value[4], Fw16s  *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16sc_C1RSfs      ( const Fw16sc *pSrc, int srcStep,       Fw16sc value   , Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16sc_C3RSfs      ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_16sc_AC4RSfs     ( const Fw16sc *pSrc, int srcStep, const Fw16sc value[3], Fw16sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32sc_C1RSfs      ( const Fw32sc *pSrc, int srcStep,       Fw32sc value   , Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32sc_C3RSfs      ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32sc_AC4RSfs     ( const Fw32sc *pSrc, int srcStep, const Fw32sc value[3], Fw32sc *pDst, int dstStep, FwiSize roiSize, int scaleFactor );
FwStatus STDCALL fwiSubC_32f_C1R          ( const Fw32f  *pSrc, int srcStep,       Fw32f  value   , Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32f_C3R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32f_AC4R         ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[3], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32f_C4R          ( const Fw32f  *pSrc, int srcStep, const Fw32f  value[4], Fw32f  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32fc_C1R         ( const Fw32fc *pSrc, int srcStep,       Fw32fc value   , Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32fc_C3R         ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiSubC_32fc_AC4R        ( const Fw32fc *pSrc, int srcStep, const Fw32fc value[3], Fw32fc *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        And
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAnd_8u_C1IR           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_8u_C3IR           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_8u_C4IR           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_8u_AC4IR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_C1IR          ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_C3IR          ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_C4IR          ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_AC4IR         ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_C1IR          ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_C3IR          ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_C4IR          ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_AC4IR         ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAnd_8u_C1R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_8u_C3R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_8u_C4R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_8u_AC4R           ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_C1R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_C3R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_C4R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_16u_AC4R          ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_C1R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_C3R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_C4R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAnd_32s_AC4R          ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        AndC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAndC_8u_C1IR          (       Fw8u  value   , Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_8u_C3IR          ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_8u_AC4IR         ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_8u_C4IR          ( const Fw8u  value[4], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_C1IR         (       Fw16u value   , Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_C3IR         ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_AC4IR        ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_C4IR         ( const Fw16u value[4], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_C1IR         (       Fw32s value   , Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_C3IR         ( const Fw32s value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_AC4IR        ( const Fw32s value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_C4IR         ( const Fw32s value[4], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiAndC_8u_C1R           ( const Fw8u   *pSrc, int srcStep,       Fw8u  value   , Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_8u_C3R           ( const Fw8u   *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_8u_AC4R          ( const Fw8u   *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_8u_C4R           ( const Fw8u   *pSrc, int srcStep, const Fw8u  value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_C1R          ( const Fw16u  *pSrc, int srcStep,       Fw16u value   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_C3R          ( const Fw16u  *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_AC4R         ( const Fw16u  *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_16u_C4R          ( const Fw16u  *pSrc, int srcStep, const Fw16u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_C1R          ( const Fw32s  *pSrc, int srcStep,       Fw32s value   , Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_C3R          ( const Fw32s  *pSrc, int srcStep, const Fw32s value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_AC4R         ( const Fw32s  *pSrc, int srcStep, const Fw32s value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiAndC_32s_C4R          ( const Fw32s  *pSrc, int srcStep, const Fw32s value[4], Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Comp
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiComplement_32s_C1IR   ( Fw32s *pSrcDst, int srcDstStep,FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Not
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiNot_8u_C1IR           ( Fw8u *pSrcDst, int srcDstStep, FwiSize roiSize);
FwStatus STDCALL fwiNot_8u_C3IR           ( Fw8u *pSrcDst, int srcDstStep, FwiSize roiSize);
FwStatus STDCALL fwiNot_8u_AC4IR          ( Fw8u *pSrcDst, int srcDstStep, FwiSize roiSize);
FwStatus STDCALL fwiNot_8u_C4IR           ( Fw8u *pSrcDst, int srcDstStep, FwiSize roiSize);

FwStatus STDCALL fwiNot_8u_C1R            ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiNot_8u_C3R            ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiNot_8u_AC4R           ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiNot_8u_C4R            ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize);

////////////////////////////////////////////////////////////////
//                        Or
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiOr_8u_C1IR            ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_8u_C3IR            ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_8u_C4IR            ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_8u_AC4IR           ( const Fw8u  *pSrc,  int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_C1IR           ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_C3IR           ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_C4IR           ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_AC4IR          ( const Fw16u *pSrc,  int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_C1IR           ( const Fw32s *pSrc,  int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_C3IR           ( const Fw32s *pSrc,  int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_C4IR           ( const Fw32s *pSrc,  int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_AC4IR          ( const Fw32s *pSrc,  int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiOr_8u_C1R             ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_8u_C3R             ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_8u_C4R             ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_8u_AC4R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_C1R            ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_C3R            ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_C4R            ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_16u_AC4R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_C1R            ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_C3R            ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_C4R            ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOr_32s_AC4R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        OrC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiOrC_8u_C1IR           (       Fw8u  value   , Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_8u_C3IR           ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_8u_AC4IR          ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_8u_C4IR           ( const Fw8u  value[4], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_C1IR          (       Fw16u value   , Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_C3IR          ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_AC4IR         ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_C4IR          ( const Fw16u value[4], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_C1IR          (       Fw32s value   , Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_C3IR          ( const Fw32s value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_AC4IR         ( const Fw32s value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_C4IR          ( const Fw32s value[4], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiOrC_8u_C1R            ( const Fw8u   *pSrc, int srcStep,       Fw8u  value   , Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_8u_C3R            ( const Fw8u   *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_8u_AC4R           ( const Fw8u   *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_8u_C4R            ( const Fw8u   *pSrc, int srcStep, const Fw8u  value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_C1R           ( const Fw16u  *pSrc, int srcStep,       Fw16u value   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_C3R           ( const Fw16u  *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_AC4R          ( const Fw16u  *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_16u_C4R           ( const Fw16u  *pSrc, int srcStep, const Fw16u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_C1R           ( const Fw32s  *pSrc, int srcStep,       Fw32s value   , Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_C3R           ( const Fw32s  *pSrc, int srcStep, const Fw32s value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_AC4R          ( const Fw32s  *pSrc, int srcStep, const Fw32s value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiOrC_32s_C4R           ( const Fw32s  *pSrc, int srcStep, const Fw32s value[4], Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        LShiftC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiLShiftC_8u_C1IR       (       Fw32u value   , Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_8u_C3IR       ( const Fw32u value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_8u_AC4IR      ( const Fw32u value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_8u_C4IR       ( const Fw32u value[4], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_C1IR      (       Fw32u value   , Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_C3IR      ( const Fw32u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_AC4IR     ( const Fw32u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_C4IR      ( const Fw32u value[4], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_C1IR      (       Fw32u value   , Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_C3IR      ( const Fw32u value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_AC4IR     ( const Fw32u value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_C4IR      ( const Fw32u value[4], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiLShiftC_8u_C1R        ( const Fw8u  *pSrc, int srcStep,       Fw32u value   , Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_8u_C3R        ( const Fw8u  *pSrc, int srcStep, const Fw32u value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_8u_AC4R       ( const Fw8u  *pSrc, int srcStep, const Fw32u value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_8u_C4R        ( const Fw8u  *pSrc, int srcStep, const Fw32u value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_C1R       ( const Fw16u *pSrc, int srcStep,       Fw32u value   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_C3R       ( const Fw16u *pSrc, int srcStep, const Fw32u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_AC4R      ( const Fw16u *pSrc, int srcStep, const Fw32u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_16u_C4R       ( const Fw16u *pSrc, int srcStep, const Fw32u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_C1R       ( const Fw32s *pSrc, int srcStep,       Fw32u value   , Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_C3R       ( const Fw32s *pSrc, int srcStep, const Fw32u value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_AC4R      ( const Fw32s *pSrc, int srcStep, const Fw32u value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLShiftC_32s_C4R       ( const Fw32s *pSrc, int srcStep, const Fw32u value[4], Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RShiftC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRShiftC_8u_C1IR       (       Fw32u value   , Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8u_C3IR       ( const Fw32u value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8u_AC4IR      ( const Fw32u value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8u_C4IR       ( const Fw32u value[4], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_C1IR       (       Fw32u value   , Fw8s  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_C3IR       ( const Fw32u value[3], Fw8s  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_AC4IR      ( const Fw32u value[3], Fw8s  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_C4IR       ( const Fw32u value[4], Fw8s  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_C1IR      (       Fw32u value   , Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_C3IR      ( const Fw32u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_AC4IR     ( const Fw32u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_C4IR      ( const Fw32u value[4], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_C1IR      (       Fw32u value   , Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_C3IR      ( const Fw32u value[3], Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_AC4IR     ( const Fw32u value[3], Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_C4IR      ( const Fw32u value[4], Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_C1IR      (       Fw32u value   , Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_C3IR      ( const Fw32u value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_AC4IR     ( const Fw32u value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_C4IR      ( const Fw32u value[4], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiRShiftC_8u_C1R        ( const Fw8u   *pSrc, int srcStep,       Fw32u value   , Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8u_C3R        ( const Fw8u   *pSrc, int srcStep, const Fw32u value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8u_AC4R       ( const Fw8u   *pSrc, int srcStep, const Fw32u value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8u_C4R        ( const Fw8u   *pSrc, int srcStep, const Fw32u value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_C1R        ( const Fw8s   *pSrc, int srcStep,       Fw32u value   , Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_C3R        ( const Fw8s   *pSrc, int srcStep, const Fw32u value[3], Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_AC4R       ( const Fw8s   *pSrc, int srcStep, const Fw32u value[3], Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_8s_C4R        ( const Fw8s   *pSrc, int srcStep, const Fw32u value[4], Fw8s  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_C1R       ( const Fw16u  *pSrc, int srcStep,       Fw32u value   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_C3R       ( const Fw16u  *pSrc, int srcStep, const Fw32u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_AC4R      ( const Fw16u  *pSrc, int srcStep, const Fw32u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16u_C4R       ( const Fw16u  *pSrc, int srcStep, const Fw32u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_C1R       ( const Fw16s  *pSrc, int srcStep,       Fw32u value   , Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_C3R       ( const Fw16s  *pSrc, int srcStep, const Fw32u value[3], Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_AC4R      ( const Fw16s  *pSrc, int srcStep, const Fw32u value[3], Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_16s_C4R       ( const Fw16s  *pSrc, int srcStep, const Fw32u value[4], Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_C1R       ( const Fw32s  *pSrc, int srcStep,       Fw32u value   , Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_C3R       ( const Fw32s  *pSrc, int srcStep, const Fw32u value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_AC4R      ( const Fw32s  *pSrc, int srcStep, const Fw32u value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRShiftC_32s_C4R       ( const Fw32s  *pSrc, int srcStep, const Fw32u value[4], Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Xor
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiXor_8u_C1IR           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_8u_C3IR           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_8u_C4IR           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_8u_AC4IR          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_C1IR          ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_C3IR          ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_C4IR          ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_AC4IR         ( const Fw16u *pSrc, int srcStep, Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_C1IR          ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_C3IR          ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_C4IR          ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_AC4IR         ( const Fw32s *pSrc, int srcStep, Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiXor_8u_C1R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_8u_C3R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_8u_C4R            ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_8u_AC4R           ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_C1R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_C3R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_C4R           ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_16u_AC4R          ( const Fw16u *pSrc1, int src1Step, const Fw16u *pSrc2, int src2Step, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_C1R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_C3R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_C4R           ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXor_32s_AC4R          ( const Fw32s *pSrc1, int src1Step, const Fw32s *pSrc2, int src2Step, Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        XorC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiXorC_8u_C1IR          (       Fw8u  value   , Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_8u_C3IR          ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_8u_AC4IR         ( const Fw8u  value[3], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_8u_C4IR          ( const Fw8u  value[4], Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_C1IR         (       Fw16u value   , Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_C3IR         ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_AC4IR        ( const Fw16u value[3], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_C4IR         ( const Fw16u value[4], Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_C1IR         (       Fw32s value   , Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_C3IR         ( const Fw32s value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_AC4IR        ( const Fw32s value[3], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_C4IR         ( const Fw32s value[4], Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize );

FwStatus STDCALL fwiXorC_8u_C1R           ( const Fw8u  *pSrc, int srcStep,       Fw8u  value   , Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_8u_C3R           ( const Fw8u  *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_8u_AC4R          ( const Fw8u  *pSrc, int srcStep, const Fw8u  value[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_8u_C4R           ( const Fw8u  *pSrc, int srcStep, const Fw8u  value[4], Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_C1R          ( const Fw16u *pSrc, int srcStep,       Fw16u value   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_C3R          ( const Fw16u *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_AC4R         ( const Fw16u *pSrc, int srcStep, const Fw16u value[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_16u_C4R          ( const Fw16u *pSrc, int srcStep, const Fw16u value[4], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_C1R          ( const Fw32s *pSrc, int srcStep,       Fw32s value   , Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_C3R          ( const Fw32s *pSrc, int srcStep, const Fw32s value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_AC4R         ( const Fw32s *pSrc, int srcStep, const Fw32s value[3], Fw32s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXorC_32s_C4R          ( const Fw32s *pSrc, int srcStep, const Fw32s value[4], Fw32s *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToYUV
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYUV_8u_C3R       ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV_8u_AC4R      ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV_8u_P3R       ( const Fw8u * const pSrc[3], int srcStep, Fw8u *pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV_8u_C3P3R     ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst[3], int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YUVToRGB
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiYUVToRGB_8u_C3R       ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUVToRGB_8u_AC4R      ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUVToRGB_8u_P3R       ( const Fw8u * const pSrc[3], int srcStep, Fw8u *pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUVToRGB_8u_P3C3R     ( const Fw8u * const pSrc[3], int srcStep, Fw8u *pDst   , int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToYUV422
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYUV422_8u_C3C2R  ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst   , int dstStep   , FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV422_8u_P3R    ( const Fw8u * const pSrc[3], int srcStep, Fw8u *pDst[3], int dstStep[3], FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV422_8u_P3     ( const Fw8u * const pSrc[3],              Fw8u *pDst[3],                 FwiSize imgSize );
FwStatus STDCALL fwiRGBToYUV422_8u_C3P3R  ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst[3], int dstStep[3], FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV422_8u_C3P3   ( const Fw8u *       pSrc   ,              Fw8u *pDst[3],                 FwiSize imgSize );

////////////////////////////////////////////////////////////////
//                        YUV422ToRGB
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiYUV422ToRGB_8u_C2C3R  ( const Fw8u *       pSrc   , int srcStep,    Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV422ToRGB_8u_P3R    ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV422ToRGB_8u_P3     ( const Fw8u * const pSrc[3],                 Fw8u * const pDst[3],              FwiSize imgSize );
FwStatus STDCALL fwiYUV422ToRGB_8u_P3C3R  ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV422ToRGB_8u_P3AC4R ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV422ToRGB_8u_P3C3   ( const Fw8u * const pSrc[3],                 Fw8u *       pDst   ,              FwiSize imgSize );

////////////////////////////////////////////////////////////////
//                        RGBToYUV420
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYUV420_8u_P3R    ( const Fw8u * const pSrc[3], int srcStep, Fw8u * const pDst[3], int dstStep[3], FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV420_8u_P3     ( const Fw8u * const pSrc[3],              Fw8u * const pDst[3],                 FwiSize imgSize );
FwStatus STDCALL fwiRGBToYUV420_8u_C3P3R  ( const Fw8u *       pSrc   , int srcStep, Fw8u * const pDst[3], int dstStep[3], FwiSize roiSize );
FwStatus STDCALL fwiRGBToYUV420_8u_C3P3   ( const Fw8u *       pSrc   ,              Fw8u * const pDst[3],                 FwiSize imgSize );

////////////////////////////////////////////////////////////////
//                        YUV420ToRGB
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiYUV420ToRGB_8u_P3R    ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToRGB_8u_P3     ( const Fw8u * const pSrc[3],                 Fw8u * const pDst[3],              FwiSize imgSize );
FwStatus STDCALL fwiYUV420ToRGB_8u_P3C3R  ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToRGB_8u_P3AC4R ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToRGB_8u_P3C3   ( const Fw8u * const pSrc[3],                 Fw8u *       pDst   ,              FwiSize imgSize );

////////////////////////////////////////////////////////////////
//                        YUV420ToBGR
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYUV420ToBGR_8u_P3C3R  ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YUV420ToRGB*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYUV420ToRGB565_8u16u_P3C3R        ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToRGB555_8u16u_P3C3R        ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToRGB444_8u16u_P3C3R        ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YUV420ToBGR*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYUV420ToBGR565_8u16u_P3C3R        ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToBGR555_8u16u_P3C3R        ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYUV420ToBGR444_8u16u_P3C3R        ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToYCbCr
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYCbCr_8u_C3R                 ( const Fw8u *       pSrc   , int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCbCr_8u_AC4R                ( const Fw8u *       pSrc   , int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCbCr_8u_P3R                 ( const Fw8u * const pSrc[3], int srcStep, Fw8u * const pDst[3], int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCrToRGB
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiYCbCrToRGB_8u_C3R                 ( const Fw8u *       pSrc   , int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB_8u_AC4R                ( const Fw8u *       pSrc   , int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB_8u_P3R                 ( const Fw8u * const pSrc[3], int srcStep, Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB_8u_P3C3R               ( const Fw8u * const pSrc[3], int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCrToRGB*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCrToRGB565_8u16u_C3R           ( const Fw8u *       pSrc   , int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB555_8u16u_C3R           ( const Fw8u *       pSrc   , int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB444_8u16u_C3R           ( const Fw8u *       pSrc   , int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB565_8u16u_P3C3R         ( const Fw8u * const pSrc[3], int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB555_8u16u_P3C3R         ( const Fw8u * const pSrc[3], int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToRGB444_8u16u_P3C3R         ( const Fw8u * const pSrc[3], int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCrToBGR*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCrToBGR565_8u16u_C3R           ( const Fw8u *       pSrc   , int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToBGR555_8u16u_C3R           ( const Fw8u *       pSrc   , int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToBGR444_8u16u_C3R           ( const Fw8u *       pSrc   , int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToBGR565_8u16u_P3C3R         ( const Fw8u * const pSrc[3], int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToBGR555_8u16u_P3C3R         ( const Fw8u * const pSrc[3], int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCrToBGR444_8u16u_P3C3R         ( const Fw8u * const pSrc[3], int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToYCbCr422
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYCbCr422_8u_C3C2R            ( const Fw8u *       pSrc   , int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCbCr422_8u_P3C2R            ( const Fw8u * const pSrc[3], int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCr422ToRGB
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiYCbCr422ToRGB_8u_C2C3R            ( const Fw8u *       pSrc   , int srcStep   , Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB_8u_C2P3R            ( const Fw8u *       pSrc   , int srcStep   , Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB_8u_P3C3R            ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *       pDst   , int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToCbYCr422*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToCbYCr422_8u_C3C2R            ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToCbYCr422Gamma_8u_C3C2R       ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        CbYCr422ToRGB
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCbYCr422ToRGB_8u_C2C3R            ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        BGRToCbYCr422
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiBGRToCbYCr422_8u_AC4C2R           ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        CbYCr422ToBGR
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCbYCr422ToBGR_8u_C2C4R            ( const Fw8u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize, Fw8u alpha );

////////////////////////////////////////////////////////////////
//                        YCbCr422ToRGB*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr422ToRGB565_8u16u_C2C3R      ( const Fw8u *       pSrc   , int srcStep   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB555_8u16u_C2C3R      ( const Fw8u *       pSrc   , int srcStep   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB444_8u16u_C2C3R      ( const Fw8u *       pSrc   , int srcStep   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB565_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB555_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToRGB444_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCr422ToBGR*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr422ToBGR565_8u16u_C2C3R      ( const Fw8u *       pSrc   , int srcStep   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToBGR555_8u16u_C2C3R      ( const Fw8u *       pSrc   , int srcStep   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToBGR444_8u16u_C2C3R      ( const Fw8u *       pSrc   , int srcStep   , Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToBGR565_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToBGR555_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr422ToBGR444_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToYCbCr420
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYCbCr420_8u_C3P3R            ( const Fw8u *pSrc, int srcStep, Fw8u * const pDst[3], int dstStep[3], FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        BGRToYCbCr420
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiBGRToYCbCr420_8u_C3P3R            ( const Fw8u *pSrc, int srcStep, Fw8u * const pDst[3], int dstStep[3], FwiSize roiSize);
FwStatus STDCALL fwiBGRToYCbCr420_8u_AC4P3R           ( const Fw8u *pSrc, int srcStep, Fw8u * const pDst[3], int dstStep[3], FwiSize roiSize);

////////////////////////////////////////////////////////////////
//                        YCbCr420ToRGB
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr420ToRGB_8u_P3C3R            ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u  *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCr422ToYCbCr420
////////////////////////////////////////////////////////////////


FwStatus STDCALL  fwiYCbCr422ToYCbCr420_8u_P3R ( const Fw8u* pSrc[3], int srcStep[3], Fw8u* pDst[3], int dstStep[3], FwiSize roiSize);
FwStatus STDCALL  fwiYCbCr422ToYCbCr420_8u_C2P3R(const Fw8u* pSrc, int srcStep, Fw8u* pDst[3], int dstStep[3], FwiSize roiSize);

////////////////////////////////////////////////////////////////
//                        YCbCr420ToRGB*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr420ToRGB565_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr420ToRGB555_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr420ToRGB444_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCr420ToBGR
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr420ToBGR_8u_P3C3R            ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCr420ToBGR*
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr420ToBGR565_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr420ToBGR555_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr420ToBGR444_8u16u_P3C3R      ( const Fw8u * const pSrc[3], int srcStep[3], Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCbCr411ToBGR
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr411ToBGR_8u_P3C3R            ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCbCr411ToBGR_8u_P3C4R            ( const Fw8u * const pSrc[3], int srcStep[3], Fw8u *pDst, int dstStep, FwiSize roiSize, Fw8u alpha );

////////////////////////////////////////////////////////////////
//                        RGBToXYZ
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToXYZ_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToXYZ_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        XYZToRGB
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiXYZToRGB_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiXYZToRGB_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToLUV
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToLUV_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToLUV_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        LUVToRGB
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiLUVToRGB_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLUVToRGB_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        BGRToLab
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiBGRToLab_8u_C3R       ( const Fw8u *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToLab_8u16u_C3R    ( const Fw8u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        LabToBGR
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiLabToBGR_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiLabToBGR_16u8u_C3R    ( const Fw16u *pSrc, int srcStep, Fw8u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToYCC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToYCC_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToYCC_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        YCCToRGB
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiYCCToRGB_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiYCCToRGB_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToHLS
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToHLS_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHLS_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        HLSToRGB
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiHLSToRGB_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToRGB_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        BGRToHLS
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiBGRToHLS_8u_AC4R      ( const Fw8u *       pSrc   , int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToHLS_8u_C3P3R     ( const Fw8u *       pSrc   , int srcStep, Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToHLS_8u_AC4P4R    ( const Fw8u *       pSrc   , int srcStep, Fw8u * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToHLS_8u_AP4R      ( const Fw8u * const pSrc[4], int srcStep, Fw8u * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToHLS_8u_P3R       ( const Fw8u * const pSrc[3], int srcStep, Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToHLS_8u_AP4C4R    ( const Fw8u * const pSrc[4], int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiBGRToHLS_8u_P3C3R     ( const Fw8u * const pSrc[3], int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        HLSToBGR
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiHLSToBGR_8u_C3P3R     ( const Fw8u *       pSrc   , int srcStep, Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToBGR_8u_AC4P4R    ( const Fw8u *       pSrc   , int srcStep, Fw8u * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToBGR_8u_AP4R      ( const Fw8u * const pSrc[4], int srcStep, Fw8u * const pDst[4], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToBGR_8u_P3R       ( const Fw8u * const pSrc[3], int srcStep, Fw8u * const pDst[3], int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToBGR_8u_AP4C4R    ( const Fw8u * const pSrc[4], int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHLSToBGR_8u_P3C3R     ( const Fw8u * const pSrc[3], int srcStep, Fw8u *       pDst   , int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        RGBToHSV
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToHSV_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHSV_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHSV_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiRGBToHSV_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        HSVToRGB
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiHSVToRGB_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHSVToRGB_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHSVToRGB_16u_C3R      ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );
FwStatus STDCALL fwiHSVToRGB_16u_AC4R     ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        ColorToGray
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiColorToGray_8u_C3C1R(const Fw8u* pSrc, int srcStep, Fw8u* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_16u_C3C1R(const Fw16u* pSrc, int srcStep, Fw16u* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_16s_C3C1R(const Fw16s* pSrc, int srcStep, Fw16s* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_32f_C3C1R(const Fw32f* pSrc, int srcStep, Fw32f* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_8u_AC4C1R(const Fw8u* pSrc, int srcStep, Fw8u* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_16u_AC4C1R(const Fw16u* pSrc, int srcStep, Fw16u* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_16s_AC4C1R(const Fw16s* pSrc, int srcStep, Fw16s* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);
FwStatus STDCALL fwiColorToGray_32f_AC4C1R(const Fw32f* pSrc, int srcStep, Fw32f* pDst, int dstStep, FwiSize roiSize, const Fw32f coeffs[3]);

////////////////////////////////////////////////////////////////
//                        RGBToGray
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRGBToGray_8u_C3C1R(const Fw8u* pSrc, int srcStep,Fw8u* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_16u_C3C1R(const Fw16u* pSrc, int srcStep,Fw16u* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_16s_C3C1R(const Fw16s* pSrc, int srcStep,Fw16s* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_32f_C3C1R(const Fw32f* pSrc, int srcStep,Fw32f* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_8u_AC4C1R(const Fw8u* pSrc, int srcStep,Fw8u* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_16u_AC4C1R(const Fw16u* pSrc, int srcStep,Fw16u* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_16s_AC4C1R(const Fw16s* pSrc, int srcStep,Fw16s* pDst, int dstStep, FwiSize roiSize);
FwStatus STDCALL fwiRGBToGray_32f_AC4C1R(const Fw32f* pSrc, int srcStep,Fw32f* pDst, int dstStep, FwiSize roiSize);

////////////////////////////////////////////////////////////////
//                        YCbCr422
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiYCbCr422_8u_C2P3R     (const Fw8u *       pSrc   , int srcStep   , Fw8u *pDst[3], int dstStep[3], FwiSize roiSize);
FwStatus STDCALL fwiYCbCr422_8u_P3C2R     (const Fw8u * const pSrc[3], int srcStep[3], Fw8u *pDst   , int dstStep   , FwiSize roiSize);

////////////////////////////////////////////////////////////////
//                        CbYCr422ToYCbCr
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCbYCr422ToYCbCr420_8u_C2P3R       ( const Fw8u *pSrc, int srcStep, Fw8u *pDst[3], int dstStep[3], FwiSize roiSize );

////////////////////////////////////////////////////////////////
//                        Sum
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiSum_8u_C1R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f* pSum);
FwStatus STDCALL fwiSum_16s_C1R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f* pSum);
FwStatus STDCALL fwiSum_8u_C3R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[3]);
FwStatus STDCALL fwiSum_16s_C3R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[3]);
FwStatus STDCALL fwiSum_8u_AC4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[3]);
FwStatus STDCALL fwiSum_16s_AC4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[3]);
FwStatus STDCALL fwiSum_8u_C4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[4]);
FwStatus STDCALL fwiSum_16s_C4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[4]);
FwStatus STDCALL fwiSum_32f_C3R (const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[3], FwHintAlgorithm hint);
FwStatus STDCALL fwiSum_32f_AC4R (const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw64f sum[3], FwHintAlgorithm hint);
FwStatus STDCALL fwiSum_32f_C4R (const Fw32f* pSrc, int srcStep, FwiSize roiSize, Fw64f sum[4], FwHintAlgorithm hint);

////////////////////////////////////////////////////////////////
//                        Min
////////////////////////////////////////////////////////////////



FwStatus STDCALL fwiMin_8u_C1R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u* pMin);
FwStatus STDCALL fwiMin_16s_C1R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s* pMin);
FwStatus STDCALL fwiMin_32f_C1R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f* pMin);

FwStatus STDCALL fwiMin_8u_AC4R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u min[3]);
FwStatus STDCALL fwiMin_16s_AC4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s min[3]);
FwStatus STDCALL fwiMin_32f_AC4R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f min[3]);

FwStatus STDCALL fwiMin_8u_C4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u min[4]);
FwStatus STDCALL fwiMin_16s_C4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s min[4]);
FwStatus STDCALL fwiMin_32f_C4R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f min[4]);

FwStatus STDCALL fwiMin_8u_C3R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u min[3]);
FwStatus STDCALL fwiMin_16s_C3R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s min[3]);
FwStatus STDCALL fwiMin_32f_C3R (const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f min[3]);

////////////////////////////////////////////////////////////////
//                        Max
////////////////////////////////////////////////////////////////



FwStatus STDCALL fwiMax_8u_C1R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u* pMax);
FwStatus STDCALL fwiMax_16s_C1R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s* pMax);
FwStatus STDCALL fwiMax_32f_C1R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f* pMax);

FwStatus STDCALL fwiMax_8u_AC4R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u max[3]);
FwStatus STDCALL fwiMax_16s_AC4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s max[3]);
FwStatus STDCALL fwiMax_32f_AC4R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f max[3]);

FwStatus STDCALL fwiMax_8u_C4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u max[4]);
FwStatus STDCALL fwiMax_16s_C4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s max[4]);
FwStatus STDCALL fwiMax_32f_C4R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f max[4]);

FwStatus STDCALL fwiMax_8u_C3R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u max[3]);
FwStatus STDCALL fwiMax_16s_C3R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s max[3]);
FwStatus STDCALL fwiMax_32f_C3R (const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f max[3]);

////////////////////////////////////////////////////////////////
//                        Min
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiMinMax_8u_C1R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u* pMin,Fw8u* pMax);
FwStatus STDCALL fwiMinMax_16s_C1R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s* pMin, Fw16s* pMax);
FwStatus STDCALL fwiMinMax_32f_C1R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f* pMin, Fw32f* pMax);
FwStatus STDCALL fwiMinMax_8u_AC4R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u min[3], Fw8u max[3]);
FwStatus STDCALL fwiMinMax_16s_AC4R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s min[3], Fw16s max[3]);
FwStatus STDCALL fwiMinMax_32f_AC4R (const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f min[3], Fw32f max[3]);
FwStatus STDCALL fwiMinMax_8u_C4R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u min[4], Fw8u max[4]);
FwStatus STDCALL fwiMinMax_16s_C4R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s min[4], Fw16s max[4]);
FwStatus STDCALL fwiMinMax_32f_C4R (const Fw32f* pSrc, int srcStep,FwiSize roiSize,Fw32f min[4],Fw32f max[4]);
FwStatus STDCALL fwiMinMax_8u_C3R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw8u min[3], Fw8u max[3]);
FwStatus STDCALL fwiMinMax_16s_C3R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw16s min[3], Fw16s max[3]);
FwStatus STDCALL fwiMinMax_32f_C3R (const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw32f min[3], Fw32f max[3]);

////////////////////////////////////////////////////////////////
//                        Mean
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiMean_8u_C1R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f* pMean);
FwStatus STDCALL fwiMean_16s_C1R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f* pMean);
FwStatus STDCALL fwiMean_32f_C1R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, Fw64f* pMean, FwHintAlgorithm hint);
FwStatus STDCALL fwiMean_8u_C3R (const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f mean[3]);
FwStatus STDCALL fwiMean_16s_C3R (const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f mean[3]);
FwStatus STDCALL fwiMean_8u_AC4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f mean[3]);
FwStatus STDCALL fwiMean_16s_AC4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f mean[3]);
FwStatus STDCALL fwiMean_8u_C4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, Fw64f mean[4]);
FwStatus STDCALL fwiMean_16s_C4R(const Fw16s* pSrc, int srcStep,FwiSize roiSize, Fw64f mean[4]);

////////////////////////////////////////////////////////////////
//                        Count
////////////////////////////////////////////////////////////////


FwStatus  STDCALL fwiCountInRange_8u_C1R(const Fw8u* pSrc, int srcStep, FwiSize roiSize, int* counts, Fw8u lowerBound,Fw8u upperBound);
FwStatus  STDCALL fwiCountInRange_32f_C1R(const Fw32f* pSrc, int srcStep, FwiSize roiSize, int* counts, Fw32f lowerBound,Fw32f upperBound);
FwStatus  STDCALL fwiCountInRange_8u_C3R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, int counts[3], Fw8u lowerBound[3],Fw8u upperBound[3]);
FwStatus  STDCALL fwiCountInRange_32f_C3R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, int counts[3], Fw32f lowerBound[3],Fw32f upperBound[3]);
FwStatus  STDCALL fwiCountInRange_8u_AC4R(const Fw8u* pSrc, int srcStep,FwiSize roiSize, int counts[3], Fw8u lowerBound[3],Fw8u upperBound[3]);
FwStatus  STDCALL fwiCountInRange_32f_AC4R(const Fw32f* pSrc, int srcStep,FwiSize roiSize, int counts[3], Fw32f lowerBound[3],Fw32f upperBound[3]);

////////////////////////////////////////////////////////////////
//                        Threshold
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiThreshold_8u_C1IR                 ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  threshold   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_8u_C3IR                 ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_8u_AC4IR                ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_16s_C1IR                ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s threshold   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_16s_C3IR                ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_16s_AC4IR               ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_32f_C1IR                ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f threshold   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_32f_C3IR                ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_32f_AC4IR               ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], FwCmpOp fwCmpOp);

FwStatus STDCALL fwiThreshold_8u_C1R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  threshold   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_8u_C3R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_8u_AC4R                 ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_16s_C1R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s threshold   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_16s_C3R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_16s_AC4R                ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_32f_C1R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f threshold   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_32f_C3R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_32f_AC4R                ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], FwCmpOp fwCmpOp);

////////////////////////////////////////////////////////////////
//                        Threshold_GT
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiThreshold_GT_8u_C1IR              ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  threshold   );
FwStatus STDCALL fwiThreshold_GT_8u_C3IR              ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_GT_8u_AC4IR             ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_GT_16s_C1IR             ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s threshold   );
FwStatus STDCALL fwiThreshold_GT_16s_C3IR             ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_GT_16s_AC4IR            ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_GT_32f_C1IR             ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f threshold   );
FwStatus STDCALL fwiThreshold_GT_32f_C3IR             ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3]);
FwStatus STDCALL fwiThreshold_GT_32f_AC4IR            ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3]);

FwStatus STDCALL fwiThreshold_GT_8u_C1R               ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  threshold   );
FwStatus STDCALL fwiThreshold_GT_8u_C3R               ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_GT_8u_AC4R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_GT_16s_C1R              ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s threshold   );
FwStatus STDCALL fwiThreshold_GT_16s_C3R              ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_GT_16s_AC4R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_GT_32f_C1R              ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f threshold   );
FwStatus STDCALL fwiThreshold_GT_32f_C3R              ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3]);
FwStatus STDCALL fwiThreshold_GT_32f_AC4R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3]);

////////////////////////////////////////////////////////////////
//                        Threshold_LT
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiThreshold_LT_8u_C1IR              ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  threshold   );
FwStatus STDCALL fwiThreshold_LT_8u_C3IR              ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_LT_8u_AC4IR             ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_LT_16s_C1IR             ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s threshold   );
FwStatus STDCALL fwiThreshold_LT_16s_C3IR             ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_LT_16s_AC4IR            ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_LT_32f_C1IR             ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f threshold   );
FwStatus STDCALL fwiThreshold_LT_32f_C3IR             ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3]);
FwStatus STDCALL fwiThreshold_LT_32f_AC4IR            ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3]);

FwStatus STDCALL fwiThreshold_LT_8u_C1R               ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  threshold   );
FwStatus STDCALL fwiThreshold_LT_8u_C3R               ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_LT_8u_AC4R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3]);
FwStatus STDCALL fwiThreshold_LT_16s_C1R              ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s threshold   );
FwStatus STDCALL fwiThreshold_LT_16s_C3R              ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_LT_16s_AC4R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3]);
FwStatus STDCALL fwiThreshold_LT_32f_C1R              ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f threshold   );
FwStatus STDCALL fwiThreshold_LT_32f_C3R              ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3]);
FwStatus STDCALL fwiThreshold_LT_32f_AC4R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3]);

////////////////////////////////////////////////////////////////
//                        Threshold_Val
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiThreshold_Val_8u_C1IR             ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  threshold   ,       Fw8u  value,    FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_8u_C3IR             ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_8u_AC4IR            ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_16s_C1IR            ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s threshold   ,       Fw16s value,    FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_16s_C3IR            ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_16s_AC4IR           ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_32f_C1IR            ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f threshold   ,       Fw32f value,    FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_32f_C3IR            ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_32f_AC4IR           ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3], FwCmpOp fwCmpOp);

FwStatus STDCALL fwiThreshold_Val_8u_C1R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  threshold,          Fw8u  value   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_8u_C3R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_8u_AC4R             ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_16s_C1R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s threshold,          Fw16s value   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_16s_C3R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_16s_AC4R            ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_32f_C1R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f threshold,          Fw32f value   , FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_32f_C3R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3], FwCmpOp fwCmpOp);
FwStatus STDCALL fwiThreshold_Val_32f_AC4R            ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3], FwCmpOp fwCmpOp);

////////////////////////////////////////////////////////////////
//                        Threshold_GTVal
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiThreshold_GTVal_8u_C1IR           ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  threshold   ,       Fw8u  value   );
FwStatus STDCALL fwiThreshold_GTVal_8u_C3IR           ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_GTVal_8u_AC4IR          ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_GTVal_8u_C4IR           ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[4], const Fw8u  value[4]);
FwStatus STDCALL fwiThreshold_GTVal_16s_C1IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s threshold   ,       Fw16s value   );
FwStatus STDCALL fwiThreshold_GTVal_16s_C3IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_GTVal_16s_AC4IR         ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_GTVal_16s_C4IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[4], const Fw16s value[4]);
FwStatus STDCALL fwiThreshold_GTVal_32f_C1IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f threshold   ,       Fw32f value   );
FwStatus STDCALL fwiThreshold_GTVal_32f_C3IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_GTVal_32f_AC4IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_GTVal_32f_C4IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[4], const Fw32f value[4]);

FwStatus STDCALL fwiThreshold_GTVal_8u_C1R            ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  threshold   ,       Fw8u  value   );
FwStatus STDCALL fwiThreshold_GTVal_8u_C3R            ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_GTVal_8u_AC4R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_GTVal_8u_C4R            ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[4], const Fw8u  value[4]);
FwStatus STDCALL fwiThreshold_GTVal_16s_C1R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s threshold   ,       Fw16s value   );
FwStatus STDCALL fwiThreshold_GTVal_16s_C3R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_GTVal_16s_AC4R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_GTVal_16s_C4R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[4], const Fw16s value[4]);
FwStatus STDCALL fwiThreshold_GTVal_32f_C1R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f threshold   ,       Fw32f value   );
FwStatus STDCALL fwiThreshold_GTVal_32f_C3R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_GTVal_32f_AC4R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_GTVal_32f_C4R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[4], const Fw32f value[4]);

////////////////////////////////////////////////////////////////
//                        Threshold_LTVal
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiThreshold_LTVal_8u_C1IR           ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  threshold   ,       Fw8u  value   );
FwStatus STDCALL fwiThreshold_LTVal_8u_C3IR           ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_LTVal_8u_AC4IR          ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_LTVal_8u_C4IR           ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  threshold[4], const Fw8u  value[4]);
FwStatus STDCALL fwiThreshold_LTVal_16s_C1IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s threshold   ,       Fw16s value   );
FwStatus STDCALL fwiThreshold_LTVal_16s_C3IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_LTVal_16s_AC4IR         ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_LTVal_16s_C4IR          ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s threshold[4], const Fw16s value[4]);
FwStatus STDCALL fwiThreshold_LTVal_32f_C1IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f threshold   ,       Fw32f value   );
FwStatus STDCALL fwiThreshold_LTVal_32f_C3IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_LTVal_32f_AC4IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_LTVal_32f_C4IR          ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f threshold[4], const Fw32f value[4]);

FwStatus STDCALL fwiThreshold_LTVal_8u_C1R            ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  threshold,          Fw8u  value   );
FwStatus STDCALL fwiThreshold_LTVal_8u_C3R            ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_LTVal_8u_AC4R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[3], const Fw8u  value[3]);
FwStatus STDCALL fwiThreshold_LTVal_8u_C4R            ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  threshold[4], const Fw8u  value[4]);
FwStatus STDCALL fwiThreshold_LTVal_16s_C1R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s threshold,          Fw16s value   );
FwStatus STDCALL fwiThreshold_LTVal_16s_C3R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_LTVal_16s_AC4R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[3], const Fw16s value[3]);
FwStatus STDCALL fwiThreshold_LTVal_16s_C4R           ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s threshold[4], const Fw16s value[4]);
FwStatus STDCALL fwiThreshold_LTVal_32f_C1R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f threshold,          Fw32f value   );
FwStatus STDCALL fwiThreshold_LTVal_32f_C3R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_LTVal_32f_AC4R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[3], const Fw32f value[3]);
FwStatus STDCALL fwiThreshold_LTVal_32f_C4R           ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f threshold[4], const Fw32f value[4]);

////////////////////////////////////////////////////////////////
//                        Threshold_LTValGTVal
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiThreshold_LTValGTVal_8u_C1IR      ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw8u  thresholdLT   ,       Fw8u  valueLT,          Fw8u  thresholdGT   ,       Fw8u  valueGT   );
FwStatus STDCALL fwiThreshold_LTValGTVal_8u_C3IR      ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  thresholdLT[3], const Fw8u  valueLT[3], const Fw8u  thresholdGT[3], const Fw8u  valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_8u_AC4IR     ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw8u  thresholdLT[3], const Fw8u  valueLT[3], const Fw8u  thresholdGT[3], const Fw8u  valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_16s_C1IR     ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw16s thresholdLT   ,       Fw16s valueLT,          Fw16s thresholdGT   ,       Fw16s valueGT   );
FwStatus STDCALL fwiThreshold_LTValGTVal_16s_C3IR     ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s thresholdLT[3], const Fw16s valueLT[3], const Fw16s thresholdGT[3], const Fw16s valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_16s_AC4IR    ( Fw16s *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16s thresholdLT[3], const Fw16s valueLT[3], const Fw16s thresholdGT[3], const Fw16s valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_32f_C1IR     ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize,       Fw32f thresholdLT   ,       Fw32f valueLT,          Fw32f thresholdGT   ,       Fw32f valueGT   );
FwStatus STDCALL fwiThreshold_LTValGTVal_32f_C3IR     ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f thresholdLT[3], const Fw32f valueLT[3], const Fw32f thresholdGT[3], const Fw32f valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_32f_AC4IR    ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw32f thresholdLT[3], const Fw32f valueLT[3], const Fw32f thresholdGT[3], const Fw32f valueGT[3]);

FwStatus STDCALL fwiThreshold_LTValGTVal_8u_C1R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize,       Fw8u  thresholdLT   ,       Fw8u  valueLT   ,       Fw8u  thresholdGT   ,       Fw8u  valueGT   );
FwStatus STDCALL fwiThreshold_LTValGTVal_8u_C3R       ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  thresholdLT[3], const Fw8u  valueLT[3], const Fw8u  thresholdGT[3], const Fw8u  valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_8u_AC4R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, const Fw8u  thresholdLT[3], const Fw8u  valueLT[3], const Fw8u  thresholdGT[3], const Fw8u  valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_16s_C1R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize,       Fw16s thresholdLT   ,       Fw16s valueLT   ,       Fw16s thresholdGT   ,       Fw16s valueGT   );
FwStatus STDCALL fwiThreshold_LTValGTVal_16s_C3R      ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s thresholdLT[3], const Fw16s valueLT[3], const Fw16s thresholdGT[3], const Fw16s valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_16s_AC4R     ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize roiSize, const Fw16s thresholdLT[3], const Fw16s valueLT[3], const Fw16s thresholdGT[3], const Fw16s valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_32f_C1R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize,       Fw32f thresholdLT   ,       Fw32f valueLT   ,       Fw32f thresholdGT   ,       Fw32f valueGT   );
FwStatus STDCALL fwiThreshold_LTValGTVal_32f_C3R      ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f thresholdLT[3], const Fw32f valueLT[3], const Fw32f thresholdGT[3], const Fw32f valueGT[3]);
FwStatus STDCALL fwiThreshold_LTValGTVal_32f_AC4R     ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, const Fw32f thresholdLT[3], const Fw32f valueLT[3], const Fw32f thresholdGT[3], const Fw32f valueGT[3]);

////////////////////////////////////////////////////////////////
//                        Compare
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCompare_8u_C1R                    ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_8u_C3R                    ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_8u_C4R                    ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_8u_AC4R                   ( const Fw8u  *pSrc1, int src1Step, const Fw8u  *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_16s_C1R                   ( const Fw16s *pSrc1, int src1Step, const Fw16s *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_16s_C3R                   ( const Fw16s *pSrc1, int src1Step, const Fw16s *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_16s_C4R                   ( const Fw16s *pSrc1, int src1Step, const Fw16s *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_16s_AC4R                  ( const Fw16s *pSrc1, int src1Step, const Fw16s *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_32f_C1R                   ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_32f_C3R                   ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_32f_C4R                   ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompare_32f_AC4R                  ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );

////////////////////////////////////////////////////////////////
//                        CompareC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCompareC_8u_C1R                   ( const Fw8u  *pSrc, int srcStep,       Fw8u value    , Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_8u_C3R                   ( const Fw8u  *pSrc, int srcStep, const Fw8u value[3] , Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_8u_AC4R                  ( const Fw8u  *pSrc, int srcStep, const Fw8u value[3] , Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_8u_C4R                   ( const Fw8u  *pSrc, int srcStep, const Fw8u value[4] , Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_16s_C1R                  ( const Fw16s *pSrc, int srcStep,       Fw16s value   , Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_16s_C3R                  ( const Fw16s *pSrc, int srcStep, const Fw16s value[3], Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_16s_AC4R                 ( const Fw16s *pSrc, int srcStep, const Fw16s value[3], Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_16s_C4R                  ( const Fw16s *pSrc, int srcStep, const Fw16s value[4], Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_32f_C1R                  ( const Fw32f *pSrc, int srcStep,       Fw32f value   , Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_32f_C3R                  ( const Fw32f *pSrc, int srcStep, const Fw32f value[3], Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_32f_AC4R                 ( const Fw32f *pSrc, int srcStep, const Fw32f value[3], Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );
FwStatus STDCALL fwiCompareC_32f_C4R                  ( const Fw32f *pSrc, int srcStep, const Fw32f value[4], Fw8u *pDst, int dstStep, FwiSize roiSize, FwCmpOp fwCmpOp );

////////////////////////////////////////////////////////////////
//                        CompareEqualEps
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCompareEqualEps_32f_C1R           ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);
FwStatus STDCALL fwiCompareEqualEps_32f_C3R           ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);
FwStatus STDCALL fwiCompareEqualEps_32f_C4R           ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);
FwStatus STDCALL fwiCompareEqualEps_32f_AC4R          ( const Fw32f *pSrc1, int src1Step, const Fw32f *pSrc2, int src2Step, Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);

////////////////////////////////////////////////////////////////
//                        CompareEqualEpsC
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiCompareEqualEpsC_32f_C1R          ( const Fw32f *pSrc, int srcStep,       Fw32f value   , Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);
FwStatus STDCALL fwiCompareEqualEpsC_32f_C3R          ( const Fw32f *pSrc, int srcStep, const Fw32f value[3], Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);
FwStatus STDCALL fwiCompareEqualEpsC_32f_AC4R         ( const Fw32f *pSrc, int srcStep, const Fw32f value[3], Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);
FwStatus STDCALL fwiCompareEqualEpsC_32f_C4R          ( const Fw32f *pSrc, int srcStep, const Fw32f value[4], Fw8u *pDst, int dstStep, FwiSize roiSize, Fw32f eps);

////////////////////////////////////////////////////////////////
//                        Dilate3X3
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiDilate3x3_8u_C1R      ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize );
#ifndef __SUNPRO_CC


////////////////////////////////////////////////////////////////
//                        Sharpen
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterSharpen_8u_C1R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_8u_C3R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_8u_C4R              ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_8u_AC4R             ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_16s_C1R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_16s_C3R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_16s_C4R             ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_16s_AC4R            ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_32f_C1R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_32f_C3R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_32f_C4R             ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSharpen_32f_AC4R            ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FilterBox
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterBox_8u_C1R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_8u_C3R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_8u_C4R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_8u_AC4R                 ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_C1R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_C3R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_C4R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_AC4R                ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_C1R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_C3R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_C4R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_AC4R                ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        FilterBoxInplace
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterBox_8u_C1IR                 ( Fw8u  *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_8u_C3IR                 ( Fw8u  *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_8u_C4IR                 ( Fw8u  *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_8u_AC4IR                ( Fw8u  *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_C1IR                ( Fw16s *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_C3IR                ( Fw16s *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_C4IR                ( Fw16s *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_16s_AC4IR               ( Fw16s *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_C1IR                ( Fw32f *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_C3IR                ( Fw32f *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_C4IR                ( Fw32f *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterBox_32f_AC4IR               ( Fw32f *pSrcDst, int srcDstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        FilterMin
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMin_8u_C1R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_8u_C3R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_8u_C4R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_8u_AC4R                 ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_16s_C1R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_16s_C3R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_16s_C4R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_16s_AC4R                ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_32f_C1R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_32f_C3R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_32f_C4R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMin_32f_AC4R                ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        FilterMax
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMax_8u_C1R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_8u_C3R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_8u_C4R                  ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_8u_AC4R                 ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_16s_C1R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_16s_C3R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_16s_C4R                 ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_16s_AC4R                ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_32f_C1R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_32f_C3R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_32f_C4R                 ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );
FwStatus STDCALL fwiFilterMax_32f_AC4R                ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiSize maskSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        SumWindowRow
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiSumWindowRow_8u32f_C1R            ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowRow_8u32f_C3R            ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowRow_8u32f_C4R            ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowRow_16s32f_C1R           ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowRow_16s32f_C3R           ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowRow_16s32f_C4R           ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );

////////////////////////////////////////////////////////////////
//                        SumWindow
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiSumWindowColumn_8u32f_C1R         ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowColumn_8u32f_C3R         ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowColumn_8u32f_C4R         ( const Fw8u  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowColumn_16s32f_C1R        ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowColumn_16s32f_C3R        ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );
FwStatus STDCALL fwiSumWindowColumn_16s32f_C4R        ( const Fw16s *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, int maskSize, int anchor );

////////////////////////////////////////////////////////////////
//                        FilterMedian
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMedian_8u_C1R               ( const Fw8u *pSrc, int srcStep,
                                                                Fw8u *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_8u_C3R               ( const Fw8u *pSrc, int srcStep,
                                                                Fw8u *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_8u_C4R               ( const Fw8u *pSrc, int srcStep,
                                                                Fw8u *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_8u_AC4R              ( const Fw8u *pSrc, int srcStep,
                                                                Fw8u *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_16s_C1R              ( const Fw16s *pSrc, int srcStep,
                                                                Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_16s_C3R              ( const Fw16s *pSrc, int srcStep,
                                                                Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_16s_C4R              ( const Fw16s *pSrc, int srcStep,
                                                                Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

FwStatus STDCALL fwiFilterMedian_16s_AC4R             ( const Fw16s *pSrc, int srcStep,
                                                                Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                                FwiSize maskSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        FilterMedianHoriz
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMedianHoriz_8u_C1R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_8u_C3R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_8u_C4R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_8u_AC4R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_16s_C1R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_16s_C3R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_16s_C4R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianHoriz_16s_AC4R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        FilterMedianVert
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMedianVert_8u_C1R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_8u_C3R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_8u_C4R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_8u_AC4R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_16s_C1R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_16s_C3R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_16s_C4R          ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianVert_16s_AC4R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        FilterMedianCross
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMedianCross_8u_C1R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianCross_8u_C3R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianCross_8u_AC4R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianCross_16s_C1R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianCross_16s_C3R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianCross_16s_AC4R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        FilterMedianColor
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterMedianColor_8u_C3R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianColor_8u_AC4R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianColor_16s_C3R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianColor_16s_AC4R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianColor_32f_C3R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterMedianColor_32f_AC4R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        Filter
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilter_8u_C1R             ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_8u_C3R             ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_8u_C4R             ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s  *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_8u_AC4R            ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_16s_C1R            ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_16s_C3R            ( const Fw16s *pSrc,  int srcStep,
                                                        Fw16s *pDst,  int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize,FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_16s_C4R            ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_16s_AC4R           ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, FwiSize kernelSize, FwiPoint anchor, int divisor );

FwStatus STDCALL fwiFilter_32f_C1R            ( const Fw32f *pSrc, int srcStep,
                                                        Fw32f *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter_32f_C3R            ( const Fw32f *pSrc, int srcStep,
                                                        Fw32f  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter_32f_C4R            ( const Fw32f *pSrc, int srcStep,
                                                        Fw32f *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter_32f_AC4R           ( const Fw32f *pSrc, int srcStep,
                                                        Fw32f *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        Filter32f
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilter32f_8u_C1R          ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f  *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_8u_C3R          ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_8u_C4R          ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_8u_AC4R         ( const Fw8u  *pSrc, int srcStep,
                                                        Fw8u  *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_16s_C1R         ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_16s_C3R         ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_16s_C4R         ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

FwStatus STDCALL fwiFilter32f_16s_AC4R        ( const Fw16s *pSrc, int srcStep,
                                                        Fw16s *pDst, int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, FwiSize kernelSize, FwiPoint anchor );

////////////////////////////////////////////////////////////////
//                        FilterColumn
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterColumn_8u_C1R       ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_8u_C3R       ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_8u_C4R       ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_8u_AC4R      ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_16s_C1R      ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_16s_C3R      ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_16s_C4R      ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_16s_AC4R     ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int yAnchor, int divisor );

FwStatus STDCALL fwiFilterColumn_32f_C1R      ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn_32f_C3R      ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn_32f_C4R      ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn_32f_AC4R     ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

////////////////////////////////////////////////////////////////
//                        FilterColumn32f
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterColumn32f_8u_C1R    ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_8u_C3R    ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_8u_C4R    ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_8u_AC4R   ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_16s_C1R   ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_16s_C3R   ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_16s_C4R   ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

FwStatus STDCALL fwiFilterColumn32f_16s_AC4R  ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int yAnchor );

////////////////////////////////////////////////////////////////
//                        FilterRow
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterRow_8u_C1R          ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_8u_C3R          ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_8u_C4R          ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_8u_AC4R         ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_16s_C1R         ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_16s_C3R         ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_16s_C4R         ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_16s_AC4R        ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32s *pKernel, int kernelSize, int xAnchor, int divisor );

FwStatus STDCALL fwiFilterRow_32f_C1R         ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow_32f_C3R         ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow_32f_C4R         ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow_32f_AC4R        ( const Fw32f *pSrc,    int srcStep,
                                                        Fw32f *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

////////////////////////////////////////////////////////////////
//                        FilterRow32f
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterRow32f_8u_C1R       ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_8u_C3R       ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_8u_C4R       ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_8u_AC4R      ( const Fw8u  *pSrc,    int srcStep,
                                                        Fw8u  *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_16s_C1R      ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_16s_C3R      ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_16s_C4R      ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

FwStatus STDCALL fwiFilterRow32f_16s_AC4R     ( const Fw16s *pSrc,    int srcStep,
                                                        Fw16s *pDst,    int dstStep, FwiSize dstRoiSize,
                                                  const Fw32f *pKernel, int kernelSize, int xAnchor );

////////////////////////////////////////////////////////////////
//                        FilterPrewittHoriz
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterPrewittHoriz_8u_C1R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_8u_C3R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_8u_C4R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_8u_AC4R        ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_16s_C1R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_16s_C3R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_16s_C4R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_16s_AC4R       ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_32f_C1R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_32f_C3R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_32f_C4R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittHoriz_32f_AC4R       ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FiltePrewittVert
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterPrewittVert_8u_C1R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_8u_C3R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_8u_C4R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_8u_AC4R         ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_16s_C1R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_16s_C3R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_16s_C4R         ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_16s_AC4R        ( const Fw16s *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_32f_C1R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_32f_C3R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_32f_C4R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterPrewittVert_32f_AC4R        ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FilterScharrHoriz
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterScharrHoriz_8u16s_C1R       ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterScharrHoriz_8s16s_C1R       ( const Fw8s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterScharrHoriz_32f_C1R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FilterScharrVert
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterScharrVert_8u16s_C1R        ( const Fw8u  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterScharrVert_8s16s_C1R        ( const Fw8s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterScharrVert_32f_C1R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FilterSobelHoriz
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterSobelHoriz_8u_C1R           ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_8u_C3R           ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_8u_C4R           ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_8u_AC4R          ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_16s_C1R          ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_16s_C3R          ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_16s_C4R          ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_16s_AC4R         ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_32f_C1R          ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_32f_C3R          ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_32f_C4R          ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_32f_AC4R         ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelHoriz_8u16s_C1R        ( const Fw8u   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelHoriz_8s16s_C1R        ( const Fw8s   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelHorizMask_32f_C1R      ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );

////////////////////////////////////////////////////////////////
//                        FilterSobelVert
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterSobelVert_8u_C1R            ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_8u_C3R            ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_8u_C4R            ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_8u_AC4R           ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_16s_C1R           ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_16s_C3R           ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_16s_C4R           ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_16s_AC4R          ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_32f_C1R           ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_32f_C3R           ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_32f_C4R           ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_32f_AC4R          ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterSobelVert_8u16s_C1R         ( const Fw8u   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelVert_8s16s_C1R         ( const Fw8s   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelVertMask_32f_C1R       ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );

////////////////////////////////////////////////////////////////
//                        FilterSobelHorizSecond
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterSobelHorizSecond_32f_C1R    ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelHorizSecond_8s16s_C1R  ( const Fw8s   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelHorizSecond_8u16s_C1R  ( const Fw8u   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );

////////////////////////////////////////////////////////////////
//                        FilterSobelVertSecond
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterSobelVertSecond_32f_C1R     ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelVertSecond_8s16s_C1R   ( const Fw8s   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelVertSecond_8u16s_C1R   ( const Fw8u   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );

////////////////////////////////////////////////////////////////
//                        FilterSobelCross
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterSobelCross_8u16s_C1R        ( const Fw8u   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelCross_8s16s_C1R        ( const Fw8s   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );
FwStatus STDCALL fwiFilterSobelCross_32f_C1R          ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize mask );

////////////////////////////////////////////////////////////////
//                        FilterRobertsDown
////////////////////////////////////////////////////////////////



FwStatus STDCALL fwiFilterRobertsDown_8u_C1R          ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_8u_C3R          ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_8u_AC4R         ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_16s_C1R         ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_16s_C3R         ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_16s_AC4R        ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_32f_C1R         ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_32f_C3R         ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsDown_32f_AC4R        ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FilterRobertsUp
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiFilterRobertsUp_8u_C1R            ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_8u_C3R            ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_8u_AC4R           ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_16s_C1R           ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_16s_C3R           ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_16s_AC4R          ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_32f_C1R           ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_32f_C3R           ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );
FwStatus STDCALL fwiFilterRobertsUp_32f_AC4R          ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize );

////////////////////////////////////////////////////////////////
//                        FilterLaplace
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterLaplace_8u_C1R              ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_8u_C3R              ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_8u_C4R              ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_8u_AC4R             ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_16s_C1R             ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_16s_C3R             ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_16s_C4R             ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_16s_AC4R            ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_32f_C1R             ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_32f_C3R             ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_32f_C4R             ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_32f_AC4R            ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_8u16s_C1R           ( const Fw8u   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLaplace_8s16s_C1R           ( const Fw8s   *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        FilterGauss
////////////////////////////////////////////////////////////////



FwStatus STDCALL fwiFilterGauss_8u_C1R                ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_8u_C3R                ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_8u_C4R                ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_8u_AC4R               ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_16s_C1R               ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_16s_C3R               ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_16s_C4R               ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_16s_AC4R              ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_32f_C1R               ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_32f_C3R               ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_32f_C4R               ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterGauss_32f_AC4R              ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        FilterHipass
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterHipass_8u_C1R               ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_8u_C3R               ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_8u_C4R               ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_8u_AC4R              ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_16s_C1R              ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_16s_C3R              ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_16s_C4R              ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_16s_AC4R             ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_32f_C1R              ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_32f_C3R              ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_32f_C4R              ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterHipass_32f_AC4R             ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );

////////////////////////////////////////////////////////////////
//                        FilterLowpass
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiFilterLowpass_8u_C1R              ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_8u_C3R              ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_8u_AC4R             ( const Fw8u   *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_16s_C1R             ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_16s_C3R             ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_16s_AC4R            ( const Fw16s  *pSrc, int srcStep, Fw16s *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_32f_C1R             ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_32f_C3R             ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
FwStatus STDCALL fwiFilterLowpass_32f_AC4R            ( const Fw32f  *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize dstRoiSize, FwiMaskSize maskSize );
#endif // __SUNPRO_CC


////////////////////////////////////////////////////////////////
//                        DCT8X8
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiDCT8x8Fwd_16s_C1      (const Fw16s *pSrc, Fw16s *pDst   );
FwStatus STDCALL fwiDCT8x8Fwd_16s_C1I     (      Fw16s*               pSrcDst);
FwStatus STDCALL fwiDCT8x8Inv_16s_C1      (const Fw16s *pSrc, Fw16s *pDst   );
FwStatus STDCALL fwiDCT8x8Inv_16s_C1I     (      Fw16s*               pSrcDst);

////////////////////////////////////////////////////////////////
//                        Resize
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiResize_8u_C1R         ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_8u_C3R         ( const  Fw8u *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                  int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_8u_C4R         ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_8u_AC4R        ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_16u_C1R        ( const  Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_16u_C3R        ( const  Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_16u_C4R        ( const  Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_16u_AC4R       ( const  Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_32f_C1R        ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_32f_C3R        ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_32f_C4R        ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_32f_AC4R       ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_8u_P3R         ( const  Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u * const pDst[3],                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_16u_P3R        ( const  Fw16u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u * const pDst[3],                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_32f_P3R        ( const  Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f* const pDst[3],                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_8u_P4R         ( const  Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u * const pDst[4], int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_16u_P4R        ( const  Fw16u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u * const pDst[4],                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

FwStatus STDCALL fwiResize_32f_P4R        ( const  Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f* const pDst[4],                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

////////////////////////////////////////////////////////////////
//                        ResizeCenter
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiResizeCenter_8u_C1R   ( const  Fw8u    *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u    *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_8u_C3R   ( const  Fw8u    *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u    *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_8u_C4R   ( const  Fw8u    *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u    *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_8u_AC4R  ( const  Fw8u    *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u    *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_16u_C1R  ( const  Fw16u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_16u_C3R  ( const  Fw16u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_16u_C4R  ( const  Fw16u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_16u_AC4R ( const  Fw16u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_32f_C1R  ( const  Fw32f   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_32f_C3R  ( const  Fw32f   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_32f_C4R  ( const  Fw32f   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_32f_AC4R ( const  Fw32f   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f   *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_8u_P3R   ( const  Fw8u *   const pSrc[3] , FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *   const pDst[3] ,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_16u_P3R  ( const  Fw16u *  const pSrc[3] , FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *  const pDst[3] ,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_32f_P3R  ( const  Fw32f * const pSrc[3] , FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f * const pDst[3] ,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_8u_P4R   ( const  Fw8u *  const pSrc[4] , FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *  const pDst[4] ,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_16u_P4R  ( const  Fw16u * const pSrc[4] , FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u * const pDst[4] ,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiResizeCenter_32f_P4R  ( const  Fw32f * const pSrc[4] , FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f * const pDst[4] ,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, double xCenter, double yCenter, int interpolation );

////////////////////////////////////////////////////////////////
//                        GetResizeFract
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetResizeFract        (FwiSize srcSize, FwiRect srcRoi, double xFactor, double yFactor,
                                             double* xFr, double* yFr, int interpolation );

////////////////////////////////////////////////////////////////
//                        ResizeShift
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiResizeShift_8u_C1R    ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_8u_C3R    ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *  pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_8u_C4R    ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_8u_AC4R   ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_16u_C1R   ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_16u_C3R   ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_16u_C4R   ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_16u_AC4R  ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_32f_C1R   ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_32f_C3R   ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_32f_C4R   ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_32f_AC4R  ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_8u_P3R    ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[3],                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_16u_P3R   ( const Fw16u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u * const pDst[3],                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_32f_P3R   ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[3],                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_8u_P4R    ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[4],                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_16u_P4R   ( const Fw16u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u * const pDst[4],                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiResizeShift_32f_P4R   ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[4],                   int dstStep, FwiSize dstRoiSize,
                                              double xFr, double yFr, double xShift, double yShift, int interpolation );

////////////////////////////////////////////////////////////////
//                        ResizeSqrPixelGetBufSize
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiResizeSqrPixelGetBufSize  (FwiSize dstSize, int nChannel,int interpolation, int *pBufferSize);

////////////////////////////////////////////////////////////////
//                        ResizeSqrPixel
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiResizeSqrPixel_8u_C1R             ( const  Fw8u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw8u   *pDst,                   int dstStep, FwiRect dstRoi, 
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_8u_C3R             ( const  Fw8u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw8u   *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_8u_C4R             ( const  Fw8u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw8u   *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_8u_AC4R            ( const  Fw8u   *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw8u   *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_16u_C1R            ( const  Fw16u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw16u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_16u_C3R            ( const  Fw16u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw16u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_16u_C4R            ( const  Fw16u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw16u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_16u_AC4R           ( const  Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_32f_C1R            ( const  Fw32f  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw32f  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_32f_C3R            ( const  Fw32f  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw32f  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_32f_C4R            ( const  Fw32f  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw32f  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_32f_AC4R           ( const  Fw32f  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw32f  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_8u_P3R             ( const  Fw8u  * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw8u  * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_8u_P4R             ( const  Fw8u  * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw8u  * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor,  double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_16u_P3R            ( const  Fw16u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw16u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_16u_P4R            ( const  Fw16u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw16u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_32f_P3R            ( const  Fw32f * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw32f * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

FwStatus STDCALL fwiResizeSqrPixel_32f_P4R            ( const  Fw32f * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                 Fw32f * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          double xFactor, double yFactor, double xShift, double yShift, int interpolation, Fw8u *pBuffer);

////////////////////////////////////////////////////////////////
//                        ResizeYUV422
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiResizeYUV422_8u_C2R   ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiSize dstRoiSize,
                                              double xFactor, double yFactor, int interpolation );

////////////////////////////////////////////////////////////////
//                        Mirror
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiMirror_8u_C1R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_8u_C3R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_8u_C4R           ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_8u_AC4R          ( const Fw8u  *pSrc, int srcStep, Fw8u  *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_C1R          ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_C3R          ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_C4R          ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_AC4R         ( const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_C1R          ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_C3R          ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_C4R          ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_AC4R         ( const Fw32s *pSrc, int srcStep, Fw32s *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_C1R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_C3R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_C4R          ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_AC4R         ( const Fw32f *pSrc, int srcStep, Fw32f *pDst, int dstStep, FwiSize roiSize, FwiAxis flip);

FwStatus STDCALL fwiMirror_8u_C1IR          ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_8u_C3IR          ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_8u_C4IR          ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_8u_AC4IR         ( Fw8u  *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_C1IR         ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_C3IR         ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_C4IR         ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_16u_AC4IR        ( Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_C1IR         ( Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_C3IR         ( Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_C4IR         ( Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32s_AC4IR        ( Fw32s *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_C1IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_C3IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_C4IR         ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);
FwStatus STDCALL fwiMirror_32f_AC4IR        ( Fw32f *pSrcDst, int srcDstStep, FwiSize roiSize, FwiAxis flip);

////////////////////////////////////////////////////////////////
//                        Remap
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRemap_8u_C1R          ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw8u  *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_8u_C3R          ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw8u  *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_8u_C4R          ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw8u  *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_8u_AC4R         ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw8u  *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_32f_C1R         ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw32f *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_32f_C3R         ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw32f *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_32f_C4R         ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw32f *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_32f_AC4R        ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw32f *pDst,  int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_8u_P3R          ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw8u * const pDst[3], int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_8u_P4R          ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw8u * const pDst[4], int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_32f_P3R         ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw32f* const pDst[3], int dstStep, FwiSize dstRoiSize, int interpolation );

FwStatus STDCALL fwiRemap_32f_P4R         ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                              const Fw32f *pxMap, int xMapStep, const Fw32f *pyMap, int yMapStep,
                                                    Fw32f* const pDst[4], int dstStep, FwiSize dstRoiSize, int interpolation );

////////////////////////////////////////////////////////////////
//                        Rotate
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRotate_8u_C1R         ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_8u_C3R         ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_8u_C4R         ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_8u_AC4R        ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_16u_C1R        ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_16u_C3R        ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_16u_C4R        ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_16u_AC4R       ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_32f_C1R        ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_32f_C3R        ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_32f_C4R        ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_32f_AC4R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_8u_P3R         ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_8u_P4R         ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_16u_P3R        ( const Fw16u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_16u_P4R        ( const Fw16u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_32f_P3R        ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiRotate_32f_P4R        ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              double angle, double xShift, double yShift, int interpolation );

////////////////////////////////////////////////////////////////
//                        GetRotateShift
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetRotateShift        (double xCenter, double yCenter,
                                             double angle, double* xShift, double* yShift);

////////////////////////////////////////////////////////////////
//                        AddRotateShift
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiAddRotateShift        (double xCenter, double yCenter,
                                             double angle, double* xShift, double* yShift);

////////////////////////////////////////////////////////////////
//                        GetRotateQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetRotateQuad         (FwiRect srcRoi, double quad[4][2],
                                             double angle, double xShift, double yShift);

////////////////////////////////////////////////////////////////
//                        GetRotateBound
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetRotateBound        (FwiRect srcRoi, double bound[2][2],
                                             double angle, double xShift, double yShift);

////////////////////////////////////////////////////////////////
//                        RotateCenter
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiRotateCenter_8u_C1R   ( const  Fw8u  *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u  *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_8u_C3R   ( const  Fw8u  *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u  *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_8u_C4R   ( const  Fw8u  *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u  *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_8u_AC4R  ( const  Fw8u  *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u  *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_16u_C1R  ( const  Fw16u *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_16u_C3R  ( const  Fw16u *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_16u_C4R  ( const  Fw16u *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_16u_AC4R ( const  Fw16u *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_32f_C1R  ( const  Fw32f *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_32f_C3R  ( const  Fw32f *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_32f_C4R  ( const  Fw32f *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle, double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_32f_AC4R ( const  Fw32f *pSrc,FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_8u_P3R   ( const  Fw8u * const pSrc[3],FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u * const pDst[3],                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_8u_P4R   ( const  Fw8u * const pSrc[4],FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u * const pDst[4],                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_16u_P3R  ( const  Fw16u * const pSrc[3],FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u * const pDst[3],                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_16u_P4R  ( const  Fw16u * const pSrc[4],FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw16u * const pDst[4],                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_32f_P3R  ( const  Fw32f* const pSrc[3],FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f* const pDst[3],                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

FwStatus STDCALL fwiRotateCenter_32f_P4R  ( const  Fw32f* const pSrc[4],FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f* const pDst[4],                  int dstStep, FwiRect dstRoi,
                                              double angle,  double xCenter, double yCenter, int interpolation );

////////////////////////////////////////////////////////////////
//                        Shear
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiShear_8u_C1R          ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiRect dstRoi, 
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_8u_C3R          ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_8u_C4R          ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_8u_AC4R         ( const  Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_32f_C1R         ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_32f_C3R         ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_32f_C4R         ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_32f_AC4R        ( const  Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation );

FwStatus STDCALL fwiShear_8u_P3R          ( const  Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation);

FwStatus STDCALL fwiShear_8u_P4R          ( const  Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation);

FwStatus STDCALL fwiShear_32f_P3R         ( const  Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation);

FwStatus STDCALL fwiShear_32f_P4R         ( const  Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                     Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              double xShear, double yShear, double xShift, double yShift, int interpolation);

////////////////////////////////////////////////////////////////
//                        GetShearQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetShearQuad          (FwiRect srcRoi, double quad[4][2],
                                             double xShear, double yShear, double xShift, double yShift);

////////////////////////////////////////////////////////////////
//                        GetShearBound
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetShearBound         (FwiRect srcRoi, double bound[2][2],
                                             double xShear, double yShear, double xShift, double yShift);

////////////////////////////////////////////////////////////////
//                        WarpAffine
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpAffine_8u_C1R     ( const Fw8u *pSrc, FwiSize srcSize, int srcStep,FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_8u_C3R     ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_8u_C4R     ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_8u_AC4R    ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_16u_C1R    ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_16u_C3R    ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_16u_C4R    ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_16u_AC4R   ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_32f_C1R    ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_32f_C3R    ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_32f_C4R    ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_32f_AC4R   ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_8u_P3R     ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_8u_P4R     ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_16u_P3R    ( const Fw16u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_16u_P4R    ( const Fw16u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw16u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_32f_P3R    ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffine_32f_P4R    ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][3], int interpolation );

////////////////////////////////////////////////////////////////
//                        WarpAffineBack
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpAffineBack_8u_C1R             ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_8u_C3R             ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_8u_C4R             ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_8u_AC4R            ( const Fw8u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_16u_C1R            ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_16u_C3R            ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_16u_C4R            ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_16u_AC4R           ( const Fw16u *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw16u *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_32f_C1R            ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_32f_C3R            ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_32f_C4R            ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_32f_AC4R           ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_8u_P3R             ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_8u_P4R             ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_16u_P3R            ( const Fw16u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw16u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_16u_P4R            ( const Fw16u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw16u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_32f_P3R            ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

FwStatus STDCALL fwiWarpAffineBack_32f_P4R            ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][3], int interpolation );

////////////////////////////////////////////////////////////////
//                        WarpAffineQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpAffineQuad_8u_C1R             ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_8u_C3R             ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_8u_C4R             ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_8u_AC4R            ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_32f_C1R            ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_32f_C3R            ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_32f_C4R            ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_32f_AC4R           ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_8u_P3R             ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_8u_P4R             ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_32f_P3R            ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2], 
                                                          int interpolation );

FwStatus STDCALL fwiWarpAffineQuad_32f_P4R            ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

////////////////////////////////////////////////////////////////
//                        GetAffineQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetAffineQuad         (FwiRect srcRoi, double quad[4][2], const double coeffs[2][3]);

////////////////////////////////////////////////////////////////
//                        GetAffineBound
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetAffineBound        (FwiRect srcRoi, double bound[2][2], const double coeffs[2][3]);

////////////////////////////////////////////////////////////////
//                        GetAffineTransform
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetAffineTransform    (FwiRect srcRoi, const double quad[4][2],double coeffs[2][3]);

////////////////////////////////////////////////////////////////
//                        WarpPerspective
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpPerspective_8u_C1R            ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_8u_C3R            ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_8u_C4R            ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_8u_AC4R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_32f_C1R           ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_32f_C3R           ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_32f_C4R           ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_32f_AC4R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_8u_P3R            ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_8u_P4R            ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_32f_P3R           ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspective_32f_P4R           ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

////////////////////////////////////////////////////////////////
//                        WarpPerspectiveBack
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpPerspectiveBack_8u_C1R        ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_8u_C3R        ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_8u_C4R        ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_8u_AC4R       ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_32f_C1R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep,FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_32f_C3R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_32f_C4R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_32f_AC4R      ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_8u_P3R        ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_8u_P4R        ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_32f_P3R       ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

FwStatus STDCALL fwiWarpPerspectiveBack_32f_P4R       ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[3][3], int interpolation );

////////////////////////////////////////////////////////////////
//                        WarpPerspectiveQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpPerspectiveQuad_8u_C1R        ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2], 
                                                          int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_8u_C3R        ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_8u_C4R        ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_8u_AC4R       ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_32f_C1R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_32f_C3R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_32f_C4R       ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_32f_AC4R      ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_8u_P3R        ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_8u_P4R        ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation );

FwStatus STDCALL fwiWarpPerspectiveQuad_32f_P3R       ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );


FwStatus STDCALL fwiWarpPerspectiveQuad_32f_P4R       ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                         int interpolation );

////////////////////////////////////////////////////////////////
//                        GetPerspectiveQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetPerspectiveQuad                (FwiRect srcRoi, double quad[4][2], const double coeffs[3][3]);

////////////////////////////////////////////////////////////////
//                        GetPerspectiveBound
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetPerspectiveBound               (FwiRect srcRoi, double bound[2][2], const double coeffs[3][3]);

////////////////////////////////////////////////////////////////
//                        GetPerspectiveTransform
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetPerspectiveTransform           (FwiRect srcRoi, const double quad[4][2],double coeffs[3][3]);

////////////////////////////////////////////////////////////////
//                        WarpBilinear
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpBilinear_8u_C1R   ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_8u_C3R   ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep,FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_8u_C4R   ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_8u_AC4R  ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_32f_C1R  ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_32f_C3R  ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_32f_C4R  ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_32f_AC4R ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_8u_P3R   ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_8u_P4R   ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_32f_P3R  ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinear_32f_P4R  ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                    Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                              const double coeffs[2][4], int interpolation);

////////////////////////////////////////////////////////////////
//                        WarpBilinearBack
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpBilinearBack_8u_C1R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_8u_C3R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_8u_C4R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_8u_AC4R          ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_32f_C1R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_32f_C3R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_32f_C4R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_32f_AC4R         ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_8u_P3R           ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_8u_P4R           ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_32f_P3R          ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

FwStatus STDCALL fwiWarpBilinearBack_32f_P4R          ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi,
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi,
                                                          const double coeffs[2][4], int interpolation);

////////////////////////////////////////////////////////////////
//                        WarpBilinearQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiWarpBilinearQuad_8u_C1R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_8u_C3R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_8u_C4R           ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_8u_AC4R          ( const Fw8u  *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi,  const double srcQuad[4][2],
                                                                Fw8u  *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_32f_C1R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_32f_C3R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_32f_C4R          ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2], 
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_32f_AC4R         ( const Fw32f *pSrc, FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f *pDst,                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_8u_P3R           ( const Fw8u * const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u * const pDst[3],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2], 
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_8u_P4R           ( const Fw8u * const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw8u * const pDst[4],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_32f_P3R          ( const Fw32f* const pSrc[3], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f* const pDst[3],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

FwStatus STDCALL fwiWarpBilinearQuad_32f_P4R          ( const Fw32f* const pSrc[4], FwiSize srcSize, int srcStep, FwiRect srcRoi, const double srcQuad[4][2],
                                                                Fw32f* const pDst[4],                   int dstStep, FwiRect dstRoi, const double dstQuad[4][2],
                                                          int interpolation);

////////////////////////////////////////////////////////////////
//                        GetBilinearQuad
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetBilinearQuad       ( FwiRect srcRoi, double quad[4][2], const double coeffs[2][4]);

////////////////////////////////////////////////////////////////
//                        GetBilinearBound
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetBilinearBound      ( FwiRect srcRoi, double bound[2][2], const double coeffs[2][4]);

////////////////////////////////////////////////////////////////
//                        GetBilinearTransform
////////////////////////////////////////////////////////////////

FwStatus STDCALL fwiGetBilinearTransform  ( FwiRect srcRoi, const double quad[4][2],double coeffs[2][4]);

////////////////////////////////////////////////////////////////
//                        LookUp3DSpecInitAlloc
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiLookUp3DSpecInitAlloc(const Fw16u cubeDimensions, const Fw16u cubeMax, FwiLUTSpec** ppLUTSpec);

////////////////////////////////////////////////////////////////
//                        LookUp3DSpecInitAlloc
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiLookUp3D_16u_C3R(const Fw16u *pSrc, int srcStep, Fw16u *pDst, int dstStep, FwiSize roiSize, const Fw16u *pCube, FwiLUTSpec* pLUTSpec);
FwStatus STDCALL fwiLookUp3D_16u_C3IR(Fw16u *pSrcDst, int srcDstStep, FwiSize roiSize, const Fw16u *pCube, FwiLUTSpec* pLUTSpec);

////////////////////////////////////////////////////////////////
//                        LookUp3DSpecFree
////////////////////////////////////////////////////////////////


FwStatus STDCALL fwiLookUp3DSpecFree(FwiLUTSpec* pLUTSpec);

#ifdef __cplusplus
}
#endif


#endif // __FWIMAGE_H__
