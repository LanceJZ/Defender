#include "EnemyShot.h"

EnemyShot::~EnemyShot()
{
}

void EnemyShot::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void EnemyShot::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool EnemyShot::Initialize()
{
	Model3D::Initialize();

	ModelScale = 3;
	Radius = 2;
	Enabled = false;

	return false;
}

bool EnemyShot::BeginRun()
{
	Mirror.SetModel(TheModel, ModelScale);

	return false;
}

void EnemyShot::Input()
{

}

void EnemyShot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (!Enabled)
		return;

	LifeTimer->Update(deltaTime);

	if (LifeTimer->Elapsed())
	{
		Enabled = false;
	}

	if (ScreenEdgeBoundY(GetScreenHeight() * 0.15f, 0))
	{
		Enabled = false;
	}

	Mirror.PositionUpdate(Enabled, X(), Y());
}

void EnemyShot::Draw()
{
	Model3D::Draw();

	Mirror.Draw();
}

void EnemyShot::Spawn(Vector3 position, Vector3 velocity, float life)
{
	Enabled = true;
	LifeTimer->Reset(life);
	Position = position;
	Velocity = velocity;
	Mirror.PositionUpdate(Enabled, X(), Y());
}

float EnemyShot::GetShotAngle(Vector3 position)
{
	float angle = 0;

	if (GetRandomValue(0, 10) > 1)
	{
		angle = AimedShot(position);
	}
	else
	{
		angle = GetRandomRadian();
	}

	return angle;
}

float EnemyShot::AimedShot(Vector3 position)
{
	float percentChance = GetRandomFloat(0.0f, 0.05f);

	Vector3 aimv = ThePlayer->Position;
	aimv.x += ThePlayer->Velocity.x;

	return AngleFromVectorZ(aimv) + GetRandomFloat(-percentChance, percentChance);
}
