#include "Integrator.h"

namespace Integrator
{
	void Integrator::ExplicitEuler(Body& body, float dt)
	{
		body.position += body.velocity * dt;
		body.velocity += (body.force * body.invMass) * dt;
	}

	void Integrator::SemiImplicitEuler(Body& body, float dt)
	{
		body.velocity += (body.force * body.invMass) * dt;
		body.position += body.velocity * dt;
	}
}