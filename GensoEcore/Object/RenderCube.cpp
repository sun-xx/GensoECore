#include"RenderCube.hpp"
#include <boost/range/adaptor/reversed.hpp>
template<size_t MaxLayer,size_t MaxLayerObject>
bool Genso::render::RenderCube<MaxLayer,MaxLayerObject>::fill(sf::Sprite* sprite,sf::RenderStates* rdstat,size_t layer)
{
    if(layer>=MaxLayer)
    {
        return false;
    }
    if(auto id=cube[layer].alloc();id.has_value())
    {
        cube[layer][*id]=std::make_pair(sprite,rdstat);
        if(layerused[layer]==false)
        {
            layerused[layer]=true;
        }
        return true;
    }else
    {
        return false;
    }
}
template<size_t MaxLayer,size_t MaxLayerObject>
void Genso::render::RenderCube<MaxLayer,MaxLayerObject>::clear()
{
    for(auto& s:cube)
    {
        s.clear();
    }
    cube.clear();
}
template<size_t MaxLayer,size_t MaxLayerObject>
void Genso::render::RenderCube<MaxLayer,MaxLayerObject>::batchRender(const sf::RenderWindow& wind) const
{
    for(size_t i=0;i<MaxLayer;i++)
    {
        size_t i_=MaxLayer-1-i;
        if(layerused[i_]==true)
        {
            for(size_t j=0;j<MaxLayerObject-1;j++)
            {
                size_t j_=MaxLayerObject-1-j;
                if(auto res=cube[i_].at(j_);res.has_value())
                {
                    wind.draw(*(res->first),*(res->second));
                }
            }
        }
    }
}
