#pragma once

#include <random>

template<typename T>
class RandomGenerator {
public:
	RandomGenerator(RandomGenerator const&) = delete;
	void operator=(RandomGenerator const&) = delete;

	static RandomGenerator& getGenerator();
	T getRandom(T begin, T end);
private:
	RandomGenerator() {}

	static std::random_device rd;
	static std::mt19937 generate;
};
