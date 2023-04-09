#include "Lander.h"

Lander::Lander()
{
	for (int i = 0; i < 10; i++)
	{
		People[i] = nullptr;
	}
}

Lander::~Lander()
{
	for (int i = 0; i < 10; i++)
	{
		People[i] = nullptr;
	}

	PersonTarget = nullptr;
	Explosion = nullptr;
}

bool Lander::Initialize()
{
	Enemy::Initialize();

	for (auto &shot : Shots)
	{
		shot.Initialize();
	}

	ShotTimer.Set(1);
	Radius = 14.0f;

	return false;
}

void Lander::SetShotModel(Model &model)
{
	for (auto &shot : Shots)
	{
		shot.SetModel(model, 3.0f);
	}
}

void Lander::SetPersonSound(Sound &person, Sound& dropped, Sound& mutate)
{
	PersonGrabbedSound = person;
	PersonDroppedSound = dropped;
	MutateSound = mutate;
}

bool Lander::BeginRun(Camera *camera)
{
	Enemy::BeginRun(camera);

	SetSoundVolume(PersonGrabbedSound, 0.5f);
	SetSoundVolume(PersonDroppedSound, 0.5f);

	return false;
}

void Lander::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (Enabled)
	{
		if (ShotTimer.Elapsed())
		{
			if (State != FoundPersonMan)
			{
				ShotTimer.Reset(GetRandomFloat(2.75f, 4.75f));
			}
			else
			{
				ShotTimer.Reset(GetRandomFloat(0.375f, 1.2175f));
			}

			FireShot();
		}

		if (State == GoingToGround)
		{
			GoToGround();
		}
		else if (State == Seek)
		{
			SeekPersonMan();
		}
		else if (State == FoundPersonMan)
		{
			FoundPersonManGoingDown();
		}
		else if (State == PickUpPersonMan)
		{
			GrabPersonMan();
		}
		else if (State == Mutate)
		{
			SpawnMutatant();
		}
	}
}

void Lander::Draw()
{
	Enemy::Draw();
}

void Lander::Spawn(Vector3 position)
{
	Enemy::Spawn(position);

	State = GoingToGround;
	ShotTimer.Reset(GetRandomFloat(1.1f, 1.75f));
	PersonTarget = nullptr;

	float velX = 0;

	if (GetRandomValue(0, 100) < 50)
	{
		velX = GetRandomFloat(30.0f, 60.0f);
	}
	else
	{
		velX = GetRandomFloat(-60.0f, -30.0f);
	}

	float velY = GetRandomFloat(-30.0f, -20.0f);
	Velocity = { velX, velY, 0 };
	GroundHoverY = GetRandomFloat(-20.0f, 80.0f);
}

void Lander::FireShot()
{
	Enemy::FireShot();

}

bool Lander::CheckCollision()
{
	if (Enemy::CheckCollision())
	{
		if (PersonTarget && State != Mutate && State != FoundPersonMan)
		{
			PersonTarget->Dropped();
			PlaySound(PersonDroppedSound);
		}
	}

	return false;
}

void Lander::Reset()
{
	Enemy::Reset();

	State = GoingToGround;
	PersonTarget = nullptr;
}

void Lander::Destroy()
{
	Enemy::Destroy();

	if (State == Mutate)
	{
		PlaySound(MutateSound);
	}
}

void Lander::GoToGround()
{
	if (Y() < (-GetScreenHeight() * 0.2f) + GroundHoverY)
	{
		State = Seek;
		Velocity.y = 0;
	}
}

void Lander::SeekPersonMan()
{
	for (auto person : People)
	{
		if (person->Enabled)
		{
			if (person->X() < X() + 25.0f && person->X() > X() - 25.0f)
			{
				if (person->State == Person::TargetedByLander || person->State != Person::OnGround)
					return;

				State = FoundPersonMan;
				ShotTimer.Reset(GetRandomFloat(0.275f, 0.4375f));
				Velocity.x = 0;
				Velocity.y = GetRandomFloat(-40.0f, -30.0f);
				PersonTarget = person;
				person->State = Person::TargetedByLander;
				return;
			}
		}
	}
}

void Lander::FoundPersonManGoingDown()
{
	if (X() != PersonTarget->X())
	{
		if (X() > PersonTarget->X())
		{
			Velocity.x = -10.0f;
		}
		else if (X() < PersonTarget->X())
		{
			Velocity.x = 10.0f;
		}
		else if (X() == PersonTarget->X())
		{
			Velocity.x = 0;
		}
	}

	if (Y() + 25 > PersonTarget->Y() && Y() - 25 < PersonTarget->Y())
	{
		PlaySound(PersonGrabbedSound);
		State = PickUpPersonMan;
		Velocity.y = GetRandomFloat(40, 60);
		Velocity.x = 0;
	}
}

void Lander::GrabPersonMan()
{
	if (Y() > GetScreenHeight() * 0.333f)
	{
		State = Mutate;
		return;
	}

	PersonTarget->Y(Y() -25.0f);
}

void Lander::SpawnMutatant()
{
	Velocity.y = 0;
	PersonTarget->Destroy();
	MutateLander = true;
	Enemy::Reset();
}