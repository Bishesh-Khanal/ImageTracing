#include "Assets.h"
#include <stdexcept>

void Assets::addTexture(const std::string& name, const std::string& path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		std::cerr << "Error loading texture from: " << path << std::endl;
		return;
	}
	else
	{
		m_textures[name] = std::move(texture);
		std::cout << "Successfully loaded texture: " << name << " from: " << path << std::endl;
	}
}

void Assets::addAnimations(const std::string& name, const Animation& animation)
{
	m_animations[name] = animation;
	std::cout << "Successfully loaded animation: " << name << std::endl;
}

const sf::Texture& Assets::getTexture(const std::string& name)
{
	auto it = m_textures.find(name);
	if (it != m_textures.end())
		return it->second;
	throw std::runtime_error("Texture not found: " + name);

}

const Animation& Assets::getAnimation(const std::string& name)
{
	auto it = m_animations.find(name);
	if (it != m_animations.end())
		return it->second;
	throw std::runtime_error("Animation not found: " + name);

}