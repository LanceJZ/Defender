#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	UnloadSound(ShotSound);
	UnloadSound(ExplodeSound);
	UnloadSound(ThrustSound);
}

bool Player::Initialize()
{
	Model3D::Initialize();

	Radius = 13.0f;
	Cull = false;
	Flame.Cull = false;
	Radar.Cull = false;
	//ModelScale = 2.0f;
	RotationY = (PI * 2) - 0.045f;

	for (auto &shot : Shots)
	{
		shot.Initialize();
	}

	Reset();

	return false;
}

void Player::SetModel(Model model)
{
	Model3D::SetModel(model, 2.0f);
}

void Player::SetFlameModel(Model model)
{
	Flame.SetModel(model, 2.0f);
}

void Player::SetShotModel(Model model)
{
	for (auto &shot : Shots)
	{
		shot.SetModel(model, 3.0f);
	}
}

void Player::SetTailModel(Model model)
{
	for (auto &shot : Shots)
	{
		shot.SetTailModel(model);
	}
}

void Player::SetRadarModel(Model model)
{
	Radar.SetModel(model, 10.0f);
}

void Player::SetSounds(Sound shot, Sound explode, Sound thrust)
{
	ShotSound = shot;
	ExplodeSound = explode;
	ThrustSound = thrust;
}

bool Player::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;
	Flame.Position.x = -80.0f;
	Flame.RotationVelocity = 50.0f;
	Flame.RotationAxis.x = 1.0f;
	Flame.BeginRun(camera);
	AddChild(&Flame);
	Radar.BeginRun(camera);
	SetSoundPitch(ThrustSound, 0.5f);
	SetSoundPitch(ExplodeSound, 0.75f);

	for (auto &shot : Shots)
	{
		shot.BeginRun(camera);
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

	for (auto &shot : Shots)
	{
		shot.Update(deltaTime);
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

	for (auto &shot : Shots)
	{
		shot.Draw();
	}
}

void Player::Reset()
{
	BeenHit = false;
	ThrustOff();
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Acceleration = { 0, 0, 0 };
	FacingRight = true;
	RotationY = (PI * 2) - 0.045f;
	Enabled = true;

	for (auto &shot : Shots)
	{
		shot.Reset();
	}
}

void Player::Hit()
{
	Entity::BeenHit = true;
	PlaySound(ExplodeSound);
	Velocity = { 0,0,0 };
	Acceleration = { 0,0,0 };
	Enabled = false;
	ThrustOff();
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
	if (!IsSoundPlaying(ThrustSound))
		PlaySound(ThrustSound);

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
	StopSound(ThrustSound);

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
	if (IsSoundPlaying(ShotSound))
	{
		StopSound(ShotSound);
	}

	PlaySound(ShotSound);

	for (auto &shot : Shots)
	{
		if (!shot.Enabled)
		{
			shot.Spawn(Position, Velocity, !FacingRight);
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