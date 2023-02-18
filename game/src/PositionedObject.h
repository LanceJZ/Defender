#pragma once
#include "Common.h"

class PositionedObject : public Common
{
public:
	bool IsChild = false;
	bool IsParent = false;
	bool IsConnectedChild = true;
	int ChildNumber = 0;
	float MaxSpeed = 0;
	float Radius = 0;
	float WindowWidth = GetScreenWidth() / 2;
	float WindowHeight = GetScreenHeight() / 2;
	float Rotation = 0;
	float RotationVelocity = 0;
	float RotationAcceleration = 0;
	Vector2 Acceleration2 = { 0 };
	Vector2 Velocity2 = { 0 };
	Vector2 Position2 = { 0 };
	Vector3 Acceleration = { 0 };
	Vector3 Velocity = { 0 };
	Vector3 Position = { 0 };
	Vector3 RotationAxis = { 0, 0, 0 };
	Vector3 ChildPosition = { 0 };
	float ChildRotation = 0;
	float Chase(PositionedObject Chasing);
	float RotateTowardsTargetZ(Vector3 target, float magnitude);
	float AngleFromVectorsZ(Vector3 target);
	float AngleFromVectorsZ(Vector3 origin, Vector3 target);
	float AngleFromVectorZ(Vector3 target);
	Vector3 RandomVelocity(float magnitude);
	Vector3 VelocityFromAngleZ(float magnitude);
	Vector3 VelocityFromAngleZ(float angle, float magnitude);
	vector <PositionedObject*> Children;
	vector <PositionedObject*> Parents;

	bool Initialize();
	virtual void Update(float deltaTime);

	virtual float X();
	virtual float Y();
	virtual float Z();
	virtual void X(float x);
	virtual void Y(float y);
	virtual void Z(float z);
	void AddChild(PositionedObject* child);
	void AddChildren(PositionedObject* child);
	void RemoveChild(PositionedObject* child);
	void RemoveFromParents(PositionedObject* child);
	void DisconnectChild(PositionedObject* child);
	void ConnectChild(PositionedObject* child);

	void CheckScreenEdge();
	void CheckScreenEdgeX();
	void CheckScreenEdgeY();
	bool ScreenEdgeBoundY();
	bool OffScreen();
	bool OffScreenSide();
	bool OffScreenTopBottom();
	void LeavePlay(float turnSpeed, float speed);
	void RotateVelocity(Vector3 position, float turnSpeed, float speed);
	void CheckPlayfieldSides(float left, float right);
	void CheckPlayfieldHeight(float top, float bottom);

private:

};

