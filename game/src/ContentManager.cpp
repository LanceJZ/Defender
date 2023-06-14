#include "ContentManager.h"

ContentManager::ContentManager()
{

}

ContentManager::~ContentManager()
{
	for (int i = 0; i < LoadedModels.size(); i++)
	{
		UnloadModel(LoadedModels[i]);
	}

	for (int i = 0; i < LoadedSounds.size(); i++)
	{
		UnloadSound(LoadedSounds[i]);
	}

	LoadedModels.clear();
	LoadedSounds.clear();
}

bool ContentManager::Initialize()
{

	return false;
}

bool ContentManager::BeginRun()
{

	return false;
}

int ContentManager::LoadTheModel(std::string modelFileName)
{
	LoadedModels.push_back(LoadModelWithTexture(modelFileName));

	return LoadedModels.size()-1;
}

int ContentManager::LoadTheSound(std::string soundFileName)
{
	LoadedSounds.push_back(LoadSoundFile(soundFileName));

	return LoadedSounds.size() - 1;
}

int ContentManager::LoadTheTexture(std::string textureFileName)
{
	LoadedTextures.push_back(LoadTextureFile(textureFileName));

	return LoadedTextures.size() - 1;
}

Model& ContentManager::GetModel(int modelNumber)
{
	return LoadedModels[modelNumber];
}

Model ContentManager::LoadAndGetModel(std::string modelFilename)
{
	return GetModel(LoadTheModel(modelFilename));
}

Sound& ContentManager::GetSound(int soundNumber)
{
	return LoadedSounds[soundNumber];
}

Sound ContentManager::LoadAndGetSound(std::string soundFileName)
{
	return GetSound(LoadTheSound(soundFileName));
}

Texture& ContentManager::GetTexture(int textureNumber)
{
	return LoadedTextures[textureNumber];
}

Texture ContentManager::LoadAndGetTexture(std::string textureFileName)
{
	return GetTexture(LoadTheTexture(textureFileName));
}
//Load OBJ model file only with texture/material in same folder no path or ext.
Model ContentManager::LoadModelWithTexture(std::string modelFileName)
{
	std::string path = "Models/";

	std::string namePNG = path;
	namePNG.append(modelFileName);
	namePNG.append(".png");

	std::string nameOBJ = path;
	nameOBJ.append(modelFileName);
	nameOBJ.append(".obj");
	Image image = { 0 };
	Model loadModel = { 0 };

	if (FileExists(nameOBJ.c_str()) &&
		FileExists(namePNG.c_str()))
	{
		loadModel = SetTextureToModel(LoadModel((nameOBJ.c_str())),
			LoadTexture(namePNG.c_str()));
	}
	else
	{
		TraceLog(LOG_ERROR, "***********************  Image  :%s missing. ***********************\n",
			(nameOBJ.c_str()));
		TraceLog(LOG_ERROR, "***********************  Image  :%s missing. ***********************\n",
			(namePNG.c_str()));
	}

	return loadModel;
}

Model ContentManager::SetTextureToModel(Model model, Texture2D texture)
{
	if (IsTextureReady(texture))
	{
		model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	}

	return model;
}

Sound ContentManager::LoadSoundFile(std::string soundFileName)
{
	std::string path = "Sounds/";
	std::string nameWAV = path;
	nameWAV.append(soundFileName);
	nameWAV.append(".wav");

	if (!FileExists(nameWAV.c_str()))
	{
		TraceLog(LOG_ERROR, "***********************  Image  :%s missing. ***********************\n",
			(nameWAV.c_str()));
	}

	return LoadSound(nameWAV.c_str());
}
//Load PNG file only, without path or ext.
Texture ContentManager::LoadTextureFile(std::string textureFileName)
{
	std::string path = "Textures/";
	std::string namePNG = path;
	namePNG.append(textureFileName);
	namePNG.append(".png");

	if (!FileExists(namePNG.c_str()))
	{
		TraceLog(LOG_ERROR, "***********************  Image  :%s missing. ***********************\n",
			(namePNG.c_str()));
	}

	return LoadTexture(namePNG.c_str());
}
