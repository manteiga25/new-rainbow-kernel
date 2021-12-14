/**************************************************************************/ /*!
@File
@Title          Common MMU Management
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@Description    Implements basic low level control of MMU.
@License        Dual MIT/GPLv2

The contents of this file are subject to the MIT license as set out below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Alternatively, the contents of this file may be used under the terms of
the GNU General Public License Version 2 ("GPL") in which case the provisions
of GPL are applicable instead of those above.

If you wish to allow use of your version of this file only under the terms of
GPL, and not to allow others to use your version of this file under the terms
of the MIT license, indicate your decision by deleting the provisions above
and replace them with the notice and other provisions required by GPL as set
out in the file called "GPL-COPYING" included in this distribution. If you do
not delete the provisions above, a recipient may use your version of this file
under the terms of either the MIT license or GPL.

This License is also included in this distribution in the file called
"MIT-COPYING".

EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ /***************************************************************************/

#ifndef SRVKM_PDUMP_MMU_H
#define SRVKM_PDUMP_MMU_H

/* kernel/server/include/ */
#include "pdump_symbolicaddr.h"
/* include/ */
#include "img_types.h"
#include "pvrsrv_error.h"

#include "mmu_common.h"

/*
 * PDUMP MMU attributes
 */
typedef struct _PDUMP_MMU_ATTRIB_DEVICE_
{
	/* Per-Device Pdump attribs */

	/*!< Pdump memory bank name */
	IMG_CHAR *pszPDumpMemDevName;

	/*!< Pdump register bank name */
	IMG_CHAR *pszPDumpRegDevName;

} PDUMP_MMU_ATTRIB_DEVICE;

typedef struct _PDUMP_MMU_ATTRIB_CONTEXT_
{
	IMG_UINT32 ui32Dummy;
} PDUMP_MMU_ATTRIB_CONTEXT;

typedef struct _PDUMP_MMU_ATTRIB_HEAP_
{
	/* data page info */
	IMG_UINT32 ui32DataPageMask;
} PDUMP_MMU_ATTRIB_HEAP;

typedef struct _PDUMP_MMU_ATTRIB_
{
	/* FIXME: would these be better as pointers rather than copies? */
	struct _PDUMP_MMU_ATTRIB_DEVICE_ sDevice;
	struct _PDUMP_MMU_ATTRIB_CONTEXT_ sContext;
	struct _PDUMP_MMU_ATTRIB_HEAP_ sHeap;
} PDUMP_MMU_ATTRIB;

#if defined(PDUMP)
extern PVRSRV_ERROR
PDumpMMUMalloc(const IMG_CHAR *pszPDumpDevName,
#if defined(PVR_SUPPORT_HMMU_VALIDATION)
               IMG_BOOL bIsHMMUAlloc,
               IMG_UINT32 ui32OSid,
#endif
               MMU_LEVEL eMMULevel,
               IMG_DEV_PHYADDR *psDevPAddr,
               IMG_UINT32 ui32Size,
               IMG_UINT32 ui32Align,
               PDUMP_MMU_TYPE eMMUType);

extern PVRSRV_ERROR
PDumpMMUFree(const IMG_CHAR *pszPDumpDevName,
#if defined(PVR_SUPPORT_HMMU_VALIDATION)
             IMG_BOOL bIsHMMUAlloc,
             IMG_UINT32 ui32OSid,
#endif
             MMU_LEVEL eMMULevel,
             IMG_DEV_PHYADDR *psDevPAddr,
             PDUMP_MMU_TYPE eMMUType);

extern PVRSRV_ERROR
PDumpPTBaseObjectToMem64(const IMG_CHAR *pszPDumpDevName,
                         PMR *psPMRDest,
                         IMG_DEVMEM_OFFSET_T uiLogicalOffsetSource,
                         IMG_DEVMEM_OFFSET_T uiLogicalOffsetDest,
                         IMG_UINT32 ui32Flags,
                         MMU_LEVEL eMMULevel,
                         IMG_UINT64 ui64PxSymAddr,
                         IMG_UINT64 ui64PxOffset);

extern PVRSRV_ERROR
PDumpMMUDumpPxEntries(MMU_LEVEL eMMULevel,
                      const IMG_CHAR *pszPDumpDevName,
#if defined(PVR_SUPPORT_HMMU_VALIDATION)
                      IMG_BOOL bIsHMMUEnabled,
                      IMG_BOOL bIsHMMUAlloc,
                      IMG_UINT32 ui32OSid,
                      IMG_CHAR *pszSymbolicName,
                      IMG_UINT32 uiSubAllocOffset,
#endif
                      void *pvPxMem,
                      IMG_DEV_PHYADDR sPxDevPAddr,
                      IMG_UINT32 uiFirstEntry,
                      IMG_UINT32 uiNumEntries,
                      const IMG_CHAR *pszMemspaceName,
                      const IMG_CHAR *pszSymbolicAddr,
                      IMG_UINT64 uiSymbolicAddrOffset,
                      IMG_UINT32 uiBytesPerEntry,
                      IMG_UINT32 uiLog2Align,
                      IMG_UINT32 uiAddrShift,
                      IMG_UINT64 uiAddrMask,
                      IMG_UINT64 uiPxEProtMask,
                      IMG_UINT64 uiDataValidEnable,
                      IMG_UINT32 ui32Flags,
                      PDUMP_MMU_TYPE eMMUType);


