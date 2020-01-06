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

void ObjectManager::Release()
{
	if (!objMgr.size()) return;

	mObjMgrIter iter = objMgr.begin();
	for (;iter != objMgr.end();++iter)
	{
		for (int j = iter->second.size()-1; j >= 0; j--)
		{
			iter->second[j]->Release();
		}
		objMgr.erase(iter);
	}
	objMgr.clear();
	allObject.clear();
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
