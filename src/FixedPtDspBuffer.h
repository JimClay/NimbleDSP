//
//  FixedPtDspBuffer.h
//  SmartDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

#ifndef SmartDsp_FixedPtDspBuffer_h
#define SmartDsp_FixedPtDspBuffer_h

#include <math.h>
#include "RealDspBuffer.h"

#ifndef SMARTDSP_FLOAT_TYPE
#define SMARTDSP_FLOAT_TYPE double
#endif

namespace SmartDsp {


template <class T>
class FixedPtDspBuffer : public RealDspBuffer<T> {
 public:
    // Constructors
    FixedPtDspBuffer<T>(void) : DspBuffer<T>() {}
    FixedPtDspBuffer<T>(unsigned size) : RealDspBuffer<T>(size) {}
    template <typename U>
    FixedPtDspBuffer<T>(std::vector<U> data) : RealDspBuffer<T>(data) {}
    template <typename U>
    FixedPtDspBuffer<T>(U *data, unsigned dataLen) : RealDspBuffer<T>(data, dataLen) {}
    
    FixedPtDspBuffer<T>(const FixedPtDspBuffer<T>& other) {this->buf = other.buf;}
    FixedPtDspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    // Operators
    FixedPtDspBuffer<T> & operator++();
    FixedPtDspBuffer<T> operator++(int);
    FixedPtDspBuffer<T> & operator--();
    FixedPtDspBuffer<T> operator--(int);
    
    template <class U>
    FixedPtDspBuffer<T> & operator%=(const FixedPtDspBuffer<U> &rhs);
    FixedPtDspBuffer<T> & operator%=(const T &rhs);
    
    FixedPtDspBuffer<T> & operator~();
    template <class U>
    FixedPtDspBuffer<T> & operator&=(const FixedPtDspBuffer<U> &rhs);
    FixedPtDspBuffer<T> & operator&=(const T &rhs);
    template <class U>
    FixedPtDspBuffer<T> & operator|=(const FixedPtDspBuffer<U> &rhs);
    FixedPtDspBuffer<T> & operator|=(const T &rhs);
    template <class U>
    FixedPtDspBuffer<T> & operator^=(const FixedPtDspBuffer<U> &rhs);
    FixedPtDspBuffer<T> & operator^=(const T &rhs);
    template <class U>
    FixedPtDspBuffer<T> & operator>>=(const FixedPtDspBuffer<U> &rhs);
    FixedPtDspBuffer<T> & operator>>=(const T &rhs);
    template <class U>
    FixedPtDspBuffer<T> & operator<<=(const FixedPtDspBuffer<U> &rhs);
    FixedPtDspBuffer<T> & operator<<=(const T &rhs);
    
    // Methods
    RealDspBuffer<T> & pow(const SMARTDSP_FLOAT_TYPE exponent);
    const T mode();
};


template <class T>
FixedPtDspBuffer<T>& FixedPtDspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator++()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = this->buf[i] + 1;
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> FixedPtDspBuffer<T>::operator++(int)
{
    FixedPtDspBuffer<T> tmp(*this);
    operator++();
    return tmp;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator--()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = this->buf[i] - 1;
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> FixedPtDspBuffer<T>::operator--(int)
{
    FixedPtDspBuffer<T> tmp(*this);
    operator--();
    return tmp;
}

template <class T>
template <class U>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator%=(const FixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] %= rhs.buf[i];
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator%=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] %= rhs;
    }
    return *this;
}

template <class T, class U>
inline FixedPtDspBuffer<T> operator%(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<U>& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
inline FixedPtDspBuffer<T> operator%(FixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator~()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = ~(this->buf[i]);
    }
    return *this;
}

template <class T>
template <class U>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator&=(const FixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] &= rhs.buf[i];
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator&=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] &= rhs;
    }
    return *this;
}

template <class T, class U>
inline FixedPtDspBuffer<T> operator&(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<U>& rhs)
{
    lhs &= rhs;
    return lhs;
}

template <class T>
inline FixedPtDspBuffer<T> operator&(FixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs &= rhs;
    return lhs;
}

template <class T>
template <class U>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator|=(const FixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] |= rhs.buf[i];
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator|=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] |= rhs;
    }
    return *this;
}

template <class T, class U>
inline FixedPtDspBuffer<T> operator|(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<U>& rhs)
{
    lhs |= rhs;
    return lhs;
}

template <class T>
inline FixedPtDspBuffer<T> operator|(FixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs |= rhs;
    return lhs;
}

template <class T>
template <class U>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator^=(const FixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] ^= rhs.buf[i];
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator^=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] ^= rhs;
    }
    return *this;
}

template <class T, class U>
inline FixedPtDspBuffer<T> operator^(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<U>& rhs)
{
    lhs ^= rhs;
    return lhs;
}

template <class T>
inline FixedPtDspBuffer<T> operator^(FixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs ^= rhs;
    return lhs;
}

template <class T>
template <class U>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator>>=(const FixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] >>= rhs.buf[i];
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator>>=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] >>= rhs;
    }
    return *this;
}

template <class T, class U>
inline FixedPtDspBuffer<T> operator>>(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<U>& rhs)
{
    lhs >>= rhs;
    return lhs;
}

template <class T>
inline FixedPtDspBuffer<T> operator>>(FixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs >>= rhs;
    return lhs;
}

template <class T>
template <class U>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator<<=(const FixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] <<= rhs.buf[i];
    }
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator<<=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] <<= rhs;
    }
    return *this;
}

template <class T, class U>
inline FixedPtDspBuffer<T> operator<<(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<U>& rhs)
{
    lhs <<= rhs;
    return lhs;
}

template <class T>
inline FixedPtDspBuffer<T> operator<<(FixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs <<= rhs;
    return lhs;
}

template <class T>
RealDspBuffer<T> & FixedPtDspBuffer<T>::pow(const SMARTDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = (T) std::round(std::pow(this->buf[i], exponent));
    }
    return *this;
}
    
template <class T>
const T FixedPtDspBuffer<T>::mode() {
    assert(this->size() > 0);
    this->scratchBuf = this->buf;
    std::sort(this->scratchBuf.begin(), this->scratchBuf.end());
    
    T modeVal = 0;
    unsigned modeLen = 0;
    T currentVal = this->scratchBuf[0];
    unsigned currentLen = 1;
    
    for (unsigned i=1; i<this->size(); i++) {
        if (this->scratchBuf[i] == currentVal) {
            currentLen++;
        }
        else {
            if (currentLen > modeLen) {
                modeVal = currentVal;
                modeLen = currentLen;
            }
            currentVal = this->scratchBuf[i];
            currentLen = 1;
        }
    }
    if (currentLen > modeLen) {
        modeVal = currentVal;
        modeLen = currentLen;
    }
    return modeVal;
}

template <class T>
const T mode(FixedPtDspBuffer<T> & buffer) {
    return buffer.mode();
}

template <class T>
const SMARTDSP_FLOAT_TYPE meanF(FixedPtDspBuffer<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SMARTDSP_FLOAT_TYPE varF(FixedPtDspBuffer<T> & buffer) {
    return buffer.var();
}

template <class T>
const SMARTDSP_FLOAT_TYPE stdF(FixedPtDspBuffer<T> & buffer) {
    return buffer.stdDev();
}

template <class T>
const SMARTDSP_FLOAT_TYPE stdDevF(FixedPtDspBuffer<T> & buffer) {
    return buffer.stdDev();
}

};


#endif
