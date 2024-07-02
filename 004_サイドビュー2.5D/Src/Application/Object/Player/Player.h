#pragma once


class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player(){}

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

private:

	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;

	//アニメーション
	float m_anim = 0;

	//重力
	float m_gravity = 0;

	bool keyFlg = false;
	int jumpCount = 0;
	const int maxJumpCount = 2;
};