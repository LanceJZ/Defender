#pragma once
#include "Model3D.h"
#include "Timer.h"

class PlayerShot : public Model3D
{
public:
	PlayerShot();
	virtual ~PlayerShot();

	bool Initialize();
	void SetTailModel(Model model);
	virtual void Load();
	bool BeginRun(Camera* camera);

	void spawn(Vector3 position, Vector3 velocity, bool reverse);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Timer* LifeTimer;
	Model3D* Tail;

};

