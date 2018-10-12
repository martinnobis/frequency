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
    frequency(double val) : count(val) {}

    template <typename R>
    frequency &operator=(const frequency<R> &f)
    {
        double temp = f.get_hz();
        this->count = (temp / unit::num) * unit::den;
        return *this;
    }

    template <typename T>
    frequency &operator+=(const frequency<T> &f)
    {
        double temp = get_hz() + f.get_hz();
        this->count = (temp / unit::num) * unit::den;
        return *this;
    }

    template <typename G, typename R>
    friend typename std::common_type<frequency<G>, frequency<R>>::type operator+(const frequency<G> &f1, const frequency<R> &f2);

    template <typename F>
    friend std::ostream &operator<<(std::ostream &os, const frequency<F> &f);

    double get_count() const
    {
        return count;
    }

    double get_hz(void) const
    {
        return (count * unit::num) / unit::den;
    }

  private:
    double count; // value in units of this type (5.5 MHz = 5.5)
};    // FREQUENCY_H_

template <typename G, typename R>
typename std::common_type<frequency<G>, frequency<R>>::type operator+(const frequency<G> &f1, const frequency<R> &f2)
{
    using common = typename std::common_type<frequency<G>, frequency<R>>::type::unit;
    double temp = f1.get_hz() + f2.get_hz();
    double val = (temp / common::num) * common::den;
    return frequency<common>(val);
}

template <typename F>
std::ostream &operator<<(std::ostream &stream, const frequency<F> &f)
{
    stream << f.get_count() << " : " << f.get_hz();
    return stream;
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
