#include "Grapple.h"
#include "Renderer2D.h"
#include "RayController.h"
#include "Grab.h"
#include "nicolausYes_easing.h"

#ifndef PI
#define PI 3.14159265359;
#endif

Grapple::Grapple(Vector2 &origin, Vector2 &direction)
{
	m_length = 250;

	m_ray = {origin, direction, m_length};

	m_rayAngle = atan2(direction.y, direction.x); //remember y then x with atan

}

Grapple::~Grapple()
{
}

void Grapple::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(.3f, .3f, .3f);

	renderer->drawCircle((m_ray.origin.x), (m_ray.origin.y), 10); //comfy dot at origin
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y,		//line
		m_ray.origin.x + m_ray.direction.x *m_ray.length,	//starting HERE THIS way by LENGTH
		m_ray.origin.y + m_ray.direction.y *m_ray.length,   //starting HERE THIS way by LENGTH
		5);
}

void Grapple::Update(float deltatime,Plane& plane, std::vector<GrapplePoint>& Points,float distance)
{
	//todo fix
	//fall to ground
	if(plane.distanceTo(m_ray.origin) > 10){velocity.y -= 200 * deltatime; }
	//move
	raycontroller(m_ray, m_rayAngle, velocity, deltatime);
	m_ray.origin += velocity * deltatime;
	velocity -= (velocity * deltatime) / 4;
	Grab(this, deltatime, Points, distance);
	//keep above ground
	
	if (plane.distanceTo(m_ray.origin) < 10) { velocity.y = -velocity.y * 1; }
	if (plane.distanceTo(m_ray.origin) < 1) {
		m_ray.origin.y = 10;
		velocity.y = 0;
	}
}

float Grapple::get_angle()
{
	while (m_rayAngle > 6.283185307) { m_rayAngle -= 6.283185307; }
	return m_rayAngle;
}

Ray Grapple::get_ray()
{
	return m_ray;
}

float Grapple::get_angle_deg()
{
	auto temp = 180 / PI;
	while (m_rayAngle > 6.283185307) { m_rayAngle -= 6.283185307; }
	return m_rayAngle * temp;
}
