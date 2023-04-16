#include "PositionedObject.h"

bool PositionedObject::Initialize()
{
	Common::Initialize();

	WindowWidth = (float)(GetScreenWidth() * 0.5f);
	WindowHeight = (float)(GetScreenHeight() * 0.5f);

	return false;
}

void PositionedObject::Update(float deltaTime)
{
	LastFramePosition = Position;

	Velocity = Vector3Add(Velocity, Acceleration);
	Position = Vector3Add(Vector3Multiply({ deltaTime, deltaTime, deltaTime }, Velocity), Position);

	Rotation = AddRotationVelAcc(Rotation, RotationVelocity, RotationAcceleration, deltaTime);
	RotationX = AddRotationVelAcc(RotationX, RotationVelocityX, RotationAccelerationX, deltaTime);
	RotationY = AddRotationVelAcc(RotationY, RotationVelocityY, RotationAccelerationY, deltaTime);
	RotationZ = AddRotationVelAcc(RotationZ, RotationVelocityZ, RotationAccelerationZ, deltaTime);
}

float PositionedObject::Chase(PositionedObject Chasing)
{
	return 0.0f;
}

float PositionedObject::RotateTowardsTargetZ(Vector3 target, float magnitude)
{
	return Common::RotateTowardsTargetZ(Position, target, Rotation, magnitude);
}

float PositionedObject::AngleFromVectorZ(Vector3 target)
{
	return (atan2f(target.y - Position.y, target.x - Position.x));
}

Vector3 PositionedObject::RandomVelocity(float magnitude)
{
	float ang = GetRandomFloat(0, PI * 2);

	return VelocityFromAngleZ(ang, magnitude);
}

Vector3 PositionedObject::VelocityFromAngleZ(float magnitude)
{
	return { (float)cos(Rotation) * magnitude,	(float)sin(Rotation) * magnitude, 0 };
}

Vector3 PositionedObject::VelocityFromAngleZ(float angle, float magnitude)
{
	return { (float)cos(angle) * magnitude, (float)sin(angle) * magnitude, 0 };
}

float PositionedObject::X()
{
	return Position.x;
}

float PositionedObject::Y()
{
	return Position.y;
}

float PositionedObject::Z()
{
	return Position.z;
}

void PositionedObject::X(float x)
{
	Position.x = x;
	LastFramePosition.x = x;
}

void PositionedObject::Y(float y)
{
	Position.y = y;
	LastFramePosition.y = y;
}

void PositionedObject::Z(float z)
{
	Position.z = z;
	LastFramePosition.z = z;
}

void PositionedObject::AddChild(PositionedObject* child)
{
	for (auto parent : Parents)
	{
		parent->AddChildren(child);
	}

	Children.push_back(child);
	child->Parents.push_back(this);
	child->IsChild = true;
	child->ChildNumber = (int)(Children.size() - (size_t)1);
	IsParent = true;
}

void PositionedObject::AddChildren(PositionedObject* child)
{
	child->Parents.push_back(this);
	child->IsChild = true;
}

void PositionedObject::RemoveChild(PositionedObject* child)
{

}

void PositionedObject::RemoveFromParents(PositionedObject* child)
{

}

void PositionedObject::DisconnectChild(PositionedObject* child)
{
	if (child->IsParent)
		return;

	if (!child->IsConnectedChild)
		return;

	child->IsConnectedChild = false;
	child->ChildPosition = child->Position;
	child->ChildRotation = child->Rotation;

	for (auto parent : child->Parents)
	{
		child->Position = Vector3Add(parent->Position, child->Position);
		child->Rotation += parent->Rotation;
	}
}

void PositionedObject::ConnectChild(PositionedObject* child)
{
	if (child->IsParent)
		return;

	if (child->IsConnectedChild)
		return;

	child->IsConnectedChild = true;
	child->Position = child->ChildPosition;
	child->Rotation = child->ChildRotation;
}

void PositionedObject::CheckScreenEdge()
{
	CheckScreenEdgeX();
	CheckScreenEdgeY();
}

