#pragma once
#include "Component.h"

enum class eCollider2DType
{	
	Box = 1,
	Circle = 2,

	BoxCircle = Box | Circle,	
};

class Collider2D : public Component
{
	friend class CollisionManagement2D;
public:
	Collider2D(const eComponentType componentType, 
		const eCollider2DType mColllider2DType);
	virtual ~Collider2D();
	Collider2D(const Collider2D&) = delete;
	Collider2D& operator=(const Collider2D&) = delete;

	eCollider2DType GetCollideType() const { return mColllider2DType; }
	const Matrix& GetColliderWorldMat() const { return mColliderWorldMat; }

	const Vector3& GetScale() const { return mScale; }
	const Vector3& GetOffset() const { return mOffset; }
	float GetRadius() const { return mRadius; }

	void SetScale(const Vector2& scale) { mScale = Vector3(scale.x, scale.y, 1.f); }
	void SetOffset(const Vector2& offset) { mOffset = Vector3(offset.x, offset.y, 0.f); }
	void SetRdius(const float radius) { mRadius = radius; }




private:
	virtual void OnCollisionEnter(Collider2D* other);
	virtual void OnCollisionStay(Collider2D* other);
	virtual void OnCollisionExit(Collider2D* other);
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;

protected:
	eCollider2DType mColllider2DType;
	Matrix mColliderWorldMat;	
	Vector3 mScale;
	Vector3 mOffset;
	UINT mCollisionCount;
	float mRadius;
};
