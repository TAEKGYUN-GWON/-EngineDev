#pragma once
#include"singletonBase.h"
class JsonManager : public singletonBase<JsonManager>
{

public:
	using document = rapidjson::Document;
	using sizeType = rapidjson::SizeType;
	using Value = rapidjson::Value;
	
};

