#include "Game.h"
#include "raymath.h"
#include <string>

Game::Game()
{
	gameLogic = new GameLogic();
}

Game::~Game()
{

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

bool Game::Initialize()
{
	InitWindow(1280, 960, "Defender"); //Screen width, height and Window title.
	InitAudioDevice();
	SetTargetFPS(60);

	Image icon = LoadImage("icon-PKG_32x32.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);
	// Define the camera to look into our 3D world
	camera.position = { 0.0f, 0.0f, 500.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };     // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };         // Camera up vector (rotation towards target)
	camera.fovy = (float)GetScreenHeight();          // Camera field-of-view Y. In Orthographic is scale.
	camera.projection = CAMERA_ORTHOGRAPHIC;
	//SetCameraMode(camera, CAMERA_ORBITAL); // Camera mode type
	gameLogic->Initialize();
	gameLogic->SetCamera(&camera);

	return false;
}

bool Game::Load()
{
	gameLogic->Load();
	return 0;
}

bool Game::BeginRun()
{
	gameLogic->BeginRun();
	return false;
}

void Game::ProcessInput()
{
	gameLogic->Input();
}


void Game::Update(float deltaTime)
{
	gameLogic->Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(camera);

	//3D Drawing here.
	gameLogic->Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.
	gameLogic->Draw2D();

	EndDrawing();
}

void Game::Shutdown()
{
	CloseWindow();
	CloseAudioDevice();
}