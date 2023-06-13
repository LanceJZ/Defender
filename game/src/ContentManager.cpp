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

Model& ContentManager::GetModel(int modelNumber)
{
	return LoadedModels[modelNumber];
}

Model ContentManager::LoadAndGetModel(std::string modelFilename)
{
	return GetModel(LoadTheModel(modelFilename));
}

Model ContentManager::LoadModelWithTexture(std::string modelFileName)
{
	std::string path = "models/";

	std::string namePNG = path;
	namePNG.append(modelFileName);
	namePNG.append(".png");

	std::string nameOBJ = path;
	nameOBJ.append(modelFileName);
	nameOBJ.append(".obj");
	Image image = { 0 };
	Model loadModel = { 0 };

	if (FileExists((nameOBJ.c_str())) &&
		FileExists((namePNG.c_str())))
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