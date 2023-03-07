#include "GameLogic.h"
#include <string>
#include <raymath.h>

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

bool GameLogic::Initialize()
{
	SetWindowTitle("Defender Pre-Alpha 00.07");
	ThePlayer->Initialize();
	ControlLanderMutant->Initialize();
	TheLand->Initialize();

	return false;
}

void GameLogic::SetCamera(Camera* camera)
{
	TheCamera = camera;
	ThePlayer->SetCamera(camera);
	TheLand->SetCamera(camera);
	ControlLanderMutant->SetCamera(camera);
}

void GameLogic::Load()
{
	string path = "models/Ground";
	string pathR = "models/GroundRadar";

	for (int i = 0; i < 7; i++)
	{
		string namePNG = path;
		string nameRPNG = pathR;
		namePNG.append(to_string(i + 1));
		namePNG.append(".png");
		nameRPNG.append(to_string(i + 1));
		nameRPNG.append(".png");

		string nameOBJ = path;
		string nameROBJ = pathR;
		nameOBJ.append(to_string(i + 1));
		nameOBJ.append(".obj");
		nameROBJ.append(to_string(i + 1));
		nameROBJ.append(".obj");

		Image image = LoadImage(const_cast<char*>(namePNG.c_str()));
		Image imageR = LoadImage(const_cast<char*>(nameRPNG.c_str()));
		TheLand->LandParts[i]->LoadModel(LoadModel(const_cast<char*>(nameOBJ.c_str())), LoadTextureFromImage(image));
		TheLand->RadarLandParts[i]->LoadModel(LoadModel(const_cast<char*>(nameROBJ.c_str())), LoadTextureFromImage(imageR));
		UnloadImage(image);
		UnloadImage(imageR);
	}

	Image imageui = LoadImage("models/UIBackface.png");
	TheLand->SetUIBack(LoadModel("models/UIBackface.obj"), LoadTextureFromImage(imageui));
	UnloadImage(imageui);

	Image imageHorz = LoadImage("models/RadarH.png");
	TheLand->SetRadarHorz(LoadModel("models/RadarH.obj"), LoadTextureFromImage(imageHorz));
	UnloadImage(imageHorz);

	//Load all the models and their images used by Player.
	Image imageps = LoadImage("models/Player Ship.png"); // Load image into (RAM)
	ThePlayer->LoadModel(LoadModel("models/Player Ship.obj"), LoadTextureFromImage(imageps)); // Loads image from RAM to the GPU.
	UnloadImage(imageps); // Unload image from (RAM)

	Image imagefl = LoadImage("models/Player Flame.png"); // Load image into (RAM)
	ThePlayer->SetFlameModel(LoadModel("models/Player Flame.obj"), LoadTextureFromImage(imagefl)); // Loads image from RAM to the GPU.
	UnloadImage(imagefl); // Unload image from (RAM)

	Image imagepsh = LoadImage("models/Player Shot.png"); // I'm sure you get the idea by now.
	ThePlayer->SetShotModel(LoadModel("models/Player Shot.obj"), LoadTextureFromImage(imagepsh)); //I'm sure you get the idea.
	UnloadImage(imagepsh); // I'm sure you get the idea by now.

	Image imaget = LoadImage("models/Player Shot Tail.png");
	ThePlayer->SetShotModel(LoadModel("models/Player Shot tail.obj"), LoadTextureFromImage(imaget));
	UnloadImage(imaget);

	//Load all the models and their images used by ControlLanderMutant.
	Image imageln = LoadImage("models/Lander.png");
	ControlLanderMutant->SetLanderModel(LoadModel("models/Lander.obj"), LoadTextureFromImage(imageln));
	UnloadImage(imageln);

	Image imagemu = LoadImage("models/Mutant.png");
	ControlLanderMutant->SetMutantModel(LoadModel("models/Mutant.obj"), LoadTextureFromImage(imagemu));
	UnloadImage(imagemu);

	Image imagesh = LoadImage("models/Shot.png");
	ControlLanderMutant->SetShotModel(LoadModel("models/Shot.obj"), LoadTextureFromImage(imagesh));
	UnloadImage(imagesh);

	Image imageprsn = LoadImage("models/Person.png");
	ControlLanderMutant->SetPersonModel(LoadModel("models/Person.obj"), LoadTextureFromImage(imageprsn));
	UnloadImage(imageprsn);

	Image imageplr = LoadImage("models/Player Radar.png");
	ThePlayer->SetRadarModel(LoadModel("models/Player Radar.obj"), LoadTextureFromImage(imageplr));
	UnloadImage(imageplr);

	Image imagelr = LoadImage("models/Lander Radar.png");
	ControlLanderMutant->SetRadarModel(LoadModel("models/Lander Radar.obj"), LoadTextureFromImage(imagelr));
	UnloadImage(imagelr);

	Image imagepr = LoadImage("models/Person Radar.png");
	ControlLanderMutant->SetPersonRadar(LoadModel("models/Person Radar.obj"), LoadTextureFromImage(imagepr));
	UnloadImage(imagepr);
}

bool GameLogic::BeginRun()
{
	ThePlayer->BeginRun();
	TheLand->SetPlayer(ThePlayer);
	TheLand->BeginRun();
	ControlLanderMutant->SetPlayer(ThePlayer);
	ControlLanderMutant->BeginRun();

	return false;
}

void GameLogic::Input()
{
	ThePlayer->Input();

	if (IsKeyPressed(KEY_P))
		Pause = !Pause;
}

void GameLogic::Update(float deltaTime)
{
	if (!Pause)
	{
		ThePlayer->Update(deltaTime);
		TheLand->Update(deltaTime);
		ControlLanderMutant->Update(deltaTime);
	}
}

void GameLogic::Draw3D()
{
	TheLand->Draw();
	ControlLanderMutant->Draw();
	ThePlayer->Draw();
}

void GameLogic::Draw2D()
{

}
