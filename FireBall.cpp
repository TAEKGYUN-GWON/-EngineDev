#include "stdafx.h"
#include "FireBall.h"
#include "Player.h"
#include "Enemy.h"
void FireBall::Init(Object* onwer)
{
	SkillObject::Init();
	_name = "FireBall";
	_onwer = onwer;
	_type = OnwerType::Player;
	_skillType = SkillType::One_time;
	_atk = 10;
	_trans->SetScale(60, 30);
	Player* player = (Player*)_onwer;
	_trans->SetPos(player->GetTrans()->GetPos() + Vector2(cosf(player->GetAtkAngle()), -sinf(player->GetAtkAngle())) * 4 *(player->GetTrans()->GetScale()));
	_trans->SetRotateToRadian(-player->GetAtkAngle());
	GRAPHICMANAGER->AddFrameImage("FireBall", L"Resource/Wizard/Skill/Fireball_0_5x1.png", 5, 1);
	_sprite = AddComponent<Sprite>();
	//_sprite->SetScale(Vector2(1.3, 1.3));
	_sprite->Init(true, true);
	_sprite->SetImgName("FireBall");
	_sprite->SetFPS(3);
	_timer = 0;
	_maxTimer = 0.7f;
	_speed = 500;
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	//_physics->GetBody()->SetTransform(b2Vec2(_physics->GetBody()->GetPosition().x, _physics->GetBody()->GetPosition().y), _trans->GetRotateRadian());
	//_physics->SetBodyActive(false);
	_physics->GetBody()->SetTransform(_physics->GetBody()->GetPosition(),-player->GetAtkAngle());
	_physics->GetBody()->SetFixedRotation(true);
	_moveAngle = player->GetAtkAngle();
}

void FireBall::Move()
{
	_timer += TIMEMANAGER->getElapsedTime();
	if (_timer >= _maxTimer)SetIsRelese();
	_trans->Move(Vector2(cosf(_moveAngle), -sinf(_moveAngle)) * _speed * TIMEMANAGER->getElapsedTime());
	_physics->SetBodyPosition();
	_sprite->SetPosition(_trans->GetPos());

}
