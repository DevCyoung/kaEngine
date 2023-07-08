#include "pch.h"
#include "SMCollection.h"

SMCollection::SMCollection()
{
	for (auto& mInputElements : mInputElementsArray)
	{
		mInputElements.reserve(10);
	}

	//Default
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC>& DeafultIEDArray = 
			mInputElementsArray[static_cast<UINT>(eSMType::Default)];

		constexpr UINT MAX_INPUT_ELEMENT = 3;
		DeafultIEDArray.resize(MAX_INPUT_ELEMENT);

		DeafultIEDArray[0].AlignedByteOffset = 0;
		DeafultIEDArray[0].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		DeafultIEDArray[0].InputSlot = 0;
		DeafultIEDArray[0].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		DeafultIEDArray[0].SemanticName = "POSITION";
		DeafultIEDArray[0].SemanticIndex = 0;

		DeafultIEDArray[1].AlignedByteOffset = 12;
		DeafultIEDArray[1].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
		DeafultIEDArray[1].InputSlot = 0;
		DeafultIEDArray[1].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		DeafultIEDArray[1].SemanticName = "COLOR";
		DeafultIEDArray[1].SemanticIndex = 0;

		DeafultIEDArray[2].AlignedByteOffset = 28;
		DeafultIEDArray[2].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
		DeafultIEDArray[2].InputSlot = 0;
		DeafultIEDArray[2].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		DeafultIEDArray[2].SemanticName = "TEXCOORD";
		DeafultIEDArray[2].SemanticIndex = 0;
	}
}

SMCollection::~SMCollection()
{
}
