/*
 * Copyright (C) 2007 David Adam
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <d3dx8.h>

#ifndef __D3DX8MATH_H__
#define __D3DX8MATH_H__

#include <math.h>

#define D3DX_PI    ((FLOAT)3.141592654)
#define D3DX_1BYPI ((FLOAT)0.318309886)

#define D3DXToRadian(degree) ((degree) * (D3DX_PI / 180.0f))
#define D3DXToDegree(radian) ((radian) * (180.0f / D3DX_PI))

typedef struct D3DXVECTOR2
{
    FLOAT x, y;
} D3DXVECTOR2, *LPD3DXVECTOR2;

typedef struct _D3DVECTOR D3DXVECTOR3, *LPD3DXVECTOR3;

typedef struct D3DXVECTOR4
{
    FLOAT x, y, z, w;
} D3DXVECTOR4, *LPD3DXVECTOR4;

typedef struct _D3DMATRIX D3DXMATRIX, *LPD3DXMATRIX;

typedef struct D3DXQUATERNION
{
    FLOAT x, y, z, w;
} D3DXQUATERNION, *LPD3DXQUATERNION;

typedef struct D3DXPLANE
{
    FLOAT a, b, c, d;
} D3DXPLANE, *LPD3DXPLANE;

typedef struct D3DXCOLOR
{
    FLOAT r, g, b, a;
} D3DXCOLOR, *LPD3DXCOLOR;

D3DXQUATERNION* WINAPI D3DXQuaternionNormalize(D3DXQUATERNION *pout, CONST D3DXQUATERNION *pq);

D3DXVECTOR2* WINAPI D3DXVec2BaryCentric(D3DXVECTOR2 *pout, CONST D3DXVECTOR2 *pv1, CONST D3DXVECTOR2 *pv2, CONST D3DXVECTOR2 *pv3, FLOAT f, FLOAT g);
D3DXVECTOR2* WINAPI D3DXVec2CatmullRom(D3DXVECTOR2 *pout, CONST D3DXVECTOR2 *pv0, CONST D3DXVECTOR2 *pv1, CONST D3DXVECTOR2 *pv2, CONST D3DXVECTOR2 *pv3, FLOAT s);
D3DXVECTOR2* WINAPI D3DXVec2Hermite(D3DXVECTOR2 *pout, CONST D3DXVECTOR2 *pv1, CONST D3DXVECTOR2 *pt1, CONST D3DXVECTOR2 *pv2, CONST D3DXVECTOR2 *pt2, FLOAT s);
D3DXVECTOR2* WINAPI D3DXVec2Normalize(D3DXVECTOR2 *pout, CONST D3DXVECTOR2 *pv);
D3DXVECTOR4* WINAPI D3DXVec2Transform(D3DXVECTOR4 *pout, CONST D3DXVECTOR2 *pv, CONST D3DXMATRIX *pm);

D3DXVECTOR3* WINAPI D3DXVec3BaryCentric(D3DXVECTOR3 *pout, CONST D3DXVECTOR3 *pv1, CONST D3DXVECTOR3 *pv2, CONST D3DXVECTOR3 *pv3, FLOAT f, FLOAT g);
D3DXVECTOR3* WINAPI D3DXVec3CatmullRom( D3DXVECTOR3 *pout, CONST D3DXVECTOR3 *pv0, CONST D3DXVECTOR3 *pv1, CONST D3DXVECTOR3 *pv2, CONST D3DXVECTOR3 *pv3, FLOAT s);
D3DXVECTOR3* WINAPI D3DXVec3Hermite(D3DXVECTOR3 *pout, CONST D3DXVECTOR3 *pv1, CONST D3DXVECTOR3 *pt1, CONST D3DXVECTOR3 *pv2, CONST D3DXVECTOR3 *pt2, FLOAT s);
D3DXVECTOR3* WINAPI D3DXVec3Normalize(D3DXVECTOR3 *pout, CONST D3DXVECTOR3 *pv);
D3DXVECTOR4* WINAPI D3DXVec3Transform(D3DXVECTOR4 *pout, CONST D3DXVECTOR3 *pv, CONST D3DXMATRIX *pm);

D3DXVECTOR4* WINAPI D3DXVec4BaryCentric(D3DXVECTOR4 *pout, CONST D3DXVECTOR4 *pv1, CONST D3DXVECTOR4 *pv2, CONST D3DXVECTOR4 *pv3, FLOAT f, FLOAT g);
D3DXVECTOR4* WINAPI D3DXVec4CatmullRom(D3DXVECTOR4 *pout, CONST D3DXVECTOR4 *pv0, CONST D3DXVECTOR4 *pv1, CONST D3DXVECTOR4 *pv2, CONST D3DXVECTOR4 *pv3, FLOAT s);
D3DXVECTOR4* WINAPI D3DXVec4Hermite(D3DXVECTOR4 *pout, CONST D3DXVECTOR4 *pv1, CONST D3DXVECTOR4 *pt1, CONST D3DXVECTOR4 *pv2, CONST D3DXVECTOR4 *pt2, FLOAT s);
D3DXVECTOR4* WINAPI D3DXVec4Normalize(D3DXVECTOR4 *pout, CONST D3DXVECTOR4 *pv);
D3DXVECTOR4* WINAPI D3DXVec4Transform(D3DXVECTOR4 *pout, CONST D3DXVECTOR4 *pv, CONST D3DXMATRIX *pm);

#include <d3dx8math.inl>

#endif /* __D3DX8MATH_H__ */
