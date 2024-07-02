#include "GameScene.h"

void GameScene::Update()
{
}

void GameScene::Draw()
{
	Math::Rectangle rc;

	rc = { 0,0,64,64 };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_playerTex, 0, 0,64,64,&rc);
}

void GameScene::Init()
{
	m_playerTex.Load("Asset/Textures/player.png");
}

void GameScene::Release()
{
	m_playerTex.Release();
}
