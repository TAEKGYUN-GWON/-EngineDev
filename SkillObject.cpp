#include "stdafx.h"
#include "SkillObject.h"

void SkillObject::Init()
{
	Object::Init();
	_tag = "Skill";
}

void SkillObject::Update()
{
	Object::Update();
	Move();
}
