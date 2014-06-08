//
//  RealDspBuffer.h
//  SmartDsp
//
//  Created by Jim Clay on 6/7/14.
//
//

#ifndef SmartDsp_RealDspBuffer_h
#define SmartDsp_RealDspBuffer_h

#include "DspBuffer.h"

using namespace SmartDsp;

namespace SmartDsp {

template <class T>
class RealDspBuffer : public DspBuffer<T> {
 public:
    // Constructors
    RealDspBuffer<T>(void) : DspBuffer<T>() {}
    RealDspBuffer<T>(unsigned size) : DspBuffer<T>(size) {}
    template <typename U>
    RealDspBuffer<T>(std::vector<U> data) : DspBuffer<T>(data) {}
    template <typename U>
    RealDspBuffer<T>(U *data, unsigned dataLen) : DspBuffer<T>(data, dataLen) {}
    
    RealDspBuffer<T>(const RealDspBuffer<T>& other) {this->buf = other.buf;}
    RealDspBuffer<T>& operator=(const DspBuffer<T>& rhs) {this->buf = rhs.buf; return *this;}
    
    // Methods
    RealDspBuffer<T> & pow(const SMARTDSP_FLOAT_TYPE exponent);
    
    const SMARTDSP_FLOAT_TYPE mean() const;
    const SMARTDSP_FLOAT_TYPE var() const;
    const SMARTDSP_FLOAT_TYPE stdDev() const {return std::sqrt(this->var());}
    const T median();
    
    const T max(unsigned *maxLoc = NULL) const;
    const T min(unsigned *minLoc = NULL) const;
    RealDspBuffer<T> & saturate(T val);
};

template <class T>
RealDspBuffer<T> & RealDspBuffer<T>::pow(const SMARTDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = std::pow(this->buf[i], exponent);
    }
    return *this;
}

template <class T>
RealDspBuffer<T> & pow(RealDspBuffer<T> & buffer, const SMARTDSP_FLOAT_TYPE exponent) {
    return buffer.pow(exponent);
}

template <class T>
const SMARTDSP_FLOAT_TYPE RealDspBuffer<T>::mean() const {
    assert(this->size() > 0);
    SMARTDSP_FLOAT_TYPE sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        sum += this->buf[i];
    }
    return sum / this->size();
}

template <class T>
const SMARTDSP_FLOAT_TYPE mean(RealDspBuffer<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SMARTDSP_FLOAT_TYPE RealDspBuffer<T>::var() const {
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
const SMARTDSP_FLOAT_TYPE var(RealDspBuffer<T> & buffer) {
    return buffer.var();
}

template <class T>
const SMARTDSP_FLOAT_TYPE stdDev(RealDspBuffer<T> & buffer) {
    return buffer.stdDev();
}

template <class T>
const T RealDspBuffer<T>::median() {
    assert(this->size() > 0);
    std::vector<T> scratchBuf = this->buf;
    std::sort(scratchBuf.begin(), scratchBuf.end());
    if (this->size() & 1) {
        // Odd number of samples
        return scratchBuf[this->size()/2];
    }
    else {
        // Even number of samples.  Average the two in the middle.
        unsigned topHalfIndex = this->size()/2;
        return (scratchBuf[topHalfIndex] + scratchBuf[topHalfIndex-1]) / ((T) 2);
    }
}

template <class T>
const T median(RealDspBuffer<T> & buffer) {
    return buffer.median();
}

template <class T>
const T RealDspBuffer<T>::max(unsigned *maxLoc) const {
    assert(this->size() > 0);
    T maxVal = this->buf[0];
    unsigned maxIndex = 0;
    
    for (unsigned i=1; i<this->size(); i++) {
        //if (buf[i] > maxVal) {
        if (maxVal < this->buf[i]) {
            maxVal = this->buf[i];
            maxIndex = i;
        }
    }
    if (maxLoc != NULL) {
        *maxLoc = maxIndex;
    }
    return maxVal;
}

template <class T>
const T max(RealDspBuffer<T> & buffer, unsigned *maxLoc = NULL) {
    return buffer.max(maxLoc);
}

template <class T>
const T RealDspBuffer<T>::min(unsigned *minLoc) const {
    assert(this->size() > 0);
    T minVal = this->buf[0];
    unsigned minIndex = 0;
    
    for (unsigned i=1; i<this->size(); i++) {
        if (this->buf[i] < minVal) {
            minVal = this->buf[i];
            minIndex = i;
        }
    }
    if (minLoc != NULL) {
        *minLoc = minIndex;
    }
    return minVal;
}

template <class T>
const T min(RealDspBuffer<T> & buffer, unsigned *minLoc = NULL) {
    return buffer.min(minLoc);
}

template <class T>
RealDspBuffer<T> & RealDspBuffer<T>::saturate(T val) {
    for (unsigned i=0; i<this->size(); i++) {
        if (this->buf[i] > val)
            this->buf[i] = val;
        else if (this->buf[i] < -val)
            this->buf[i] = -val;
    }
    return *this;
}

template <class T>
RealDspBuffer<T> & saturate(RealDspBuffer<T> & buffer, T val) {
    return buffer.saturate(val);
}

};

#endif
