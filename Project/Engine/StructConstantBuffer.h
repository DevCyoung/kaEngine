#pragma once

struct alignas(16) tCBTransform // b0
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
}; // 48 bytes

struct alignas(16) tCBColorInfo // b1
{
	int	bUseColor;	
	Vector3 dummy;
	Vector4 mColor;
}; // 32 bytes