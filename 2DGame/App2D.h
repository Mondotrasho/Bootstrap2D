#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "FollowBehaviour.h"
#include "GameObject.h"

class App2D : public aie::Application {
public:

	App2D();
	virtual ~App2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	float m_cameraX, m_cameraY;
	float m_timer;

	GameObject m_player;
	FollowBehaviour m_playerFollowBehaviour;
	GameObject m_enemy;
	FollowBehaviour m_followBehaviour;

	GameObject Mouse;
};