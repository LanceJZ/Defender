#include "GameLogic.h"
#include <string>

GameLogic::GameLogic()
{
	ThePlayer = new Player();
	TheLand = new Land();
}

GameLogic::~GameLogic()
{
}

bool GameLogic::Initialize()
{
	ThePlayer->Initialize();

	return false;
}

void GameLogic::SetCamera(Camera* camera)
{
	TheCamera = camera;
	ThePlayer->SetCamera(camera);
}

void GameLogic::Load()
{
	string path = "models/Ground";

	for (int i = 0; i < 7; i++)
	{
		string namePNG = path;
		namePNG.append(to_string(i + 1));
		namePNG.append(".png");
		string nameOBJ = path;
		nameOBJ.append(to_string(i + 1));
		nameOBJ.append(".obj");
		Image image = LoadImage(const_cast<char*>(namePNG.c_str()));
		TheLand->LandParts[i]->LoadModel(LoadModel(const_cast<char*>(nameOBJ.c_str())), LoadTextureFromImage(image));
		UnloadImage(image);
	}

	Image imageps = LoadImage("models/Player Ship.png"); // Load image into (RAM)
	ThePlayer->LoadModel(LoadModel("models/Player Ship.obj"), LoadTextureFromImage(imageps)); //Load ship model into Player class.
	UnloadImage(imageps); // Unload image from (RAM)

	Image imagefl = LoadImage("models/Player Flame.png"); // Load image into (RAM)
	ThePlayer->SetFlameModel(LoadModel("models/Player Flame.obj"), LoadTextureFromImage(imagefl)); //Load flame model into Player class.
	UnloadImage(imagefl); // Unload image from (RAM)

	Image imagesh = LoadImage("models/Player Shot.png");
	Image imaget = LoadImage("models/Player Shot Tail.png");
	ThePlayer->SetShotModels(LoadModel("models/Player Shot.obj"), LoadTextureFromImage(imagesh),
		LoadModel("models/Player Shot tail.obj"), LoadTextureFromImage(imaget)); //Load shot models into Player class.
	UnloadImage(imagesh); // Unload image from (RAM)

}

bool GameLogic::BeginRun()
{
	ThePlayer->BeginRun();
	TheLand->BeginRun();

	return false;
}

void GameLogic::Input()
{
	ThePlayer->Input();
}

void GameLogic::Update(float deltaTime)
{
	ThePlayer->Update(deltaTime);
	TheLand->Update(deltaTime);
}

void GameLogic::Draw3D()
{
	ThePlayer->Draw();
	TheLand->Draw();
}

void GameLogic::Draw2D()
{

}
