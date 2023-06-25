#pragma once
#include "Entity.h"
#include "EnumComponent.h"

namespace engine
{
	class GameObject;

	class Component : public Entity
	{		
		friend class GameObject;

	public:
		Component(const eComponentType type);
		virtual ~Component();
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;

	public:
		GameObject* GetOwner() const { Assert(mOwner, WCHAR_IS_NULLPTR); return mOwner; }
		eComponentType GetType() const { return mType; }

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	private:
		eComponentType mType;
		GameObject* mOwner;
	};
}

namespace engine
{
	enum class eComponentType;

	template <typename T>
	struct engine_component_type
	{
		static constexpr bool value = false;
	};

#define REGISTER_COMPONENT_TYPE(COMPONENT_TYPE)	class COMPONENT_TYPE;			\
	template <>																	\
	struct engine_component_type<COMPONENT_TYPE>								\
	{																			\
		static constexpr bool value = true;										\
		static constexpr eComponentType type = eComponentType::COMPONENT_TYPE;	\
		static constexpr const wchar_t* const name = L#COMPONENT_TYPE;			\
	}
}
