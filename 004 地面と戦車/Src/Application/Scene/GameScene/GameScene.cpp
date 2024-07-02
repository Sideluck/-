#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Characters/Tank/Tank.h"
#include"../../GameObject/Grounds/Ground/Ground.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	//カメラの追加
	std::shared_ptr<TPSCamera> camera;
	camera = std::make_shared<TPSCamera>();
	//ベース経由のクラスは呼ぼう
	camera->Init();
	m_objList.push_back(camera);

	//戦車
	std::shared_ptr<Tank> tank;
	tank = std::make_shared<Tank>();
	m_objList.push_back(tank);

	//地面
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	m_objList.push_back(ground);
}
