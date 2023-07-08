#pragma once

class Resource
{
	friend class ResourceManager;
public:
	Resource();
	virtual ~Resource();

	virtual HRESULT Load(const std::wstring& fullPath) = 0;

	const std::wstring& GetRelativePath() const { return mRelativePath; }

private:
	std::wstring mRelativePath;
};