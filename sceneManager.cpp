#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"
#include "playGround.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

Scene* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	addScene("PG", new playGround);
	changeScene("PG");

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

Scene * sceneManager::addScene(string sceneName, Scene * scene)
{
	if(!scene) return nullptr;

	for (auto i : _mSceneList)
	{
		if (i.first == sceneName) return i.second;
	}
	cout << scene << endl;
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		//� ���� ������ ó���� ����ֱ� ������ ������ �������
		if (_currentScene) _currentScene->release();

		//���� ���� �ٲٷ��� ���� ��´�
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
