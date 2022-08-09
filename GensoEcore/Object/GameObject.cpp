#include"GameObject.hpp"
#include"../Qcalc/Qcalc.hpp"
//构造
Genso::GensoObjBase::GensoObjBase(const sf::Texture& tex,sf::Vector2f coord,size_t index,size_t collide_ref_id,size_t renderlayer,unsigned int colgroup,float colradius,sf::Vector2f velocity,sf::Vector2f acceleration,bool isdeadwhenout)
    :collidegroup(colgroup),collideradius(colradius),pos(coord),v(velocity),a(acceleration),alive(true),id(index),col_ref_id(collide_ref_id),alive_frame(0),deadwhenout(isdeadwhenout),layer(renderlayer)
{
    sprite.setTexture(tex);
    trstat.rotate_angle=0;
    trstat.scale=sf::Vector2f(1,1);
}
Genso::GensoObjBase::GensoObjBase(const Genso::GensoObjBase& gobj)
    :sprite(gobj.sprite),anchor(gobj.anchor),sprite_color(gobj.sprite_color),renderstates(gobj.renderstates),collidegroup(gobj.collidegroup),collideradius(gobj.collideradius),
     pos(gobj.pos),v(gobj.v),a(gobj.a),alive(gobj.alive),boundingbox(gobj.boundingbox),texrect(gobj.texrect),trstat(gobj.trstat),alive_frame(gobj.alive_frame),deadwhenout(gobj.deadwhenout),layer(gobj.layer)
{
    ///dyto:id,col_ref_id初始化
}
Genso::GensoObjBase& Genso::GensoObjBase::operator=(const Genso::GensoObjBase& gobj)
{
    if(&gobj!=this)
    {
        sprite=gobj.sprite;
        anchor=gobj.anchor;
        sprite_color=gobj.sprite_color;
        renderstates=gobj.renderstates;
        collidegroup=gobj.collidegroup;
        collideradius=gobj.collideradius;
        pos=gobj.pos;

        v=gobj.v;
        a=gobj.a;
        alive=gobj.alive;
        boundingbox=gobj.boundingbox;
        texrect=gobj.texrect;
        trstat=gobj.trstat;
        alive_frame=gobj.alive_frame;
        deadwhenout=gobj.deadwhenout;
        layer=gobj.layer;
    }
    return *this;
}
//位置相关
void Genso::GensoObjBase::move(sf::Vector2f d)
{
    sprite.move(d);
    pos+=d;
}
void Genso::GensoObjBase::move(float dx,float dy)
{
    sprite.move(sf::Vector2f(dx,dy));
    pos+=sf::Vector2f(dx,dy);
}
void Genso::GensoObjBase::setPosition(float x,float y)
{
    sprite.setPosition(x,y);
    pos=sf::Vector2f(x,y);
}
void Genso::GensoObjBase::setPosition(sf::Vector2f coord)
{
    sprite.setPosition(coord);
    pos=coord;
}
sf::Vector2f Genso::GensoObjBase::getPosition() const
{
    return pos;
}
//图像变换相关
void Genso::GensoObjBase::rotate(float dangle)
{
    sf::Transform tmp;
    tmp.rotate(dangle);
    trstat.rotate_angle+=dangle;
    renderstates.transform*=tmp;
}
float Genso::GensoObjBase::getRotation() const
{
    return trstat.rotate_angle;
}

