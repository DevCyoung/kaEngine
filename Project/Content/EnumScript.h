#pragma once

enum class eScriptType
{
	CameraScript,
	SampleScript,
	TestScript,
	BulletMovement,
	End
};

const wchar_t* GetComponentWstrByEnum(const eScriptType type);

