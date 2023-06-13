#pragma once
#include "Common.h"
#include <vector>

class ContentManager : Common
{
public:
	ContentManager();
	virtual ~ContentManager();

	bool Initialize();
	bool BeginRun();

	int LoadTheModel(std::string modelFileName);
	Model& GetModel(int modelNumber);
	Model LoadAndGetModel(std::string modelFilename);

private:
	std::vector<Model> LoadedModels;

	Model LoadModelWithTexture(std::string modelFileName);
	Model SetTextureToModel(Model model, Texture2D texture);

};

