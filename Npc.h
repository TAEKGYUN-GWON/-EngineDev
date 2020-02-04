#pragma once
#include "Object.h"
//#include "ShopStand.h"
#include "ShopStandManager.h"
#include "CheckStand.h"
#include "Sprite.h"
#define NPDSPEED 70

class ShopStandManager;
class CheckStand;
class NpcShopState;

//이제 어디로 가고싶은지(destination이랑 다름)
enum NPCTHOUGHT
{
	WINDOW,//창문에 가고싶음
	CHOOSE,
	GOHOME, //집에가고싶음
	BUY, //사고싶음(줄서고싶음)
	NOTBUY, //안사고싶음
	END
};

//현재 어디 있는지
enum NPCNOWPOSITION
{
	POS_ENTER,
	POS_WINDOW,
	POS_STAND1,
	POS_STAND2,
	POS_STAND3,
	POS_STAND4,
	POS_CHECKSTAND,
	POS_DOOR,
	POS_END
};

class Npc :	public Object
{
private:
	Sprite* _sprite;

	NPCTHOUGHT _npcThought; //머해야할지..
	NPCNOWPOSITION _npcNowPosition;

	float _timer;

	//float _speed;
	bool _isShopSOn;	//가판대랑 충돌중인지
	bool _isCheckSOn;	//계산대랑 충돌중인지

	bool _isAstarOn;	//astar 받아야하는 상태인지

	NpcShopState* _npcShopState;

	//ShopStand* _shopStand; //스탠드를 가져야될지 매니저를 가져야될지 모르겠음
	ShopStandManager* _shopStandMgr;
	CheckStand* _checkStand;

	list<Vector2> _lPath; //가야하는 길

public:
	Npc() {};
	~Npc() {};

	virtual void Init(string imgkey, Vector2 pos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetPath(list<Vector2> lpath);
	void Move();

	NpcShopState* GetNpcState() { return _npcShopState; }

	
	//상태 정의용
	void ChangeState(NpcShopState* state);

	//계산대/판매대 링크용
	void SetCheckStandLink(CheckStand* checkstand) { _checkStand = checkstand; }
	CheckStand* GetCheckStand() { return _checkStand; }
	void SetShopStandLink(ShopStandManager* shopstand) { _shopStandMgr = shopstand; }
	ShopStandManager* GetShopStandMgr() { return _shopStandMgr; }

	//계산대랑 가판대랑 충돌중ING인지 체크할 bool
	void SetIsShopSOn(bool shop) { _isShopSOn = shop; }
	bool GetIsShopSOn() { return _isShopSOn; }
	void SetIsCheckSOn(bool check) { _isCheckSOn = check; }
	bool GetIsCheckSOn() { return _isCheckSOn; }
	void SetIsAstarOn(bool ast) { _isAstarOn = ast; }
	bool GetIsAstarOn() { return _isAstarOn; }

	//NPC 이제 뭐하고싶은 상태인지..
	void SetNpcThought(NPCTHOUGHT npcthought) { _npcThought = npcthought; }
	NPCTHOUGHT GetNpcThought() { return _npcThought; }
	//위치 뭔지
	void SetNpcNowPosition(NPCNOWPOSITION npcnowposition) { _npcNowPosition = npcnowposition; }
	NPCNOWPOSITION GetNpcNowPosition() { return _npcNowPosition; }

	NpcShopState* GetStatePointer() { return _npcShopState; }
	list<Vector2>* GetPath() { return &_lPath; }


};