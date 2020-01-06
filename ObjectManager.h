#pragma once
#include "singletonBase.h"
#include <unordered_map>
class ObjectManager : public singletonBase<ObjectManager>
{
	typedef unordered_map<string, vector<Object*>> mObjMgr; 
	typedef unordered_map<string, vector<Object*>>::iterator mObjMgrIter;
	typedef vector<Object*> vObjMgr;
	mObjMgr objMgr;
	vObjMgr allObject;
public:
	ObjectManager();
	~ObjectManager();
	HRESULT Init();
	void Release();
	void AddObject(string sceneName, Object* obj);
	void Update(string sceneName);
	void Render(string sceneName);
	vObjMgr GetSceneObject(string sceneName) { return objMgr.find(sceneName)->second; }
	vObjMgr GetAllObject() { return allObject; }
	
};

