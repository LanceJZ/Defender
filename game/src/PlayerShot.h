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
	bool BeginRun(Camera* camera);

	void spawn(Vector3 position, Vector3 velocity, bool reverse);

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Timer* LifeTimer = new Timer();
	Model3D* Tail = new Model3D();
};

