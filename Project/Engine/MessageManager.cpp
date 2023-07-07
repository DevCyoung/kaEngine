#include "pch.h"
#include "MessageManager.h"
#include "TimeManager.h"

MessageManager::MessageManager()
	: mMessages()
	, mSecond(0.0f)
{
}

MessageManager::~MessageManager()
{
}

void MessageManager::eventUpdate(const HWND H_WND)
{	
	if (IsSendMessage())
	{
		std::wstring outMessage;
		outMessage.reserve(256);
		outMessage = L"<SEO Egine>";

		for (const std::wstring& message : mMessages)
		{
			outMessage += L" ";
			outMessage += message;
		}

		SetWindowText(H_WND, outMessage.data());

		mSecond = 0.0f;

		mMessages.clear();
	}
	else
	{
		mSecond += gDeltaTime;
	}	
}