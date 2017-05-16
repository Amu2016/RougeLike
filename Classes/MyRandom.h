#pragma once
#ifndef _MyRandom_H_
#define _MyRandom_H_
#include"stdafx.h"

//int getRandomInt(RngT& rng, int min, int max) {
//	return std::uniform_int_distribution<int>(min, max)(rng);
//}

inline float getRandomFloat(RngT& rng, const float min, const float max) {
	return std::uniform_real_distribution<float>(min, max)(rng);
}

inline int getMyRandomInt(RngT& rng, const int min, const int max) {
	return std::uniform_int_distribution<int>(min, max)(rng);
}

inline Vec2 getRandomVec2Int(RngT& rng, const int min, const int max) {
	return Vec2(getMyRandomInt(rng, min, max), getMyRandomInt(rng, min, max));
}

inline float randomClamped(RngT& rng) {
	return std::uniform_real_distribution<float>(-1.0f, 1.0f)(rng);
}


#endif // !_MyRandom_H_
