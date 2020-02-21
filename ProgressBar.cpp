#include "stdafx.h"
#include "ProgressBar.h"

void ProgressBar::Init()
{
}

void ProgressBar::Release()
{
}

void ProgressBar::Update()
{
}

// progress bar 만드는 중이였음
void ProgressBar::Render(string imgKey, Vector2 pos, Vector2 scale, float angle, float alpha, bool isCameraEffect)
{
	//Graphic* img = GRAPHICMANAGER->FindImage(imgKey);
	//
	//Matrix3x2F scale_ = Matrix3x2F::Scale(scale.x, scale.y);
	//Matrix3x2F rotation = Matrix3x2F::Rotation(angle, Point2F());
	//Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);
	//
	//D2D1_RECT_F dxArea = RectF(0, 0, img->GetFrameWidth() * scale.x, img->GetFrameHeight() * scale.y);
	//
	//
	//D2D1_RECT_F dxSrc = RectF(_graphicInfo->curFrameX * _graphicInfo->frameWidth, _graphicInfo->curFrameY * _graphicInfo->frameHeight,
	//	_graphicInfo->curFrameX * _graphicInfo->frameWidth + _graphicInfo->frameWidth,
	//	_graphicInfo->curFrameY * _graphicInfo->frameHeight + _graphicInfo->frameHeight);
	//
	//
	//ID2D1HwndRenderTarget* renderTarget = GRAPHICMANAGER->GetRenderTarget();
	//renderTarget->SetTransform(scale_ * rotation * trans);
	//if (isCameraEffect) renderTarget->SetTransform(scale_ * rotation * trans * CAMERA->GetMatrix());
	//renderTarget->DrawBitmap(img->GetBitmap(), &dxArea, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);
}
