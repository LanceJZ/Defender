#include "Bomber.h"

Bomber::Bomber()
{
}

Bomber::~Bomber()
{
}

bool Bomber::Initialize()
{
	Enemy::Initialize();


	return false;
}

void Bomber::SetBomb(Model model)
{
	BombModel = model;
}

bool Bomber::BeginRun(Camera* camera)
{
	Enemy::BeginRun(camera);

	DropBombTimer.Set(GetRandomFloat(0.5f, 1.0f));

	return false;
}

void Bomber::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

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

		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
	}
}

void Bomber::Draw()
{
	Enemy::Draw();

	for (auto bomb : Bombs)
	{
		bomb->Draw();
	}
}

void Bomber::Spawn(Vector3 position, float x)
{
	Enemy::Spawn(position);

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
		Bombs[Bombs.size() - 1]->SetModel(BombModel, 15.0f);
		Bombs[Bombs.size() - 1]->BeginRun(TheCamera);
	}

	Bombs[bombspawn]->Spawn(Position);
}