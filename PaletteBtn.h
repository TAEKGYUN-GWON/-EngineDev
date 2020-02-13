#pragma once
#include "Object.h"

class PaletteBtn : public Object
{
private:
	//PhysicsBody* _physics;
	Sprite* _sprite;
	TAttribute _attribute;

	POINT _imgSize;
	bool _isObject;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetAttribute(TAttribute atribute) { _attribute = atribute; }
	void SetImageSize(POINT size) { _imgSize = size; }
	void SetIsObject(bool isObj) { _isObject = isObj; }

	TAttribute GetAttribute() { return _attribute; }
	POINT GetImageSize() { return _imgSize; }
	Sprite* GetSprite() { return _sprite; }
	bool GetIsObject() { return _isObject; }
	//PhysicsBody* GetPhysics() { return _physics; }
};

