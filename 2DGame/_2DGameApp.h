#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "Ray.h"
#include "Vector3.h"

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


	aie::Font*	m_font;//FPS FONT
	float m_timer;//DELTA TIME MEMBER VAR


	Vector2 m_point_1,m_point_2,m_point_3, m_point_4;
	Vector2 spline_point_1, spline_point_2, spline_point_3;
	Vector2 mid_point_12, mid_point_23;
	Vector2 mid_of_mids;

	std::vector<Vector2> all;

	float t_value;
	Vector2 m_mouse;
;
	//colours
	Vector3 m_colour;

	std::vector<Vector2> points;

	Vector2 ship;
	float count;
	Vector2 ship_dest;

	// create a series of points in our spline

};
