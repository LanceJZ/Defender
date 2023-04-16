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
	float WindowWidth = (float)GetScreenWidth() / 2.0f; //Half Game Window Width.
	float WindowHeight = (float)GetScreenHeight() / 2.0f; //Half Game Window Height.
	float Rotation = 0;
	float RotationX = 0;
	float RotationY = 0;
	float RotationZ = 0;
	float RotationVelocity = 0;
	float RotationVelocityX = 0;
	float RotationVelocityY = 0;
	float RotationVelocityZ = 0;
	float RotationAcceleration = 0;
	float RotationAccelerationX = 0;
	float RotationAccelerationY = 0;
	float RotationAccelerationZ = 0;
	Vector3 Acceleration = { 0, 0, 0 };
	Vector3 Velocity = { 0, 0, 0 };
	Vector3 Position = { 0, 0, 0 };
	Vector3 LastFramePosition = { 0, 0, 0 };
	Vector3 RotationAxis = { 0, 0, 0 };
	Vector3 ChildPosition = { 0, 0, 0 };
	float ChildRotation = 0;
	std::vector <PositionedObject*> Children;
	std::vector <PositionedObject*> Parents;

	virtual bool Initialize();
	virtual void Update(float deltaTime);

	virtual float X();
	virtual float Y();
	virtual float Z();
	virtual void X(float x);
	virtual void Y(float y);
	virtual void Z(float z);
	float Chase(PositionedObject Chasing);
	float RotateTowardsTargetZ(Vector3 target, float magnitude);
	float AngleFromVectorZ(Vector3 target);
	Vector3 RandomVelocity(float magnitude);
	Vector3 VelocityFromAngleZ(float magnitude);
	Vector3 VelocityFromAngleZ(float angle, float magnitude);
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
	bool ScreenEdgeBoundY(float topOffset, float bottomOffset);
	bool OffScreen();
	bool OffScreenSide();
	bool OffScreenTopBottom();
	void LeavePlay(float turnSpeed, float speed);
	void RotateVelocity(Vector3 position, float turnSpeed, float speed);
	void CheckPlayfieldSidesWarp(float left, float right);
	void CheckPlayfieldHeightWarp(float top, float bottom);

private:
	float RadianSpin(float radian);
	float AddRotationVelAcc(float rotation, float rotationVelocity, float rotationAcceleration, float deltaTime);
};

