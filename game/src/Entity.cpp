#include "Entity.h"

bool Entity::Initialize()
{
	PositionedObject::Initialize();
	return false;
}

void Entity::Update(float deltaTime)
{
	PositionedObject::Update(deltaTime);
}

void Entity::Draw()
{
#ifdef _DEBUG
	if(Enabled)
		DrawCircle3D(Position, Radius, { 0 }, 0, { 150, 50, 200, 200 });
#endif
}

/// <summary>
/// Circle collusion detection. Target circle will be compared to this class's.
/// Will return true of they intersect. Only for use with 2D Z plane.
/// </summary>
/// <param name="target">Target Positioned Object.</param>
/// <returns></returns>
bool Entity::CirclesIntersect(Entity* target)
{
	if (!Enabled || !target->Enabled)
		return false;

	Vector2 distance = { target->Position.x - X(), target->Position.y - Y() };
	float radius = Radius + target->Radius;

	if ((distance.x * distance.x) + (distance.y * distance.y) < radius * radius)
		return true;

	return false;
}

bool Entity::CirclesIntersectBullet(Entity* target)
{
	if (!Enabled || !target->Enabled)
		return false;

	TheRay.position = Position;

	if (Velocity.x > 0)
	{
		TheRay.direction = { 1, 0, 0 };
	}
	else
	{
		TheRay.direction = { -1, 0, 0 };
	}

	TheRayCollision = GetRayCollisionSphere(TheRay, target->Position, target->Radius);

	if (TheRayCollision.hit)
	{
		float distance = Position.x - LastFramePosition.x;
		if (distance < 0) distance *= -1;

		if (TheRayCollision.distance > 0)
		{
			if (TheRayCollision.distance > distance)
				return false;
		}
		else
		{
			if (TheRayCollision.distance * -1 > distance)
				return false;
		}

		return TheRayCollision.hit;
	}

	return false;
}
