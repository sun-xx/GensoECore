#ifndef GAMEOBJECTPOOL_HPP_INCLUDED
#define GAMEOBJECTPOOL_HPP_INCLUDED

#include"GameObject.hpp"
#include"visitors.hpp"
#include"Mempool/Mempool.hpp"
#include"RenderCube.hpp"
#include<SFML/Graphics.hpp>
#include<array>
namespace Genso
{
    template<class... Ts> struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    namespace visitors
    {
        extern Genso::visitors::Obj1_box obj1_box;
        extern Genso::visitors::Obj2_box obj2_box;
        extern Genso::visitors::Obj2_col obj2_col;
        extern Genso::visitors::Obj2_pos obj2_pos;
        extern Genso::visitors::Obj1_this obj1_this;
    }


    template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
    class GensoObjPool
    {
        private:
            Genso::BaseMemPool<std::variant<T...>,MaxAllocCnt> pool;
            std::array<Genso::BaseMemPool<std::variant<T...>*,MaxAllocCnt>,CollideGroups> colgroups;
        private:
            GensoObjPool(const GensoObjPool&)=delete;
            GensoObjPool& operator=(const GensoObjPool&)=delete;
        public:
            GensoObjPool();
            template<typename Tobj> std::optional<size_t> createObj(Genso::Initializer<Tobj>& init);//返回分配对象的id
            bool delObj(size_t id);
            bool changeCollideGroup(size_t id,size_t colgroup);
            void clear();

            //对象间关系
            template<typename Obj2Visitor> std::optional<float> distance(size_t id1,size_t id2,Obj2Visitor const &vis=Genso::visitors::obj2_pos) const;
            template<typename Obj2Visitor> std::optional<float> angle(size_t id1,size_t id2,Obj2Visitor const &vis=Genso::visitors::obj2_pos) const;
            template<typename Obj2Visitor1,typename Obj2Visitor2,typename Obj2Visitor3> std::optional<bool> isCollide(size_t id1,size_t id2,Obj2Visitor1 const &vis_pos=Genso::visitors::obj2_pos,Obj2Visitor2 const &vis_box=Genso::visitors::obj2_box,Obj2Visitor3 const &vis_rad=Genso::visitors::obj2_col) const;
            template<typename Obj1Visitor> std::optional<bool> isBoxIntersectWith(size_t id,sf::FloatRect frect,Obj1Visitor const &vis=Genso::visitors::obj1_box) const;

            //渲染
            template<size_t MaxLayer,size_t MaxLayerObject,typename Obj1Visitor>
            void _batchRender(const sf::RenderWindow& rwind,const Genso::render::RenderCube<MaxLayer,MaxLayerObject>& cube,Obj1Visitor const &vis_this=Genso::visitors::obj1_this) const;

    };
}

#endif // GAMEOBJECTPOOL_HPP_INCLUDED
