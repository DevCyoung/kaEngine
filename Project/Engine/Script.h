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

enum class eScriptType;

//content
template <typename T>
struct script_component_type
{
	static constexpr bool value = false;
};

//eScriptType SampleScript
#define REGISTER_SCRIPT_TYPE(SCRIPT_TYPE)	class SCRIPT_TYPE;						\
template <>																			\
struct script_component_type<SCRIPT_TYPE>											\
{																					\
	static constexpr bool value = true;												\
	static constexpr eScriptType type = eScriptType::SCRIPT_TYPE;					\
	static constexpr const wchar_t* const name = L#SCRIPT_TYPE;						\
}\
