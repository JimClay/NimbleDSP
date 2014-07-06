/*
Copyright (c) 2014, James Clay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


/**
 * @file ComplexVector.h
 *
 * Definition of the template class ComplexVector.
 */

#ifndef NimbleDSP_ComplexVector_h
#define NimbleDSP_ComplexVector_h

#include <complex>
#include "Vector.h"
#include "kissfft.hh"



namespace NimbleDSP {

enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};

/**
 * \brief Vector class for complex numbers.
 *
 * The template type should be the "plain old data" type that you want to use, not "std::complex"
 * or your own custom complex class.  The object will automatically convert the buffer type to
 * std::complex<POD_type> for you.
 */
template <class T>
class ComplexVector : public Vector< std::complex<T> > {
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
     * Sets \ref domain to NimbleDSP::TIME_DOMAIN and calls Vector<T>::Vector(size, scratch).
     * \param size Size of \ref buf.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    ComplexVector<T>(unsigned size = DEFAULT_BUF_LEN, std::vector< std::complex<T> > *scratch = NULL) :
            Vector< std::complex<T> >(size, scratch) {domain = TIME_DOMAIN;}
            
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
     *      Valid values are NimbleDSP::TIME_DOMAIN and NimbleDSP::FREQUENCY_DOMAIN.
     */
    template <typename U>
    ComplexVector<T>(std::vector<U> data, DomainType dataDomain=TIME_DOMAIN,
                std::vector< std::complex<T> > *scratch = NULL) : Vector< std::complex<T> >(data, scratch)
                    {domain = dataDomain;}
    
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
     *      Valid values are NimbleDSP::TIME_DOMAIN and NimbleDSP::FREQUENCY_DOMAIN.
     */
    template <typename U>
    ComplexVector<T>(U *data, unsigned dataLen, DomainType dataDomain=TIME_DOMAIN,
                std::vector< std::complex<T> > *scratch = NULL) : Vector< std::complex<T> >(data, dataLen, scratch)
                    {domain = dataDomain;}
    
    /**
     * \brief Copy constructor.
     */
    ComplexVector<T>(const ComplexVector<T>& other)
            {this->vec = other.vec; domain = other.domain; this->scratchBuf = other.scratchBuf;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator from ComplexVector.
     * \return Reference to "this".
     */
    ComplexVector<T>& operator=(const ComplexVector<T>& rhs);
    
    /**
     * \brief Assignment operator from Vector.
     * \return Reference to "this".
     */
    ComplexVector<T>& operator=(const Vector<T>& rhs);
    
    /**
     * \brief Unary minus (negation) operator.
     * \return Reference to "this".
     */
    ComplexVector<T> & operator-();
    
    /**
     * \brief Add Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexVector<T> & operator+=(const Vector<U> &rhs);
    
    /**
     * \brief Add Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexVector<T> & operator+=(const std::complex<T> &rhs);
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexVector<T> & operator-=(const Vector<U> &rhs);
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexVector<T> & operator-=(const std::complex<T> &rhs);
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexVector<T> & operator*=(const Vector<U> &rhs);
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexVector<T> & operator*=(const std::complex<T> &rhs);
    
    /**
     * \brief Divide Buffer/Assignment operator.
     * \return Reference to "this".
     */
    template <class U>
    ComplexVector<T> & operator/=(const Vector<U> &rhs);
    
    /**
     * \brief Divide Scalar/Assignment operator.
     * \return Reference to "this".
     */
    ComplexVector<T> & operator/=(const std::complex<T> &rhs);
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Sets each element of \ref vec to e^(element).
     *
     * \return Reference to "this".
     */
    virtual Vector< std::complex<T> > & exp();
    
    /**
     * \brief Sets each element of \ref buf equal to its value to the power of "exponent".
     *
     * \param exponent Exponent to use.
     * \return Reference to "this".
     */
    ComplexVector<T> & pow(const std::complex<SLICKDSP_FLOAT_TYPE> & exponent);
    
    /**
     * \brief Returns the mean (average) of the data in \ref buf.
     */
    const std::complex<SLICKDSP_FLOAT_TYPE> mean() const;
    
    /**
     * \brief Returns the variance of the data in \ref buf.
     */
    const SLICKDSP_FLOAT_TYPE var() const;
    
    /**
     * \brief Returns the standard deviation of the data in \ref buf.
     */
    const SLICKDSP_FLOAT_TYPE stdDev() const {return std::sqrt(this->var());}
    
    /**
     * \brief Sets the upper and lower limit of the values in \ref buf.
     *
     * \param val Limiting value for the data in \ref buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.  This is done
     *      independently on the real and imaginary elements of \ref buf.
     * \return Reference to "this".
     */
    ComplexVector<T> & saturate(const std::complex<T> & val);
    
    /**
     * \brief Conjugates the data in \ref buf.
     * \return Reference to "this".
     */
    ComplexVector<T> & conj();
    
    /**
     * \brief Sets each element of \ref buf equal to its magnitude squared.
     * \return Reference to "this".
     */
    ComplexVector<T> & magSq();
    
    /**
     * \brief Sets each element of \ref buf equal to its angle.
     *
     * The angle is held in the real portion of \ref buf.
     * \return Reference to "this".
     */
    ComplexVector<T> & angle();
    
    /**
     * \brief Sets \ref buf equal to the FFT of the data in \ref buf.
     *
     * Sets \ref domain equal to NimbleDSP::FREQUENCY_DOMAIN.
     * \return Reference to "this".
     */
    ComplexVector<T> & fft();
    
    /**
     * \brief Sets \ref buf equal to the inverse FFT of the data in \ref buf.
     *
     * Sets \ref domain equal to NimbleDSP::TIME_DOMAIN.
     * \return Reference to "this".
     */
    ComplexVector<T> & ifft();
};


template <class T>
ComplexVector<T>& ComplexVector<T>::operator=(const ComplexVector<T>& rhs)
{
    this->vec = rhs.vec;
    domain = rhs.domain;
    return *this;
}

template <class T>
ComplexVector<T>& ComplexVector<T>::operator=(const Vector<T> & rhs)
{
    this->vec.resize(rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = std::complex<T>(rhs[i]);
    }
    domain = TIME_DOMAIN;
    return *this;
}

template <class T>
ComplexVector<T> & ComplexVector<T>::operator-()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = -(this->vec[i]);
    }
    return *this;
}

