#pragma once
#include "Component.h"

class Draw : public Component
{
private:
	vector<Component> _vRenderList;

public:
	virtual void Render() {};
};

