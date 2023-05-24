#pragma once

#include <SDL2/SDL.h>
#include <math.h>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool Circular(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool Circular(const SDL_Rect& A, const SDL_Rect& B);
};