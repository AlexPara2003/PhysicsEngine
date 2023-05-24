#pragma once
#include "ForceGenerator.h"

class DragForce : public ForceGenerator
{
public:
	DragForce(struct Body* body, float drag) :
		ForceGenerator{ body },
		m_drag{ drag }
	{}

	virtual void Apply(std::vector<struct Body*> bodies) override;

protected:
	float m_drag{ 0 };
};