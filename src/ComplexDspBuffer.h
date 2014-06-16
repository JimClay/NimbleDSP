//
//  ComplexDspBuffer.h
//  SlickDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

/**
 * @file ComplexDspBuffer.h
 *
 * Definition of the template class ComplexDspBuffer.
 */

#ifndef SlickDsp_ComplexDspBuffer_h
#define SlickDsp_ComplexDspBuffer_h

#include <complex>
#include "DspBuffer.h"
#include "kissfft.hh"



namespace SlickDsp {

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
     * \brief Indicates whether the data in \ref DspBuffer::buf is time domain data or frequency domain.
     */
    DomainType domain;
    
    /*****************************************************************************************
                                        Constructors
    *****************************************************************************************/
    /**
     * \brief Basic constructor.
     *
     * Sets \ref domain to SlickDsp::TIME_DOMAIN and calls DspBuffer<T>::DspBuffer(size, scratch).
     * \param size Size of \ref DspBuffer::buf.
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
     * \param data Vector that \ref DspBuffer::buf will be set equal to.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     * \param dataDomain Indicates whether the data is time domain data or frequency domain.
     *      Valid values are SlickDsp::TIME_DOMAIN and SlickDsp::FREQUENCY_DOMAIN.
     */
    template <typename U>
    ComplexDspBuffer<T>(std::vector<U> data, DomainType dataDomain=TIME_DOMAIN,
                std::vector< std::complex<T> > *scratch = NULL) : DspBuffer< std::complex<T> >(data, scratch)
                    {domain = dataDomain;}
    
    /**
     * \brief Array constructor.
     *
     * Sets buf equal to the input "data" array and sets the pointer to the scratch buffer,
     *      if one is provided.  Also sets \ref domain to dataDomain.
     * \param data Array that \ref DspBuffer::buf will be set equal to.
     * \param dataLen Length of "data".
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     * \param dataDomain Indicates whether the data is time domain data or frequency domain.
     *      Valid values are SlickDsp::TIME_DOMAIN and SlickDsp::FREQUENCY_DOMAIN.
     */
    template <typename U>
    ComplexDspBuffer<T>(U *data, unsigned dataLen, DomainType dataDomain=TIME_DOMAIN,
                std::vector< std::complex<T> > *scratch = NULL) : DspBuffer< std::complex<T> >(data, dataLen, scratch)
                    {domain = dataDomain;}
    
