#include "pch.h"
#include "EnumResourceTypeMaterial.h"

namespace engine
{
	const wchar_t* eResMaterialPath[static_cast<UINT>(eResMaterial::End)]
	{
		L"\\Material\\dummy.mat",
	};

	const wchar_t* EnumResourcePath(eResMaterial type)
	{
		return eResMaterialPath[static_cast<UINT>(type)];
	}
}//namespace engine End
