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
#include "kissfft.hh"



namespace SmartDsp {

enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};


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
    
    // Methods
    ComplexDspBuffer<T> & pow(const std::complex<SMARTDSP_FLOAT_TYPE> & exponent);
    
    const std::complex<SMARTDSP_FLOAT_TYPE> mean() const;
    const SMARTDSP_FLOAT_TYPE var() const;
    const SMARTDSP_FLOAT_TYPE stdDev() const {return std::sqrt(this->var());}
    
    void saturate(T val);
    
    //ComplexDspBuffer<T> & fft();
    //ComplexDspBuffer<T> & ifft();
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
ComplexDspBuffer<T> & ComplexDspBuffer<T>::pow(const std::complex<SMARTDSP_FLOAT_TYPE> & exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = std::pow(this->buf[i], exponent);
    }
    return *this;
}

template <class T>
ComplexDspBuffer<T> & pow(ComplexDspBuffer<T> & buffer, const std::complex<SMARTDSP_FLOAT_TYPE> exponent) {
    return buffer.pow(exponent);
}

template <class T>
const std::complex<SMARTDSP_FLOAT_TYPE> ComplexDspBuffer<T>::mean() const {
    assert(this->size() > 0);
    std::complex<SMARTDSP_FLOAT_TYPE> sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        sum += this->buf[i];
    }
    return sum / ((SMARTDSP_FLOAT_TYPE) this->size());
}

template <class T>
const std::complex<SMARTDSP_FLOAT_TYPE> mean(ComplexDspBuffer<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SMARTDSP_FLOAT_TYPE ComplexDspBuffer<T>::var() const {
    assert(this->size() > 1);
    std::complex<SMARTDSP_FLOAT_TYPE> meanVal = this->mean();
    std::complex<SMARTDSP_FLOAT_TYPE> sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        std::complex<SMARTDSP_FLOAT_TYPE> varDiff = this->buf[i] - meanVal;
        sum += varDiff * std::conj(varDiff);
    }
    return sum.real() / (this->size() - 1);
}

template <class T>
const SMARTDSP_FLOAT_TYPE var(ComplexDspBuffer<T> & buffer) {
    return buffer.var();
}

template <class T>
const SMARTDSP_FLOAT_TYPE stdDev(ComplexDspBuffer<T> & buffer) {
    return buffer.stdDev();
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
/*
template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::fft() {
    assert(domain == TIME_DOMAIN);
    kissfft<T> fftEngine = kissfft<T>(this->size(), false);
    std::vector<T> fftResults(this->size());
    
    fftEngine.transform((typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(this->buf),
                        (typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(fftResults));
    this->buf = fftResults;
    domain = FREQUENCY_DOMAIN;
    return *this;
}

template <class T>
ComplexDspBuffer<T> & fft(ComplexDspBuffer<T> &buffer) {
    return buffer.fft();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::ifft() {
    assert(domain == FREQUENCY_DOMAIN);
    kissfft<T> fftEngine = kissfft<T>(this->size(), true);
    std::vector<T> fftResults(this->size());
    
    fftEngine.transform(VECTOR_TO_ARRAY(this->buf), VECTOR_TO_ARRAY(fftResults));
    this->buf = fftResults;
    domain = TIME_DOMAIN;
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ifft(ComplexDspBuffer<T> &buffer) {
    return buffer.ifft();
}
*/
};

#endif
