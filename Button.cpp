#include "stdafx.h"
#include "Button.h"

void Button::Init()
{
	Object::Init();

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true);
}

void Button::Release()
{
	Object::Release();

}

void Button::Update()
{
	Object::Update();

	if (PtInRect(&_trans->GetRect(), MOUSEPOINTER->GetMouseWorldPosition().Vector2ToPOINT()))
	{
		if (_leftBtnDown) _dir = BtnDir::Down;
		else if (not _leftBtnDown and _dir == BtnDir::Down)
		{
			_dir = BtnDir::Up;
			if (_callback != nullptr) _callback();
			else if (_obj != nullptr) _callbackParameter(_obj);
		}
		else _dir = BtnDir::PlaceOn;
	}
	else _dir = BtnDir::None;
}

void Button::Render()
{
	Object::Render();

	switch (_dir)
	{
	case BtnDir::Up : case BtnDir::None :
		_sprite->GetGraphic()->FrameRender(_trans->GetPos(), _upFrame.x, _upFrame.y, _sprite->GetScale(), 0.0f, false, 1.0f, PIVOT::CENTER, false);
		break;
	case BtnDir::Down :
		_sprite->GetGraphic()->FrameRender(_trans->GetPos(), _downFrame.x, _downFrame.y, _sprite->GetScale(), 0.0f, false, 1.0f, PIVOT::CENTER, false);
		break;
	case BtnDir::PlaceOn:
		_sprite->GetGraphic()->FrameRender(_trans->GetPos(), _upFrame.x, _upFrame.y, _sprite->GetScale(), 0.0f, false, 1.0f, PIVOT::CENTER, false);
		GRAPHICMANAGER->DrawFillRect(_trans->GetPos(), _trans->GetScale(), 0.0f, _hangOnColor);
		break;
	}
}

void Button::Setting(string imgKey, Vector2 pos, POINT up, POINT down, Callback_Function cb)
{
	Object::Init();

	_callback = static_cast<Callback_Function>(cb);
	_callbackParameter = nullptr;
	_dir = BtnDir::None;

	_obj = nullptr;

	_trans->SetPos(pos);

	_upFrame = up;
	_downFrame = down;

	_sprite->SetImgName(imgKey);

	_trans->SetScale(_sprite->GetFrameWidth() * _sprite->GetScale().x, _sprite->GetFrameHeight() * _sprite->GetScale().y);
}

void Button::Setting(string imgKey, Vector2 pos, POINT up, POINT down, Callback_Function_Parameter cbp, void* obj)
{
	Object::Init();

	_callback = nullptr;
	_callbackParameter = static_cast<Callback_Function_Parameter>(cbp);
	_dir = BtnDir::None;

	_obj = obj;

	_trans->SetPos(pos);

	_upFrame = up;
	_downFrame = down;

	_sprite->SetImgName(imgKey);

	_trans->SetScale(_sprite->GetFrameWidth() * _sprite->GetScale().x, _sprite->GetFrameHeight() * _sprite->GetScale().y);
}

void Button::SetScale(Vector2 scale)
{
	_sprite->SetScale(scale);
	_trans->SetScale(_sprite->GetFrameWidth() * _sprite->GetScale().x, _sprite->GetFrameHeight() * _sprite->GetScale().y);
}
