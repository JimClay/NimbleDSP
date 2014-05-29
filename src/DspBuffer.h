#ifndef SMART_DSP_DSPBUFFER
#define SMART_DSP_DSPBUFFER


#include <vector>
#include <cassert>

const int DEFAULT_BUF_LEN = 0;
enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};


#define VECTOR_TO_ARRAY(x)      (&x[0])


template <class T>
class DspBuffer {

private:
    void initSize(int size, DomainType dataDomain = TIME_DOMAIN) {buf = std::vector<T>(size); domain = dataDomain;}
    template <class U>
    void initArray(U *array, int arrayLen, DomainType dataDomain = TIME_DOMAIN);
    
public:
    // Members
	std::vector<T> buf;
    DomainType domain;
    
    // Constructors
    DspBuffer<T>(void) {initSize(DEFAULT_BUF_LEN);}
    DspBuffer<T>(int size) {initSize(size);}
    template <typename U>
    DspBuffer<T>(std::vector<U> data, DomainType dataDomain = TIME_DOMAIN) {initArray(VECTOR_TO_ARRAY(data), data.size(), dataDomain);}
    template <typename U>
    DspBuffer<T>(U *data, int dataLen, DomainType dataDomain = TIME_DOMAIN) {initArray(data, dataLen, dataDomain);}
    
    DspBuffer<T>(const DspBuffer<T>& other) {buf = other.buf; domain = other.domain;}
    DspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    // Operators
    DspBuffer<T> & operator++();
    DspBuffer<T> operator++(int dummy);
    DspBuffer<T> & operator--();
    DspBuffer<T> operator--(int dummy);
    
    DspBuffer<T> & operator-();
    
    DspBuffer<T> & operator+=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator+=(const T &rhs);
    DspBuffer<T> & operator-=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator-=(const T &rhs);
    
    DspBuffer<T> & operator*=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator*=(const T &rhs);
    DspBuffer<T> & operator/=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator/=(const T &rhs);
    DspBuffer<T> & operator%=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator%=(const T &rhs);
    
    T& operator[](int index);
    const T& operator[](int index) const;
    
    const int size() const {return buf.size();};
};


template <class T>
template <class U>
void DspBuffer<T>::initArray(U *array, int arrayLen, DomainType dataDomain) {
    buf = std::vector<T>(arrayLen);
    for (int i=0; i<arrayLen; i++) {
        buf[i] = (T) array[i];
    }
    domain = dataDomain;
}

template <class T>
DspBuffer<T>& DspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    buf = rhs.buf;
    domain = rhs.domain;
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator++()
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] = buf[i] + 1;
    }
    return *this;
}

template <class T>
DspBuffer<T> DspBuffer<T>::operator++(int dummy)
{
    DspBuffer<T> tmp(*this);
    operator++();
    return tmp;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator--()
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] = buf[i] - 1;
    }
    return *this;
}

template <class T>
DspBuffer<T> DspBuffer<T>::operator--(int dummy)
{
    DspBuffer<T> tmp(*this);
    operator--();
    return tmp;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-()
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] = -buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator+=(const DspBuffer<T> &rhs)
{
    assert(buf.size() == rhs.buf.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] += rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator+=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] += rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator+(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator+(DspBuffer<T> lhs, const T& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-=(const DspBuffer<T> &rhs)
{
    assert(buf.size() == rhs.buf.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] -= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] -= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator-(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator-(DspBuffer<T> lhs, const T& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator*=(const DspBuffer<T> &rhs)
{
    assert(buf.size() == rhs.buf.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] *= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator*=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] *= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator*(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator*(DspBuffer<T> lhs, const T& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator/=(const DspBuffer<T> &rhs)
{
    assert(buf.size() == rhs.buf.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] /= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator/=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] /= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator/(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator/(DspBuffer<T> lhs, const T& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator%=(const DspBuffer<T> &rhs)
{
    assert(buf.size() == rhs.buf.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] %= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator%=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] %= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator%(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator%(DspBuffer<T> lhs, const T& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
T& DspBuffer<T>::operator[](int index) {
    return buf[index];
}

template <class T>
const T& DspBuffer<T>::operator[](int index) const {
    return buf[index];
}

template <class T>
inline bool operator==(const DspBuffer<T>& lhs, const DspBuffer<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    
    for (int i=0; i<lhs.size(); i++) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <class T>
inline bool operator!=(const DspBuffer<T>& lhs, const DspBuffer<T>& rhs) {return !(lhs == rhs);}

#endif
