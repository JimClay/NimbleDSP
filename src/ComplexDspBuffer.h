//
//  ComplexDspBuffer.h
//  SmartDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

/**
 * @file ComplexDspBuffer.h
 *
 * Definition of the template class ComplexDspBuffer.
 */

#ifndef SmartDsp_ComplexDspBuffer_h
#define SmartDsp_ComplexDspBuffer_h

#include <complex>
#include "DspBuffer.h"
#include "kissfft.hh"



namespace SmartDsp {

enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};

/**
 * \brief DspBuffer class for complex numbers.
 *
 * The template type should be the "plain old data" type that you want to use, not "std::complex"
 * or your own custom complex class.  The object will automatically convert the buffer type to
 * std::complex<POD_type> for you.
 */
template <class T>
class ComplexDspBuffer : public DspBuffer< std::complex<T> > {
 public:
    /**
     * \brief Indicates whether the data in \ref buf is time domain data or frequency domain.
     */
    DomainType domain;
    
    /*****************************************************************************************
                                        Constructors
    *****************************************************************************************/
    /**
     * \brief Basic constructor.
     *
     * Sets \ref domain to SmartDsp::TIME_DOMAIN and calls DspBuffer<T>::DspBuffer(size, scratch).
     * \param size Size of \ref buf.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    ComplexDspBuffer<T>(unsigned size = DEFAULT_BUF_LEN, std::vector< std::complex<T> > *scratch = NULL) :
            DspBuffer< std::complex<T> >(size, scratch) {domain = TIME_DOMAIN;}
            
    /**
     * \brief Vector constructor.
     *
     * Sets buf equal to the input "data" parameter and sets the pointer to the scratch buffer,
     *      if one is provided.  Also sets \ref domain to dataDomain.
     * \param data Vector that \ref buf will be set equal to.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     * \param dataDomain Indicates whether the data is time domain data or frequency domain.
     *      Valid values are SmartDsp::TIME_DOMAIN and SmartDsp::FREQUENCY_DOMAIN.
     */
    template <typename U>
    ComplexDspBuffer<T>(std::vector<U> data, DomainType dataDomain=TIME_DOMAIN) : DspBuffer< std::complex<T> >(data) {domain = dataDomain;}
    
    /**
     * \brief Array constructor.
     *
     * Sets buf equal to the input "data" array and sets the pointer to the scratch buffer,
     *      if one is provided.  Also sets \ref domain to dataDomain.
     * \param data Array that \ref buf will be set equal to.
     * \param dataLen Length of "data".
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     * \param dataDomain Indicates whether the data is time domain data or frequency domain.
     *      Valid values are SmartDsp::TIME_DOMAIN and SmartDsp::FREQUENCY_DOMAIN.
     */
    template <typename U>
    ComplexDspBuffer<T>(U *data, unsigned dataLen, DomainType dataDomain=TIME_DOMAIN) : DspBuffer< std::complex<T> >(data, dataLen) {domain = dataDomain;}
    
    /**
     * \brief Copy constructor.
     */
    ComplexDspBuffer<T>(const ComplexDspBuffer<T>& other) {this->buf = other.buf; domain = other.domain;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    ComplexDspBuffer<T>& operator=(const ComplexDspBuffer<T>& rhs);
    ComplexDspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    /**
     * \brief Unary minus (negation) operator.
     */
    ComplexDspBuffer<T> & operator-();
    
    /**
     * \brief Add Buffer/Assignment operator.
     */
    template <class U>
    ComplexDspBuffer<T> & operator+=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Add Scalar/Assignment operator.
     */
    ComplexDspBuffer<T> & operator+=(const std::complex<T> &rhs);
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     */
    template <class U>
    ComplexDspBuffer<T> & operator-=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     */
    ComplexDspBuffer<T> & operator-=(const std::complex<T> &rhs);
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     */
    template <class U>
    ComplexDspBuffer<T> & operator*=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     */
    ComplexDspBuffer<T> & operator*=(const std::complex<T> &rhs);
    
    /**
     * \brief Divide Buffer/Assignment operator.
     */
    template <class U>
    ComplexDspBuffer<T> & operator/=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Divide Scalar/Assignment operator.
     */
    ComplexDspBuffer<T> & operator/=(const std::complex<T> &rhs);
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    // Methods
    ComplexDspBuffer<T> & pow(const std::complex<SMARTDSP_FLOAT_TYPE> & exponent);
    
    const std::complex<SMARTDSP_FLOAT_TYPE> mean() const;
    const SMARTDSP_FLOAT_TYPE var() const;
    const SMARTDSP_FLOAT_TYPE stdDev() const {return std::sqrt(this->var());}
    
    ComplexDspBuffer<T> & saturate(const std::complex<T> & val);
    ComplexDspBuffer<T> & conj();
    ComplexDspBuffer<T> & magSq();
    ComplexDspBuffer<T> & angle();
    
    ComplexDspBuffer<T> & fft();
    ComplexDspBuffer<T> & ifft();
};


template <class T>
ComplexDspBuffer<T>& ComplexDspBuffer<T>::operator=(const ComplexDspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    domain = rhs.domain;
    return *this;
}

template <class T>
ComplexDspBuffer<T>& ComplexDspBuffer<T>::operator=(const DspBuffer<T> & rhs)
{
    this->buf.resize(rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = std::complex<T>(rhs[i]);
    }
    domain = TIME_DOMAIN;
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator-()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = -(this->buf[i]);
    }
    return *this;
}

