#pragma once

class Resource
{
	friend class ResourceManager;
public:
	Resource();
	virtual ~Resource();

	virtual HRESULT Load(const std::wstring& FULL_PATH) = 0;

	const std::wstring& GetKey() const { return mKey; }
	const std::wstring& GetPath() const { return mPath; }

private:
	std::wstring mKey;
	std::wstring mPath;
};