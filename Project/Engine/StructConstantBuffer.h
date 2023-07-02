#pragma once

struct alignas(16) tCBTransform // c0
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
}; // 48 bytes

struct alignas(16) tCBColorInfo // c1
{
	int	bUseColor;	
	Vector3 dummy;
	Vector4 mColor;
}; // 16 bytes