#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B)
{
	if (A.x + A.w >= B.x &&
		B.x + B.w >= A.x &&
		A.y + A.h >= B.y &&
		B.y + B.h >= A.y)
	{
		std::cout << "collision" << std::endl;
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.getCollider(), colB.getCollider()))
	{
		return true;
	}
	return false;
}

bool Collision::Circular(const SDL_Rect& A, const SDL_Rect& B) 
{
	if (sqrt(pow((A.x + A.w / 2), 2) + pow((B.x + B.w / 2), 2)) >= A.w / 2 + B.w / 2)
	{
		std::cout << "collision" << std::endl;
		return true;
	}
	return false;
}

bool Collision::Circular(const ColliderComponent& colA, const ColliderComponent& colB) 
{
	if (Circular(colA.getCollider(), colB.getCollider()))
	{
		return true;
	}
	return false;
}
