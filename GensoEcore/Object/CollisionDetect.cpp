#include<CollisionDetect.cpp>

inline bool Genso::AABBHit(sf::Vector2f pos1,sf::Vector2f size1,
    sf::Vector2f pos2,sf::Vector2f size2)
{
    sf::Vector2f pos1_max,pos1_min;
    sf::Vector2f pos2_max,pos2_min;

    pos1_max.x = pos1.x + size1.x;
    pos1_max.y = pos1.y;
    pos1_min.x = pos1.x;
    pos1_min.y = pos1.x - size1.y;

    pos2_max.x = pos2.x + size2.x;
    pos2_max.y = pos2.y;
    pos2_min.x = pos2.x;
    pos2_min.y = pos2.x - size2.y;

    if(pos1_max.x < pos2_min.x || pos1_min.x > pos2_max.x)
        return false;
    if(pos1_max.y < pos2_min.y || pos2_min.y > pos2_max.y)
        return false;
    return true;
}

inline bool Genso::CircleHit(sf::Vector2f pos1,float r1,
    sf::Vector2f pos2,float r2)
{
    return !((r1+r2) < 
    Qsqrt((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y)));
}

inline bool Genso::CircleHit(sf::Vector2f pos1,sf::Vector2f last_pos1,float r1,
    sf::Vector2f pos2,sf::Vector2f last_pos2,float r2)
{
    
}

inline bool Genso::SegmentLaserHit(sf::Vector2f pos1,sf::Vector2f pos2,
    sf::Vector2f myPos,float judgeValue)
{
    
}
