#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(GridPainter);

class GridPainter : public ScriptComponent
{
public:
	GridPainter();
	virtual ~GridPainter();
	GridPainter(const GridPainter&) = delete;
	GridPainter& operator=(const GridPainter&) = delete;

public:
	void SetCellSize(UINT cellSize) { mCellSize = cellSize; }
	void SetCellCount(const XMUINT2& cellCount) { mCellCount = cellCount; }
	void SetColor(const Vector4& color) { mColor = color; }

	UINT GetCellSize() const { return mCellSize; }
	XMUINT2 GetCellCount() const { return mCellCount; }
	Vector4 GetColor() const { return mColor; }

	void TurnOnDraw()  { mbPaint = true; }
	void TurnOffDraw() { mbPaint = false; }

	bool IsTurnOnDraw() const { return mbPaint; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

private:
	UINT mCellSize;
	XMUINT2 mCellCount;
	Vector4 mColor;

	bool mbPaint;
};
