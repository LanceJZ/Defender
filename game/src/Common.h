#pragma once
#pragma warning ( push )
#pragma warning ( disable : 26495 )
#pragma warning ( pop )

#include <random>
#include "raylib.h"
#include "raymath.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

class Common
{
public:
	float GameScreenHalfWidth = { 0 };
	float GameScreenHalfHeight = { 0 };

	virtual bool Initialize();
	float GetRandomScreenY();
	float GetRandomFloat(float min, float max);
	float GetRandomRadian();
	float RotateTowardsTargetZ(Vector3 origin, Vector3 target, float facingAngle, float magnitude);
	float GetAngleFromVectorsZ(Vector3 origin, Vector3 target);
	Vector3 GetRandomVelocity(float speed);
	Vector3 GetRandomVelocity(float speed, float radianDirection);
	Vector3 GetVelocityFromAngleZ(float rotation, float magnitude);

private:
	std::random_device rd;
};