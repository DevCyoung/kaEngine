#pragma once

class Resource
{
	friend class ResourceManager;
public:
	Resource();
	virtual ~Resource();

	virtual HRESULT Load(const std::wstring& path) = 0;

	//void SetKey(const std::wstring& key) { mKey = key; }
	//void SetPath(const std::wstring& path) { mPath = path; }

	const std::wstring& GetKey() const { return mKey; }
	const std::wstring& GetPath() const { return mPath; }

private:
	std::wstring mKey;
	std::wstring mPath;
};