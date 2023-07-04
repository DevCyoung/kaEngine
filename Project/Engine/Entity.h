#pragma once

class Entity
{
public:
	Entity();
	virtual ~Entity();
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	void SetName(const std::wstring& ENTITY_NAME) { mName = ENTITY_NAME; }
	const std::wstring& GetName() const { return mName; }

private:
	inline static UINT sID = 0;
	std::wstring mName;
	UINT mID;
};