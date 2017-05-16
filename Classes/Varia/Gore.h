#pragma once
#ifndef _Gore_H_
#define _Gore_H_

#include"stdafx.h"

class Gore : public Node{
public:
	enum class GoreType
	{
		Warm
	};

public:
	Gore(GoreType type) :
		goreType(type),
		rng(RngT(std::random_device()()))
	{}

	static Gore* create(GoreType type);

	virtual bool init();

	void update(float delta);

	void runWarmDieGore();


	void visibility(float delta);
	void disappear(float delta);

private:
	GoreType goreType;
	RngT rng;
	
};

#endif // !_Gore_H_
