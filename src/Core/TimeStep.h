#pragma once


class TimeStep {
public:
	TimeStep(float lastFrameTime, float time = 0.0f)
		: time(time), lastframeTime(lastFrameTime) {};

	operator float() const { return time; }

	float GetSeconds() const { return time; }
	float GetMilliseconds() const { return time * 1000.f; }

	inline void Update(double currentTime)
	{
		time = currentTime - lastframeTime;
		lastframeTime = currentTime;
	};
private:
	float time;
	float lastframeTime;
};