template <class T>
template <class U>
ComplexVector<T> & ComplexVector<T>::operator+=(const Vector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] += rhs.vec[i];
    }
    return *this;
}

template <class T>
ComplexVector<T> & ComplexVector<T>::operator+=(const std::complex<T> & rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] += rhs;
    }
    return *this;
}

/**
 * \brief Buffer addition operator.
 */
template <class T, class U>
inline ComplexVector<T> operator+(ComplexVector<T> lhs, const Vector<U>& rhs)
{
    lhs += rhs;
    return lhs;
}

/**
 * \brief Scalar addition operator.
 */
template <class T>
inline ComplexVector<T> operator+(ComplexVector<T> lhs, const std::complex<T> & rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
template <class U>
ComplexVector<T> & ComplexVector<T>::operator-=(const Vector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] -= rhs.vec[i];
    }
    return *this;
}

template <class T>
ComplexVector<T> & ComplexVector<T>::operator-=(const std::complex<T> &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] -= rhs;
    }
    return *this;
}

/**
 * \brief Buffer subtraction operator.
 */
template <class T, class U>
inline ComplexVector<T> operator-(ComplexVector<T> lhs, const Vector<U>& rhs)
{
    lhs -= rhs;
    return lhs;
}

/**
 * \brief Scalar subtraction operator.
 */
template <class T>
inline ComplexVector<T> operator-(ComplexVector<T> lhs, const std::complex<T> & rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
template <class U>
ComplexVector<T> & ComplexVector<T>::operator*=(const Vector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] *= rhs.vec[i];
    }
    return *this;
}

template <class T>
ComplexVector<T> & ComplexVector<T>::operator*=(const std::complex<T> &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] *= rhs;
    }
    return *this;
}

/**
 * \brief Buffer multiplication operator.
 */
template <class T, class U>
inline ComplexVector<T> operator*(ComplexVector<T> lhs, const Vector<U>& rhs)
{
    lhs *= rhs;
    return lhs;
}

/**
 * \brief Scalar multiplication operator.
 */
template <class T>
inline ComplexVector<T> operator*(ComplexVector<T> lhs, const std::complex<T> & rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
template <class U>
ComplexVector<T> & ComplexVector<T>::operator/=(const Vector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] /= rhs.vec[i];
    }
    return *this;
}

template <class T>
ComplexVector<T> & ComplexVector<T>::operator/=(const std::complex<T> &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] /= rhs;
    }
    return *this;
}

/**
 * \brief Buffer division operator.
 */
template <class T, class U>
inline ComplexVector<T> operator/(ComplexVector<T> lhs, const Vector<U> & rhs)
{
    lhs /= rhs;
    return lhs;
}

/**
 * \brief Scalar division operator.
 */
template <class T>
inline ComplexVector<T> operator/(ComplexVector<T> lhs, const std::complex<T> & rhs)
{
    lhs /= rhs;
    return lhs;
}
 
template <class T>
Vector< std::complex<T> > & ComplexVector<T>::exp() {
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = std::exp(this->vec[i]);
    }
    return *this;
}
   
template <class T>
ComplexVector<T> & ComplexVector<T>::pow(const std::complex<SLICKDSP_FLOAT_TYPE> & exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = std::pow(this->vec[i], exponent);
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
inline ComplexVector<T> & pow(ComplexVector<T> & buffer, const std::complex<SLICKDSP_FLOAT_TYPE> exponent) {
    return buffer.pow(exponent);
}

template <class T>
const std::complex<SLICKDSP_FLOAT_TYPE> ComplexVector<T>::mean() const {
    assert(this->size() > 0);
    std::complex<SLICKDSP_FLOAT_TYPE> sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        sum += this->vec[i];
    }
    return sum / ((SLICKDSP_FLOAT_TYPE) this->size());
}

