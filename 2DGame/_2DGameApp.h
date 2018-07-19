#pragma once

#include "Application.h"
#include "Renderer2D.h"


class GameObject;


class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	GameObject*			m_player;
	GameObject*			m_enemy;

	float m_timer;//DELTA TIME MEMBER VAR
};