void PositionedObject::CheckScreenEdgeX()
{
	if (X() > WindowWidth)
	{
		X(-WindowWidth);
	}

	if (X() < -WindowWidth)
	{
		X(WindowWidth);
	}
}

void PositionedObject::CheckScreenEdgeY()
{
	if (Y() > WindowHeight)
	{
		Y(-WindowHeight);
	}

	if (Y() < -WindowHeight)
	{
		Y(WindowHeight);
	}
}

bool PositionedObject::ScreenEdgeBoundY()
{
	bool hitBound = false;

	if (Y() > WindowHeight)
	{
		Y(WindowHeight);
		hitBound = true;
	}
	else if (Y() < -WindowHeight)
	{
		Y(-WindowHeight);
		hitBound = true;
	}

	if (hitBound)
	{
		Acceleration.y = 0;
		Velocity.y = 0;
		return true;
	}

	return false;
}

bool PositionedObject::ScreenEdgeBoundY(float topOffset, float bottomOffset)
{
	bool hitBound = false;

	if (Y() > WindowHeight - topOffset)
	{
		Y(WindowHeight - topOffset);
		hitBound = true;
	}
	else if (Y() < -WindowHeight + bottomOffset)
	{
		Y(-WindowHeight + bottomOffset);
		hitBound = true;
	}

	if (hitBound)
	{
		Acceleration.y = 0;
		Velocity.y = 0;
		return true;
	}

	return false;
}

bool PositionedObject::OffScreen()
{
	return OffScreenSide() || OffScreenTopBottom();
}

bool PositionedObject::OffScreenSide()
{
	if (X() > WindowWidth || X() < -WindowWidth)
	{
		return true;
	}

	return false;
}

bool PositionedObject::OffScreenTopBottom()
{
	if (Y() > WindowHeight || Y() < -WindowHeight)
	{
		return true;
	}

	return false;
}

void PositionedObject::LeavePlay(float turnSpeed, float speed)
{
	float stageLeft = 0;

	if (Position.x > 0)
	{
		stageLeft = 60;
	}
	else
	{
		stageLeft = -60;
	}

	RotateVelocity({ stageLeft, Position.y, 0 }, turnSpeed, speed);
}

void PositionedObject::RotateVelocity(Vector3 position, float turnSpeed, float speed)
{
	RotationVelocity = RotateTowardsTargetZ(position, turnSpeed);
	Velocity = VelocityFromAngleZ(Rotation, speed);
}

void PositionedObject::CheckPlayfieldSidesWarp(float left, float right)
{
	if (X() > GetScreenWidth() * right + (GetScreenWidth() * 0.5f))
	{
		X(-GetScreenWidth() * left + (GetScreenWidth() * 0.5f));
	}
	else if (X() < -GetScreenWidth() * left + (GetScreenWidth() * 0.5f))
	{
		X(GetScreenWidth() * right + (GetScreenWidth() * 0.5f));
	}
}

void PositionedObject::CheckPlayfieldHeightWarp(float top, float bottom)
{
	if (Y() > GetScreenHeight() * top + (GetScreenHeight() * 0.5f))
	{
		Y(-GetScreenHeight() * bottom + (GetScreenHeight() * 0.5f));
	}
	else if (Y() < -GetScreenHeight() * bottom + (GetScreenHeight() * 0.5f))
	{
		Y(GetScreenHeight() * top + (GetScreenHeight() * 0.5f));
	}
}

float PositionedObject::RadianSpin(float radian)
{
	if (radian > PI * 2)
	{
		radian = 0;
	}
	else if (radian < 0)
	{
		radian = PI * 2;
	}

	return radian;
}

float PositionedObject::AddRotationVelAcc(float rotation, float rotationVelocity, float rotationAcceleration, float deltaTime)
{
	rotationVelocity += rotationAcceleration * deltaTime;
	rotation += rotationVelocity * deltaTime;

	return rotation;
}