/**
 * \brief Returns the mean (average) of the data in "buffer".
 */
template <class T>
inline const std::complex<SLICKDSP_FLOAT_TYPE> mean(ComplexVector<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SLICKDSP_FLOAT_TYPE ComplexVector<T>::var() const {
    assert(this->size() > 1);
    std::complex<SLICKDSP_FLOAT_TYPE> meanVal = this->mean();
    std::complex<SLICKDSP_FLOAT_TYPE> sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        std::complex<SLICKDSP_FLOAT_TYPE> varDiff = this->vec[i] - meanVal;
        sum += varDiff * std::conj(varDiff);
    }
    return sum.real() / (this->size() - 1);
}

/**
 * \brief Returns the variance of the data in "buffer".
 */
template <class T>
inline const SLICKDSP_FLOAT_TYPE var(ComplexVector<T> & buffer) {
    return buffer.var();
}

/**
 * \brief Returns the standard deviation of the data in "buffer".
 */
template <class T>
inline const SLICKDSP_FLOAT_TYPE stdDev(ComplexVector<T> & buffer) {
    return buffer.stdDev();
}

template <class T>
ComplexVector<T> & ComplexVector<T>::saturate(const std::complex<T> & val) {
    for (unsigned i=0; i<this->size(); i++) {
        if (this->vec[i].real() > val.real())
            this->vec[i].real(val.real());
        else if (this->vec[i].real() < -val.real())
            this->vec[i].real(-val.real());
        if (this->vec[i].imag() > val.imag())
            this->vec[i].imag(val.imag());
        else if (this->vec[i].imag() < -val.imag())
            this->vec[i].imag(-val.imag());
    }
    return *this;
}

/**
 * \brief Sets the upper and lower limit of the values in "vector".
 *
 * \param vector Data to limit.
 * \param val Limiting value for the data in "vector".  Any values that
 *      are greater than "val" are made equal to "val", and
 *      any that are less than -val are made equal to -val.  This is done
 *      independently on the real and imaginary elements of "vector".
 * \return Reference to "vector".
 */
template <class T>
ComplexVector<T> & saturate(ComplexVector<T> & vector, const std::complex<T> & val) {
    return vector.saturate(val);
}
    
template <class T>
ComplexVector<T> & ComplexVector<T>::fft() {
    assert(domain == TIME_DOMAIN);
    kissfft<T> fftEngine = kissfft<T>(this->size(), false);
    std::vector< std::complex<T> > fftResults(this->size());
    
    fftEngine.transform((typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(this->vec),
                        (typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(fftResults));
    this->vec = fftResults;
    domain = FREQUENCY_DOMAIN;
    return *this;
}

/**
 * \brief Sets "buffer" equal to the FFT of the data in buffer.
 *
 * Sets \ref domain equal to NimbleDSP::FREQUENCY_DOMAIN.
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexVector<T> & fft(ComplexVector<T> &buffer) {
    return buffer.fft();
}

template <class T>
ComplexVector<T> & ComplexVector<T>::conj() {
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i].imag(-this->vec[i].imag());
    }
    return *this;
}

/**
 * \brief Conjugates the data in "buffer".
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexVector<T> & conj(ComplexVector<T> & buffer) {
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
ComplexVector<T> & ComplexVector<T>::magSq() {
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i].real(NimbleDSP::magSq(this->vec[i]));
        this->vec[i].imag(0);
    }
    return *this;
}

/**
 * \brief Sets each element of "buffer" equal to its magnitude squared.
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexVector<T> & magSq(ComplexVector<T> & buffer) {
    return buffer.magSq();
}

template <class T>
ComplexVector<T> & ComplexVector<T>::ifft() {
    assert(domain == FREQUENCY_DOMAIN);
    kissfft<T> fftEngine = kissfft<T>(this->size(), true);
    std::vector< std::complex<T> > fftResults(this->size());
    
    fftEngine.transform((typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(this->vec),
                        (typename kissfft_utils::traits<T>::cpx_type *) VECTOR_TO_ARRAY(fftResults));
    this->vec = fftResults;
    domain = TIME_DOMAIN;
    return *this;
}

/**
 * \brief Sets "buffer" equal to the inverse FFT of the data in buffer.
 *
 * Sets \ref domain equal to NimbleDSP::TIME_DOMAIN.
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
inline ComplexVector<T> & ifft(ComplexVector<T> &buffer) {
    return buffer.ifft();
}

template <class T>
ComplexVector<T> & ComplexVector<T>::angle() {
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i].real(std::arg(this->vec[i]));
        this->vec[i].imag(0);
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
inline ComplexVector<T> & angle(ComplexVector<T> & buffer) {
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
