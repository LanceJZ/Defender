#include "EnemyMirror.h"

EnemyMirror::EnemyMirror()
{
}

EnemyMirror::~EnemyMirror()
{
}

bool EnemyMirror::Initialize()
{
	MirrorL.Initialize();
	MirrorR.Initialize();

	return false;
}

void EnemyMirror::SetModel(Model model, float scale)
{
	MirrorL.SetModel(model, scale);
	MirrorR.SetModel(model, scale);
}

bool EnemyMirror::BeginRun(Camera* camera)
{
	MirrorL.BeginRun(camera);
	MirrorR.BeginRun(camera);

	return false;
}

void EnemyMirror::Update(float deltaTime)
{

}

void EnemyMirror::Draw()
{
	float xmult = 2.75f;

	if (X > GetScreenWidth() * xmult)
	{
		MirrorL.Draw();
	}
	else if (X < -GetScreenWidth() * xmult)
	{
		MirrorR.Draw();
	}

}

void EnemyMirror::PositionUpdate(bool enabled, Vector3 position)
{
	X = position.x;
	float mirror = 7.0f;
	MirrorL.X(position.x - GetScreenWidth() * mirror);
	MirrorL.Position.y = position.y;
	MirrorL.Enabled = enabled;
	MirrorR.X(position.x + GetScreenWidth() * mirror);
	MirrorR.Position.y = position.y;
	MirrorR.Enabled = enabled;
}

void EnemyMirror::EnabledUpdate(bool enabled)
{
	MirrorL.Enabled = enabled;
	MirrorR.Enabled = enabled;
}

void EnemyMirror::DeleteModels()
{
	UnloadModel(MirrorL.GetModel());
	UnloadModel(MirrorR.GetModel());
}
