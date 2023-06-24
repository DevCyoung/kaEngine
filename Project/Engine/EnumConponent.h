#pragma once
namespace engine
{
	enum class eComponentType
	{
		Transform,
		Camera,
		MeshRenderer,
		End,
		Script,
	};

	class Transform;	
	class Camera;
	class MeshRenderer;	
}