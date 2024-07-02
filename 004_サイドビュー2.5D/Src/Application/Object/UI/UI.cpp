#include "UI.h"

void UI::Init()
{
	m_hpTex.Load("Asset/Textures/HPBer.png");
}

void UI::Update()
{
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_hp += 1;
		if (m_hp > 100)
		{
			m_hp = 100;
		}
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_hp -= 1;
		if (m_hp < 0)
		{
			m_hp = 0;
		}
	}
}

void UI::DrawSprite()
{
	//SetMatrixはしない
	//回転させたい場合のみOK

	//テクスチャの幅を取得
	int w = m_hpTex.GetWidth();
	//HPが1の時、幅はいくつにしたらいいか
	float singlew = w / 100.0f;

	Math::Rectangle rc = { 0,0,long(singlew * m_hp),(long)m_hpTex.GetHeight() };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_hpTex,-600,300,rc.width,rc.height,&rc,nullptr,{0,0.5f});
}