template <class T>
template <class U>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator+=(const DspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] += rhs.buf[i];
    }
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator+=(const std::complex<T> & rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] += rhs;
    }
    return *this;
}

template <class T, class U>
inline ComplexDspBuffer<T> operator+(ComplexDspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
inline ComplexDspBuffer<T> operator+(ComplexDspBuffer<T> lhs, const std::complex<T> & rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
template <class U>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator-=(const DspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] -= rhs.buf[i];
    }
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator-=(const std::complex<T> &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] -= rhs;
    }
    return *this;
}

template <class T, class U>
inline ComplexDspBuffer<T> operator-(ComplexDspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
inline ComplexDspBuffer<T> operator-(ComplexDspBuffer<T> lhs, const std::complex<T> & rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
template <class U>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator*=(const DspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] *= rhs.buf[i];
    }
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator*=(const std::complex<T> &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] *= rhs;
    }
    return *this;
}

template <class T, class U>
inline ComplexDspBuffer<T> operator*(ComplexDspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
inline ComplexDspBuffer<T> operator*(ComplexDspBuffer<T> lhs, const std::complex<T> & rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
template <class U>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator/=(const DspBuffer<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] /= rhs.buf[i];
    }
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::operator/=(const std::complex<T> &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] /= rhs;
    }
    return *this;
}

template <class T, class U>
inline ComplexDspBuffer<T> operator/(ComplexDspBuffer<T> lhs, const DspBuffer<U> & rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline ComplexDspBuffer<T> operator/(ComplexDspBuffer<T> lhs, const std::complex<T> & rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::pow(const std::complex<SMARTDSP_FLOAT_TYPE> & exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = std::pow(this->buf[i], exponent);
    }
    return *this;
}

template <class T>
inline ComplexDspBuffer<T> & pow(ComplexDspBuffer<T> & buffer, const std::complex<SMARTDSP_FLOAT_TYPE> exponent) {
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
inline const std::complex<SMARTDSP_FLOAT_TYPE> mean(ComplexDspBuffer<T> & buffer) {
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
inline const SMARTDSP_FLOAT_TYPE var(ComplexDspBuffer<T> & buffer) {
    return buffer.var();
}

template <class T>
inline const SMARTDSP_FLOAT_TYPE stdDev(ComplexDspBuffer<T> & buffer) {
    return buffer.stdDev();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::saturate(const std::complex<T> & val) {
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
    return *this;
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::fft() {
    assert(domain == TIME_DOMAIN);
    kissfft<T> fftEngine = kissfft<T>(this->size(), false);
    std::vector< std::complex<T> > fftResults(this->size());
    
    fftEngine.transform((typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(this->buf),
                        (typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(fftResults));
    this->buf = fftResults;
    domain = FREQUENCY_DOMAIN;
    return *this;
}

template <class T>
inline ComplexDspBuffer<T> & fft(ComplexDspBuffer<T> &buffer) {
    return buffer.fft();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::conj() {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i].imag(-this->buf[i].imag());
    }
    return *this;
}

template <class T>
inline ComplexDspBuffer<T> & conj(ComplexDspBuffer<T> & buffer) {
    return buffer.conj();
}

template <class T>
inline T magSq(const std::complex<T> &val) {
    return val.real() * val.real() + val.imag() * val.imag();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::magSq() {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i].real(SmartDsp::magSq(this->buf[i]));
        this->buf[i].imag(0);
    }
    return *this;
}

template <class T>
inline ComplexDspBuffer<T> & magSq(ComplexDspBuffer<T> & buffer) {
    return buffer.magSq();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::ifft() {
    assert(domain == FREQUENCY_DOMAIN);
    kissfft<T> fftEngine = kissfft<T>(this->size(), true);
    std::vector< std::complex<T> > fftResults(this->size());
    
    fftEngine.transform((typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(this->buf),
                        (typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(fftResults));
    this->buf = fftResults;
    domain = TIME_DOMAIN;
    return *this;
}

template <class T>
inline ComplexDspBuffer<T> & ifft(ComplexDspBuffer<T> &buffer) {
    return buffer.ifft();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::angle() {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i].real(std::arg(this->
        
        
        
        
        
        buf[i]));
        this->buf[i].imag(0);
    }
    return *this;
}

template <class T>
inline ComplexDspBuffer<T> & angle(ComplexDspBuffer<T> & buffer) {
    return buffer.angle();
}

template <class T>
inline T angle(std::complex<T> &val) {
    return std::arg(val);
}

};

#endif
