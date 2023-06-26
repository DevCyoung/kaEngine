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

void MessageManager::lateUpdate()
{
}

void MessageManager::render(HWND hWnd)
{
	mSecond += gDeltaTime;

	if (1.0f < mSecond)
	{
		std::wstring outMessage;
		outMessage.reserve(256);
		outMessage = L"<SEO Egine>";

		for (const std::wstring& message : mMessages)
		{			
			outMessage += L" ";
			outMessage += message;
		}

		SetWindowText(hWnd, outMessage.data());

		mSecond = 0.0f;
	}

	mMessages.clear();
}


