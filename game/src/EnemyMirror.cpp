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
	Xmult = GetScreenWidth() * 2.75f;
	MirrorMult = GetScreenWidth() * 7.0f;
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
	if (X > Xmult)
	{
		MirrorL.Draw();
	}
	else if (X < -Xmult)
	{
		MirrorR.Draw();
	}

}

void EnemyMirror::PositionUpdate(bool enabled, Vector3 position)
{
	X = position.x;
	MirrorL.X(position.x - MirrorMult);
	MirrorL.Position.y = position.y;
	MirrorL.Enabled = enabled;
	MirrorR.X(position.x + MirrorMult);
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
