#include "pch.h"
#include "CBCollection.h"
#include "GraphicDeviceDx11.h"

namespace engine
{
	CBCollection::CBCollection()
		: transform(eCBType::Transform, 16)
	{		
	}

	CBCollection::~CBCollection()
	{
	}

	void CBCollection::Initialize()
	{
	}
}