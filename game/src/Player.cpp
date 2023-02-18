#include "Player.h"

Player::~Player()
{
}

bool Player::Initialize()
{
	Model3D::Initialize();

	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new PlayerShot();
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

void Player::SetShotModel(Model model, Texture2D texture)
{

}

bool Player::BeginRun()
{
	ModelScale = 2.0f;
	Flame.ModelScale = 2.0f;
	Flame.Position.x = -80.0f;
	Flame.RotationVelocity = 50.0f;
	Flame.RotationAxis.x = 1.0f;
	AddChild(&Flame);

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
		if (Velocity.y > 0)
		{
			Acceleration.y = -HorzSpeed / HorzDrag;
		}
		else if (Velocity.y < 0)
		{
			Acceleration.y = HorzSpeed / HorzDrag;
		}
	}

	if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_SPACE)) // Fire.
	{
		if (FacingRight)
		{

		}
		else
		{

		}
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
		if (Velocity.x > 0)
		{
			Acceleration.x = -ForwardSpeed / ForwardDrag;
		}
		else if (Velocity.x < 0)
		{
			Acceleration.x = ForwardSpeed / ForwardDrag;
		}

		Flame.Enabled = false;
	}

	if (IsKeyPressed(KEY_Z)) // Flip player ship facing.
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
	ScreenEdgeBoundY();
	CheckPlayfieldSides(4.0f, 3.0f);

	TheCamera->position.x = X();
	TheCamera->target.x = X();
}

void Player::Draw()
{
	Model3D::Draw();

	Flame.Draw();
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