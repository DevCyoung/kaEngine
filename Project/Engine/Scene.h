#pragma once
#include "Resource.h"
#include "Layer.h"


namespace engine
{
	class GameObject;
	enum class eLayerType;

	class Scene : public Resource
	{
		friend class Engine;
		friend class SceneManager;

	public:
		Scene();
		virtual ~Scene();

		void AddGameObject(GameObject* const obj, eLayerType type);

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	public:
		virtual HRESULT Load(const std::wstring& path) override;

	private:
		Layer mLayers[static_cast<UINT>(eLayerType::End)];
	};
}
