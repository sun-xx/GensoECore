//integrated by @dynamder
#ifndef QCALC_HPP_INCLUDED
#define QCALC_HPP_INCLUDED

#include<boost/math/ccmath/ccmath.hpp>
#include<boost/math/special_functions.hpp>
namespace Genso
{
    namespace qc
    {
        inline float Qsqrt( float number );

        inline float negative_log(float q);

        inline float Qloge(float x);

        inline float Qlog(float m,float N);//logm(N)

        inline float Qsin(float angle);//360*1e5:<<8,*140625;1e5:<<5,*3125;

        inline float Qcos(float angle);

        inline float Qtan(float angle);

        inline float Qpow(float x, int n);

        inline float Qatan2( float y, float x );

        inline float Qexp(float y);//误差有点大，对精度要求高的场合不要使用

        inline float Qpowf(float a, float b);//a^b=2^(blog2(a)),误差有点大，对精度要求高的场合不要使用

        inline float Qhypot(float x,float y);

        template<typename T>
        T Qabs(T num);
    }
}


#endif // QCALC_HPP_INCLUDED