void Genso::GensoObjBase::scale(float sdx,float sdy)
{
    sf::Transform tmp;
    tmp.scale(sdx,sdy);
    trstat.scale.x*=sdx;
    trstat.scale.y*=sdy;
    renderstates.transform*=tmp;
}
void Genso::GensoObjBase::scale(sf::Vector2f ds)
{
    sf::Transform tmp;
    tmp.scale(ds);
    trstat.scale.x*=ds.x;
    trstat.scale.y*=ds.y;
    renderstates.transform*=tmp;
}
sf::Vector2f Genso::GensoObjBase::getScale() const
{
    return trstat.scale;
}
void Genso::GensoObjBase::setAnchor(float x,float y)
{
    sprite.setOrigin(x,y);
}
void Genso::GensoObjBase::setAnchor(sf::Vector2f coord)
{
    sprite.setOrigin(coord);
}
sf::Vector2f Genso::GensoObjBase::getAnchor() const
{
    return sprite.getOrigin();
}
void Genso::GensoObjBase::addTransMat(const sf::Transform& ts)
{
    renderstates.transform*=ts;
}
void Genso::GensoObjBase::clearTransMat()
{
    renderstates.transform=sf::Transform::Identity;
}
sf::FloatRect Genso::GensoObjBase::getboundingbox() const
{
    return sprite.getGlobalBounds();
}
bool Genso::GensoObjBase::isBoxIntersect(const Genso::GensoObjBase& gobj) const
{
    return boundingbox.intersects(gobj.boundingbox);
}
void Genso::GensoObjBase::setVelocity(float vx,float vy)
{
    v=sf::Vector2f(vx,vy);
}
void Genso::GensoObjBase::setVelocity(sf::Vector2f velocity)
{
    v=velocity;
}
sf::Vector2f Genso::GensoObjBase::getVelocity() const
{
    return v;
}
void Genso::GensoObjBase::setAcceleration(float ax,float ay)
{
    a=sf::Vector2f(ax,ay);
}
void Genso::GensoObjBase::setAcceleration(sf::Vector2f acceleration)
{
    a=acceleration;
}
sf::Vector2f Genso::GensoObjBase::getAcceleration() const
{
    return a;
}
void Genso::GensoObjBase::setCollideGroup(unsigned int group)
{
    ///dyto:发送消息至对象池中，进行组变换
    collidegroup=group;
}
unsigned int Genso::GensoObjBase::getCollideGroup() const
{
    return collidegroup;
}
void Genso::GensoObjBase::setCollideRadius(float radius)
{
    collideradius=radius;
}
float Genso::GensoObjBase::getCollideRadius() const
{
    return collideradius;
}
void Genso::GensoObjBase::setTexture(const sf::Texture& tex)
{
    sprite.setTexture(tex);
}
void Genso::GensoObjBase::setTextureRect(sf::IntRect rect)
{
    sprite.setTextureRect(rect);
    texrect=rect;
}
const sf::Sprite& Genso::GensoObjBase::getSprite() const
{
    return sprite;
}
sf::IntRect Genso::GensoObjBase::getTextureRect() const
{
    return texrect;
}
void Genso::GensoObjBase::setSpriteColor(sf::Color color)
{
    sprite.setColor(color);
    sprite_color=color;
}
sf::Color Genso::GensoObjBase::getSpriteColor() const
{
    return sprite_color;
}
sf::Transform Genso::GensoObjBase::getInverseTransMat() const
{
    return renderstates.transform.getInverse();
}
sf::Transform Genso::GensoObjBase::getTransMat() const
{
    return renderstates.transform;
}
bool Genso::GensoObjBase::isAlive() const
{
    return alive;
}
void Genso::GensoObjBase::setDead()
{
    alive=false;
}
size_t Genso::GensoObjBase::getid() const
{
    return id;
}
void Genso::GensoObjBase::_set_id(size_t index)
{
    id=index;
}
void Genso::GensoObjBase::_set_col_ref_id(size_t index)
{
    col_ref_id=index;
}
size_t Genso::GensoObjBase::_get_col_ref_id() const
{
    return col_ref_id;
}
void Genso::GensoObjBase::set_layer(size_t l)
{
    this->layer=l;
}
size_t Genso::GensoObjBase::get_layer() const
{
    return layer;
}
void Genso::GensoObjBase::setRenderStates(const sf::RenderStates& rdstat)
{
    this->renderstates=rdstat;
}
const sf::RenderStates& Genso::GensoObjBase::getRenderStates() const
{
    return renderstates;
}
