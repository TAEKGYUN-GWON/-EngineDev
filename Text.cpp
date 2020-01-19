#include "stdafx.h"
#include "Text.h"

void Text::SetLayout()
{
	if (_layout) _layout->Release();
	_layout = Direct2D::GetInstance()->CreateTextLayout(_text, _fontName, _fontSize, _maxWidth, _maxHeight);
}

void Text::SetAnchor(ANCHORS anchor)
{
	switch (anchor)
	{
	case ANCHORS::LEFT_TOP:
		break;
	case ANCHORS::CENTER:
		_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;
	case ANCHORS::RIGHT_TOP:
		break;
	default:
		break;
	}
}

void Text::CreateText(wstring text, float fontSize, float maxWidth, float maxHeight, ColorF::Enum color, float alpha, wstring fontName, wstring localeName)
{
	_text = text;
	_fontName = fontName;
	_locale = localeName;
	_fontSize = fontSize;
	_maxWidth = maxWidth;
	_maxHeight = maxHeight;

	SetLayout();

	_trans = _object->GetTrans();
	_trans->SetScale(Vector2(maxWidth, maxHeight));

	Direct2D::GetInstance()->GetRenderTarger()->CreateSolidColorBrush(ColorF(color, alpha), &_brush);
}

void Text::Init()
{
	DrawComponent::Init();
}

void Text::Render()
{
	auto renderTarger = Direct2D::GetInstance()->GetRenderTarger();

	//Matrix3x3 trans = _trans->GetLocalToWorldMatrix();
	//if(_isCameraAffect) 
	//Matrix3x3 trans = { _object->GetTrans()->GetPos().x, 0, 0,
	//					0, _object->GetTrans()->GetPos().y, 0,
	//					0, 0, 1};

	//renderTarger->SetTransform(trans.To_D2D1_Matrix_3x2_F());
	renderTarger->SetTransform(Matrix3x2F::Identity());
	//renderTarger->DrawTextLayout(Point2F(_trans->GetPos().x, _trans->GetPos().y), _layout, _brush);

	renderTarger->DrawTextLayout(Point2F(_trans->GetPos().x, _trans->GetPos().y), _layout, _brush);
	//renderTarger->DrawTextLayout(Point2F(100, 100), _layout, _brush);
}
