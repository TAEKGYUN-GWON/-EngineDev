#pragma once
#include "Object.h"

class PaletteBtn : public Object
{
private:
	//PhysicsBody* _physics;
	Sprite* _sprite;
	TAttribute _attribute;
	string _imgKey;

	bool _isObject;
	POINT _imgSize;

public:
	PaletteBtn() : _imgKey("None") {}
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetAttribute(TAttribute atribute) { _attribute = atribute; }
	void SetImageSize(POINT size) { _imgSize = size; }
	void SetIsObject(bool isObj) { _isObject = isObj; }
	void SetImageKey(string imgKey) { _imgKey = imgKey; }

	TAttribute GetAttribute() { return _attribute; }
	POINT GetImageSize() { return _imgSize; }
	Sprite* GetSprite() { return _sprite; }
	string GetImageKey() { return _imgKey; }
	bool GetIsObject() { return _isObject; }

	//PhysicsBody* GetPhysics() { return _physics; }
};

