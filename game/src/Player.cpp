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

	Radius = 13.0f;
	Cull = false;
	Flame.Cull = false;
	Radar.Cull = false;
	ModelScale = 2.0f;
	RotationY = (PI * 2) - 0.045f;

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	NewWaveReset();

	return false;
}

void Player::SetModel(Model model)
{
	Model3D::SetModel(model);
}

void Player::SetFlameModel(Model model)
{
	Flame.SetModel(model);
}

void Player::SetShotModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->SetModel(model);
	}
}

void Player::SetTailModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->SetTailModel(model);
	}
}

void Player::SetRadarModel(Model model)
{
	Radar.SetModel(model);
}

bool Player::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;
	Flame.ModelScale = 2.0f;
	Flame.Position.x = -80.0f;
	Flame.RotationVelocity = 50.0f;
	Flame.RotationAxis.x = 1.0f;
	Flame.BeginRun(camera);
	AddChild(&Flame);

	Radar.ModelScale = 10;
	Radar.BeginRun(camera);

	for (auto shot : Shots)
	{
		shot->BeginRun(camera);
	}

	return false;
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

	if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_SPACE))
	{
		Fire();
	}

	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		Thrust();
	}
	else
	{
		ThrustOff();
	}

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT))
	{
		Reverse();
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL))
	{
		SmartBomb();
	}

	if (IsKeyPressed(KEY_RIGHT_SHIFT))
	{
		Hyperspace();
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

	ScreenEdgeBoundY(GetScreenHeight() * 0.161f, GetScreenHeight() * 0.015f);
	CheckPlayfieldSidesWarp(4.0f, 3.0f);

	if (RotateFacing)
		RotateShipFacing();

	CameraMovement();
	RadarMovement();
}

void Player::Draw()
{
	Model3D::Draw();

	Flame.Draw();
	Radar.Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}
}

void Player::NewWaveReset()
{
	ThrustOff();
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Acceleration = { 0, 0, 0 };
	FacingRight = true;
	RotationY = (PI * 2) - 0.045f;

	for (auto shot : Shots)
	{
		shot->Reset();
	}
}

void Player::CameraMovement()
{
	float facingOffset = GetScreenWidth() * 0.2f;

	if (ChangedFacing)
	{
		if (FacingRight)
		{
			if (TheCamera->position.x < X() + facingOffset - 0.05f)
			{
				TheCamera->position.x = (X() - facingOffset) + (facingOffset * moveToOffset);
			}
			else
			{
				ChangedFacing = false;
			}
		}
		else
		{
			if (TheCamera->position.x > X() - facingOffset + 0.05f)
			{
				TheCamera->position.x = (X() + facingOffset) - (facingOffset * moveToOffset);
			}
			else
			{
				ChangedFacing = false;
			}
		}

		moveToOffset += 0.02f;
	}
	else
	{
		if (FacingRight)
		{
			TheCamera->position.x = X() + facingOffset;
		}
		else
		{
			TheCamera->position.x = X() - facingOffset;
		}
	}

	TheCamera->target.x = TheCamera->position.x;;
}

void Player::RotateShipFacing()
{
	float rotateSpeed = 0.055f;

	if (FacingRight)
	{
		if (RotationY < (PI * 2) -0.045f)
		{
			RotationY += rotateSpeed;
		}
		else
		{
			RotateFacing = false;
		}
	}
	else
	{
		if (RotationY > PI)
		{
			RotationY -= rotateSpeed;
		}
		else
		{
			RotateFacing = false;
		}
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

void Player::Reverse()
{
	if (FacingRight)
	{
		FacingRight = false;
	}
	else
	{
		FacingRight = true;
	}

	moveToOffset = 0.01f;
	RotateFacing = true;
	ChangedFacing = true;
}

void Player::RadarMovement()
{
	Radar.X(TheCamera->position.x);
	Radar.Y((Y() * 0.147f) + (GetScreenHeight() * 0.4374f));
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

void Player::Thrust()
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
			shot->Spawn(Position, Velocity, !FacingRight);
			return;
		}
	}
}

void Player::SmartBomb()
{
}

void Player::Hyperspace()
{
}