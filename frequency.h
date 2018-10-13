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
  public:
    using unit = Unit;
    frequency(double val) : count_(val) {}

    template <typename R>
    frequency &operator=(const frequency<R> &f)
    {
        double temp = (f.count() * R::num) / R::den;
        this->count_ = (temp / unit::num) * unit::den;
        return *this;
    }

    template <typename T>
    frequency &operator+=(const frequency<T> &f)
    {
        double temp = get_hz() + ((f.count() * T::num) / T::den);
        this->count_ = (temp / unit::num) * unit::den;
        return *this;
    }

    template <typename G, typename R>
    friend typename std::common_type<frequency<G>, frequency<R>>::type operator+(const frequency<G> &f1, const frequency<R> &f2);

    constexpr double count() const
    {
        return count_;
    }

  private:
    constexpr double get_hz(void) const
    {
        return (count_ * unit::num) / unit::den;
    }
    double count_;
}; // FREQUENCY_H_

template <typename G, typename R>
typename std::common_type<frequency<G>, frequency<R>>::type operator+(const frequency<G> &f1, const frequency<R> &f2)
{
    using common = typename std::common_type<frequency<G>, frequency<R>>::type::unit;
    double temp = f1.get_hz() + f2.get_hz();
    double val = (temp / common::num) * common::den;
    return frequency<common>(val);
}

namespace std
{
template <typename A, typename B>
struct common_type<frequency<A>, frequency<B>>
{
    using type = typename std::conditional<std::ratio_less<A, B>::value, frequency<A>, frequency<B>>::type;
};
} // namespace std

#endif
