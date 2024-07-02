#pragma once

class Enemy:public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() {};

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void OnHit()override;

private:

	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	Math::Vector3 m_scale;

	//アニメーション
	float m_anim = 0;

	float m_hp = 0;

	//重力
	float m_gravity = 0;

	int m_dir = 1;
	float m_goal = 0;
	float m_speed = 0;
};