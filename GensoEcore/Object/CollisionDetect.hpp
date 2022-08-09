#ifndef COLLISION_DETECT_HPP_INCLUDED
#define COLLISION_DETECT_HPP_INCLUDED

#include<SFML/System.hpp>

namespace Genso
{
    inline bool AABBHit(sf::Vector2f pos1,sf::Vector2f size1,
        sf::Vector2f pos2,sf::Vector2f size2);

    inline bool Genso::CircleHit(sf::Vector2f pos1,float r1,
        sf::Vector2f pos2,float r2);

    inline bool Genso::CircleHit(sf::Vector2f pos1,sf::Vector2f last_pos1,float r1,
        sf::Vector2f pos2,sf::Vector2f last_pos2,float r2);

    inline bool Genso::SegmentLaserHit(sf::Vector2f pos1,sf::Vector2f pos2,
        sf::Vector2f myPos,float judgeValue);
}

#endif