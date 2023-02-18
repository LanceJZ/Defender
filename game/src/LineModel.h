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
	void LoadModel(string fileName);

	vector<Vector3> GetModel();
	vector<Vector3> LinePoints;
	void SetModel(vector<Vector3> lines);

private:
	vector<Vector3> ConvertStringToVector(string linesString);
	void DrawLines(vector <Vector3> points, Vector3 rotationAxis, Color color);
	void DrawLines(Color color);
};