#pragma once
namespace engine
{
	enum class eComponentType
	{
		Transform,
		Sprite,
		Animator,
		MeshRenderer,		
		End,
		Script,
	};

	class Transform;
	class Animator;
	class MeshRenderer;
}