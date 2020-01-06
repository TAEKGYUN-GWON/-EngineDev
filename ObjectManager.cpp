#include "stdafx.h"
#include "ObjectManager.h"
#include"Object.h"

ObjectManager::ObjectManager()
{

}


ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::Init()
{
	return S_OK;
}

void ObjectManager::Release(string sceneName)
{
	mObjMgrIter iter = objMgr.find(sceneName);
	for (int i = iter->second.size() - 1; i <= 0; i--)
	{
		SAFE_OBJECT_RELEASE(iter->second[i]);
	}
	iter->second.clear();
}


void ObjectManager::AddObject(string sceneName, Object * obj)
{
	//objMgr ����� 0�̶�� ���� ���� �־��ֱ�
	if (!objMgr.size())
	{
		vObjMgr a;
		a.push_back(obj);
		allObject.push_back(obj);
		objMgr.insert(make_pair(sceneName, a));
		return;
	}

	mObjMgrIter iter = objMgr.find(sceneName);

	if (iter != objMgr.end())
	{
		for (Object* i : iter->second)
			if (i == obj)return;

		iter->second.push_back(obj);
		allObject.push_back(obj);
		return;
	}
	else return;
	//�ش� ���� �������� �ʴ´ٸ� ���� ���� �ʿ� �߰�

	vObjMgr a;
	a.push_back(obj);
	allObject.push_back(obj);
	objMgr.insert(make_pair(sceneName, a));
}

void ObjectManager::Update(string sceneName)
{
	vObjMgr vSceneObjec;
	mObjMgrIter iter = objMgr.find(sceneName);

	vSceneObjec = iter->second;

	if (iter == objMgr.end()) return;

	for (Object* i : vSceneObjec)
	{
		if(i->GetAllawsUpdate())
			i->Update();
	}

}

void ObjectManager::Render(string sceneName)
{
	vObjMgr vSceneObjec;
	mObjMgrIter iter = objMgr.find(sceneName);

	vSceneObjec = iter->second;

	if (iter == objMgr.end()) return;

	for (Object* i : vSceneObjec)
		i->Render();
}
