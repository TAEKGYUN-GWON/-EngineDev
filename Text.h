#pragma once
#include "DrawComponent.h"

enum class ANCHORS
{
	LEFT_TOP,
	CENTER,
	RIGHT_TOP,
};

class Transform;

class Text : public DrawComponent
{
private:

	wstring _text;
	wstring _fontName;
	wstring _locale;
	float _fontSize;
	float _maxWidth;
	float _maxHeight;
	IDWriteTextLayout* _layout;
	ID2D1SolidColorBrush* _brush;

private:
	void SetLayout();

public:
	void CreateText(wstring text, float fontSize, float maxWidth, float maxHeight, ColorF::Enum color = ColorF::Black, float alpha = 1.0f, wstring fontName = L"µ¸¿ò", wstring localeName = L"ko");
	void SetAnchor(ANCHORS anchor);

	virtual void Init();
	virtual void Render();
};

