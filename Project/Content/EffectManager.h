#pragma once

#include <Engine/GameObject.h>
#include <Engine/Scene.h>

#define MAX_EFFECT_COUNT 100
#define MAX_SLASH_COUNT 10

class EffectManager
{
public:
	EffectManager();
	virtual ~EffectManager();
	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;

	void Initialize(Scene* scene);
	GameObject* GetShotEffect(const std::wstring& str);
	void Shot(const std::wstring& str, Vector3 pos);
	void Shot(const std::wstring& str, Vector3 pos, bool bFlip);
	void Shot(const std::wstring& str, Vector3 pos, GameObject* parent);
	void Shot(const std::wstring& str, Vector3 pos, Vector3 rotation, bool bFlip);
	void Shot(const std::wstring& str, Vector3 pos, Vector2 direction, float speed);
	void Slash(Vector3 pos, float rotation, float speed);

	//void MonsterAttack(Vector3 pos, Vector2 scale, float time);

	GameObject* mEffects[MAX_EFFECT_COUNT];
	GameObject* mSlashs[MAX_SLASH_COUNT];
	GameObject* mMonsterAttacks[MAX_SLASH_COUNT];

	int mEffectIdx;
	int mAttackIdx;
};

