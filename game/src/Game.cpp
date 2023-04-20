#include "Game.h"
#include "raymath.h"
#include <string>

Game::Game()
{
}

Game::~Game()
{

}

bool Game::Initialize()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280, 960, "Defender"); //Screen width, height and Window title.
	InitAudioDevice();
	SetTargetFPS(60);

	Image icon = LoadImage("icon.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);
	// Define the camera to look into our 3D world
	TheCamera.position = { 0.0f, 0.0f, 500.0f }; // Camera position
	TheCamera.target = { 0.0f, 0.0f, 0.0f };     // Camera looking at point
	TheCamera.up = { 0.0f, 1.0f, 0.0f };         // Camera up vector (rotation towards target)
	TheCamera.fovy = (float)GetScreenHeight();   // Camera field-of-view Y. In Orthographic is scale.
	TheCamera.projection = CAMERA_ORTHOGRAPHIC;  // Camera mode type
	gameLogic.Initialize();

	return false;
}

bool Game::Load()
{
	gameLogic.Load();
	return 0;
}

bool Game::BeginRun()
{
	gameLogic.BeginRun(&TheCamera);
	return false;
}

void Game::GameLoop()
{
	while (!WindowShouldClose())
	{
		ProcessInput();
		Update(GetFrameTime());
		Draw();
	}

	Shutdown();
}

void Game::ProcessInput()
{
	gameLogic.Input();
}


void Game::Update(float deltaTime)
{
	gameLogic.Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(TheCamera);

	//3D Drawing here.
	gameLogic.Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.
	gameLogic.Draw2D();

	EndDrawing();
}

void Game::Shutdown()
{
	CloseWindow();
	CloseAudioDevice();
}