//
//  ComplexDspBuffer.h
//  SmartDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

#ifndef SmartDsp_ComplexDspBuffer_h
#define SmartDsp_ComplexDspBuffer_h

#include <complex>
#include "DspBuffer.h"



namespace SmartDsp {

enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};


#define VECTOR_TO_ARRAY(x)      (&x[0])


template <class T>
class ComplexDspBuffer : public DspBuffer<T> {
    
public:
    DomainType domain;
    
    // Constructors
    ComplexDspBuffer<T>(void) : DspBuffer<T>() {domain = TIME_DOMAIN;}
    ComplexDspBuffer<T>(unsigned size) : DspBuffer<T>(size) {domain = TIME_DOMAIN;}
    template <typename U>
    ComplexDspBuffer<T>(std::vector<U> data, DomainType dataDomain=TIME_DOMAIN) : DspBuffer<T>(data) {domain = dataDomain;}
    template <typename U>
    ComplexDspBuffer<T>(U *data, unsigned dataLen, DomainType dataDomain=TIME_DOMAIN) : DspBuffer<T>(data, dataLen) {domain = dataDomain;}
    
    ComplexDspBuffer<T>(const ComplexDspBuffer<T>& other) {this->buf = other.buf; domain = other.domain;}
    ComplexDspBuffer<T>& operator=(const ComplexDspBuffer<T>& rhs);
    ComplexDspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    const T var() const;
    const T stdDev() const {return std::sqrt(var());}
    void saturate(T val);
    
    // Inherited methods that don't apply to complex
    const T max(unsigned *maxLoc = NULL) const {assert(false);}  // No max function for ComplexDspBuffer.
    const T min(unsigned *minLoc = NULL) const {assert(false);}  // No min function for ComplexDspBuffer.
    const T median() {assert(false);}
};


template <class T>
ComplexDspBuffer<T>& ComplexDspBuffer<T>::operator=(const ComplexDspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    domain = rhs.domain;
    return *this;
}

template <class T>
ComplexDspBuffer<T>& ComplexDspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    domain = TIME_DOMAIN;
    return *this;
}

template <class T>
const T ComplexDspBuffer<T>::var() const {
    assert(this->size() > 1);
    T meanVal = this->mean();
    T sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        T varDiff = this->buf[i] - meanVal;
        sum += varDiff * std::conj(varDiff);
    }
    return sum / ((T) (this->size() - 1));
}

template <class T>
void ComplexDspBuffer<T>::saturate(T val) {
    for (unsigned i=0; i<this->size(); i++) {
        if (this->buf[i].real() > val.real())
            this->buf[i].real(val.real());
        else if (this->buf[i].real() < -val.real())
            this->buf[i].real(-val.real());
        if (this->buf[i].imag() > val.imag())
            this->buf[i].imag(val.imag());
        else if (this->buf[i].imag() < -val.imag())
            this->buf[i].imag(-val.imag());
    }
}

};

#endif
