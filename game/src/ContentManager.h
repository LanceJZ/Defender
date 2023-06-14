#pragma once
#include "Common.h"

class ContentManager : Common
{
public:
	ContentManager();
	virtual ~ContentManager();

	bool Initialize();
	bool BeginRun();

	int LoadTheModel(std::string modelFileName); //Without path or ext.
	int LoadTheSound(std::string soundFileName); //Without path or ext.
	int LoadTheTexture(std::string textureFileName); //Without path or ext.
	Model& GetModel(int modelNumber);
	Model LoadAndGetModel(std::string modelFilename); //Without path or ext.
	Sound& GetSound(int soundNumber);
	Sound LoadAndGetSound(std::string soundFileName); //Without path or ext.
	Texture& GetTexture(int textureNumber);
	Texture LoadAndGetTexture(std::string textureFileName); //Without path or ext.

private:
	std::vector<Model> LoadedModels;
	std::vector<Sound> LoadedSounds;
	std::vector<Texture> LoadedTextures;

	Model LoadModelWithTexture(std::string modelFileName);
	Model SetTextureToModel(Model model, Texture2D texture);
	Sound LoadSoundFile(std::string soundFileName);
	Texture LoadTextureFile(std::string textureFileName);
};

