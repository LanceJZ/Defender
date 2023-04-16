#include "Model3D.h"
#include "rlgl.h"

Model3D::Model3D()
{
}

Model3D::~Model3D()
{
	if (IsChild)
	{
		Children.clear();
		IsChild = false;
	}

	if (IsParent)
	{
		Parents.clear();
		IsParent = false;
	}

	TheCamera = nullptr;
}

bool Model3D::Initialize()
{
	Entity::Initialize();

	ViewableArea = { WindowWidth, WindowHeight };

	return false;
}

void Model3D::LoadModel(Model &model, Texture2D &texture)
{
	if (IsTextureReady(texture))
	{
		TheModel = model;
		TheModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	}
}

bool Model3D::BeginRun(Camera* camera)
{
	TheCamera = camera;

	return false;
}

void Model3D::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void Model3D::Draw()
{
	if (Enabled)
	{
		Entity::Draw();

		if (TheCamera == nullptr)
		{
			return;
		}

		if (Cull)
		{
			if (IsChild)
			{
				Vector3 parentTest = Position;

				for (auto parent : Parents)
				{
					parentTest = Vector3Add(parent->Position, parentTest);
				}

				if (TheCamera->position.x > parentTest.x + ViewableArea.x
					|| TheCamera->position.x < parentTest.x + -ViewableArea.x)
				{
					return;
				}

				if (TheCamera->position.y > parentTest.y + ViewableArea.y ||
					TheCamera->position.y < parentTest.y + -ViewableArea.y)
				{
					return;
				}
			}
			else
			{
				if (TheCamera->position.x > Position.x + ViewableArea.x
					|| TheCamera->position.x < Position.x + -ViewableArea.x)
				{
					return;
				}

				if (TheCamera->position.y > Position.y + ViewableArea.y ||
					TheCamera->position.y < Position.y + -ViewableArea.y)
				{
					return;
				}
			}
		}

		rlPushMatrix();

		if (IsChild)
		{
			for (auto parent : Parents)
			{
				rlTranslatef(parent->Position.x, parent->Position.y, Position.z);

				rlRotatef(parent->RotationX, 1, 0, 0);
				rlRotatef(parent->RotationY, 0, 1, 0);
				rlRotatef(parent->RotationZ, 0, 0, 1);
				rlRotatef(parent->Rotation, parent->RotationAxis.x, parent->RotationAxis.y,
					parent->RotationAxis.z);
				rlScalef(parent->Scale, parent->Scale, parent->Scale);
				rlColor4ub(parent->TheColor.r, parent->TheColor.g, parent->TheColor.b,
					parent->TheColor.a);
			}
		}

		rlTranslatef(Position.x, Position.y, Position.z);

		rlRotatef(RotationX, 1, 0, 0);
		rlRotatef(RotationY, 0, 1, 0);
		rlRotatef(RotationZ, 0, 0, 1);
		rlRotatef(Rotation, RotationAxis.x, RotationAxis.y, RotationAxis.z);
		rlScalef(Scale, Scale, Scale);
		rlColor4ub(TheColor.r, TheColor.g, TheColor.b, TheColor.a);

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

void Model3D::SetModel(Model &model, float scale)
{
	TheModel = model;
	ModelScale = scale;
}

void Model3D::SetModelCopy(Model model, float scale)
{
	TheModel = model;
	ModelScale = scale;
}

Model& Model3D::GetModel()
{
	return TheModel;
}

void Model3D::Unload()
{
	UnloadModel(TheModel);
}

void Model3D::AddChildren(Model3D* child)
{
	child->Parents.push_back(this);
	IsParent = true;
	child->IsChild = true;
}
