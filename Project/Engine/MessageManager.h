#pragma once
#include "Singleton.h"

class MessageManager
{
	friend class Engine;
	SINGLETON_DECLARE(MessageManager);

public:
	void AddMessage(const std::wstring& MESSAGE)
	{
		Assert(IsSendMessage(), WCHAR_IS_INVALID_TYPE);

		mMessages.push_back(MESSAGE);
	}

	bool IsSendMessage() { return mSecond > 1.0f; }

private:
	void render(const HWND H_WND);

private:
	std::vector<std::wstring> mMessages;
	float mSecond;
};
#define gMessageManager MessageManager::GetInstance()
