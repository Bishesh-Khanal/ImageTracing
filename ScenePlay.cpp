#include "ScenePlay.h"
#include "GameEngine.h"

#include <fstream>
#include <sstream>

void ScenePlay::init()
{
	std::cout << "Game started" << std::endl;
	std::cout << m_game->m_width << " " << m_game->m_height << std::endl;
	std::vector<std::vector<int>> pos;
	pos = { { 0, 0 }, { 0, static_cast<int>(m_game->m_height) }, { static_cast<int>(m_game->m_width), static_cast<int>(m_game->m_height) }, { static_cast<int>(m_game->m_width), 0 } };
	enemySpawner(pos, sf::Color::Black);
	pos = { { 100, 100 }, { 450, 110 }, { 620,390 }, { 430, 400 }, { 300, 350 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
	pos = { { 600, 800 }, { 950, 810 }, { 1120,1090 }, { 930, 1100 }, { 800, 1050 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
	pos = { { 970, 400 }, { 1320, 410 }, { 1490,690 }, { 1300, 700 }, { 1170, 650 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
	pos = { { 1350, 100 }, { 1700, 110 }, { 1870,390 }, { 1680, 400 }, { 1550, 350 } };
	enemySpawner(pos, sf::Color(192, 192, 192));

	auto target1 = m_entities.addEntity("target");
	target1->addComponent<CAnimation>(m_game->getAssets().getAnimation("Circle"), false);
	target1->addComponent<CTransform>(Vec2(550, 600));
	target1->addComponent<CBoundingBox>(Vec2(target1->getComponent<CAnimation>().animation.getSize().x, target1->getComponent<CAnimation>().animation.getSize().y), target1->getComponent<CTransform>().pos, sf::Color::Red);

	auto target2 = m_entities.addEntity("target");
	target2->addComponent<CAnimation>(m_game->getAssets().getAnimation("Circle"), false);
	target2->addComponent<CTransform>(Vec2(1500, 900));
	target2->addComponent<CBoundingBox>(Vec2(target2->getComponent<CAnimation>().animation.getSize().x, target2->getComponent<CAnimation>().animation.getSize().y), target2->getComponent<CTransform>().pos, sf::Color::Red);
}

void ScenePlay::enemySpawner(std::vector<std::vector<int>> pos, const sf::Color& color)
{
	auto entity = m_entities.addEntity("enemy");

	entity->addComponent<CShape>(pos.size(), pos, color);
}


ScenePlay::ScenePlay(std::shared_ptr<GameEngine> game)
	: Scene(std::move(game))
{
	init();
}

void ScenePlay::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "MOUSE_MOVE")
		{
			m_mPos = action.pos();
			m_mShape.setPosition(m_mPos.x, m_mPos.y);
		}
	}

	if (action.type() == "END")
	{
	}
}

void ScenePlay::update() {
	m_entities.update();
}


void ScenePlay::onEnd()
{
	for (auto& entity : m_entities.getEntities())
	{
		entity->destroy();
	}
	m_game->quit();
}

ScenePlay::Intersect ScenePlay::intersection(const Vec2& a, const Vec2& b)
{
	Vec2 r = b - a;
	Vec2 c, d;

	std::vector<Vec2> intersectionPoints(0);
	for (auto& entity : m_entities.getEntities("enemy"))
	{
		auto& shapeComponent = entity->getComponent<CShape>();
		auto& convexShape = shapeComponent.convex;

		if (shapeComponent.size <= 0) continue;

		for (int i = 0; i < shapeComponent.size; i++)
		{
			c = Vec2(convexShape.getPoint(i).x, convexShape.getPoint(i).y);
			d = Vec2(convexShape.getPoint((i + 1) % shapeComponent.size).x, convexShape.getPoint((i + 1) % shapeComponent.size).y);
			Vec2 s = d - c;
			float rxs = r.x * s.y - r.y * s.x;

			if (rxs == 0) continue;

			Vec2 cma = c - a;
			float t = (cma.x * s.y - cma.y * s.x) / rxs;
			float u = (cma.x * r.y - cma.y * r.x) / rxs;
			if ((t > 0 && t < 1) && (u > 0 && u < 1))
			{
				//return { true, Vec2(a.x + t * r.x, a.y + t * r.y) };
				intersectionPoints.push_back(Vec2(a.x + t * r.x, a.y + t * r.y));
			}
		}
	}
	size_t size = intersectionPoints.size();
	if (size != 0)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			bool swapped = false;
			for (int j = 0; j < size - i - 1; ++j)
			{
				if (a.distq(intersectionPoints[j]) > a.distq(intersectionPoints[j + 1]))
				{
					std::swap(intersectionPoints[j], intersectionPoints[j + 1]);
					swapped = true;
				}
			}
			if (!swapped)
			{
				break;
			}
		}
		return { true, intersectionPoints[0], {}};
	}
	return { false, Vec2(0, 0), {} };
}

ScenePlay::Intersect ScenePlay::checkIntersectionTarget( const Vec2& intersectedPoint, const std::vector<Vec2>& verticesTarget) const
{
	Vec2 r = intersectedPoint - m_mPos;
	Vec2 c, d;
	std::vector<Vec2> intersectionPointsTarget(0);

	for (size_t i = 0; i < 4; i++)
	{
		c = verticesTarget[i];
		d = verticesTarget[(i + 1) % 4];
		Vec2 s = d - c;
		float rxs = r.x * s.y - r.y * s.x;

		if (rxs == 0) continue;

		Vec2 cma = c - m_mPos;
		float t = (cma.x * s.y - cma.y * s.x) / rxs;
		float u = (cma.x * r.y - cma.y * r.x) / rxs;
		if ((t > 0 && t < 1) && (u > 0 && u < 1))
		{
			intersectionPointsTarget.push_back(Vec2(m_mPos.x + t * r.x, m_mPos.y + t * r.y));
		}
	}
	if (intersectionPointsTarget.size() != 0)
	{
		return { true, Vec2{0,0}, intersectionPointsTarget };
	}
	else
	{
		return { false, Vec2{0,0}, {} };
	}
}

Vec2 ScenePlay::increament(float angle, const Vec2& mousePos, const Vec2& position)
{
	Vec2 p = position + Vec2(cos(angle), sin(angle));
	ScenePlay::Intersect intersectResult = intersection(mousePos, p);

	if (position.distq(mousePos) > 10000000) {
		return position;
	}


	if (!intersectResult.result)
	{
		return increament(angle, mousePos, p);
	}
	else {
		return intersectResult.pos;
	}
}

void ScenePlay::addInterSectionPoints(const Vec2& vertex, const Vec2& neighbour)
{
	for(auto& target : m_entities.getEntities("target"))
	{
		if (vertex.distq(m_mPos) <= target->getComponent<CTransform>().pos.distq(m_mPos))
		{
			if (checkIntersectionTarget(neighbour, target->getComponent<CBoundingBox>().m_VerticesTarget).result)
			{
				for (auto& pointTarget : checkIntersectionTarget(neighbour, target->getComponent<CBoundingBox>().m_VerticesTarget).intersections)
				{
					target->getComponent<CTexture>().m_TexturePoints.emplace_back(pointTarget);
				}
			}
		}
	}
}

void ScenePlay::checkVerticesTarget(std::shared_ptr<Entity> target, const Vec2& vertix)
{
	if (!intersection(m_mPos, vertix).result)
	{
		target->getComponent<CTexture>().m_TexturePoints.emplace_back(vertix);
	}
}

sf::VertexArray ScenePlay::triangulate(std::vector<sf::Vector2f>& shape, std::vector<sf::Vector2f>& texCoords) {
	sf::VertexArray triangles(sf::Triangles);

	if (shape.size() < 3 || texCoords.size() < 3 || shape.size() != texCoords.size()) {
		std::cerr << "Invalid shape or texture mapping!" << std::endl;
		return triangles;
	}

	for (size_t i = 1; i < shape.size() - 1; i++) {
		triangles.append(sf::Vertex(shape[0], texCoords[0]));
		triangles.append(sf::Vertex(shape[i], texCoords[i]));
		triangles.append(sf::Vertex(shape[i + 1], texCoords[i + 1]));
	}

	return triangles;
}

void ScenePlay::sRender()
{
	m_game->m_window.clear();

	Vec2 mousePos(m_mShape.getPosition().x, m_mShape.getPosition().y);

	for (auto& e : m_entities.getEntities("enemy"))
	{
		auto& shapeComponent = e->getComponent<CShape>();
		auto& convexShape = shapeComponent.convex;
		m_game->m_window.draw(convexShape);

		int maxPoints = std::min(shapeComponent.size, convexShape.getPointCount());
		for (int i = 0; i < maxPoints; i++)
		{
			Vec2 vertex(convexShape.getPoint(i).x, convexShape.getPoint(i).y);
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y), sf::Color::Red),
				sf::Vertex(sf::Vector2f(vertex.x, vertex.y), sf::Color::Red)
			};

			ScenePlay::Intersect intersectResult = intersection(mousePos, vertex);
			if (!intersectResult.result)
			{
				float vertexAngle = vertex.angle(mousePos);

				m_IntersectedPoints.emplace_back(vertex);

				Vec2 neighbour(increament(vertexAngle - 0.000349, mousePos, mousePos));
				m_IntersectedPoints.emplace_back(neighbour);

				addInterSectionPoints(vertex, neighbour);

				neighbour = increament(vertexAngle + 0.000349, mousePos, mousePos);
				m_IntersectedPoints.emplace_back(neighbour);

				addInterSectionPoints(vertex, neighbour);
			}
			else
			{
				m_IntersectedPoints.emplace_back(intersectResult.pos);
			}
		}
	}


	size_t size = m_IntersectedPoints.size();
	std::sort(m_IntersectedPoints.begin(), m_IntersectedPoints.end(),
		[&](const Vec2& a, const Vec2& b) {
			return a.angle(mousePos) < b.angle(mousePos);
		});

	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color::White);

	size = m_IntersectedPoints.size();

	for (size_t k = 0; k < size; ++k)
	{
		triangle.setPoint(0, sf::Vector2f(mousePos.x, mousePos.y));
		triangle.setPoint(1, sf::Vector2f(m_IntersectedPoints[k].x, m_IntersectedPoints[k].y));
		triangle.setPoint(2, sf::Vector2f(m_IntersectedPoints.at((k + 1) % size).x, m_IntersectedPoints.at((k + 1) % size).y));
		m_game->m_window.draw(triangle);
	}

	for (auto& target : m_entities.getEntities("target"))
	{
		auto& animationComponent = target->getComponent<CAnimation>();
		auto& boundComponent = target->getComponent<CBoundingBox>();
		auto& textureComponent = target->getComponent<CTexture>();
		auto& transformComponent = target->getComponent<CTransform>();

		target->getComponent<CAnimation>().animation.update(0);

		animationComponent.animation.getSprite().setPosition(transformComponent.pos.x, transformComponent.pos.y);
		m_game->m_window.draw(animationComponent.animation.m_sprite);
		//m_game->m_window.draw(boundComponent.rectangle);

		checkVerticesTarget(target, boundComponent.m_VerticesTarget[0]);
		checkVerticesTarget(target, boundComponent.m_VerticesTarget[1]);
		checkVerticesTarget(target, boundComponent.m_VerticesTarget[2]);
		checkVerticesTarget(target, boundComponent.m_VerticesTarget[3]);

		if (textureComponent.m_TexturePoints.size() > 2)
		{
			target->getComponent<CAnimation>().animation.update(1);

			std::sort(textureComponent.m_TexturePoints.begin(), textureComponent.m_TexturePoints.end(),
				[&](const Vec2& a, const Vec2& b) {
					return a.angle(transformComponent.pos) < b.angle(transformComponent.pos);
				});

			/*
			float i = 4;
			for (auto& vertixTexture : textureComponent.m_TexturePoints)
			{
				sf::CircleShape pointIndicator(i);
				pointIndicator.setPosition(vertixTexture.x, vertixTexture.y);
				pointIndicator.setFillColor(sf::Color::Green);
				pointIndicator.setOrigin(i / 2, i / 2);
				m_game->m_window.draw(pointIndicator);
				i *= 1.5;
			}
			*/

			for (int i = 0; i < textureComponent.m_TexturePoints.size(); i++)
			{
				textureComponent.screenShape.push_back(sf::Vector2f(textureComponent.m_TexturePoints[i].x, textureComponent.m_TexturePoints[i].y));
				textureComponent.textureShape.push_back(sf::Vector2f(animationComponent.animation.getSize().x + textureComponent.m_TexturePoints[i].x - (boundComponent.rectangle.getPosition().x - boundComponent.halfSize.x), textureComponent.m_TexturePoints[i].y - (boundComponent.rectangle.getPosition().y - boundComponent.halfSize.y)));
			}

			textureComponent.triangles = triangulate(textureComponent.screenShape, textureComponent.textureShape);

			textureComponent.states.texture = animationComponent.animation.getSprite().getTexture();
			m_game->m_window.draw(textureComponent.triangles, textureComponent.states);

			textureComponent.m_TexturePoints.clear();
			textureComponent.states.Default;
			textureComponent.screenShape.clear();
			textureComponent.textureShape.clear();
			textureComponent.triangles.clear();
		}
	}

	m_IntersectedPoints.clear();

	m_mShape.setFillColor(sf::Color::Red);
	m_mShape.setRadius(10);
	m_mShape.setOrigin(5, 5);
	m_mShape.setPosition(m_mPos.x, m_mPos.y);
	m_game->m_window.draw(m_mShape);

	m_game->m_window.display();
}