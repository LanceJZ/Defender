#pragma once
class Timer
{
public:
	void Update(float deltaTime);

	void Set(float amountInSeconds);
	void Reset();
	void Reset(float amoutInSeconds);
	bool Elapsed();

private:
	float TheSeconds;
	float TheAmount;
};

