//
//  FixedPtDspBuffer.h
//  SmartDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

#ifndef SmartDsp_FixedPtDspBuffer_h
#define SmartDsp_FixedPtDspBuffer_h

#include "DspBuffer.h"

#ifndef SMARTDSP_FLOAT_TYPE
#define SMARTDSP_FLOAT_TYPE double
#endif

namespace SmartDsp {


template <class T>
class FixedPtDspBuffer : public DspBuffer<T> {
    
public:
    // Constructors
    FixedPtDspBuffer<T>(void) : DspBuffer<T>() {}
    FixedPtDspBuffer<T>(unsigned size) : DspBuffer<T>(size) {}
    template <typename U>
    FixedPtDspBuffer<T>(std::vector<U> data) : DspBuffer<T>(data) {}
    template <typename U>
    FixedPtDspBuffer<T>(U *data, unsigned dataLen) : DspBuffer<T>(data, dataLen) {}
    
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
    FixedPtDspBuffer<T> & pow(const SMARTDSP_FLOAT_TYPE exponent);
    
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
    const SMARTDSP_FLOAT_TYPE mean() const;
    const SMARTDSP_FLOAT_TYPE var() const;
    const SMARTDSP_FLOAT_TYPE stdDev() const;
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
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::pow(const SMARTDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = (T) round(std::pow(this->buf[i], exponent));
    }
    return *this;
}
    
template <class T>
const SMARTDSP_FLOAT_TYPE FixedPtDspBuffer<T>::mean() const {
    assert(this->size() > 0);
    SMARTDSP_FLOAT_TYPE sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        sum += (SMARTDSP_FLOAT_TYPE) this->buf[i];
    }
    return sum / this->size();
}

template <class T>
const SMARTDSP_FLOAT_TYPE FixedPtDspBuffer<T>::var() const {
    assert(this->size() > 1);
    SMARTDSP_FLOAT_TYPE meanVal = mean();
    SMARTDSP_FLOAT_TYPE sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        SMARTDSP_FLOAT_TYPE varDiff = ((SMARTDSP_FLOAT_TYPE) this->buf[i]) - meanVal;
        sum += varDiff * varDiff;
    }
    return sum / (this->size() - 1);
}

template <class T>
const SMARTDSP_FLOAT_TYPE FixedPtDspBuffer<T>::stdDev() const {
    return (SMARTDSP_FLOAT_TYPE) sqrt(var());
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


};


#endif
