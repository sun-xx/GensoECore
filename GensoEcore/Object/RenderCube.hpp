#ifndef RENDERCUBE_HPP_INCLUDED
#define RENDERCUBE_HPP_INCLUDED
#include<SFML/Graphics.hpp>
#include"Mempool/Mempool.hpp"
namespace Genso
{
    namespace render
    {
        template<size_t MaxLayer,size_t MaxLayerObject>
        class RenderCube
        {
        private:
            std::array<Genso::BaseMemPool<std::pair<sf::Sprite*,sf::RenderStates*>,MaxLayerObject>,MaxLayer> cube;//0Îª×îÉÏ²ã
            std::array<bool,MaxLayer> layerused;
        public:
            RenderCube():cube({}),layerused({}){};
            bool fill(sf::Sprite* sprite,sf::RenderStates* rdstat,size_t layer);
            void clear();
            void batchRender(const sf::RenderWindow& wind) const;
        };
    }
}
#endif // RENDERCUBE_HPP_INCLUDED
