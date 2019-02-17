#ifndef FREQUENCY_H_
#define FREQUENCY_H_

#include <ratio>
#include <iostream>
#include <typeinfo>
#include <type_traits>

using Hz = std::ratio<1>;
using kHz = std::kilo;
using MHz = std::mega;
using GHz = std::giga;

template <typename Unit = Hz>
class frequency
{
    using unit = Unit;

    /*************************************************************/
    /* Constructors                                              */
    /*************************************************************/

  public:
    frequency(long double val) : count_(val) {}

public:

    /*************************************************************/
    /* Operators                                                 */
    /*************************************************************/

    template <typename R>
    frequency &operator=(const frequency<R> &f)
    {
        long double temp = (f.count() * R::num) / R::den;
        this->count_ = (temp / unit::num) * unit::den;
        return *this;
    }

    template <typename T>
    frequency &operator+=(const frequency<T> &f)
    {
        long double temp = get_hz() + ((f.count() * T::num) / T::den);
        this->count_ = (temp / unit::num) * unit::den;
        return *this;
    }

    template <typename G, typename R>
    friend typename std::common_type<frequency<G>, frequency<R>>::type operator+(const frequency<G> &f1, const frequency<R> &f2);

    /*************************************************************/
    /* Functions                                                 */
    /*************************************************************/

public:

    constexpr long double count() const
    {
        return count_;
    }

private:

    constexpr long double get_hz(void) const
    {
        return (count_ * unit::num) / unit::den;
    }

private:

    /*************************************************************/
    /* Member variables                                          */
    /*************************************************************/

    long double count_;
}; // FREQUENCY_H_

template <typename G, typename R>
typename std::common_type<frequency<G>, frequency<R>>::type operator+(const frequency<G> &f1, const frequency<R> &f2)
{
    using common = typename std::common_type<frequency<G>, frequency<R>>::type::unit;
    long double temp = f1.get_hz() + f2.get_hz();
    long double val = (temp / common::num) * common::den;
    return frequency<common>(val);
}

frequency<Hz> operator"" _hz(long double value)
{
    return frequency<Hz>(value);
}

frequency<kHz> operator"" _khz(long double value)
{
    return frequency<kHz>(value);
}

frequency<MHz> operator"" _mhz(long double value)
{
    return frequency<MHz>(value);
}

frequency<GHz> operator"" _ghz(long double value) 
{
    return frequency<GHz>(value);
}

frequency<Hz> operator"" _hz(unsigned long long value) 
{
    return frequency<Hz>(value);
}

frequency<kHz> operator"" _khz(unsigned long long value) 
{
    return frequency<kHz>(value);
}

frequency<MHz> operator"" _mhz(unsigned long long value) 
{
    return frequency<MHz>(value);
}

frequency<GHz> operator"" _ghz(unsigned long long value) 
{
    return frequency<GHz>(value);
}

namespace std
{
template <typename A, typename B>
struct common_type<frequency<A>, frequency<B>>
{
    using type = typename std::conditional<std::ratio_less<A, B>::value, frequency<A>, frequency<B>>::type;
};
} // namespace std

#endif // FREQUENCY_H_
