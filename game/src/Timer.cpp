#include "Timer.h"

void Timer::Update(float deltaTime)
{
    TheSeconds += deltaTime;
}

void Timer::Set(float amountInSeconds)
{
    TheAmount = amountInSeconds;
}

void Timer::Reset()
{
    TheSeconds = 0;
}

void Timer::Reset(float amoutInSeconds)
{
    Reset();
    Set(amoutInSeconds);
}

bool Timer::Elapsed()
{
    return TheSeconds > TheAmount;
}
