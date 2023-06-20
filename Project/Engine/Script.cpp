#include "pch.h"
#include "Script.h"

namespace engine
{
	Script::Script(eScriptType type)
		: Component(eComponentType::Script)
		, mScriptType(type)
	{
	}
	Script::~Script()
	{
	}

	void Script::initialize()
	{
	}
	void Script::update()
	{
	}
	void Script::lateUpdate()
	{
	}
	void Script::render()
	{
	}
}