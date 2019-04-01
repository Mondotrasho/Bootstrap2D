#include "_2DGameApp.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"

_2DGameApp::_2DGameApp() {

}
_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_navMesh = new NavMesh(1280, 720);

	// just to help mess with the random 1 is asy to debug the pop issue
	srand(1);

	// random obstacles
	for (int i = 0; i < 12; ++i) {

		bool safe = false;
		do {
			safe = m_navMesh->addObstacle(rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
				rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f,
				60, 60,
				10);
		} while (safe == false);
	}

	m_navMesh->build();

	Fish = new GameObject;
	Mouse = new GameObject;
	Fish->position = Vector2(getWindowWidth() / 2, getWindowHeight() / 2);
	Fish->speed = 400;
	Mouse->position = Vector2(getWindowWidth() / 2 + 100, getWindowHeight() / 2 +100);


	follow = new FollowPathBehaviour();
	Fish->behaviours.emplace_back(follow);
	newpath = new NewPathBehaviour(m_navMesh, Fish->smoothPath);
	newpath->m_navMesh = m_navMesh;
	newpath->m_smoothPath = Fish->smoothPath;// = NewPathBehaviour(m_navMesh, Fish->smoothPath);
	//Fish->behaviours.emplace_back(newpath);
	mousepath = new MouseGenPathBehaviour(m_navMesh, Fish->smoothPath);
	mousepath->m_navMesh = m_navMesh;
	mousepath->m_smoothPath = Fish->smoothPath;
	mousepath->settarget(Mouse);
	Fish->behaviours.emplace_back(mousepath);
	return true;
}

void _2DGameApp::shutdown() {

	delete m_navMesh;

	delete m_font;
	delete m_2dRenderer;
}

void _2DGameApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	Fish->Update(deltaTime);

	if(input->isMouseButtonDown(0))
		Mouse->position = Vector2(input->getMouseX(), input->getMouseY());
	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _2DGameApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	//auto a = m_navMesh->getRandomNode();
	//auto b = m_navMesh->getRandomNode();
	//std::list<Node*> c;
	//c.push_back(a);
	//c.push_back(b);
	//
	//const std::list<Node*> e = { c };
	//
	//std::list<Vector2> d;
	//auto size = m_navMesh->smoothPath(e, d);
	// draw nav mesh polygons
	for (auto node : m_navMesh->getNodes()) {

		m_2dRenderer->setRenderColour(1, 1, 0);
		m_2dRenderer->drawLine(node->vertices[0].x, node->vertices[0].y, node->vertices[1].x, node->vertices[1].y);
		m_2dRenderer->drawLine(node->vertices[1].x, node->vertices[1].y, node->vertices[2].x, node->vertices[2].y);
		m_2dRenderer->drawLine(node->vertices[2].x, node->vertices[2].y, node->vertices[0].x, node->vertices[0].y);
		
		node->Draw(m_2dRenderer);
	}
	m_2dRenderer->setRenderColour(0, 1, 0);
	if (!Fish->smoothPath.empty()) {
		Vector2 last = Fish->smoothPath.front();
		for (auto place : Fish->smoothPath)
		{
			m_2dRenderer->drawCircle(place.x, place.y, 2);
			m_2dRenderer->drawLine(place.x, place.y, last.x, last.y, 1);
			last = place;
		}
	
	m_2dRenderer->setRenderColour(1, 0, 0);
	last = Fish->path.front()->Pos;
	for (auto place : Fish->path)
	{
		
		m_2dRenderer->drawCircle(place->Pos.x, place->Pos.y, 2);
		m_2dRenderer->drawLine(place->Pos.x, place->Pos.y, last.x, last.y, 1);
		last = place->Pos;
	}
	}
	// draw obstacles
	m_2dRenderer->setRenderColour(1, 0, 0);
	for (auto& o : m_navMesh->getObstacles()) {
		m_2dRenderer->drawBox(o.x + o.w * 0.5f, o.y + o.h * 0.5f, o.w, o.h);
	}

	Fish->Draw(m_2dRenderer);
	// done drawing sprites
	m_2dRenderer->end();
}