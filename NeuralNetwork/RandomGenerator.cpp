#include "stdafx.h"
#include "RandomGenerator.h"

template<typename T>
std::random_device RandomGenerator<T>::rd;
template<typename T>
std::mt19937 RandomGenerator<T>::generate(RandomGenerator<T>::rd());

template<typename T>
RandomGenerator<T> & RandomGenerator<T>::getGenerator()
{
	static RandomGenerator<T> instance;
	return instance;
}

template<typename T>
T RandomGenerator<T>::getRandom(T begin, T end)
{
	return T();
}

template<>
int RandomGenerator<int>::getRandom(int begin, int end)
{
	std::uniform_int_distribution<> rInt(begin, end);
	return rInt(generate);
}

template<>
double RandomGenerator<double>::getRandom(double begin, double end)
{
	std::uniform_real_distribution<> rDouble(begin, end);
	return rDouble(generate);
}

template<>
float RandomGenerator<float>::getRandom(float begin, float end)
{
	std::uniform_real_distribution<> rFloat(begin, end);
	return static_cast<float>(rFloat(generate));
}

template class RandomGenerator<int>;
template RandomGenerator<int>& RandomGenerator<int>::getGenerator();
template int RandomGenerator<int>::getRandom(int begin, int end);

template class RandomGenerator<double>;
template RandomGenerator<double>& RandomGenerator<double>::getGenerator();
template double RandomGenerator<double>::getRandom(double begin, double end);

template class RandomGenerator<float>;
template RandomGenerator<float>& RandomGenerator<float>::getGenerator();
template float RandomGenerator<float>::getRandom(float begin, float end);
