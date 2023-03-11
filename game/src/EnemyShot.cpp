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
	MirrorR = TheModel;
	MirrorL = TheModel;

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
}

void EnemyShot::Draw()
{
	Model3D::Draw();

	if (Enabled)
		DrawMirror(); //Add a common Mirror Update Method.
}

void EnemyShot::Spawn(Vector3 position, Vector3 velocity, float life)
{
	Enabled = true;
	LifeTimer->Reset(life);
	Position = position;
	Velocity = velocity;
}

void EnemyShot::DrawMirror()
{
	float mirror = 7.0f;
	float xmult = 2.75f;

	if (X() > GetScreenWidth() * xmult)
	{
		DrawModel(MirrorL, { X() - GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	}
	else if (X() < -GetScreenWidth() * xmult)
	{
		DrawModel(MirrorR, { X() + GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	}
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
