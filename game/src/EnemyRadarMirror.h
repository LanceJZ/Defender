#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Player.h"
#include "EnemyMirror.h"

class EnemyRadarMirror : public Model3D
{
public:
	EnemyRadarMirror();
	virtual ~EnemyRadarMirror();

	void SetRadarModel(Model model, float scale);
	void SetMirrorModel(Model model, float scale);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun(Camera* camera);
	void PositionUpdate(bool enabled, Vector3 position);
	void EnabledUpdate(bool enabled);
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Vector3 OrgPosition = { 0 };
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;
	EnemyMirror Mirrors;

	void UpdateRadar();
};