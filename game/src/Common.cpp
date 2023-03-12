#include "Common.h"

bool Common::Initialize()
{

	return false;
}

Model Common::LoadTextureToModel(Model model, Texture2D texture)
{
	Model buildModel;
	buildModel = model;
	buildModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	return buildModel;
}

float Common::GetRandomScreenY()
{
	return GetRandomFloat(-GameScreenHeight, GameScreenHeight);
}

float Common::GetRandomFloat(float min, float max)
{
	default_random_engine eng(rd());
	uniform_real_distribution<float> distr(min, max);

	return distr(eng);
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
	return (atan2f(target.y - origin.y, target.x - origin.x));
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