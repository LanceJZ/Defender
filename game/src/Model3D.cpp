#include "Model3D.h"
#include "rlgl.h"

bool Model3D::Initialize()
{
	Entity::Initialize();
	return false;
}

void Model3D::LoadModel(Model model, Texture2D texture)
{
	TheModel = model;
	TheModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

void Model3D::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void Model3D::Draw()
{
	Entity::Draw();

	if (Enabled)
	{
		rlPushMatrix();

		if (IsConnectedChild)
		{
			for (auto parent : Parents)
			{
				rlTranslatef(parent->Position.x, parent->Position.y, Position.z);
				rlRotatef(parent->Rotation, parent->RotationAxis.x, parent->RotationAxis.y, parent->RotationAxis.z);
			}
		}

		rlTranslatef(Position.x, Position.y, Position.z);
		rlRotatef(Rotation, RotationAxis.x, RotationAxis.y, RotationAxis.z);
		rlScalef(Scale, Scale, Scale);
		//rlColor4ub(ModelColor.r, ModelColor.g, ModelColor.b, ModelColor.a);

		DrawModel(TheModel, ModelPosition, ModelScale, ModelColor);	// Draw 3D model

		rlPopMatrix();
		rlEnd();
	}
}

void Model3D::AddChild(Model3D* child)
{
	for (auto parent : Parents)
	{
		parent->AddChildren(child);
	}

	Children.push_back(child);
	child->Parents.push_back(this);
	child->IsChild = true;
	IsParent = true;

}

void Model3D::AddChildren(Model3D* child)
{
	child->Parents.push_back(this);
	IsParent = true;
	child->IsChild = true;
}
