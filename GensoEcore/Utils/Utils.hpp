#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED
template <typename U>
struct class_str
{

    template <typename T, string(T::*)() = &T::str>
    static constexpr bool check(T*)
    {
        return true;
    };   //  (1)
    static constexpr bool check(...)
    {
        return false;
    }; //  (2)

    static constexpr bool ret = check(static_cast<U*>(0));  //  (3)
};

#endif // UTILS_HPP_INCLUDED
