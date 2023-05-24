#include "JointTest.h"
#include "../Physics/Shapes/CircleShape.h" 
#include "../Engine/World.h" 
#include "../Physics/Body.h" 
#include "../Physics/Constraints/Joint.h" 

#define CHAIN

#define SPRING_STIFFNESS 100
#define SPRING_LENGTH 1
#define BODY_DAMPING 10
#define CHAIN_SIZE 3

void JointTest::Initialize()
{
    Test::Initialize();

    m_anchor = new Body(new CircleShape(1, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
    m_world->AddBody(m_anchor);

#if defined(CHAIN)
    auto prevBody = m_anchor;

    //chains
    for (int i = 0; i < CHAIN_SIZE; i++)
    {
        auto body = new Body(new CircleShape(0.5f, { 1, 1, 1, 1 }), { 0, 0 });
        //body->gravityScale = 150;
        body->damping = BODY_DAMPING;
        m_world->AddBody(body);

        auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
        m_world->AddJoint(joint);

        prevBody = body;
    }
#else
    Body* prevA = nullptr;
    Body* prevB = nullptr;
    Joint* joint = nullptr;

    for (int i = 0; i < CHAIN_SIZE; i++)
    {
        auto bodyA = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
        bodyA->gravityScale = 250;
        bodyA->damping = BODY_DAMPING;
        m_world->AddBody(bodyA);
        auto bodyB = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 200, 400 }, { 0, 0 }, 1, Body::DYNAMIC);
        bodyB->gravityScale = 250;
        bodyB->damping = BODY_DAMPING;
        m_world->AddBody(bodyB);
        auto joint = new Joint(bodyA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
        m_world->AddJoint(joint);

        if (!prevA && !prevB)
        {
            joint = new Joint(bodyA, m_anchor, SPRING_STIFFNESS, SPRING_LENGTH);
            m_world->AddJoint(joint);
            joint = new Joint(bodyB, m_anchor, SPRING_STIFFNESS, SPRING_LENGTH);
            m_world->AddJoint(joint);
        }
        else
        {
            joint = new Joint(bodyA, prevA, SPRING_STIFFNESS, SPRING_LENGTH);
            m_world->AddJoint(joint);
            joint = new Joint(bodyB, prevB, SPRING_STIFFNESS, SPRING_LENGTH);
            m_world->AddJoint(joint);
            joint = new Joint(bodyA, prevB, SPRING_STIFFNESS, SPRING_LENGTH);
            m_world->AddJoint(joint);
            joint = new Joint(bodyB, prevA, SPRING_STIFFNESS, SPRING_LENGTH);
            m_world->AddJoint(joint);
        }
        prevA = bodyA;
        prevB = bodyB;
    }
#endif



}

void JointTest::Update()
{
    Test::Update();
    m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
    m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
    m_world->Draw(m_graphics);
    m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}