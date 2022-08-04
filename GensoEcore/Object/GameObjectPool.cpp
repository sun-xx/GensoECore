#include"GameObjectPool.hpp"
#include"../Qcalc/Qcalc.hpp"
#include"RenderCube.hpp"
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::GensoObjPool()
{
    clear();
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
void Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::clear()
{
    pool.clear();
    for(auto& s:colgroups)
    {
        s.clear();
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
template<typename Tobj>
std::optional<size_t> Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::createObj(Genso::Initializer<Tobj>& init)
{
    size_t index=pool.alloc();
    if(auto mem=pool.at(index);mem.has_value())
    {
        init._set_id(index);
        size_t ref_id=colgroups[init.getCollideGroup()].alloc();
        colgroups[init.getCollideGroup()][ref_id]=&mem;
        init._set_col_ref_id(ref_id);
        mem=Tobj(init);
        return {index};
    }else
    {
        return std::nullopt;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
bool Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::delObj(size_t id)
{
    if(auto obj=pool.at(id);obj.has_value())
    {
        colgroups[obj.getCollideGroup()].free(obj._get_col_ref_id());
        pool.free(id);
        return true;
    }else
    {
        return false;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
bool Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::changeCollideGroup(size_t id,size_t colgroup)
{
    if(auto obj=pool.at(id);obj.has_value())
    {
        colgroups[obj.getCollideGroup()].free(obj._get_col_ref_id());
        size_t new_ref_id=colgroups[colgroup].alloc();
        colgroups[colgroup][new_ref_id]=obj;
        obj._set_col_ref_id(new_ref_id);
        return true;
    }else
    {
        return false;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
template<typename Obj2Visitor>
std::optional<float> Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::distance(size_t id1,size_t id2,Obj2Visitor const &vis) const
{
    auto v1=pool.at(id1);
    auto v2=pool.at(id2);
    if(v1.has_value()&&v2.has_value())
    {
       auto[pos1,pos2]=std::visit(vis,v1,v2);
       auto dpos=pos1-pos2;
       return {Genso::qc::Qhypot(dpos.x,dpos.y)};
    }else
    {
        return std::nullopt;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
template<typename Obj2Visitor>
std::optional<float> Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::angle(size_t id1,size_t id2,Obj2Visitor const &vis) const
{
    auto v1=pool.at(id1);
    auto v2=pool.at(id2);
    if(v1.has_value()&&v2.has_value())
    {
       auto[pos1,pos2]=std::visit(vis,v1,v2);
       auto dpos=pos2-pos1;
       return {Genso::qc::Qatan2(dpos.y,dpos.x)};
    }else
    {
        return std::nullopt;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
template<typename Obj2Visitor1,typename Obj2Visitor2,typename Obj2Visitor3>
std::optional<bool> Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::isCollide(size_t id1,size_t id2,Obj2Visitor1 const &vis_pos,Obj2Visitor2 const &vis_box,Obj2Visitor3 const &vis_rad) const
{
    if(id1==id2)
    {
        return false;
    }
    auto v1=pool.at(id1);
    auto v2=pool.at(id2);
    if(v1.has_value()&&v2.has_value)
    {
        auto[box1,box2]=std::visit(vis_box,v1,v2);
        auto[pos1,pos2]=std::visit(vis_pos,v1,v2);
        auto[rad1,rad2]=std::visit(vis_rad,v1,v2);
        ///todo:collision detect
    }else
    {
        return std::nullopt;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
template<typename Obj1Visitor>
std::optional<bool> Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::isBoxIntersectWith(size_t id,sf::FloatRect frect,Obj1Visitor const &vis) const
{
    if(auto v=pool.at(id);v.has_value())
    {
        return v.getboundingbox().intersects(frect);
    }else
    {
        return std::nullopt;
    }
}
template<size_t MaxAllocCnt,size_t CollideGroups,typename ...T>
template<size_t MaxLayer,size_t MaxLayerObject>
void Genso::GensoObjPool<MaxAllocCnt,CollideGroups,T...>::_batchRender(const sf::RenderWindow& rwind,const Genso::render::RenderCube<MaxLayer,MaxLayerObject>& cube) const
{
    for(size_t i=0;i<MaxAllocCnt;i++)
    {
        if(auto s=pool.at(i);s.has_value())
        {
            cube.fill(s);
        }
    }
}
