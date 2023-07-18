#pragma once

enum class eRenderPriorityType
{
	Opqaue,
	CutOut,
	Transparent,
	End
};

enum class eCameraPriorityType
{
	BackGround,
	Main,
	UI,
	End
};

enum class eCameraProjectionType
{
	Perspective,
	Orthographic,
	End
};
