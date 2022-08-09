#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <SFML/System.hpp>
#include <../Qcalc/Qcalc.hpp>

template <typename U>
struct class_str
{

    template <typename T, string(T::*)() = &T::str>
    static constexpr bool check(T*)
    {
        return true;
    };   //  (1)
    static constexpr bool check(...)
    {
        return false;
    }; //  (2)

    static constexpr bool ret = check(static_cast<U*>(0));  //  (3)
};

float getDistance(sf::Vector2f pos1,sf::Vector2f pos2)
{
    return Genso::qc::Qsqrt((pos1.x-pos2.x)*(pos1.x-pos2.x)+
        (pos1.y-pos2.y)*(pos1.y-pos2.y));
}

#endif // UTILS_HPP_INCLUDED
