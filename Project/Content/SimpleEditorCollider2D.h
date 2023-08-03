#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include <Engine/Collider2D.h>

REGISTER_SCRIPTCOMPONENT_TYPE(SimpleEditorCollider2D);

class SimpleEditorCollider2D : public ScriptComponent
{
public:
	SimpleEditorCollider2D();
	virtual ~SimpleEditorCollider2D();
	SimpleEditorCollider2D(const SimpleEditorCollider2D&) = delete;
	SimpleEditorCollider2D& operator=(const SimpleEditorCollider2D&) = delete;


	struct tEditCollider
	{
		eCollider2DType type;
		Vector3 startPos;
		Vector3 endPos;
		//Collider2D collider;
	};

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

	std::deque< tEditCollider> mEditColliders;
};
