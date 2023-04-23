#include "EnemyShot.h"

EnemyShot::~EnemyShot()
{
}

bool EnemyShot::Initialize()
{
	Model3D::Initialize();

	Mirror.Initialize();

	Radius = 2;
	Enabled = false;

	return false;
}

void EnemyShot::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool EnemyShot::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Mirror.SetModel(GetModel(), ModelScale);
	Mirror.BeginRun(camera);

	return false;
}

void EnemyShot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	Mirror.EnabledUpdate(Enabled);

	if (Enabled)
	{
		LifeTimer.Update(deltaTime);

		if (LifeTimer.Elapsed())
		{
			Enabled = false;
			Position = { (float)GetScreenWidth() * 4.0f, (float)GetScreenHeight(), 0 };

		}

		if (ScreenEdgeBoundY(GetScreenHeight() * 0.15f, 0))
		{
			Enabled = false;
		}

		Mirror.PositionUpdate(Enabled, Position);
	}
}

void EnemyShot::Draw()
{
	Model3D::Draw();

	Mirror.Draw();
}

void EnemyShot::Spawn(Vector3 position, Vector3 velocity, float life)
{
	Enabled = true;
	LifeTimer.Reset(life);
	Position = position;
	Velocity = velocity;
	Mirror.PositionUpdate(Enabled, Position);
}

float EnemyShot::GetShotAngle(Vector3 position)
{
	float angle = 0;

	if (GetRandomValue(0, 100) > 50)
	{
		angle = AimedShot(position);
	}
	else
	{
		angle = GetRandomRadian();
	}

	return angle;
}

float EnemyShot::AimedShot(Vector3 position) //TODO: add aiming for other side when player near edge.
{
	float percentChance = GetRandomFloat(0.0f, 0.05f);

	Vector3 aimv = ThePlayer->Position;
	aimv.x += ThePlayer->Velocity.x;

	return AngleFromVectorZ(aimv) + GetRandomFloat(-percentChance, percentChance);
}
