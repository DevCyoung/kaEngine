#pragma once
#include "RenderComponent.h"
#include "StructBuffer.h"

REGISTER_COMPONENT_TYPE(SpriteRenderer);

class Mesh;
class Material;
class Texture;

class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	void SetTestColor(const Vector4& color) { mTestColor = color; }
	
	const Vector4& GetTestColor() const { return mTestColor; }

	void SetUvOffsetX(float uvOffsetX);

	void SetColorR(float r);
	void SetColorG(float g);
	void SetColorB(float b);
	void SetColorA(float a);	
	void SetColorReset();

	void MulColorR(float r);
	void MulColorG(float g);
	void MulColorB(float b);
	void MulColorA(float a);	
	void MulColorReset();



private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	
	virtual void render(const Camera* const camera) override final;

	Vector4 mTestColor;
public:	
	Vector4 testX;	
	tSprite2DInfo mSprite2DInfo;
	int bColorInfo;
	float mUvOffsetX;
};
