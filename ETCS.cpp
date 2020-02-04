#include "stdafx.h"
#include "ETCS.h"
#include"ItemScript.h"

void Vine::Init(Vector2 pos)
{
	ETC::Init();

	_trans->SetPos(pos);
	_name = "vine";



	_image->SetImgName("Vine");

	_image->SetSize(Vector2(30, 30));
	_physics->SetBodyPosition();
}

void Crystal_Energy::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "crystal_Energy";

	_image->SetImgName("Crystal_Energy");
	_image->SetSize(Vector2(30, 30));
	_physics->SetBodyPosition();
}

void Treated_Wood::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "treated_Wood";
	_image->SetImgName("Treated_Wood");
	_image->SetSize(Vector2(30, 30));
	_physics->SetBodyPosition();
}

void amulet_ring::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "amulet_ring";
	_physics->SetBodyPosition();
	_image->SetImgName("Amulet_ring");
	_image->SetSize(Vector2(30, 30));
	
}

void Broken_Sword::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "broken_Sword";
	_physics->SetBodyPosition();
	_image->SetImgName("Broken_Sword");
	_image->SetSize(Vector2(30, 30));
}

void Energy_Crystal::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "energy_Crystal";
	_physics->SetBodyPosition();
	_image->SetImgName("Energy_Crystal");
	_image->SetSize(Vector2(30, 30));
}

void Naja_Note::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "naja_Note";
	_physics->SetBodyPosition();
	_image->SetImgName("Naja_Note");
	_image->SetSize(Vector2(30, 30));
}

void Reinforced_Steel_G::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "reinforced_Steel_G";
	_physics->SetBodyPosition();
	_image->SetImgName("Reinforced_Steel_G");
	_image->SetSize(Vector2(30, 30));
}

void Golem_Core::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "golem_Core";
	_physics->SetBodyPosition();
	_image->SetImgName("Golem_Core");
	_image->SetSize(Vector2(30, 30));

}

void Familiar_Egg::Init(Vector2 pos)

{
	super::Init();

	_trans->SetPos(pos);
	_name = "familiar_Egg";
	_physics->SetBodyPosition();
	_image->SetImgName("Familiar_Egg");
	_image->SetSize(Vector2(30, 30));
}

void Reinforced_Steel_Y::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos);
	_name = "reinforced_Steel_Y";
	_physics->SetBodyPosition();
	_image->SetImgName("Reinforced_Steel_Y");
	_image->SetSize(Vector2(30, 30));
}

void Golem_King_Design::Init(Vector2 pos)
{
	super::Init();

	_trans->SetPos(pos); 
	_name = "golem_King_Design";
	_physics->SetBodyPosition();
	_image->SetImgName("Golem_King_Design");
	_image->SetSize(Vector2(30, 30));
}
