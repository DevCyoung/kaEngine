#pragma once
#include "Singleton.h"

class MessageManager
{
	friend class Engine;
	SINGLETON_DECLARE(MessageManager);

public:
	void AddMessage(const std::wstring& message) { mMessages.push_back(message); }

private:
	void lateUpdate();
	void render(HWND hWnd);

private:
	std::vector<std::wstring> mMessages;
	float mSecond;
};
#define gMessageManager MessageManager::GetInstance()
