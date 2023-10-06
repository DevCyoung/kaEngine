#pragma once

class GameObject;
class Scene;

enum class eLayerType;

enum class eMonsterType
{
	Default,
	Ganster,
	Cop,
	Shield,
	Shotgun,
	End,
};


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
	static GameObject* InstantiateMonster(const eMonsterType type, Scene* const scene);
	static GameObject* InstantiateKissyface(Scene* const scene);
	static GameObject* InstantiateDoor(Scene* const scene);
	static GameObject* InstantiateClubDoor(Scene* const scene);
	static GameObject* Slash();	
	

	static GameObject* InstantiatePlayer(Scene* const scene);
	static GameObject* InstantiateGlobalLight2D(Scene* const scene, const eLayerType type);

	static void AddUI(Scene* const scene);
	static GameObject* AddCamera(Scene* const scene);


private:

};