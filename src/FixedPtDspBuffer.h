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
    FixedPtDspBuffer<T> & operator%=(const FixedPtDspBuffer<T> &rhs);
    FixedPtDspBuffer<T> & operator%=(const T &rhs);
    void pow(const SMARTDSP_FLOAT_TYPE exponent);
    
    // Methods
    const SMARTDSP_FLOAT_TYPE mean() const;
    const SMARTDSP_FLOAT_TYPE var() const;
    const SMARTDSP_FLOAT_TYPE stdDev() const;
};


template <class T>
FixedPtDspBuffer<T>& FixedPtDspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    return *this;
}

template <class T>
FixedPtDspBuffer<T> & FixedPtDspBuffer<T>::operator%=(const FixedPtDspBuffer<T> &rhs)
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

template <class T>
inline FixedPtDspBuffer<T> operator%(FixedPtDspBuffer<T> lhs, const FixedPtDspBuffer<T>& rhs)
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
void FixedPtDspBuffer<T>::pow(const SMARTDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = (T) round(std::pow(this->buf[i], exponent));
    }
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


};


#endif
