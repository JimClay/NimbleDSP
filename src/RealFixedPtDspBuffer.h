//
//  RealFixedPtDspBuffer.h
//  SlickDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

#ifndef SlickDsp_RealFixedPtDspBuffer_h
#define SlickDsp_RealFixedPtDspBuffer_h

#include <math.h>
#include "RealDspBuffer.h"


namespace SlickDsp {


template <class T>
class RealFixedPtDspBuffer : public RealDspBuffer<T> {
 public:
    // Constructors
    RealFixedPtDspBuffer<T>(void) : RealDspBuffer<T>() {}
    RealFixedPtDspBuffer<T>(unsigned size) : RealDspBuffer<T>(size) {}
    template <typename U>
    RealFixedPtDspBuffer<T>(std::vector<U> data) : RealDspBuffer<T>(data) {}
    template <typename U>
    RealFixedPtDspBuffer<T>(U *data, unsigned dataLen) : RealDspBuffer<T>(data, dataLen) {}
    
    RealFixedPtDspBuffer<T>(const RealFixedPtDspBuffer<T>& other) {this->buf = other.buf;}
    RealFixedPtDspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    // Operators
    RealFixedPtDspBuffer<T> & operator++();
    RealFixedPtDspBuffer<T> operator++(int);
    RealFixedPtDspBuffer<T> & operator--();
    RealFixedPtDspBuffer<T> operator--(int);
    
    template <class U>
    RealFixedPtDspBuffer<T> & operator%=(const RealFixedPtDspBuffer<U> &rhs);
    RealFixedPtDspBuffer<T> & operator%=(const T &rhs);
    
    RealFixedPtDspBuffer<T> & operator~();
    template <class U>
    RealFixedPtDspBuffer<T> & operator&=(const RealFixedPtDspBuffer<U> &rhs);
    RealFixedPtDspBuffer<T> & operator&=(const T &rhs);
    template <class U>
    RealFixedPtDspBuffer<T> & operator|=(const RealFixedPtDspBuffer<U> &rhs);
    RealFixedPtDspBuffer<T> & operator|=(const T &rhs);
    template <class U>
    RealFixedPtDspBuffer<T> & operator^=(const RealFixedPtDspBuffer<U> &rhs);
    RealFixedPtDspBuffer<T> & operator^=(const T &rhs);
    template <class U>
    RealFixedPtDspBuffer<T> & operator>>=(const RealFixedPtDspBuffer<U> &rhs);
    RealFixedPtDspBuffer<T> & operator>>=(const T &rhs);
    template <class U>
    RealFixedPtDspBuffer<T> & operator<<=(const RealFixedPtDspBuffer<U> &rhs);
    RealFixedPtDspBuffer<T> & operator<<=(const T &rhs);
    
    // Methods
    RealDspBuffer<T> & pow(const SLICKDSP_FLOAT_TYPE exponent);
    const T mode();
};


template <class T>
RealFixedPtDspBuffer<T>& RealFixedPtDspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator++()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = this->buf[i] + 1;
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> RealFixedPtDspBuffer<T>::operator++(int)
{
    RealFixedPtDspBuffer<T> tmp(*this);
    operator++();
    return tmp;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator--()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = this->buf[i] - 1;
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> RealFixedPtDspBuffer<T>::operator--(int)
{
    RealFixedPtDspBuffer<T> tmp(*this);
    operator--();
    return tmp;
}

template <class T>
template <class U>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator%=(const RealFixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] %= rhs.buf[i];
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator%=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] %= rhs;
    }
    return *this;
}

template <class T, class U>
inline RealFixedPtDspBuffer<T> operator%(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
inline RealFixedPtDspBuffer<T> operator%(RealFixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator~()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = ~(this->buf[i]);
    }
    return *this;
}

template <class T>
template <class U>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator&=(const RealFixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] &= rhs.buf[i];
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator&=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] &= rhs;
    }
    return *this;
}

template <class T, class U>
inline RealFixedPtDspBuffer<T> operator&(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs &= rhs;
    return lhs;
}

template <class T>
inline RealFixedPtDspBuffer<T> operator&(RealFixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs &= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator|=(const RealFixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] |= rhs.buf[i];
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator|=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] |= rhs;
    }
    return *this;
}

template <class T, class U>
inline RealFixedPtDspBuffer<T> operator|(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs |= rhs;
    return lhs;
}

template <class T>
inline RealFixedPtDspBuffer<T> operator|(RealFixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs |= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator^=(const RealFixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] ^= rhs.buf[i];
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator^=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] ^= rhs;
    }
    return *this;
}

template <class T, class U>
inline RealFixedPtDspBuffer<T> operator^(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs ^= rhs;
    return lhs;
}

template <class T>
inline RealFixedPtDspBuffer<T> operator^(RealFixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs ^= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator>>=(const RealFixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] >>= rhs.buf[i];
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator>>=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] >>= rhs;
    }
    return *this;
}

template <class T, class U>
inline RealFixedPtDspBuffer<T> operator>>(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs >>= rhs;
    return lhs;
}

template <class T>
inline RealFixedPtDspBuffer<T> operator>>(RealFixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs >>= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator<<=(const RealFixedPtDspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] <<= rhs.buf[i];
    }
    return *this;
}

template <class T>
RealFixedPtDspBuffer<T> & RealFixedPtDspBuffer<T>::operator<<=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] <<= rhs;
    }
    return *this;
}

template <class T, class U>
inline RealFixedPtDspBuffer<T> operator<<(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs <<= rhs;
    return lhs;
}

template <class T>
inline RealFixedPtDspBuffer<T> operator<<(RealFixedPtDspBuffer<T> lhs, const T& rhs)
{
    lhs <<= rhs;
    return lhs;
}

template <class T>
RealDspBuffer<T> & RealFixedPtDspBuffer<T>::pow(const SLICKDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = (T) std::round(std::pow(this->buf[i], exponent));
    }
    return *this;
}
    
template <class T>
const T RealFixedPtDspBuffer<T>::mode() {
    assert(this->size() > 0);
    std::vector<T> tempScratch;
    std::vector<T> *scratch;

    if (this->scratchBuf == NULL) {
        scratch = &tempScratch;
    }
    else {
        scratch = this->scratchBuf;
    }
    *scratch = this->buf;
    std::sort(scratch->begin(), scratch->end());
    
    T modeVal = 0;
    unsigned modeLen = 0;
    T currentVal = (*scratch)[0];
    unsigned currentLen = 1;
    
    for (unsigned i=1; i<this->size(); i++) {
        if ((*scratch)[i] == currentVal) {
            currentLen++;
        }
        else {
            if (currentLen > modeLen) {
                modeVal = currentVal;
                modeLen = currentLen;
            }
            currentVal = (*scratch)[i];
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
const T mode(RealFixedPtDspBuffer<T> & buffer) {
    return buffer.mode();
}

template <class T>
const SLICKDSP_FLOAT_TYPE meanF(RealFixedPtDspBuffer<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SLICKDSP_FLOAT_TYPE varF(RealFixedPtDspBuffer<T> & buffer) {
    return buffer.var();
}

template <class T>
const SLICKDSP_FLOAT_TYPE stdF(RealFixedPtDspBuffer<T> & buffer) {
    return buffer.stdDev();
}

template <class T>
const SLICKDSP_FLOAT_TYPE stdDevF(RealFixedPtDspBuffer<T> & buffer) {
    return buffer.stdDev();
}

};


#endif
