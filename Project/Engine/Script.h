#pragma once
#include "Component.h"

//Content Project Define
enum class eScriptType;

namespace engine
{
	class Script : public Component
	{
		friend class GameObject;
	public:
		Script(eScriptType type);
		virtual ~Script();
		Script(const Script&) = delete;
		Script& operator=(const Script&) = delete;

		eScriptType GetScriptType() const { return mScriptType; }

	private:
		virtual void initialize() override;
		virtual void update() override;
		virtual void lateUpdate() override;
		virtual void render() override;

	private:
		eScriptType mScriptType;
	};
}	