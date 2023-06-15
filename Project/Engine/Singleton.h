#pragma once

#define SINGLETON_DECLARE(CLASSNAME)							\
	private:													\
		static void initialize();								\
		static void deleteInstance()							\
	{															\
		assert(sInstance);										\
		delete sInstance;										\
		sInstance = nullptr;									\
	}															\
	public:														\
		static CLASSNAME* GetInstance()							\
	{															\
		assert(sInstance);										\
		return sInstance;										\
	}															\
	private:													\
		CLASSNAME();											\
		virtual ~CLASSNAME();									\
		CLASSNAME(const CLASSNAME& other) = delete;				\
		CLASSNAME& operator=(const CLASSNAME& other) = delete;	\
	private:													\
		inline static CLASSNAME* sInstance = nullptr;