    /**
     * \brief Copy constructor.
     */
    ComplexDspBuffer<T>(const ComplexDspBuffer<T>& other)
            {this->buf = other.buf; domain = other.domain; this->scratchBuf = other.scratchBuf;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator from ComplexDspBuffer.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T>& operator=(const ComplexDspBuffer<T>& rhs);
    
    /**
     * \brief Assignment operator from DspBuffer.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    /**
     * \brief Unary minus (negation) operator.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & operator-();
    
    /**
     * \brief Add Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexDspBuffer<T> & operator+=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Add Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & operator+=(const std::complex<T> &rhs);
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexDspBuffer<T> & operator-=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & operator-=(const std::complex<T> &rhs);
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexDspBuffer<T> & operator*=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & operator*=(const std::complex<T> &rhs);
    
    /**
     * \brief Divide Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexDspBuffer<T> & operator/=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Divide Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & operator/=(const std::complex<T> &rhs);
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Sets each element of \ref DspBuffer::buf equal to its value to the power of "exponent".
     *
     * \param exponent Exponent to use.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & pow(const std::complex<SLICKDSP_FLOAT_TYPE> & exponent);
    
    /**
     * \brief Returns the mean (average) of the data in \ref DspBuffer::buf.
     */
    const std::complex<SLICKDSP_FLOAT_TYPE> mean() const;
    
    /**
     * \brief Returns the variance of the data in \ref DspBuffer::buf.
     */
    const SLICKDSP_FLOAT_TYPE var() const;
    
    /**
     * \brief Returns the standard deviation of the data in \ref DspBuffer::buf.
     */
    const SLICKDSP_FLOAT_TYPE stdDev() const {return std::sqrt(this->var());}
    
    /**
     * \brief Sets the upper and lower limit of the values in \ref DspBuffer::buf.
     *
     * \param val Limiting value for the data in \ref DspBuffer::buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.  This is done
     *      independently on the real and imaginary elements of \ref DspBuffer::buf.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & saturate(const std::complex<T> & val);
    
    /**
     * \brief Conjugates the data in \ref DspBuffer::buf.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & conj();
    
    /**
     * \brief Sets each element of \ref DspBuffer::buf equal to its magnitude squared.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & magSq();
    
    /**
     * \brief Sets each element of \ref DspBuffer::buf equal to its angle.
     *
     * The angle is held in the real portion of \ref DspBuffer::buf.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & angle();
    
    /**
     * \brief Sets \ref DspBuffer::buf equal to the FFT of the data in \ref DspBuffer::buf.
     *
     * Sets \ref domain equal to SlickDsp::FREQUENCY_DOMAIN.
     * \return Reference to "this".
     */
    ComplexDspBuffer<T> & fft();
    
    /**
     * \brief Sets \ref DspBuffer::buf equal to the inverse FFT of the data in \ref DspBuffer::buf.
     *
     * Sets \ref domain equal to SlickDsp::TIME_DOMAIN.
     * \return Reference to "this".
     */
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

/**
 * \brief Buffer addition operator.
 */
template <class T, class U>
inline ComplexDspBuffer<T> operator+(ComplexDspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs += rhs;
    return lhs;
}

/**
 * \brief Scalar addition operator.
 */
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

/**
 * \brief Buffer subtraction operator.
 */
template <class T, class U>
inline ComplexDspBuffer<T> operator-(ComplexDspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs -= rhs;
    return lhs;
}

/**
 * \brief Scalar subtraction operator.
 */
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

/**
 * \brief Buffer multiplication operator.
 */
template <class T, class U>
inline ComplexDspBuffer<T> operator*(ComplexDspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs *= rhs;
    return lhs;
}

/**
 * \brief Scalar multiplication operator.
 */
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

/**
 * \brief Buffer division operator.
 */
template <class T, class U>
inline ComplexDspBuffer<T> operator/(ComplexDspBuffer<T> lhs, const DspBuffer<U> & rhs)
{
    lhs /= rhs;
    return lhs;
}

/**
 * \brief Scalar division operator.
 */
template <class T>
inline ComplexDspBuffer<T> operator/(ComplexDspBuffer<T> lhs, const std::complex<T> & rhs)
{
    lhs /= rhs;
    return lhs;
}
    
template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::pow(const std::complex<SLICKDSP_FLOAT_TYPE> & exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = std::pow(this->buf[i], exponent);
    }
    return *this;
}

/**
 * \brief Sets each element of "buffer" equal to its value to the power of "exponent".
 *
 * \param buffer Buffer to operate on.
 * \param exponent Exponent to use.
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexDspBuffer<T> & pow(ComplexDspBuffer<T> & buffer, const std::complex<SLICKDSP_FLOAT_TYPE> exponent) {
    return buffer.pow(exponent);
}

template <class T>
const std::complex<SLICKDSP_FLOAT_TYPE> ComplexDspBuffer<T>::mean() const {
    assert(this->size() > 0);
    std::complex<SLICKDSP_FLOAT_TYPE> sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        sum += this->buf[i];
    }
    return sum / ((SLICKDSP_FLOAT_TYPE) this->size());
}

/**
 * \brief Returns the mean (average) of the data in "buffer".
 */
template <class T>
inline const std::complex<SLICKDSP_FLOAT_TYPE> mean(ComplexDspBuffer<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SLICKDSP_FLOAT_TYPE ComplexDspBuffer<T>::var() const {
    assert(this->size() > 1);
    std::complex<SLICKDSP_FLOAT_TYPE> meanVal = this->mean();
    std::complex<SLICKDSP_FLOAT_TYPE> sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        std::complex<SLICKDSP_FLOAT_TYPE> varDiff = this->buf[i] - meanVal;
        sum += varDiff * std::conj(varDiff);
    }
    return sum.real() / (this->size() - 1);
}

/**
 * \brief Returns the variance of the data in "buffer".
 */
template <class T>
inline const SLICKDSP_FLOAT_TYPE var(ComplexDspBuffer<T> & buffer) {
    return buffer.var();
}

/**
 * \brief Returns the standard deviation of the data in "buffer".
 */
template <class T>
inline const SLICKDSP_FLOAT_TYPE stdDev(ComplexDspBuffer<T> & buffer) {
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

/**
 * \brief Sets "buffer" equal to the FFT of the data in buffer.
 *
 * Sets \ref domain equal to SlickDsp::FREQUENCY_DOMAIN.
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
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

/**
 * \brief Conjugates the data in "buffer".
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexDspBuffer<T> & conj(ComplexDspBuffer<T> & buffer) {
    return buffer.conj();
}

/**
 * \brief Returns the squared magnitude of "val".
 */
template <class T>
inline T magSq(const std::complex<T> &val) {
    return val.real() * val.real() + val.imag() * val.imag();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::magSq() {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i].real(SlickDsp::magSq(this->buf[i]));
        this->buf[i].imag(0);
    }
    return *this;
}

/**
 * \brief Sets each element of "buffer" equal to its magnitude squared.
 * \return Reference to "buffer".
 */
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

/**
 * \brief Sets "buffer" equal to the inverse FFT of the data in buffer.
 *
 * Sets \ref domain equal to SlickDsp::TIME_DOMAIN.
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexDspBuffer<T> & ifft(ComplexDspBuffer<T> &buffer) {
    return buffer.ifft();
}

template <class T>
ComplexDspBuffer<T> & ComplexDspBuffer<T>::angle() {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i].real(std::arg(this->buf[i]));
        this->buf[i].imag(0);
    }
    return *this;
}

/**
 * \brief Sets each element of "buffer" equal to its angle.
 *
 * The angle is held in the real portion of "buffer".
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexDspBuffer<T> & angle(ComplexDspBuffer<T> & buffer) {
    return buffer.angle();
}

/**
 * \brief Returns the angle of a single std::complex value.
 *
 * \param val Value whose angle is returned.
 */
template <class T>
inline T angle(std::complex<T> &val) {
    return std::arg(val);
}

};

#endif
