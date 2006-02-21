/*
 * Copyright 2000 Corel Corporation
 * Copyright 2006 CodeWeavers, Aric Stewart
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "wingdi.h"
#include "winuser.h"
#include "twain.h"
#include "twain_i.h"
#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(twain);

/* DG_IMAGE/DAT_CIECOLOR/MSG_GET */
TW_UINT16 TWAIN_CIEColorGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                             TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_EXTIMAGEINFO/MSG_GET */
TW_UINT16 TWAIN_ExtImageInfoGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                 TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_GRAYRESPONSE/MSG_RESET */
TW_UINT16 TWAIN_GrayResponseReset (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                   TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_GRAYRESPONSE/MSG_SET */
TW_UINT16 TWAIN_GrayResponseSet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                 TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_IMAGEFILEXFER/MSG_GET */
TW_UINT16 TWAIN_ImageFileXferGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                  TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_IMAGEINFO/MSG_GET */
TW_UINT16 TWAIN_ImageInfoGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                              TW_MEMREF pData)
{
#ifndef HAVE_SANE
    return TWRC_FAILURE;
#else
    TW_UINT16 twRC = TWRC_SUCCESS;
    pTW_IMAGEINFO pImageInfo = (pTW_IMAGEINFO) pData;
    activeDS *pSource = TWAIN_LookupSource (pDest);
    SANE_Status status;

    TRACE("DG_IMAGE/DAT_IMAGEINFO/MSG_GET\n");

    if (!pSource)
    {
        twRC = TWRC_FAILURE;
        DSM_twCC = TWCC_BADDEST;
    }
    else if (pSource->currentState != 6 && pSource->currentState != 7)
    {
        twRC = TWRC_FAILURE;
        pSource->twCC = TWCC_SEQERROR;
    }
    else
    {
        if (pSource->currentState == 6)
        {
            /* return general image description information about the image about to be transferred */
            status = sane_get_parameters (pSource->deviceHandle, &pSource->sane_param);
            pSource->sane_param_valid = TRUE;
            TRACE("Getting parameters\n");
        }

        pImageInfo->XResolution.Whole = -1;
        pImageInfo->XResolution.Frac = 0;
        pImageInfo->YResolution.Whole = -1;
        pImageInfo->YResolution.Frac = 0;
        pImageInfo->ImageWidth = pSource->sane_param.pixels_per_line;
        pImageInfo->ImageLength = pSource->sane_param.lines;

        TRACE("Bits per Sample %i\n",pSource->sane_param.depth);
        TRACE("Frame Format %i\n",pSource->sane_param.format);

        if (pSource->sane_param.format == 1 /*RGB*/ )
        {
            pImageInfo->BitsPerPixel = pSource->sane_param.depth * 3;
            pImageInfo->Compression = TWCP_NONE;
            pImageInfo->Planar = TRUE;
            pImageInfo->SamplesPerPixel = 3;
            pImageInfo->BitsPerSample[0] = pSource->sane_param.depth;
            pImageInfo->BitsPerSample[1] = pSource->sane_param.depth;
            pImageInfo->BitsPerSample[2] = pSource->sane_param.depth;
            pImageInfo->PixelType = TWPT_RGB;
        }
        else
        {
            ERR("Unhandled source frame type\n");
            twRC = TWRC_FAILURE;
            pSource->twCC = TWCC_SEQERROR;
        }
    }

    return twRC;
#endif
}

