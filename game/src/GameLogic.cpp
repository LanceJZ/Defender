#include "GameLogic.h"
#include <string>

GameLogic::GameLogic()
{
	ThePlayer = new Player();
	TheLand = new Land();
	ControlLanderMutant = new LanderMutantControl();
}

GameLogic::~GameLogic()
{
}

bool GameLogic::Initialize()
{
	ThePlayer->Initialize();

	ControlLanderMutant->Initialize();

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

	Image imagepsh = LoadImage("models/Player Shot.png");
	ThePlayer->SetShotModel(LoadModel("models/Player Shot.obj"), LoadTextureFromImage(imagepsh)); //Load shot model into Player class.
	UnloadImage(imagepsh); // Unload image from (RAM)

	Image imaget = LoadImage("models/Player Shot Tail.png");
	ThePlayer->SetShotModel(LoadModel("models/Player Shot tail.obj"), LoadTextureFromImage(imaget)); //Load tail model into Player class.
	UnloadImage(imaget);

	Image imageln = LoadImage("models/Lander.png");
	ControlLanderMutant->SetLanderModel(LoadModel("models/Lander.obj"), LoadTextureFromImage(imageln));
	UnloadImage(imageln);

	Image imagemu = LoadImage("models/Mutant.png");
	ControlLanderMutant->SetMutantModel(LoadModel("models/Mutant.obj"), LoadTextureFromImage(imagemu));
	UnloadImage(imagemu);

	Image imagesh = LoadImage("models/Shot.png");
	ControlLanderMutant->SetShotModel(LoadModel("models/Shot.obj"), LoadTextureFromImage(imagesh));
	UnloadImage(imagesh);
}

bool GameLogic::BeginRun()
{
	ThePlayer->BeginRun();
	TheLand->BeginRun();
	ControlLanderMutant->BeginRun();

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
	ControlLanderMutant->Update(deltaTime);
}

void GameLogic::Draw3D()
{
	ThePlayer->Draw();
	TheLand->Draw();
	ControlLanderMutant->Draw();
}

void GameLogic::Draw2D()
{

}
