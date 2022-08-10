#include<CollisionDetect.hpp>
#include<../Utils/Utils.hpp>

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
    return !((r1+r2) < getDistance(pos1,pos2));
}

inline bool Genso::CircleHit(sf::Vector2f pos1,sf::Vector2f last_pos1,float r1,
    sf::Vector2f pos2,sf::Vector2f last_pos2,float r2)
{
    float X1 = pos1.x - pos2.x,
    X2 = last_pos1.x - last_pos2.x - X1,
    Y1 = pos1.y - pos2.y,
    Y2 = last_pos1.y - last_pos2.y - Y1;

    float a = X2*X2 + Y2*Y2,
    b = 2*(X1*X2 + Y1*Y2),
    c = X1*X1 + Y1*Y1 - r1*r1 - r2*r2,
    delta = b*b - 4*a*c;

    if(delta < 0) return false;

    float t1 = (Genso::qc::Qsqrt(delta)-b)/(2*a),
    t2 = (0-Genso::qc::Qsqrt(delta)-b)/(2*a);

    return (t1>0 && t1<1) || (t2>0 && t2<1);
}

inline bool Genso::AABBCircleHit(sf::Vector2f pos1,sf::Vector2f size1,
        sf::Vector2f pos2,float r)
{
    pos1.x -= r;
    pos1.y += r;
    size1.x += 2*r;
    size1.y += 2*r;

    return Genso::AABBHit(pos1,size1,pos2,0.f);
}

inline bool Genso::SegmentLaserHit(sf::Vector2f pos1,sf::Vector2f pos2,
    sf::Vector2f myPos,float judgeValue)
{
    return (getDistance(pos1,myPos) + getDistance(pos2,myPos)) < judgeValue;
}
