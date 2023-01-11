#pragma once


class TimeStep {
public:
	TimeStep(float time = 0.0f)
		: time(time) {};

	operator float() const { return time; }

	float GetSeconds() const { return time; }
	float GetMilliseconds() const { return time * 1000.f; }
private:
	float time;
};