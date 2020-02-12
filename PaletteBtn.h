#pragma once
#include "Object.h"

class PaletteBtn : public Object
{
private:
	//PhysicsBody* _physics;
	Sprite* _sprite;
	TAttribute _attribute;

	POINT _imgSize;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetAttribute(TAttribute atribute) { _attribute = atribute; }
	void SetImageSize(POINT size) { _imgSize = size; }

	TAttribute GetAttribute() { return _attribute; }
	POINT GetImageSize() { return _imgSize; }
	Sprite* GetSprite() { return _sprite; }
	//PhysicsBody* GetPhysics() { return _physics; }
};

