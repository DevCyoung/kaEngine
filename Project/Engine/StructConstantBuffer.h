#pragma once

struct alignas(16) tCBTransform // b0
{
	Matrix World;
	Matrix View;
	Matrix Proj;
}; // 48 bytes

struct alignas(16) tCBColorInfo // b1
{
	int	bUseColor;	
	Vector3 Dummy;
	Vector4 Color;
}; // 32 bytes

struct alignas(16) tCBGridInfo // b2
{
	Vector3 MouseWorldPos;
	float dummy;	
	Vector2 Scale;
	int XYCount[2];
}; // 16 bytes