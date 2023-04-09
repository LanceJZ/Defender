#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	UnloadSound(ShotSound);
	UnloadSound(ExplodeSound);
	UnloadSound(ThrustSound);
	UnloadModel(GetModel());
	UnloadModel(Flame.GetModel());
	UnloadModel(ShotModel);
	UnloadModel(ShotTrailModel);
	UnloadModel(RadarModel);

	TheCamera = nullptr;
	Explosion = nullptr;
}

bool Player::Initialize()
{
	Model3D::Initialize();

	Flame.Initialize();
	Radar.Initialize();
	BackCollusion.Initialize();
	FrontCollusion.Initialize();

	Radius = 8.25f;
	BackCollusion.Radius = 12.0f;
	FrontCollusion.Radius = 5.5f;
	Cull = false;
	Flame.Cull = false;
	Radar.Cull = false;
	Enabled = false;
	Flame.Enabled = false;
	Radar.Enabled = false;
	BackCollusion.Enabled = false;
	FrontCollusion.Enabled = false;
	RotationY = (PI * 2) - 0.045f;

	for (auto &shot : Shots)
	{
		shot.Initialize();
	}

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

	ShotModel = model;
}

void Player::SetTailModel(Model model)
{
	for (auto &shot : Shots)
	{
		shot.SetTailModel(model);
	}

	ShotTrailModel = model;
}

void Player::SetRadarModel(Model model)
{
	Radar.SetModel(model, 10.0f);
	RadarModel = model;
}

void Player::SetSmartbombModel(Model model)
{
	SmartbombModel = model;
}

void Player::SetSounds(Sound shot, Sound explode, Sound thrust, Sound bomb)
{
	ShotSound = shot;
	ExplodeSound = explode;
	ThrustSound = thrust;
	SmartbombSound = bomb;
}

void Player::SetExplosion(ExplosionControl* explosion)
{
	Explosion = explosion;
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

	for (auto &shot : Shots)
	{
		shot.BeginRun(camera);
	}

	SetSoundPitch(ThrustSound, 0.5f);
	SetSoundPitch(ExplodeSound, 0.75f);
	SetSoundVolume(ThrustSound, 0.5f);
	SetSoundVolume(ShotSound, 0.5f);
	SetSoundVolume(SmartbombSound, 0.5f);

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

	if (FacingRight)
	{
		BackCollusion.Position.x = Position.x - 18.0f;
		FrontCollusion.Position.x = Position.x + 18.0f;
	}
	else
	{
		BackCollusion.Position.x = Position.x + 18.0f;
		FrontCollusion.Position.x = Position.x - 18.0f;
	}

	BackCollusion.Position.y = Position.y;
	FrontCollusion.Position.y = Position.y;

	CameraMovement();
	RadarMovement();
	LivesDisplayUpdate();
	SmartbombsDisplayUpdate();
}

void Player::Draw()
{
	Model3D::Draw();

	Flame.Draw();
	Radar.Draw();
	BackCollusion.Draw();
	FrontCollusion.Draw();

	for (auto &shot : Shots)
	{
		shot.Draw();
	}

	for (auto& ship : LivesShips)
	{
		ship->Draw();
	}

	for (auto& bomb : SmartbombIcons)
	{
		bomb->Draw();
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
	Radar.Enabled = true;
	BackCollusion.Enabled = true;
	FrontCollusion.Enabled = true;

	for (auto &shot : Shots)
	{
		shot.Reset();
	}

	LivesDisplay();
	SmartbombsDisplay();
}

void Player::NewGame()
{
	Lives = 4;
	SmartBombs = 3;
	GameOver = false;
	Reset();
}

void Player::NewWave()
{
	if (SmartBombs < 3)
	{
		SmartBombs++;
		SmartbombsDisplay();
	}
}

void Player::Hit()
{
	Entity::BeenHit = true;
	Lives--;

	if (Lives < 0)
	{
		GameOver = true;
	}

	PlaySound(ExplodeSound);
	Velocity = { 0,0,0 };
	Acceleration = { 0,0,0 };
	Enabled = false;
	BackCollusion.Enabled = false;
	FrontCollusion.Enabled = false;
	ThrustOff();
	Explosion->Spawn(Position, 100, 5.5f);

	for (auto& shot : Shots)
	{
		shot.Reset();
	}

	SmartBombs = 3;
}

void Player::Bonus()
{
	Lives++;
	SmartBombs++;

	LivesDisplay();
	SmartbombsDisplay();
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

		BackCollusion.Position.x = -24.0f;
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

		BackCollusion.Position.x = 24.0f;
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
	if (SmartBombs > 0)
	{
		SmartBombs--;
		PlaySound(SmartbombSound);
		SmartbombsDisplay();
		SmartBombFired = true;
	}
}

void Player::Hyperspace()
{
}

void Player::LivesDisplay()
{
	int ships = (int)LivesShips.size();
	float row = WindowHeight - Radius * 4.5f;

	if (Lives > ships)
	{
		for (int i = 0; i < Lives - ships; i++)
		{
			LivesShips.push_back(new Model3D());
			LivesShips[ships + i]->Initialize();
			LivesShips[ships + i]->SetModel(GetModel(), ModelScale * 0.5f);
			LivesShips[ships + i]->Z(200.0f);
			LivesShips[ships + i]->Y(row);
			LivesShips[ships + i]->Cull = false;
			LivesShips[ships + i]->BeginRun(TheCamera);
		}
	}

	for (auto& ship : LivesShips)
	{
		ship->Enabled = false;
	}

	for (int i = 0; i < Lives; i++)
	{
		LivesShips[i]->Enabled = true;
	}
}

void Player::LivesDisplayUpdate()
{
	float column = WindowWidth - Radius * 4.5f;

	for (auto& ship : LivesShips)
	{
		ship->X(-column + TheCamera->position.x);
		column -= Radius * 5.5f;
	}
}

void Player::SmartbombsDisplay()
{
	int bombs = (int)SmartbombIcons.size();
	float row = WindowHeight - 15 * 7.75f;

	if (SmartBombs > bombs)
	{
		for (int i = 0; i < SmartBombs - bombs; i++)
		{
			SmartbombIcons.push_back(new Model3D());
			SmartbombIcons[bombs + i]->Initialize();
			SmartbombIcons[bombs + i]->SetModel(SmartbombModel, 15.0f);
			SmartbombIcons[bombs + i]->Z(200.0f);
			SmartbombIcons[bombs + i]->Y(row);
			SmartbombIcons[bombs + i]->Cull = false;
			SmartbombIcons[bombs + i]->BeginRun(TheCamera);
			row += (10 * 2) * (bombs + 1);
		}
	}

	for (auto& bomb : SmartbombIcons)
	{
		bomb->Enabled = false;
	}

	for (int i = 0; i < SmartBombs; i++)
	{
		SmartbombIcons[i]->Enabled = true;
	}
}

void Player::SmartbombsDisplayUpdate()
{
	float column = WindowWidth - 15 * 22.5f;

	for (auto& bomb : SmartbombIcons)
	{
		bomb->X(-column + TheCamera->position.x);
	}
}
