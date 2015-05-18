#pragma once
#include <vector>
class Layer
{
public:
	virtual void render() = 0;
	virtual void update() = 0;

protected:

	virtual ~Layer(){}
};

