#include "Bomber.h"

Bomber::Bomber()
{
}

Bomber::~Bomber()
{
}

void Bomber::SetBomb(Model model)
{
	BombModel = model;
}

void Bomber::SetRadar(Model model)
{
	Radar.TheModel = model;
}

void Bomber::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);
}

bool Bomber::Initialize()
{
	Model3D::Initialize();

	Radar.Initialize();
	Mirror.Initialize();
	ModelScale = 10;

	return false;
}

bool Bomber::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;
	Mirror.SetModel(TheModel, ModelScale);
	Mirror.BeginRun(camera);
	Radar.SetPlayer(ThePlayer);
	Radar.ModelScale = 3;
	Radar.BeginRun(camera);
	DropBombTimer->Set(GetRandomFloat(0.5f, 1.0f));

	return false;
}

void Bomber::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);

	for (auto bomb : Bombs)
	{
		bomb->Update(deltaTime);
	}

	DropBombTimer->Update(deltaTime);

	if (DropBombTimer->Elapsed())
	{
		DropBombTimer->Reset(GetRandomFloat(2.5, 5.0f));
		DropABomb();
	}

	CheckPlayfieldSidesWarp(4.0f, 3.0f);
	CheckPlayfieldHeightWarp(-0.15f, 1.0f);
	Mirror.PositionUpdate(Enabled, X(), Y());
}

void Bomber::Draw()
{
	Model3D::Draw();

	Radar.Draw();

	for (auto bomb : Bombs)
	{
		bomb->Draw();
	}

	Mirror.Draw();
}

void Bomber::Spawn(Vector2 position, float x)
{
	Enabled = true;
	Position = { position.x, position.y, 0 };

	Velocity.x = x;

	float min = 30;
	float max = 75;
	float yV = GetRandomFloat(min, max);

	if (GetRandomValue(0, 10) < 5)
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
		Bombs[Bombs.size() - 1]->TheModel = BombModel;
		Bombs[Bombs.size() - 1]->BeginRun(TheCamera);
	}

	Bombs[bombspawn]->Spawn(Position);
}