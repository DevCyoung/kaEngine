#pragma once

class GameObject;
class Scene;

enum class eLayerType;


class GameObjectBuilder
{
public:
	GameObjectBuilder() = delete;
	virtual ~GameObjectBuilder() = delete;
	GameObjectBuilder(const GameObjectBuilder&) = delete;
	GameObjectBuilder& operator=(const GameObjectBuilder&) = delete;

public:
	static GameObject* Default2D(const std::wstring& materialName);
	static GameObject* Player();
	static GameObject* Slash();

	static GameObject* InstantiatePlayer(Scene* const scene);
	static void InstantiateGlobalLight2D(Scene* const scene, const eLayerType type);

	static void AddUI(Scene* const scene);
	static void AddCamera(Scene* const scene);
};