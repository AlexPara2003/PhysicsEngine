#include "Body.h"
#include "Integrator.h"
#include "..\Engine\World.h"
#include "..\Physics\Shapes\Shape.h"
#include "..\Physics\Shapes\CircleShape.h"

void Body::ApplyForce(const glm::vec2& force)
{
	this->force += force;
}

void Body::Step(float dt)
{
	if (type != DYNAMIC) return;

	//gravity
	ApplyForce(World::gravity * gravityScale * mass);

	Integrator::ExplicitEuler(*this, dt);
	ClearForce();

	//damping
	velocity *= (1.0f / (1.0f + dt * damping));
}

void Body::Draw(Graphics* graphics)
{
	shape->Draw(graphics, position);
}

bool Body::Intersects(Body* body)
{
	glm::vec2 direction = body->position - this->position ;
	float distance = glm::length(direction);
	float radius = dynamic_cast<CircleShape*>(this->shape)->radius + 
		static_cast<CircleShape*>(body->shape)->radius;

	return distance <= radius;
}