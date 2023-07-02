#pragma once

class GameObject;

class GameObjectBuilder
{
public:
	GameObjectBuilder() = delete;
	virtual ~GameObjectBuilder() = delete;
	GameObjectBuilder(const GameObjectBuilder&) = delete;
	GameObjectBuilder& operator=(const GameObjectBuilder&) = delete;

public:
	static GameObject* BuildDefault2DGameObject(const std::wstring& materialName);
};