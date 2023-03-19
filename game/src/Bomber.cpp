#include "Bomber.h"

Bomber::Bomber()
{
}

Bomber::~Bomber()
{
}

bool Bomber::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();
	ModelScale = 10.0f;

	return false;
}

void Bomber::SetBomb(Model model)
{
	BombModel = model;
}

void Bomber::SetRadar(Model model)
{
	RadarMirror.SetRadarModel(model, 3.0f);
}

void Bomber::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);
}

bool Bomber::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;
	RadarMirror.SetMirrorModel(GetModel(), ModelScale);
	RadarMirror.SetPlayer(ThePlayer);
	RadarMirror.BeginRun(camera);
	DropBombTimer.Set(GetRandomFloat(0.5f, 1.0f));

	return false;
}

void Bomber::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto bomb : Bombs)
	{
		bomb->Update(deltaTime);
	}

	if (Enabled)
	{
		DropBombTimer.Update(deltaTime);

		if (DropBombTimer.Elapsed())
		{
			DropBombTimer.Reset(GetRandomFloat(2.5f, 5.0f));
			DropABomb();
		}

		CheckPlayfieldSidesWarp(4.0f, 3.0f);
		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
		RadarMirror.PositionUpdate(Enabled, Position);
	}
	else
	{
		RadarMirror.EnabledUpdate(Enabled);
	}
}

void Bomber::Draw()
{
	Model3D::Draw();

	for (auto bomb : Bombs)
	{
		bomb->Draw();
	}

	RadarMirror.Draw();
}

void Bomber::Spawn(Vector2 position, float x)
{
	Enabled = true;
	Position = { position.x, position.y, 0 };
	Velocity.x = x;

	float min = 30;
	float max = 75;
	float yV = GetRandomFloat(min, max);

	if (GetRandomValue(0, 100) < 50)
	{
		Velocity.y = -yV;
	}
	else
	{
		Velocity.y = yV;
	}
}

void Bomber::DropABomb()
{
	size_t bombspawn = Bombs.size();
	bool newBomb = true;

	int bombcount = 0;

	for (auto bomb : Bombs)
	{
		if (!bomb->Enabled)
		{
			newBomb = false;
			bombspawn = (size_t)bombcount;
		}

		bombcount++;
	}

	if (newBomb)
	{
		Bombs.push_back(new Bomb());
		Bombs[Bombs.size() - 1]->Initialize();
		Bombs[Bombs.size() - 1]->SetModel(BombModel);
		Bombs[Bombs.size() - 1]->BeginRun(TheCamera);
	}

	Bombs[bombspawn]->Spawn(Position);
}