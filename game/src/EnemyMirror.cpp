#include "EnemyMirror.h"

EnemyMirror::EnemyMirror()
{

}

EnemyMirror::~EnemyMirror()
{
}

bool EnemyMirror::Initialize()
{

	return false;
}

void EnemyMirror::SetModel(Model model, float scale)
{
	MirrorL.TheModel = model;
	MirrorL.ModelScale = scale;
	MirrorR.TheModel = model;
	MirrorR.ModelScale = scale;
}

bool EnemyMirror::BeginRun()
{

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

void EnemyMirror::PositionUpdate(bool enabled, float x, float y)
{
	X = x;
	float mirror = 7.0f;
	MirrorL.X(x - GetScreenWidth() * mirror);
	MirrorL.Y(y);
	MirrorL.Enabled = enabled;
	MirrorR.X(x + GetScreenWidth() * mirror);
	MirrorR.Y(y);
	MirrorR.Enabled = enabled;
}
