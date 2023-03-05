#include "Lander.h"

Lander::Lander()
{
	ThePlayer = nullptr;
	TheCamera = nullptr;
	ShotTimer = new Timer();

	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new EnemyShot();
	}
}

Lander::~Lander()
{
}

void Lander::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Lander::SetShotModel(Model model, Texture2D texture)
{
	for (auto shot : Shots)
	{
		shot->SetModel(model, texture);
	}
}

void Lander::SetRadarModel(Model model, Texture2D texture)
{
	Radar.SetModel(model, texture);
}

void Lander::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);
}

void Lander::SetCamera(Camera* camera)
{
	TheCamera = camera;
	Radar.SetCamera(camera);
}

bool Lander::Initialize()
{
	Model3D::Initialize();
	Radar.Initialize();

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	ShotTimer->Set(1);
	ModelScale = 14;
	Radius = 14;

	return false;
}

bool Lander::BeginRun()
{
	for (auto shot : Shots)
	{
		shot->BeginRun();
	}

	Radar.BeginRun();

	MirrorL.TheModel = TheModel;
	MirrorL.ModelScale = ModelScale;
	MirrorR.TheModel = TheModel;
	MirrorR.ModelScale = ModelScale;
	Radar.ModelScale = 2;

	return false;
}

void Lander::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	ShotTimer->Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	if (ShotTimer->Elapsed())
	{
		ShotTimer->Reset();
		FireShot();
	}

	if (GoToGroundMode)
	{
		if (Y() < (-GetScreenHeight() * 0.2f) + GroundHoverY)
		{
			Velocity.y = 0;
			SeekMode = true;
			GoToGroundMode = false;
		}
	}

	CheckPlayfieldSidesWarp(4.0f, 3.0f);
	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);
	MirrorUpdate();
}

void Lander::Draw()
{
	Model3D::Draw();

	MirrorL.Draw();
	MirrorR.Draw();
	Radar.Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}
}

void Lander::Spawn(Vector3 position)
{
	Enabled = true;
	SeekMode = false;
	Position = position;
	ShotTimer->Reset(GetRandomFloat(1.1f, 1.75f));

	float velX = 0;

	if (GetRandomValue(0, 10) < 5)
	{
		velX = GetRandomFloat(30, 60);
	}
	else
	{
		velX = GetRandomFloat(-60, -30);
	}

	float velY = GetRandomFloat(-30, -20);
	Velocity = { velX, velY, 0 };
	GroundHoverY = GetRandomFloat(-20, 80);
}

void Lander::FireShot()
{
	float angle = 0;

	if (GetRandomValue(0, 10) < 5)
	{
		angle = AimedShot();
	}
	else
	{
		angle = GetRandomRadian();
	}


	if (!Shots[0]->Enabled)
	{
		Shots[0]->Spawn(Position, VelocityFromAngleZ(angle, 125.0f), 8.0f);
	}
}

void Lander::FireShots() //When Lander lowers to grab human, shoots four at a time, four times as rapid.
{

}

float Lander::AimedShot()
{
	float percentChance = GetRandomFloat(0.0f, 0.075f);

	Vector3 aimv = ThePlayer->Position;
	aimv.x += ThePlayer->Velocity.x;

	return AngleFromVectorZ(aimv) + GetRandomFloat(-percentChance, percentChance);
}

void Lander::MirrorUpdate()
{
	float mirror = 7.0f;
	MirrorL.X(X() - GetScreenWidth() * mirror);
	MirrorL.Y(Y());
	MirrorL.Enabled = Enabled;
	MirrorR.X(X() + GetScreenWidth() * mirror);
	MirrorR.Y(Y());
	MirrorR.Enabled = Enabled;
}
