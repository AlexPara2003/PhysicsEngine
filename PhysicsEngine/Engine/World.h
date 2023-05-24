#pragma once
#include <list>
#include <glm/glm.hpp>
#include <vector>

class World
{
public:
	~World();

	void Step(float dt);
	void Draw(class Graphics* graphics);

	void AddBody(class Body* body);
	void RemoveBody(class Body* body);

	void AddJoint(class Joint* joint);
	void RemoveJoint(class Joint* joint);

	void AddForceGenerator(class ForceGenerator* forceGenerator);
public:
	static glm::vec2 gravity;

private:
	std::vector<class Body*> m_bodies;
	std::list<class Joint*> m_joints;
	std::vector<class ForceGenerator*> m_forceGenerators;
};