/* DG_IMAGE/DAT_IMAGELAYOUT/MSG_GET */
TW_UINT16 TWAIN_ImageLayoutGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_IMAGELAYOUT/MSG_GETDEFAULT */
TW_UINT16 TWAIN_ImageLayoutGetDefault (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                       TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_IMAGELAYOUT/MSG_RESET */
TW_UINT16 TWAIN_ImageLayoutReset (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                  TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_IMAGELAYOUT/MSG_SET */
TW_UINT16 TWAIN_ImageLayoutSet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_IMAGEMEMXFER/MSG_GET */
TW_UINT16 TWAIN_ImageMemXferGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                 TW_MEMREF pData)
{
#ifndef HAVE_SANE
    return TWRC_FAILURE;
#else
    TW_UINT16 twRC = TWRC_SUCCESS;
    pTW_IMAGEMEMXFER pImageMemXfer = (pTW_IMAGEMEMXFER) pData;
    activeDS *pSource = TWAIN_LookupSource (pDest);
    SANE_Status status = SANE_STATUS_GOOD;

    TRACE ("DG_IMAGE/DAT_IMAGEMEMXFER/MSG_GET\n");

    if (!pSource)
    {
        twRC = TWRC_FAILURE;
        DSM_twCC = TWCC_NODS;
    }
    else if (pSource->currentState < 6 || pSource->currentState > 7)
    {
        twRC = TWRC_FAILURE;
        pSource->twCC = TWCC_SEQERROR;
    }
    else
    {
        LPBYTE buffer;
        int buff_len = 0;
        int consumed_len = 0;
        LPBYTE ptr;
        int rows;

        /* Transfer an image from the source to the application */
        if (pSource->currentState == 6)
        {
            status = sane_start (pSource->deviceHandle);
            if (status != SANE_STATUS_GOOD)
            {
                WARN("sane_start: %s\n", sane_strstatus (status));
                sane_cancel (pSource->deviceHandle);
                pSource->twCC = TWCC_OPERATIONERROR;
                return TWRC_FAILURE;
            }

            status = sane_get_parameters (pSource->deviceHandle,
                    &pSource->sane_param);
            pSource->sane_param_valid = TRUE;

            if (status != SANE_STATUS_GOOD)
            {
                WARN("sane_get_parameters: %s\n", sane_strstatus (status));
                sane_cancel (pSource->deviceHandle);
                pSource->twCC = TWCC_OPERATIONERROR;
                return TWRC_FAILURE;
            }

            TRACE("Acquiring image %dx%dx%d bits (format=%d last=%d) from sane...\n"
              , pSource->sane_param.pixels_per_line, pSource->sane_param.lines,
              pSource->sane_param.depth, pSource->sane_param.format,
              pSource->sane_param.last_frame);

            pSource->currentState = 7;
        }

        /* access memory buffer */
        if (pImageMemXfer->Memory.Length < pSource->sane_param.bytes_per_line)
        {
            sane_cancel (pSource->deviceHandle);
            pSource->twCC = TWCC_BADVALUE;
            return TWRC_FAILURE;
        }

        if (pImageMemXfer->Memory.Flags & TWMF_HANDLE)
        {
            FIXME("Memory Handle, may not be locked correctly\n");
            buffer = LocalLock(pImageMemXfer->Memory.TheMem);
        }
        else
            buffer = pImageMemXfer->Memory.TheMem;
       
        memset(buffer,0,pImageMemXfer->Memory.Length);

        ptr = buffer;
        consumed_len = 0;
        rows = pImageMemXfer->Memory.Length / pSource->sane_param.bytes_per_line;

        /* must fill full lines */
        while (consumed_len < (pSource->sane_param.bytes_per_line*rows) && 
                status == SANE_STATUS_GOOD)
        {
            status = sane_read (pSource->deviceHandle, ptr, 
                    (pSource->sane_param.bytes_per_line*rows) - consumed_len ,
                    &buff_len);
            consumed_len += buff_len;
            ptr += buff_len;
        }

        if (status == SANE_STATUS_GOOD || status == SANE_STATUS_EOF)
        {
            pImageMemXfer->Compression = TWCP_NONE;
            pImageMemXfer->BytesPerRow = pSource->sane_param.bytes_per_line;
            pImageMemXfer->Columns = pSource->sane_param.pixels_per_line;
            pImageMemXfer->Rows = rows;
            pImageMemXfer->XOffset = 0;
            pImageMemXfer->YOffset = 0;
            pImageMemXfer->BytesWritten = consumed_len;

            if (status == SANE_STATUS_EOF)
            {
                TRACE("sane_read: %s\n", sane_strstatus (status));
                sane_cancel (pSource->deviceHandle);
                twRC = TWRC_XFERDONE;
            }
            pSource->twCC = TWRC_SUCCESS;
        }
        else if (status != SANE_STATUS_EOF)
        {
            WARN("sane_read: %s\n", sane_strstatus (status));
            sane_cancel (pSource->deviceHandle);
            pSource->twCC = TWCC_OPERATIONERROR;
            twRC = TWRC_FAILURE;
        }
    }

    if (pImageMemXfer->Memory.Flags & TWMF_HANDLE)
        LocalUnlock(pImageMemXfer->Memory.TheMem);
    
    return twRC;
#endif
}

/* DG_IMAGE/DAT_IMAGENATIVEXFER/MSG_GET */
TW_UINT16 TWAIN_ImageNativeXferGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                    TW_MEMREF pData)
{
#ifndef HAVE_SANE
    return TWRC_FAILURE;
#else
    TW_UINT16 twRC = TWRC_SUCCESS;
    pTW_UINT32 pHandle = (pTW_UINT32) pData;
    activeDS *pSource = TWAIN_LookupSource (pDest);
    SANE_Status status;
    SANE_Byte buffer[32*1024];
    int buff_len;
    HBITMAP hDIB;
    BITMAPINFO bmpInfo;
    VOID *pBits;
    HDC dc;

    TRACE("DG_IMAGE/DAT_IMAGENATIVEXFER/MSG_GET\n");

    if (!pSource)
    {
        twRC = TWRC_FAILURE;
        DSM_twCC = TWCC_NODS;
    }
    else if (pSource->currentState != 6)
    {
        twRC = TWRC_FAILURE;
        pSource->twCC = TWCC_SEQERROR;
    }
    else
    {
        /* Transfer an image from the source to the application */
        status = sane_start (pSource->deviceHandle);
        if (status != SANE_STATUS_GOOD)
        {
            WARN("sane_start: %s\n", sane_strstatus (status));
            sane_cancel (pSource->deviceHandle);
            pSource->twCC = TWCC_OPERATIONERROR;
            return TWRC_FAILURE;
        }

        status = sane_get_parameters (pSource->deviceHandle, &pSource->sane_param);
        pSource->sane_param_valid = TRUE;
        if (status != SANE_STATUS_GOOD)
        {
            WARN("sane_get_parameters: %s\n", sane_strstatus (status));
            sane_cancel (pSource->deviceHandle);
            pSource->twCC = TWCC_OPERATIONERROR;
            return TWRC_FAILURE;
        }

        TRACE("Acquiring image %dx%dx%d bits (format=%d last=%d) from sane...\n"
              , pSource->sane_param.pixels_per_line, pSource->sane_param.lines,
              pSource->sane_param.depth, pSource->sane_param.format,
              pSource->sane_param.last_frame);

        ZeroMemory (&bmpInfo, sizeof (BITMAPINFO));
        bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth = pSource->sane_param.pixels_per_line;
        bmpInfo.bmiHeader.biHeight = pSource->sane_param.lines;
        bmpInfo.bmiHeader.biPlanes = 1;
        bmpInfo.bmiHeader.biBitCount = pSource->sane_param.depth;
        bmpInfo.bmiHeader.biCompression = BI_RGB;
        bmpInfo.bmiHeader.biSizeImage = 0;
        bmpInfo.bmiHeader.biXPelsPerMeter = 0;
        bmpInfo.bmiHeader.biYPelsPerMeter = 0;
        bmpInfo.bmiHeader.biClrUsed = 1;
        bmpInfo.bmiHeader.biClrImportant = 0;
        bmpInfo.bmiColors[0].rgbBlue = 128;
        bmpInfo.bmiColors[0].rgbGreen = 128;
        bmpInfo.bmiColors[0].rgbRed = 128;
        hDIB = CreateDIBSection ((dc = GetDC(pSource->hwndOwner)), &bmpInfo,
                                 DIB_RGB_COLORS, &pBits, 0, 0);
        if (!hDIB)
        {
            sane_cancel (pSource->deviceHandle);
            pSource->twCC = TWCC_LOWMEMORY;
            return TWRC_FAILURE;
        }

        do
        {
            status = sane_read (pSource->deviceHandle, buffer,
                                sizeof (buffer),  &buff_len);
            if (status == SANE_STATUS_GOOD)
            {
                /* FIXME: put code for converting the image data into DIB here */

            }
            else if (status != SANE_STATUS_EOF)
            {
                WARN("sane_read: %s\n", sane_strstatus (status));
                sane_cancel (pSource->deviceHandle);
                pSource->twCC = TWCC_OPERATIONERROR;
                return TWRC_FAILURE;
            }
        } while (status == SANE_STATUS_GOOD);

        sane_cancel (pSource->deviceHandle);
        ReleaseDC (pSource->hwndOwner, dc);
        *pHandle = (TW_UINT32)hDIB;
        twRC = TWRC_XFERDONE;
        pSource->twCC = TWCC_SUCCESS;
        pSource->currentState = 7;
    }
    return twRC;
#endif
}

