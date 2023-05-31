#include "LineModel.h"
#include "rlgl.h"

void LineModel::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	ModelColor.a = (char)Alpha;
}

void LineModel::Draw()
{
	Entity::Draw();

	if (!Enabled)
	{
		return;
	}

	if (LinePoints.size() < 2)
	{
		return;
	}

	rlPushMatrix();

	if (IsConnectedChild)
	{
		for (auto parent : Parents)
		{
			rlTranslatef(parent->Position.x, parent->Position.y, Position.z);
			rlRotatef(parent->Rotation * (float)(180.0f / PI), RotationAxis.x, RotationAxis.y, RotationAxis.z);
		}
	}

	rlTranslatef(Position.x, Position.y, Position.z);
	rlRotatef(Rotation * (float)(180.0f / PI), RotationAxis.x, RotationAxis.y, RotationAxis.z);
	rlScalef(Scale, Scale, Scale);
	rlBegin(RL_LINES);
	rlColor4ub(ModelColor.r, ModelColor.g, ModelColor.b, ModelColor.a);

	int one = 1;

	for (int i = 0; i < LinePoints.size() - 1; i++)
	{
		rlVertex3f(LinePoints[i].x, LinePoints[i].y, LinePoints[i].z);
		rlVertex3f(
			LinePoints[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].x,
			LinePoints[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].y,
			LinePoints[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].z
		);
	}

	rlPopMatrix();
	rlEnd();
}

void LineModel::Load()
{

}

void LineModel::LoadModel(std::string fileName)
{
	if (FileExists(fileName.c_str()))
	{
		std::string linesTemp = LoadFileText(fileName.c_str());
		LinePoints = ConvertStringToVector(linesTemp);
	}
}

std::vector<Vector3> LineModel::GetModel()
{
	return LinePoints;
}

void LineModel::SetModel(std::vector<Vector3> lines)
{
	LineModel::LinePoints = lines;
}

std::vector<Vector3> LineModel::ConvertStringToVector(std::string linesString)
{
	std::vector<Vector3> linesConverted;
	bool isNumber = false;
	float x = 0;
	float y = 0;
	float z = 0;
	std::string number;
	std::string onAxis;
	Vector3 line = { 0 };

	for (auto character : linesString)
	{
		if (character > 44 && character < 58)
		{
			number.append(1, character);
		}
		else
		{
			if (character == 88)
			{
				onAxis = "X";
			}
			else if (character == 89)
			{
				onAxis = "Y";

				line.x = stof(number);
				number = "";
			}
			else if (character == 90)
			{
				onAxis = "Z";

				line.y = stof(number);
				number = "";
			}
			else if (character == 125)
			{
				line.z = stof(number);
				number = "";

				linesConverted.push_back(line);
			}
		}
	}

	return linesConverted;
}

void LineModel::DrawLines(std::vector <Vector3> points, Vector3 rotationAxis, Color color)
{
	if (points.size() >= 2)
	{
		rlPushMatrix();
		rlTranslatef(Position.x, Position.y, 0);
		rlRotatef(Rotation * (float)(180.0f / PI), rotationAxis.x, rotationAxis.y, rotationAxis.z);
		rlBegin(RL_LINES);
		rlColor4ub(color.r, color.g, color.b, color.a);

		for (int i = 0; i < points.size() - 1; i++)
		{
			rlVertex3f(points[i].x, points[i].y, points[i].z);
			rlVertex3f(
				points[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].x,
				points[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].y,
				points[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].z
			);
		}

		rlEnd();
		rlPopMatrix();
	}
}

void LineModel::DrawLines(Color color)
{
	rlBegin(RL_LINES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	for (int i = 0; i < LinePoints.size() - 1; i++)
	{
		rlVertex3f(LinePoints[i].x, LinePoints[i].y, LinePoints[i].z);
		rlVertex3f(
			LinePoints[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].x,
			LinePoints[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].y,
			LinePoints[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(i) + 1].z
		);
	}

	rlEnd();
}
