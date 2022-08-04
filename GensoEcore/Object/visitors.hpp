#ifndef VISITORS_HPP_INCLUDED
#define VISITORS_HPP_INCLUDED
#include<tuple>
namespace Genso
{
    namespace visitors
    {
        struct Obj2_pos
        {
            template<typename T,typename U>
            auto operator()(const T& obj1,const U& obj2) const
            {
                return std::make_tuple(obj1.getPosition(),obj2.getPosition());
            }
        };
        struct Obj1_box
        {
            template<typename T>
            auto operator()(const T& obj) const
            {
                return obj.getboundingbox();
            }
        };
        struct Obj2_box
        {
            template<typename T,typename U>
            auto operator()(const T& obj1,const U& obj2) const
            {
                return std::make_tuple(obj1.getboundingbox(),obj2.getboundingbox());
            }
        };
        struct Obj2_col
        {
            template<typename T,typename U>
            auto operator()(const T& obj1,const U& obj2) const
            {
                return std::make_tuple(obj1.getCollideRadius(),obj2.getCollideRadius());
            }
        };
    }
}

#endif // VISITORS_HPP_INCLUDED
