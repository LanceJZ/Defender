#include "Player.h"

Player::Player()
{
	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new PlayerShot();
	}
}

Player::~Player()
{
}

bool Player::Initialize()
{
	Model3D::Initialize();

	ModelScale = 2.0f;

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	return false;
}

void Player::SetCamera(Camera* camera)
{
	TheCamera = camera;
}

void Player::SetFlameModel(Model model, Texture2D texture)
{
	Flame.LoadModel(model, texture);
}

void Player::SetShotModels(Model model, Texture2D texture, Model tailModel, Texture2D tailTexture)
{
	for (auto shot : Shots)
	{
		shot->LoadModel(model, texture);
		shot->SetTailModel(tailModel, tailTexture);
	}
}

bool Player::BeginRun()
{
	Flame.ModelScale = 2.0f;
	Flame.Position.x = -80.0f;
	Flame.RotationVelocity = 50.0f;
	Flame.RotationAxis.x = 1.0f;
	AddChild(&Flame);

	for (auto shot : Shots)
	{
		shot->BeginRun();
	}

	return false;
}

void Player::Load()
{

}

void Player::Input()
{
	if (IsKeyDown(KEY_UP))
	{
		MoveUp();
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		MoveDown();
	}
	else
	{
		Horzfriction();
	}

	if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_SPACE)) // Fire.
	{
		Fire();
	}

	if (IsKeyDown(KEY_LEFT_SHIFT)) // Thrust.
	{
		if (FacingRight)
		{
			MoveRight();
		}
		else
		{
			MoveLeft();
		}
	}
	else
	{
		ThrustOff();
	}

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT)) // Flip player ship facing.
	{
		if (FacingRight)
		{
			Rotation = PI;
			RotationAxis.y = 1.0f;
			FacingRight = false;
		}
		else
		{
			Rotation = 0;
			RotationAxis.y = 1.0f;
			FacingRight = true;
		}
	}
}

void Player::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	Flame.Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	ScreenEdgeBoundY(GetScreenHeight() / 6, 0);
	CheckPlayfieldSidesWarp(4.0f, 3.0f);

	TheCamera->position.x = X();
	TheCamera->target.x = X();
}

void Player::Draw()
{
	Model3D::Draw();

	Flame.Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}
}

void Player::MoveUp()
{
	if (Velocity.y < HorzMaxSpeed)
	{
		Acceleration.y = HorzSpeed;
	}
	else
	{
		Acceleration.y = 0;
	}
}

void Player::MoveDown()
{
	if (Velocity.y > -HorzMaxSpeed)
	{
		Acceleration.y = -HorzSpeed;
	}
	else
	{
		Acceleration.y = 0;
	}
}

void Player::MoveLeft()
{
	if (Velocity.x > -MaxFowardV)
	{
		Acceleration.x = -HorzSpeed;
		Flame.Enabled = true;
	}
	else
	{
		Acceleration.x = 0;
	}
}

void Player::MoveRight()
{
	if (Velocity.x < MaxFowardV)
	{
		Acceleration.x = HorzSpeed;
		Flame.Enabled = true;
	}
	else
	{
		Acceleration.x = 0;
	}
}

void Player::Horzfriction()
{
		if (Velocity.y > 0)
		{
			Acceleration.y = -HorzSpeed / (HorzDrag / (Velocity.y * AirDrag));
		}
		else if (Velocity.y < 0)
		{
			Acceleration.y = HorzSpeed / (HorzDrag / -(Velocity.y * AirDrag));
		}
}

void Player::ThrustOff()
{
		if (Velocity.x > 0)
		{
			Acceleration.x = -ForwardAcceleration / (ForwardDrag / (Velocity.x * AirDrag));
		}
		else if (Velocity.x < 0)
		{
			Acceleration.x = ForwardAcceleration / (ForwardDrag / -(Velocity.x * AirDrag));
		}

		Flame.Enabled = false;
}

void Player::Fire()
{
	for (auto shot : Shots)
	{
		if (!shot->Enabled)
		{
			shot->spawn(Position, Velocity, !FacingRight);
			return;
		}
	}
}
