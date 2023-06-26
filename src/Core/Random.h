#pragma once
#include <cstdlib> 
#include <ctime> 
#include "Logging.h"
#include <random>  

class RandomGenerator {
public:
	inline static int random(int max) 
	{
		// Non-deterministic generator
	   // to seed mersenne twister.
	   // Random values on each execution.
		std::random_device rd;
		std::mt19937 engine(rd());

		// Use the uniform distribution to generate
		// a value between lower and upper bound inclusive.
		std::uniform_int_distribution<> dist(0, max);

		int i;
		i = dist(engine);

		LOG_INFO(i);
		return i;
	}
};