#include "TitleScene.h"

void TitleScene::Init()
{
	//テクスチャ初期化
	m_titleTex.Load("Asset/Textures/title.png");
	m_startTex.Load("Asset/Textures/start.png");
}

void TitleScene::Update()
{
	m_alpha += m_alphaAdd;
	if (m_alpha > 1)
	{
		m_alpha = 1.0f;
		m_alphaAdd = -0.02f;
		//m_tadd *= -1;
	}

	//完全に透明にはしない(a値0.3くらいに調整)
	if (m_alpha < 0.3)
	{
		m_alpha = 0.3f;
		m_alphaAdd = 0.02f;
		//m_tadd *= -1;
	}
}

void TitleScene::Draw()
{
	//Shaderはマクロ定義されていた(1年)
	//SHADER.m_spriteShader.DrawTex();
	//2D描画はSetMatrixが不要(回転させるときはいる)
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, 0, 0);

	Math::Color col = { 1,1,1,m_alpha };

	//スタートボタン
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_startTex, 40, -200, nullptr, &col);
}

void TitleScene::Release()
{
	m_titleTex.Release();
	m_startTex.Release();
}
