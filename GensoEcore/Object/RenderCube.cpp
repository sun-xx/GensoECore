#include"RenderCube.hpp"
#include <boost/range/adaptor/reversed.hpp>
template<size_t MaxLayer,size_t MaxLayerObject>
bool Genso::render::RenderCube<MaxLayer,MaxLayerObject>::fill(sf::Sprite* sprite,sf::RenderStates* rdstat,size_t layer)
{
    if(layer>=MaxLayer)
    {
        return false;
    }
    if(size_t id=cube[layer].alloc();id!=-1)
    {
        cube[layer][id]=std::make_pair(sprite,rdstat);
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
    for(size_t i=MaxLayer-1;i>=0;i--)
    {
        if(layerused[i]==true)
        {
            for(size_t j=MaxLayerObject-1;j>=0;j--)
            {
                if(auto res=cube[i].at(j);res.has_value())
                {
                    wind.draw(*(cube[i][j].first),cube[i][j].second);
                }
            }
        }
    }
}
