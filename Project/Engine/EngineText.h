#pragma once
#include "RenderComponent.h"

REGISTER_COMPONENT_TYPE(EngineText);

#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

class EngineText : public RenderComponent
{
public:
	EngineText();
	virtual ~EngineText();
	EngineText(const EngineText&) = delete;
	EngineText& operator=(const EngineText&) = delete;

	void SetText(const std::wstring& text) { mText = text; }
	void SetPosition(const XMUINT2& position) { mPosition = position; }
	void SetScale(const float scale) { mScale = scale; }
	void SetColor(const XMUINT4& color) { mColor = color; }

	void TurnOnCamera() { mbCamera = true; }
	void TurnOffCamera() { mbCamera = false; }

	const std::wstring& GetText() const { return mText; }
	const XMUINT2& GetPosition() const { return mPosition; }
	const float GetScale() const { return mScale; }
	const XMUINT4& GetColor() const { return mColor; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	
	virtual void render(const Camera* const camera) override;

private:
	std::wstring mText;
	XMUINT2 mPosition;
	float mScale;
	XMUINT4 mColor;

	bool mbCamera;
};
