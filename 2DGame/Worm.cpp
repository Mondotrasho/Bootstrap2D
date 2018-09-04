#include "Worm.h"
#include "Input.h"


Worm::Worm()
{
}

Worm::Worm(const char* WormImage, const char* worm_body_image)
{


	load(WormImage);
	m_body1.load(worm_body_image);
	m_body2.load(worm_body_image);
	m_body3.load(worm_body_image);
	m_body4.load(worm_body_image);
	m_body5.load(worm_body_image);
	m_body6.load(worm_body_image);

	// attach Wormbody to top of Worm
	addChild(&m_body1);
	m_body1.scale(0.9, 0.9);
	m_body1.setPosition(0, -60);
	m_body1.addChild(&m_body2);
	m_body2.scale(0.9, 0.9);
	m_body2.setPosition(0, -60);
	m_body2.addChild(&m_body3);
	m_body3.scale(0.9, 0.9);
	m_body3.setPosition(0, -60);
	m_body3.addChild(&m_body4);
	m_body4.scale(0.9, 0.9);
	m_body4.setPosition(0, -60);
	m_body4.addChild(&m_body5);
	m_body5.scale(0.9, 0.9);
	m_body5.setPosition(0, -60);
	m_body5.addChild(&m_body6);


}

Worm::~Worm()
{
}


void Worm::setup(const char* WormImage, const char* worm_body_image)
{
	//shrink
	scale(0.5, 0.5);
	//load textures
	load(WormImage);
	m_body1.load(worm_body_image);
	m_body2.load(worm_body_image);
	m_body3.load(worm_body_image);
	m_body4.load(worm_body_image);
	m_body5.load(worm_body_image);
	m_body6.load(worm_body_image);

	//attach body segments
	addChild(&m_body1);
	m_body1.scale(0.9, 0.9);
	m_body1.setPosition(0, -60);
	m_body1.addChild(&m_body2);
	m_body2.scale(0.9,0.9);
	m_body2.setPosition(0,-60);
	m_body2.addChild(&m_body3);
	m_body3.scale(0.9, 0.9);
	m_body3.setPosition(0, -60);
	m_body3.addChild(&m_body4);
	m_body4.scale(0.9, 0.9);
	m_body4.setPosition(0, -60);
	m_body4.addChild(&m_body5);
	m_body5.scale(0.9, 0.9);
	m_body5.setPosition(0, -60);
	m_body5.addChild(&m_body6);
	

}

void Worm::onUpdate(float deltaTime, std::vector<Plane>& planes)
{
	// input example
	aie::Input* input = aie::Input::getInstance();	
	// rotate Worm
	if (worm_states == 1) {
		rotate(-deltaTime);

	m_body1.rotate(0.4f * deltaTime);
	m_body2.rotate(0.4f * deltaTime);
	m_body3.rotate(0.4f * deltaTime);
	m_body4.rotate(0.4f * deltaTime);
	m_body5.rotate(0.4f * deltaTime);
	m_body5.rotate(0.4f * deltaTime);
	//rotate(-deltaTime*3);
}
if (worm_states == 2) {
	rotate(deltaTime);
	m_body1.rotate(-0.4f * deltaTime);
	m_body2.rotate(-0.4f * deltaTime);
	m_body3.rotate(-0.4f * deltaTime);
	m_body4.rotate(-0.4f * deltaTime);
	m_body5.rotate(-0.4f * deltaTime);
	m_body5.rotate(-0.4f * deltaTime);
}

	//correct rotation
if (m_body1.getLocalTransform().x_axis.y < 0) {
	m_body1.rotate(0.3f* deltaTime);
	m_body2.rotate(0.3f* deltaTime);
	m_body3.rotate(0.3f* deltaTime);
	m_body4.rotate(0.3f* deltaTime);
	m_body5.rotate(0.3f* deltaTime);
	m_body6.rotate(0.3f* deltaTime);
}
if (m_body1.getLocalTransform().x_axis.y > 0) {
	m_body1.rotate(-0.3f* deltaTime);
	m_body2.rotate(-0.3f* deltaTime);
	m_body3.rotate(-0.3f* deltaTime);
	m_body4.rotate(-0.3f* deltaTime);
	m_body5.rotate(-0.3f* deltaTime);
	m_body6.rotate(-0.3f* deltaTime);
}

for (auto p : planes)
{
	//top and bottom planes
	if (p.N.x == 0 && p.distanceTo(worm_face.closestPoint(p.closestPoint(worm_face.center))) < 10)
	{
		if (p.N.y == 1) {
			auto facing = getLocalTransform()[1];
			translate(facing.x, facing.y*-velocity.y + 1.5f);
			updateTransform();
		}
		if (p.N.y == -1) {
			auto facing = getLocalTransform()[1];
			translate(facing.x, facing.y*-velocity.y - 1.5f);
			updateTransform();
		}
		
	}
	//left and right planes
	if (p.N.y == 0 && p.distanceTo(worm_face.closestPoint(p.closestPoint(worm_face.center))) < 10)
	{
		if (p.N.x == 1) {
			auto facing = getLocalTransform()[1];
			translate(facing.x*-velocity.x, facing.y + 1.5f);
			updateTransform();
		}
		if (p.N.x == -1) {
			auto facing = getLocalTransform()[1];
			translate(facing.x*-velocity.x, facing.y - 1.5f);
			updateTransform();
		}
	}
	
}
;

auto facing = getLocalTransform()[1];
translate(facing.x*velocity.x, facing.y*velocity.y);


}
