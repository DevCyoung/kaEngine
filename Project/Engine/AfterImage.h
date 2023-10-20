#pragma once
#include "RenderComponent.h"
#include "StructBuffer.h"
#include "Texture.h"
#include "Animator2D.h"

REGISTER_COMPONENT_TYPE(AfterImage);

class AfterImage : public RenderComponent
{
public:
	struct tAfterImageInfo
	{
		tCBTransform CBTransform;
		tCBAnimationInfo CBAnimationInfo;
		Texture* texture;		
		float CurTime;
		float MaxTime;
		float Alpha;
		int colorType;
	};

public:
	AfterImage();
	virtual ~AfterImage();
	AfterImage(const AfterImage&) = delete;
	AfterImage& operator=(const AfterImage&) = delete;

	//void AddAfterImageByAnimation();

	void SetCreateDeltaTime(const float deltaTime) { mCreateDeltaTime = deltaTime; }
	void SetAlphaTime(const float alphaTime) { mAlphaTime = alphaTime; }
	void SetAlphaMaxTime(const float alphaMaxTime) { mAlphaMaxTime = alphaMaxTime; }


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


	// RenderComponent을(를) 통해 상속됨
	virtual void render(const Camera* const camera) override;

	std::vector<tAfterImageInfo> afters;	
	tCBColorInfo mCBColorInfo;

	Animator2D* mAnimator;
	float mCreateDeltaTime;
	float mCurTime;
	float mAlphaTime;
	float mAlphaMaxTime;
	float mAlphaSpeed;
	int colorType;
	int count;
};
