#pragma once
#include "Behaviour.h"
#include "GameObject.h"
#include "Utilities.h"

class ActionMoveAlongPath :
	public Behaviour
{
public:
	ActionMoveAlongPath();
	~ActionMoveAlongPath();

	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		if (gameObject->target != nullptr) {
			if (gameObject->target->Occupied == gameObject->Occupied)
			{
				return SUCCESS;
			}
		}
		if (gameObject->smoothPath.empty())
			return SUCCESS;

		// access first node we're heading towards
		Vector2 first = gameObject->smoothPath.front();

		// distance to first
		float xDiff = first.x - gameObject->position.x;
		float yDiff = first.y - gameObject->position.y;

		float distance = xDiff * xDiff + yDiff * yDiff;

		// if not at the target then move towards it
		if (distance > 25) {

			distance = sqrt(distance);
			xDiff /= distance;
			yDiff /= distance;

			// move to target (can overshoot!)
			gameObject->position.x += xDiff * gameObject->speed * deltaTime;
			gameObject->position.y += yDiff * gameObject->speed * deltaTime;

			auto dir = gameObject->position - first;
			auto angle = Vector2(0, 1).angle_between(dir);

			if (gameObject->position.x < first.x)
			{
				gameObject->angle = angle;
			}
			if (gameObject->position.x > first.x)
			{
				gameObject->angle = -angle;
			}
		}
		else {
			// at the node, remove it and move to the next
			gameObject->smoothPath.pop_front();
			gameObject->path.pop_front();
		}
		return RUNNING;
	}
};

