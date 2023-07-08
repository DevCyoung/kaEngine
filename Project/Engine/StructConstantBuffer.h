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

struct alignas(16) tCBDebugInfo // b2
{
	Vector3 MouseWorldPos;
	float dummy;
	Vector2 Scale;
	int XYCount[2];

	Vector4 Color_0;
	Vector4 Color_1;
	Vector4 Color_2;
	Vector4 Color_3;

	Vector4 Vector4_0;
	Vector4 Vector4_1;
	Vector4 Vector4_2;
	Vector4 Vector4_3;

}; // 16 bytes