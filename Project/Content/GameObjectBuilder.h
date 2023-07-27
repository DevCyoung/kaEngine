#pragma once

class GameObject;
class Scene;

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

	static void AddUI(Scene* const scene);
	static void AddCamera(Scene* const scene);
};