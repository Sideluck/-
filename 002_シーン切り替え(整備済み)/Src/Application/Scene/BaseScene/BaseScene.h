#pragma once

class BaseScene
{
public:
	BaseScene() {};
	~BaseScene() {};

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

private:

};