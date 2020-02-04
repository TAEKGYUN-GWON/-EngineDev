#include "stdafx.h"
#include "Item.h"
#include "Potion.h"
#include "ItemScript.h"
Item::Item()
{

}

void Item::Init()
{
	Object::Init();
	_tag = "Item";
	_maxCount = 1;
	_price = 0;
	_followingMovement = 0;
	_image = AddComponent<Sprite>();
	_image->Init();
	_trans->SetScale(20, 20);
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 0, 0, false, true);
	
	AddComponent<ItemScript>();
}

void Item::Update()
{
	Object::Update();
	//if (_isDungeon)
		//부모를 통해 플레이어를 찾아 좌표를 받아옴
		FollowPlayer(SCENEMANAGER->GetNowScene()->GetChildFromName("Will")->GetTrans()->GetPos());

	if (!_isActive) Release();
}

void Item::Render()
{
	if (!_isActive)return;
	Object::Render();

}

void Item::Release()
{
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_physics->GetBody());
	Object::Release();
}

void Item::FollowPlayer(Vector2 playerPos)
{
	_followingMovement += 0.001f;

	_trans->SetPos(Vector2::Lerp(_trans->GetPos(), playerPos, _followingMovement));
	_physics->SetBodyPosition();
	_image->SetPosition(_trans->GetPos());
}
