#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include<SFML/Graphics.hpp>
#include"../Qcalc/Qcalc.hpp"
#include<stack>
#include"GameObjectPool.hpp"
namespace Genso
{
    struct _TransStat
    {
        float rotate_angle;
        sf::Vector2f scale;
    };
    class GensoObjBase
    {
        private:
            sf::Sprite sprite;//贴图精灵
            sf::Vector2f anchor;//图像变换锚点
            sf::Color sprite_color;
            sf::RenderStates renderstates;
            unsigned int collidegroup;//碰撞组
            float collideradius;
            sf::Vector2f pos;//坐标
            sf::Vector2f v,a;//速度，加速度
            bool alive;//是否存在

            sf::FloatRect boundingbox;
            sf::IntRect texrect;

            //stack<sf::Transform> matbuffer;
            _TransStat trstat;

            size_t id;
            size_t col_ref_id;
            unsigned int alive_frame;

            bool deadwhenout;
            size_t layer;

        public:
            GensoObjBase() {};
            GensoObjBase(const sf::Texture& tex,sf::Vector2f coord,size_t index,size_t collide_ref_id,size_t renderlayer,unsigned int colgroup=0,float colradius=0,sf::Vector2f velocity=sf::Vector2f(0,0),sf::Vector2f acceleration=sf::Vector2f(0,0),bool isdeadwhenout=true);//0碰撞组为幽灵组
            GensoObjBase(const GensoObjBase& gobj);
            GensoObjBase& operator=(const GensoObjBase& gobj);

            virtual ~GensoObjBase()=0;

            virtual void draw()=0;

            virtual void frame()=0;

            virtual void oncreate()=0;//被创建时除了构造外的准备工作

            virtual void ondead()=0;

            //位置相关
            void move(sf::Vector2f d);//相对移动
            void move(float dx,float dy);
            void setPosition(sf::Vector2f coord);//绝对坐标
            void setPosition(float x,float y);
            sf::Vector2f getPosition() const;

            //图像变换相关
            //void setRotation(float angle);
            void rotate(float dangle);
            float getRotation() const;

            //void setScale(float sx,float sy);
            //void setScale(sf::Vector2f s);
            void scale(float sdx,float sdy);
            void scale(sf::Vector2f ds);
            sf::Vector2f getScale() const;

            void setAnchor(float x,float y);//设置图像变换锚点，锚点默认为对象当前的坐标
            void setAnchor(sf::Vector2f coord);
            sf::Vector2f getAnchor() const;

            void addTransMat(const sf::Transform& ts);
            //void castTransform();
            void clearTransMat();

            sf::FloatRect getboundingbox() const;
            bool isBoxIntersect(const GensoObjBase& gobj) const;

            //速度相关
            void setVelocity(sf::Vector2f velocity);
            void setVelocity(float vx,float vy);

            sf::Vector2f getVelocity() const;


            void setAcceleration(sf::Vector2f acceleration);
            void setAcceleration(float ax,float ay);

            sf::Vector2f getAcceleration() const;


            void setCollideGroup(unsigned int group);
            unsigned int getCollideGroup() const;

            void setCollideRadius(float radius);//圆心为对象坐标
            float getCollideRadius() const;


            //Sprite相关,见sfml官网
            void setTexture(const sf::Texture& tex);
            void setTextureRect(sf::IntRect rect);
            sf::IntRect getTextureRect() const;
            const sf::Sprite& getSprite() const;

            void setSpriteColor(sf::Color color);
            sf::Color getSpriteColor() const;

            sf::Transform getInverseTransMat() const;
            sf::Transform getTransMat() const;

            //
            bool isAlive() const;
            void setDead();
            size_t getid() const;
            size_t _get_col_ref_id() const;

            void _set_id(size_t index);//never call a function with a '_'prefix
            void _set_col_ref_id(size_t index);

            void set_layer(size_t l);
            size_t get_layer() const;

            void setRenderStates(const sf::RenderStates& rdstat);
            const sf::RenderStates& getRenderStates() const;

    };

    template<typename Tobj>
    class Initializer
    {
        ///dyto
    };
}

#endif // GAMEOBJECT_HPP_INCLUDED

