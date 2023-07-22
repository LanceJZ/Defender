#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	//UnloadSound(ShotSound);
	//UnloadSound(ExplodeSound);
	//UnloadSound(ThrustSound);
	//Unload();
	//Flame.Unload();
	//UnloadModel(ShotModel);
	//UnloadModel(ShotTrailModel);
	//UnloadModel(RadarModel);
	//UnloadModel(SmartbombModel);

	TheCamera = nullptr;
	Explosion = nullptr;

	for (int i = 0; i < LivesShips.size(); i++)
	{
		delete LivesShips[i];
	}

	LivesShips.clear();

	for (int i = 0; i < SmartbombIcons.size(); i++)
	{
		delete SmartbombIcons[i];
	}

	SmartbombIcons.clear();
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

void Player::SetSounds(Sound shot, Sound explode, Sound thrust, Sound bomb, Sound bonus)
{
	ShotSound = shot;
	ExplodeSound = explode;
	ThrustSound = thrust;
	SmartbombSound = bomb;
	BonusSound = bonus;
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
	Flame.RotationAxis = { 1.0f, 0, 0 };
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
	if (IsGamepadAvailable(0))
	{
		Gamepad();
	}
	else
	{
		Keyboard();
	}
}

void Player::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto &shot : Shots)
	{
		shot.Update(deltaTime);
	}

	if (Enabled)
	{
		Flame.Update(deltaTime);
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

	if (Lives >= 0)
	{
		for (auto& ship : LivesShips)
		{
			ship->Draw();
		}

		for (auto& bomb : SmartbombIcons)
		{
			bomb->Draw();
		}
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

	for (auto& shot : Shots)
	{
		shot.Reset();
	}
}


void Player::NewGame()
{
	Lives = 4;
	SmartBombs = 4;
	GameOver = false;
	Reset();

	LivesDisplay();
	SmartbombsDisplay();
}

void Player::NewWave()
{
	LivesDisplay();
	SmartbombsDisplay();
}

void Player::Hit()
{
	Entity::BeenHit = true;
	Lives--;
	SmartBombs = 4;

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
}

void Player::Bonus()
{
	PlaySound(BonusSound);

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
	if (Velocity.x > -MaxForwardV)
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
	if (Velocity.x < MaxForwardV)
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

void Player::HorzFriction()
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

void Player::Keyboard()
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
		HorzFriction();
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

void Player::Gamepad()
{
	//Button B is 6 for Smartbomb //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Reverse //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for Move Up	//Dpad Down is 3 for Move Down
	//Axis 1 is up -1/down 1 on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
		Thrust();
	}
	else
	{
		ThrustOff();
	}

	if (IsGamepadButtonDown(0, 1) || GetGamepadAxisMovement(0, 1) < -0.25f)
	{
		MoveUp();
	}
	else if (IsGamepadButtonDown(0, 3) || GetGamepadAxisMovement(0, 1) > 0.25f)
	{
		MoveDown();
	}
	else
	{
		HorzFriction();
	}

	if (IsGamepadButtonPressed(0, 7))
	{
		Fire();
	}

	if (IsGamepadButtonPressed(0, 11))
	{
		Reverse();
	}

	if (IsGamepadButtonPressed(0, 6))
	{
		SmartBomb();
	}

	if (IsGamepadButtonPressed(0, 8))
	{
		Hyperspace();
	}
}

void Player::LivesDisplay()
{
	int ships = (int)LivesShips.size();
	float row = WindowHeight - Radius * 4.5f;

	if (Lives > ships)
	{
		for (int i = 0; i < Lives - ships; i++)
		{
			LivesShips.push_back(DBG_NEW Model3D());
			LivesShips[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(ships) + i]->Initialize();
			LivesShips[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(ships) + i]->SetModel(GetModel(), ModelScale * 0.5f);
			LivesShips[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(ships) + i]->Z(200.0f);
			LivesShips[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(ships) + i]->Y(row);
			LivesShips[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(ships) + i]->Cull = false;
			LivesShips[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(ships) + i]->BeginRun(TheCamera);
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
	float row = WindowHeight - 15 * 7.75f + (20 * bombs);

	if (SmartBombs > bombs)
	{
		for (int i = 0; i < SmartBombs - bombs; i++)
		{
			SmartbombIcons.push_back(DBG_NEW Model3D());
			SmartbombIcons[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(bombs) + i]->Initialize();
			SmartbombIcons[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(bombs) + i]->SetModel(SmartbombModel, 15.0f);
			SmartbombIcons[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(bombs) + i]->Z(200.0f);
			SmartbombIcons[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(bombs) + i]->Y(row);
			SmartbombIcons[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(bombs) + i]->Cull = false;
			SmartbombIcons[static_cast<std::vector<Model3D*, std::allocator<Model3D*>>::size_type>(bombs) + i]->BeginRun(TheCamera);
			row += 20;
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