#if defined(PVR_SUPPORT_HMMU_VALIDATION)
extern PVRSRV_ERROR
PDumpMMUAllocMMUContext(const IMG_CHAR *pszPDumpMemSpaceName,
                        IMG_DEV_PHYADDR sPCDevPAddr,
                        PDUMP_MMU_TYPE eMMUType,
                        IMG_UINT32 *pui32MMUContextID,
                        IMG_UINT32 ui32PDumpFlags,
                        IMG_DEV_PHYADDR sPCDevIpaAddr,
                        IMG_BOOL bIsHMMUEnabled,
                        IMG_UINT32 ui32OSid,
                        IMG_UINT64 ui64HPCBase,
                        IMG_UINT32 ui32Log2PageSize);

extern PVRSRV_ERROR
PDumpMMUFreeMMUContext(const IMG_CHAR *pszPDumpMemSpaceName,
                       IMG_UINT32 ui32MMUContextID,
                       IMG_UINT32 ui32PDumpFlags,
                       IMG_BOOL bIsHMMUEnabled);

#else
extern PVRSRV_ERROR
PDumpMMUAllocMMUContext(const IMG_CHAR *pszPDumpMemSpaceName,
                        IMG_DEV_PHYADDR sPCDevPAddr,
                        PDUMP_MMU_TYPE eMMUType,
                        IMG_UINT32 *pui32MMUContextID,
                        IMG_UINT32 ui32PDumpFlags);

extern PVRSRV_ERROR
PDumpMMUFreeMMUContext(const IMG_CHAR *pszPDumpMemSpaceName,
                       IMG_UINT32 ui32MMUContextID,
                       IMG_UINT32 ui32PDumpFlags);

#endif /* PVR_SUPPORT_HMMU_VALIDATION */

/* FIXME: split to separate file... (debatable whether this is anything to do with MMU) */
extern PVRSRV_ERROR
PDumpMMUSAB(const IMG_CHAR *pszPDumpMemNamespace,
            IMG_UINT32 uiPDumpMMUCtx,
            IMG_DEV_VIRTADDR sDevAddrStart,
            IMG_DEVMEM_SIZE_T uiSize,
            const IMG_CHAR *pszFilename,
            IMG_UINT32 uiFileOffset,
            IMG_UINT32 ui32PDumpFlags);

#if defined(PVR_SUPPORT_HMMU_VALIDATION)
#define PDUMP_MMU_ALLOC_MMUCONTEXT(pszPDumpMemDevName, sPCDevPAddr, eMMUType, puiPDumpCtxID, ui32PDumpFlags,\
                                   sPCDevIpaAddr, bHMMUEnabled, ui32OSid, ui64HPCBase, ui32Log2PageSize) \
        PDumpMMUAllocMMUContext(pszPDumpMemDevName,                     \
                                sPCDevPAddr,                            \
                                eMMUType,                               \
                                puiPDumpCtxID,                          \
                                ui32PDumpFlags,                         \
                                sPCDevIpaAddr,                          \
                                bHMMUEnabled,                           \
                                ui32OSid,                               \
                                ui64HPCBase,                            \
                                ui32Log2PageSize)

#define PDUMP_MMU_FREE_MMUCONTEXT(pszPDumpMemDevName, uiPDumpCtxID, ui32PDumpFlags, bIsHMMUEnabled) \
        PDumpMMUFreeMMUContext(pszPDumpMemDevName, uiPDumpCtxID, ui32PDumpFlags, bIsHMMUEnabled)
#else
#define PDUMP_MMU_ALLOC_MMUCONTEXT(pszPDumpMemDevName, sPCDevPAddr, eMMUType, puiPDumpCtxID, ui32PDumpFlags) \
        PDumpMMUAllocMMUContext(pszPDumpMemDevName,                     \
                                sPCDevPAddr,                            \
                                eMMUType,                               \
                                puiPDumpCtxID,                          \
                                ui32PDumpFlags)

#define PDUMP_MMU_FREE_MMUCONTEXT(pszPDumpMemDevName, uiPDumpCtxID, ui32PDumpFlags) \
        PDumpMMUFreeMMUContext(pszPDumpMemDevName, uiPDumpCtxID, ui32PDumpFlags)
#endif /* PVR_SUPPORT_HMMU_VALIDATION */
#else /* PDUMP */

#define PDUMP_MMU_ALLOC_MMUCONTEXT(pszPDumpMemDevName, sPCDevPAddr, eMMUType, puiPDumpCtxID, ui32PDumpFlags) \
        ((void)0)
#define PDUMP_MMU_FREE_MMUCONTEXT(pszPDumpMemDevName, uiPDumpCtxID, ui32PDumpFlags) \
        ((void)0)

#endif /* PDUMP */

#endif
