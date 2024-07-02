#pragma once

class UI:public KdGameObject
{
public:
	UI() { Init(); }
	~UI(){}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

private:

	KdTexture m_hpTex;

	float m_hp = 100;

};