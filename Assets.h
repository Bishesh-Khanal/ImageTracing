#pragma once

#include <map>
#include "Animation.h"
#include "SFML/Audio.hpp"

class Assets {
public:
    void addTexture(const std::string&, const std::string&);
    void addAnimations(const std::string&, const Animation&);

    const sf::Texture& getTexture(const std::string&);
    const Animation& getAnimation(const std::string&);

private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, Animation> m_animations;
};
