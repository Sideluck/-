#pragma once

class GameScene
{
public:
	GameScene() { Init(); };
	~GameScene() { Release(); };

	void Update();
	void Draw();

private:
	void Init();
	void Release();

	KdTexture m_playerTex;
};