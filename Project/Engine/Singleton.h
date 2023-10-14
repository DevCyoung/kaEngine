#pragma once
#include "DefineMacro.h"

#define SINGLETON_DECLARE(CLASSNAME)						\
private:													\
	static void initialize()								\
	{														\
		Assert(!sInstance, WCHAR_IS_NOT_NULLPTR);			\
		sInstance = new CLASSNAME();						\
	}														\
static void deleteInstance()								\
	{														\
		Assert(sInstance, WCHAR_IS_NULLPTR);				\
		delete sInstance;									\
		sInstance = nullptr;								\
	}														\
public:														\
	static CLASSNAME* GetInstance()							\
	{														\
		Assert(sInstance, WCHAR_IS_NULLPTR);				\
		return sInstance;									\
	}														\
private:													\
	CLASSNAME();											\
	virtual ~CLASSNAME();									\
	CLASSNAME(const CLASSNAME&) = delete;					\
	CLASSNAME& operator=(const CLASSNAME&) = delete;		\
private:													\
	inline static CLASSNAME* sInstance = nullptr;			\
