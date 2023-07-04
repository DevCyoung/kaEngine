#pragma once
#include "RenderComponent.h"

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

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	
	virtual void render(const Camera* const camera) override final;

	Vector4 mTestColor;
public:
	Vector4 testX;
	int bColorInfo;
};
