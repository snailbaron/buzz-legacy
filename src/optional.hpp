#ifndef _OPTIONAL_HPP_
#define _OPTIONAL_HPP_

#include <cassert>

template <class T> class Opt
{
public:
    Opt() : m_valid(false) {}
    Opt(const T &t) : m_valid(true), m_value(t) {}
    Opt(const Opt &other) : m_valid(other.m_valid), m_value(other.m_value) {}
    ~Opt() {}

    const bool operator==(const Opt &other) const;
    Opt & operator=(const T &t);
    Opt & operator=(const Opt &other);
    const bool Valid() const { return m_valid; }
    void Clear() { m_valid = false; }

private:
    bool m_valid;
    T m_value;
};

template <class T> const bool Opt<T>::operator==(const Opt &other) const
{
    return (!m_valid && !other.m_valid || m_valid && other.m_valid && m_value == other.m_value);
}

template <class T> Opt<T> & Opt<T>::operator=(const T &t)
{
    m_valid = true;
    m_value = t;
    return *this;
}

template <class T> Opt<T> & Opt<T>::operator=(const Opt &other)
{
    if (&t != this) {
        m_valid = other.m_valid;
        m_value = other.m_value;
    }
    return *this;
}

#endif
