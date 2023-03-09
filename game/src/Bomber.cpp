#include "Bomber.h"

Bomber::Bomber()
{

}

Bomber::~Bomber()
{
}

void Bomber::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Bomber::SetBomb(Model model, Texture2D texture)
{
	Bomb = model;
	BombTexture = texture;
}

void Bomber::SetRadar(Model model, Texture2D texture)
{
	Radar.LoadModel(model, texture);
}

void Bomber::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);
}

void Bomber::SetCamera(Camera* camera)
{
	TheCamera = camera;
	Radar.SetCamera(camera);
}

bool Bomber::Initialize()
{
	Model3D::Initialize();

	Radar.Initialize();

	return false;
}

bool Bomber::BeginRun()
{
	Radar.SetPlayer(ThePlayer);
	Radar.ModelScale = 3;
	Radar.BeginRun();

	return false;
}

void Bomber::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);
}

void Bomber::Draw()
{
	Model3D::Draw();

	Radar.Draw();
}