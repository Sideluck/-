#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Stage/Stage.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Cannon/Cannon.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/UI/UI.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//プレイヤーの座標が必要
	//①オブジェクトリストからプレイヤー情報を取得
	//②プレイヤー情報はゲームシーンが持っておく
	//今回は②で実装
	Math::Vector3 playerPos;
	//m_playerに代入されているアドレス先はまだありますか？
	//expired 有効期限
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}

	Math::Matrix transMat;
	Math::Vector3 cameraPos = { 2.0f,1.5f,-5.0f };
	transMat = Math::Matrix::CreateTranslation(cameraPos + playerPos);
	m_camera->SetCameraMatrix(transMat);

	//被写界深度
	//m_camera->SetFocus(5, 2, 8);

	//ブルーム
	//KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7);
}

void GameScene::Init()
{
	//カメラ実体化
	// unique_ptr コピー不可能
	m_camera = std::make_unique<KdCamera>();

//影の方向を変えたいときは触る
//平行光(ディレクショナルライト)								      方向      色
	//KdShaderManager::Instance().WorkAmbientController().SetDirLight({0,-1,0.1f}, {3,3,3});
//画面全体が暗いときに触る
//環境光(アンビエントライト)
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1,1,1,1});
//フォグ(霧)
	//KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false,true);
	//距離フォグ														霧の色     密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.05f);
	//高さフォグ														霧の色     上 下 カメラとの距離
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 0,-2,0);

	
//ステージ
	//ポインタの作成
	std::shared_ptr<Stage> stage;
	for (int i = 0; i < 5; i++)
	{
		//ステージクラスを実体化
		stage = std::make_shared<Stage>();

		//縦に5つ
		stage->SetPos({ 0, -2.0f + 5.0f * i ,0});
		//オブジェクトリストに登録
		m_objList.push_back(stage);
	}

	for (int i = 0; i < 5; i++)
	{
		//奥に3つ
		stage = std::make_shared<Stage>();

		stage->SetPos({ 0, -2.0f ,3.0f * i });
		m_objList.push_back(stage);
	}

//プレイヤー

	std::shared_ptr<Player> player;

	player = std::make_shared<Player>();

	m_objList.push_back(player);

	m_player = player;

//大砲
	std::shared_ptr<Cannon> cannon;

	cannon = std::make_shared<Cannon>();

	m_objList.push_back(cannon);

//背景
	std::shared_ptr<Back> back;

	back = std::make_shared<Back>();

	m_objList.push_back(back);

//敵
	std::shared_ptr<Enemy> enemy;

	for (int i = 0; i < 5; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->SetPos({ -25.0f + i, 0 ,0});
		m_objList.push_back(enemy);
	}

//UI
	std::shared_ptr<UI> ui;

	ui = std::make_shared<UI>();

	m_objList.push_back(ui);
}
