#include "Common.h"

bool Common::Initialize()
{
	GameScreenHalfHeight = GetScreenHeight() * 0.5f;
	GameScreenHalfWidth = GetScreenWidth() * 0.5f;

	return false;
}

bool Common::BeginRun()
{

	return true;
}

void Common::Update()
{
}

float Common::GetRandomScreenY()
{
	return GetRandomFloat(-GameScreenHalfHeight, GameScreenHalfHeight);
}

float Common::GetRandomFloat(float min, float max)
{
	if (min > max)
	{
		TraceLog(LOG_INFO, "*****\n");
		TraceLog(LOG_INFO, "********* GetRandomFloat used with min more than max *********\n");
		return 0;
	}

	std::default_random_engine randEngine(RandomDevice());
	std::uniform_real_distribution<float> urdRand(min, max);

	return urdRand(randEngine);
}

float Common::GetRandomRadian()
{
	return GetRandomFloat(0, PI * 2);
}

float Common::RotateTowardsTargetZ(Vector3 origin, Vector3 target, float facingAngle, float magnitude)
{
	float turnVelocity = 0;
	float targetAngle = GetAngleFromVectorsZ(origin, target);
	float targetLessFacing = targetAngle - facingAngle;
	float facingLessTarget = facingAngle - targetAngle;

	if (abs(targetLessFacing) > PI)
	{
		if (facingAngle > targetAngle)
		{
			facingLessTarget = (((PI *2) - facingAngle) + targetAngle) * -1;
		}
		else
		{
			facingLessTarget = ((PI * 2) - targetAngle) + facingAngle;
		}
	}

	if (facingLessTarget > 0)
	{
		turnVelocity = -magnitude;
	}
	else
	{
		turnVelocity = magnitude;
	}

	return turnVelocity;
}

float Common::GetAngleFromVectorsZ(Vector3 origin, Vector3 target)
{
	return { atan2f(target.y - origin.y, target.x - origin.x) };
}

Vector3 Common::GetRandomVelocity(float speed)
{
	return GetVelocityFromAngleZ(GetRandomRadian(), speed);
}

Vector3 Common::GetRandomVelocity(float speed, float radianDirection)
{
	return GetVelocityFromAngleZ(radianDirection, GetRandomFloat(speed * 0.15f, speed));
}

Vector3 Common::GetVelocityFromAngleZ(float rotation, float magnitude)
{
	return { cosf(rotation) * magnitude, sinf(rotation) * magnitude, 0 };
}