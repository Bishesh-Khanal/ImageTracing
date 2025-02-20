#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include "Animation.h"

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

class CBoundingBox : public Component
{
public:
	Vec2 boundingbox = { 0.0f, 0.0f };
	Vec2 halfSize = { 0.0f, 0.0f };
	sf::Color boxColor;
	sf::RectangleShape rectangle;
	std::vector<Vec2>m_VerticesTarget;
	
	CBoundingBox()
	{
	}

	CBoundingBox(const Vec2& bbox, const Vec2& position, const sf::Color& color = sf::Color::White, bool h = true)
		: boundingbox(bbox)
		, boxColor(color)
		, halfSize(bbox / 2)
		, m_VerticesTarget(4)
	{
		rectangle.setPosition(position.x, position.y);

		m_VerticesTarget[0] = Vec2(position.x - halfSize.x, position.y - halfSize.y);
		m_VerticesTarget[1] = Vec2(position.x + halfSize.x, position.y - halfSize.y);
		m_VerticesTarget[2] = Vec2(position.x + halfSize.x, position.y + halfSize.y);
		m_VerticesTarget[3] = Vec2(position.x - halfSize.x, position.y + halfSize.y);

		has = h;

		rectangle.setSize(sf::Vector2f(bbox.x, bbox.y));
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color(boxColor));
		rectangle.setOutlineThickness(1.0f);
		rectangle.setOrigin(bbox.x / 2, bbox.y / 2);
	}
};

class CAnimation : public Component
{
public:
	bool destroy = false;

	Animation animation;

	CAnimation()
	{
	}

	CAnimation(const Animation anim, bool d, bool h = true)
		: animation(anim)
		, destroy(d)
	{
		has = h;
	}
};

class CTexture : public Component
{
public :
	std::vector<Vec2> m_TexturePoints;
	std::vector<sf::Vector2f> screenShape;
	std::vector<sf::Vector2f> textureShape;
	sf::VertexArray triangles;
	sf::RenderStates states;

	CTexture()
	{ }

	CTexture(size_t s)
		: screenShape(s)
		, textureShape(s)
	{
	}
};