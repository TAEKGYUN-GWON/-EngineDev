#include "stdafx.h"
#include "ProgressBar.h"

void ProgressBar::Init(Vector2 pos, string key)
{
	this->pos = pos;
	_progressBar = GRAPHICMANAGER->FindImage(key);
	_width = _progressBar->GetFrameWidth();
}

void ProgressBar::Release()
{
}

void ProgressBar::Update()
{
}

void ProgressBar::Render()
{
	//progressBar->Render(pos,1,PIVOT::LEFT_TOP,false);
	_progressBar->FrameRender(pos,0,1,1,PIVOT::LEFT_TOP,false);
}

void ProgressBar::SetGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBar->GetFrameWidth();
}
