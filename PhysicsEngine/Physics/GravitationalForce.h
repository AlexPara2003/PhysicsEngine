#pragma once
#include "Forces/ForceGenerator.h"

class GravitationalForce : public ForceGenerator
{
public:
	GravitationalForce(float strength) : m_strength{ strength } {}

	void Apply(std::vector<class Body*> bodies) override;

private:
	float m_strength{ 0 };
};