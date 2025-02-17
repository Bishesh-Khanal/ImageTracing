#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"
#include <cstdlib>

class Component
{
public:
	bool has = false;
};

class CTransform : public Component
{
public:
	Vec2 pos = { 0.0f, 0.0f };
	Vec2 prevPos = { 0.0f, 0.0f };
	Vec2 velocity = { 0.0f, 0.0f };
	Vec2 scale = { 1.0f, 1.0f };
	float rotation = 0.0f;
	float speed = 0.0f;
	float angle = 1.0f;

	CTransform()
	{
	}

	CTransform(const Vec2& p, bool h = true)
		: pos(p)
	{
		has = h;
	}

	CTransform(const Vec2& p, const Vec2& v, bool h = true, float r = 0, float s = 0, float a = 0)
		: pos(p)
		, velocity(v)
		, rotation(r)
		, speed(s)
		, angle(a)
	{
		has = h;
	}
};

class CInput : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	CInput()
	{
	}
};

class CShape : public Component
{
public:
	sf::ConvexShape convex;
	size_t size = 0;

	CShape()
	{
	}

	CShape(size_t s, std::vector<std::vector<int>> pos, const sf::Color& color, bool h = true)
		: size(s)
	{
		has = h;
		convex.setPointCount(size);
		for (int i = 0; i < size; i++)
		{
			convex.setPoint(i, sf::Vector2f(pos[i][0], pos[i][1]));
		}
		convex.setFillColor(sf::Color(color));
	}
};