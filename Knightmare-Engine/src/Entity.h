#pragma once
#include "PositionedObject.h"

class Entity : public PositionedObject
{
public:
	bool Enabled = true;
	bool BeenHit = false;
	bool EntityOnly = false;
	float Scale = 1;

	virtual bool Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

	bool CirclesIntersect(Entity& target);
	bool CirclesIntersectBullet(Entity& target);

private:
	Ray TheRay = { 0 };
	RayCollision TheRayCollision = { 0 };
};