/* DG_IMAGE/DAT_JPEGCOMPRESSION/MSG_GET */
TW_UINT16 TWAIN_JPEGCompressionGet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                    TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_JPEGCOMPRESSION/MSG_GETDEFAULT */
TW_UINT16 TWAIN_JPEGCompressionGetDefault (pTW_IDENTITY pOrigin,
                                           pTW_IDENTITY pDest,
                                           TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_JPEGCOMPRESSION/MSG_RESET */
TW_UINT16 TWAIN_JPEGCompressionReset (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                      TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_JPEGCOMPRESSION/MSG_SET */
TW_UINT16 TWAIN_JPEGCompressionSet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                    TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_PALETTE8/MSG_GET */
TW_UINT16 TWAIN_Palette8Get (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                             TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_PALETTE8/MSG_GETDEFAULT */
TW_UINT16 TWAIN_Palette8GetDefault (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                    TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_PALETTE8/MSG_RESET */
TW_UINT16 TWAIN_Palette8Reset (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                               TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_PALETTE8/MSG_SET */
TW_UINT16 TWAIN_Palette8Set (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                             TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_RGBRESPONSE/MSG_RESET */
TW_UINT16 TWAIN_RGBResponseReset (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                  TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}

/* DG_IMAGE/DAT_RGBRESPONSE/MSG_SET */
TW_UINT16 TWAIN_RGBResponseSet (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest,
                                TW_MEMREF pData)
{
    FIXME ("stub!\n");

    return TWRC_FAILURE;
}
