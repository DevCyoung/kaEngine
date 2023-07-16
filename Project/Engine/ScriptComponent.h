#pragma once
#include "Component.h"
#include "ScriptComponentTrait.h"
class Collider2D;

class ScriptComponent : public Component
{
	friend class GameObject;
	friend class Collider;

protected:
	ScriptComponent(eScriptComponentType scriptComonentType);
public:
	virtual ~ScriptComponent();
	ScriptComponent(const ScriptComponent&) = delete;
	ScriptComponent& operator=(const ScriptComponent&) = delete;

	eScriptComponentType GetScriptType() const { return mScriptType; }	

	virtual void OnCollisionEnter(Collider2D* other);
	virtual void OnCollisionStay(Collider2D* other);
	virtual void OnCollisionExit(Collider2D* other);

private:
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;	

private:
	eScriptComponentType mScriptType;
};
