//integrated by @dynamder
#include<bits/stdc++.h>
#include "./Qcalc.hpp"

#define PI 3.14159265358979323846264338
#define M_PI_4 PI/4
#define SIGN_MASK_L ((long long)1<<sizeof(long long)*8-1)
#define SIGN_MASK_I ((int)1<<sizeof(int)*8-1)
//#define GET_SIGN_I(x) (((x)>>31)|1)//1为正，-1为负,对于占32bit的数据
//#define GET_SIGN_L(x) (((x)>>63)|1)//同上，对于占64bit的数据
//#define Qabs_L(x) ((x^(x>>(sizeof(long long)-1)))-(x>>(sizeof(long long)-1)))
//#define Qabs_I(x) ((x^(x>>(sizeof(int)-1)))-(x>>(sizeof(int)-1)))
//#define Qcos(angle) (Qsin((angle)+90))
//#define Qtan(angle) (std::tan(angle))//emmmmm,你装作没看见就好

#define GET_LAST_BIT(x) (x&1)



using namespace std;

template<typename T>
inline T Genso::qc::Qabs(T num)
{
    if constexpr (std::is_same<T, float>::value)
    {
        int m=0, n=0;
        m = *(int *)&num; //复制bit值
        n = m&0x7fffffff;
        return *(float *)&n;//复制bit值
    }
    else
    {
        return num^(num>>(sizeof(T)-1))-(num>>(sizeof(T)-1));
    }
}


inline float Genso::qc::Qsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    x2 = number * 0.5F;
    y   = number;
    i   = * ( long * ) &y;   // evil floating point bit level hacking
    i   = 0x5f3759df - ( i >> 1 ); // what the fuck?
    y   = * ( float * ) &i;
    y   = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
    y   = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
    return 1/y;
}


#define ln10 2.30258509299404568401799145468
#define pi2 6.283185307179586476925286766559
// 1e-14
#define eps2 0.00000000000001
// 1e-28
#define eps1 (eps2 * eps2)

inline float Genso::qc::negative_log(float q)
{
    // q in ( 0.01, 0.1 ]
    int p = 1;
    float r = q, s = q, n = q, q2 = q * q, q1 = q2 * q;
    for (p = 1; (n *= q1) > eps1; s += n, q1 *= q2)
        r += (p = !p) ? n : -n;
    float u = 1 - 2 * r, v = 1 + 2 * s, t = u / v;
    float a = 1, b = Qsqrt(1 - t * t * t * t);
    for (; a - b > eps2; b = Qsqrt(a * b), a = t) t = (a + b) / 2;
    return pi2 / (a + b) / v / v;
}

inline float Genso::qc::Qloge(float x)
{
    if (x <= 0) return 0;
    if (x == 1) return 0;

    int k = 0;
    for (; x > 0.1; k++) x /= 10;
    for (; x <= 0.01; k--) x *= 10;
    return k * ln10 - negative_log(x);
}

inline float Genso::qc::Qlog(float m,float N)//logm(N)
{
    return Qloge(N)/Qloge(m);
}

/*inline float Qabs_f(float x)
{
    int m=0, n=0;
    m = *(int *)&x; //复制bit值
    n = m&0x7fffffff;
    return *(float *)&n;//复制bit值

}*/

inline float Genso::qc::Qsin(float angle)//360*1e5:<<8,*140625;1e5:<<5,*3125;
{
    angle=fmod(angle,360);
    int iangle=int(angle);
    ////cout<<"iangle"<<iangle<<endl;
    if(!(iangle>=-180&&iangle<=180))
    {
        angle+=(std::copysign(1,iangle)+1)*360;
    }
    //cout<<"angle:"<<angle<<endl;
    angle*=PI/180;

    return (0.987862*angle - 0.155271*angle*angle*angle + 0.00564312*angle*angle*angle*angle*angle);
}
inline float Genso::qc::Qcos(float angle)
{
    return Genso::qc::Qsin(angle+90);
}
inline float Genso::qc::Qtan(float angle)
{
    return std::tan(angle);
}

inline float Genso::qc::Qpow(float x, int n)
{
    if(n<0)
    {
        if(n==INT_MIN)
            return 1.0 / (Qpow(x,INT_MAX)*x);
        else
            return 1.0 / Qpow(x,-n);
    }
    if(n==0)
        return 1.0;
    float ans = 1.0 ;
    for(; n>0; x *= x, n>>=1)
    {
        if((n&1)>0)
            ans *= x;
    }
    return ans;
}


static const float atan2_p1 = 0.9997878412794807f*(float)(180/PI);
static const float atan2_p3 = -0.3258083974640975f*(float)(180/PI);
static const float atan2_p5 = 0.1555786518463281f*(float)(180/PI);
static const float atan2_p7 = -0.04432655554792128f*(float)(180/PI);

inline float Genso::qc::Qatan2( float y, float x )
{
    float ax = Qabs<float>(x), ay = Qabs<float>(y);
    float a, c, c2;
    if( ax >= ay )
    {
        c = ay/(ax + (float)DBL_EPSILON);
        c2 = c*c;
        a = (((atan2_p7*c2 + atan2_p5)*c2 + atan2_p3)*c2 + atan2_p1)*c;
    }
    else
    {
        c = ax/(ay + (float)DBL_EPSILON);
        c2 = c*c;
        a = 90.f - (((atan2_p7*c2 + atan2_p5)*c2 + atan2_p3)*c2 + atan2_p1)*c;
    }
    if( x < 0 )
        a = 180.f - a;
    if( y < 0 )
        a = 360.f - a;
    return a;
}
inline float Genso::qc::Qexp(float y)//误差有点大，对精度要求高的场合不要使用
{
    float d;
    *(reinterpret_cast<short*>(&d) + 0) = 0;
    *(reinterpret_cast<short*>(&d) + 1) = static_cast<short>(184 * y + (16256-7));
    return d;
}


inline float Genso::qc::Qpowf(float a, float b)//a^b=2^(blog2(a)),误差有点大，对精度要求高的场合不要使用
{
    int t=b*Qlog(2,a);
    float d;
    *(reinterpret_cast<short*>(&d) + 0) = 0;
    *(reinterpret_cast<short*>(&d) + 1) = static_cast<short>(t*(b+127));
    return d;
}
inline float Genso::qc::Qhypot(float x,float y)
{
    return Qsqrt(x*x+y*y);
}
