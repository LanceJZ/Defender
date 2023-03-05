#include "Person.h"

Person::Person()
{
	ThePlayer = nullptr;
	TheCamera = nullptr;
	Enabled = false;
}

Person::~Person()
{
}

void Person::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);

}

void Person::SetRadar(Model model, Texture2D texture)
{
	Radar.LoadModel(model, texture);
}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void Person::SetCamera(Camera* camera)
{
	TheCamera = camera;
}

bool Person::Initialize()
{
	Model3D::Initialize();

	ModelScale = 5;

	return false;
}

bool Person::BeginRun()
{
	MirrorL.TheModel = TheModel;
	MirrorL.ModelScale = ModelScale;
	MirrorR.TheModel = TheModel;
	MirrorR.ModelScale = ModelScale;
	Radar.ModelScale = 4;

	return false;
}

void Person::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	MirrorUpdate();
	RadarUpdate();
}

void Person::Draw()
{
	Model3D::Draw();

	MirrorL.Draw();
	MirrorR.Draw();
	Radar.Draw();
}

void Person::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}

void Person::MirrorUpdate()
{
	float mirror = 7.0f;
	MirrorL.X(X() + GetScreenWidth() * mirror);
	MirrorR.X(X() - GetScreenWidth() * mirror);
}

void Person::RadarUpdate()
{
	float comp = 0.062f;
	float ww = 3.5f;

	Radar.X(TheCamera->position.x + (-ThePlayer->X() * 0.062f) + (X() * 0.062f));

	if (Radar.X() > TheCamera->position.x + (GetScreenWidth() * ww) * comp)
	{
		Radar.X(Radar.X() - ((GetScreenWidth() * ww) * 2) * comp);
	}
	else if (Radar.X() < TheCamera->position.x - (GetScreenWidth() * ww) * comp)
	{
		Radar.X(Radar.X() + ((GetScreenWidth() * ww) * 2) * comp);
	}

	Radar.Y((Y() * 0.148f) + (GetScreenHeight() * 0.4376f));
	Radar.Enabled = Enabled;
}
