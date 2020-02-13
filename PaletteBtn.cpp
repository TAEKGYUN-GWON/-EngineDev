#include "stdafx.h"
#include "PaletteBtn.h"
//#include "PaletteBtnScript.h"

void PaletteBtn::Init()
{
	Object::Init();

	_sprite = AddComponent<Sprite>();
	_sprite->Init();
	_sprite->SetImgName(_name);
	_sprite->SetShowRect(false);

	_trans->SetScale(_sprite->GetFrameWidth(), _sprite->GetFrameHeight());

	//_physics = AddComponent<PhysicsBody>();
	//_physics->Init(BodyType::DYNAMIC, 1.0f);
	//_physics->SetSensor(true);

	_attribute = TAttribute::NONE;
	_isObject = false;

	_imgSize = { _sprite->GetFrameWidth(), _sprite->GetFrameHeight() };

	//AddComponent<PaletteBtnScript>();
}

void PaletteBtn::Release()
{
	Object::Release();

}

void PaletteBtn::Update()
{
	Object::Update();

	_sprite->SetPosition(_trans->GetPos());
}

void PaletteBtn::Render()
{
	Object::Render();

}
