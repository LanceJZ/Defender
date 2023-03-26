#pragma once
#include "Entity.h"
#include <vector>
#include <string>
#include "rlgl.h"

class LineModel : public Entity
{
public:
	Color ModelColor = WHITE;
	float Alpha = 255;

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Load();
	void LoadModel(std::string fileName);

	std::vector<Vector3> GetModel();
	std::vector<Vector3> LinePoints;
	void SetModel(std::vector<Vector3> lines);

private:
	std::vector<Vector3> ConvertStringToVector(std::string linesString);
	void DrawLines(std::vector <Vector3> points, Vector3 rotationAxis, Color color);
	void DrawLines(Color color);
};