#include "PositionedObject.h"

PositionedObject::PositionedObject()
{
}

PositionedObject::~PositionedObject()
{
	Parents.clear();
}

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
	return { cosf(Rotation) * magnitude, sinf(Rotation) * magnitude, 0 };
}

Vector3 PositionedObject::VelocityFromAngleZ(float angle, float magnitude)
{
	return { cosf(angle) * magnitude, (float)sin(angle) * magnitude, 0 };
}
//Returns Vector3 acceleration based on acceleration amount this frame, to a max amount.
Vector3 PositionedObject::AccelerationToMaxAtRotation(float accelerationAmount, float topSpeed, float deltaTime)
{
	return { ((cos(Rotation) - (Velocity.x * topSpeed)) * accelerationAmount) * deltaTime,
			((sin(Rotation) - (Velocity.y * topSpeed)) * accelerationAmount) * deltaTime, 0 };
}
//Returns Vector3 deceleration down to zero.
Vector3 PositionedObject::DecelerationToZero(float decelerationAmount, float deltaTime)
{
	Vector3 deceleration = { 0, 0, 0 };

	if (Velocity.x > 0.01 || Velocity.y > 0.01 || Velocity.x < -0.01 || Velocity.y < -0.01)
	{
		deceleration = { (-Velocity.x * decelerationAmount) * deltaTime,
		(-Velocity.y * decelerationAmount) * deltaTime, 0 };
	}
	else
	{
		Velocity = { 0, 0, 0 };
	}

	return deceleration;
}

Quaternion PositionedObject::EulerToQuaternion(float yaw, float pitch, float roll)
{
	float quaternionX, quaternionY, quaternionZ, quaternionW;
	float yawDev = yaw / 2, pitchDev = pitch / 2, rollDev = roll / 2;

	quaternionX = sinf(rollDev) * cosf(pitchDev) * cosf(yawDev) -
		cosf(rollDev) * sinf(pitchDev) * sinf(yawDev);
	quaternionY = cosf(rollDev) * sinf(pitchDev) * cosf(yawDev) +
		sinf(rollDev) * cosf(pitchDev) * sinf(yawDev);
	quaternionZ = cosf(rollDev) * cosf(pitchDev) * sinf(yawDev) -
		sinf(rollDev) * sinf(pitchDev) * cosf(yawDev);
	quaternionW = cosf(rollDev) * cosf(pitchDev) * cosf(yawDev) +
		sinf(rollDev) * sinf(pitchDev) * sinf(yawDev);

	return {quaternionX, quaternionY, quaternionZ, quaternionW};
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
}

void PositionedObject::Y(float y)
{
	Position.y = y;
}

void PositionedObject::Z(float z)
{
	Position.z = z;
}

void PositionedObject::SetParent(PositionedObject* parent)
{
	if (IsChild) return;

	for (auto myParent : parent->Parents)
	{
		Parents.push_back(myParent);
	}

	Parents.push_back(parent);

	parent->IsParent = true;
	IsChild = true;
	ChildPosition = Position;
	ChildRotation = Rotation;
}

void PositionedObject::RemoveFromParents()
{
	IsChild = false;
	Position = WorldPosition;
	Rotation = WorldRotation;
}

void PositionedObject::DisconnectChild(PositionedObject* child)
{
	if (child->IsParent) return;

	if (!child->IsChild) return;

	child->IsConnectedChild = false;
	child->ChildPosition = child->Position;
	child->ChildRotation = child->Rotation;
	child->IsChild = false;
	child->Position = WorldPosition;
	child->Rotation = WorldRotation;
}

void PositionedObject::ConnectChild(PositionedObject* child)
{
	if (child->IsChild)	return;

	child->IsChild = true;
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
