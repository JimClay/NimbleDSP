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
 * @file RealFixedPtDspBuffer.h
 *
 * Definition of the template class RealFixedPtDspBuffer.
 */

#ifndef NimbleDSP_RealFixedPtDspBuffer_h
#define NimbleDSP_RealFixedPtDspBuffer_h

#include <math.h>
#include "RealDspBuffer.h"


namespace NimbleDSP {


/**
 * \brief DspBuffer class for real, fixed point (i.e. short's, int's, etc.) numbers.
 */
template <class T>
class RealFixedPtDspBuffer : public RealDspBuffer<T> {
 public:
    /*****************************************************************************************
                                        Constructors
    *****************************************************************************************/
    /**
     * \brief Basic constructor.
     *
     * Just sets the size of \ref buf and the pointer to the scratch buffer, if one is provided.
     * \param size Size of \ref buf.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    RealFixedPtDspBuffer<T>(unsigned size = DEFAULT_BUF_LEN, std::vector<T> *scratch = NULL) :
            RealDspBuffer<T>(size, scratch) {}
            
    /**
     * \brief Vector constructor.
     *
     * Sets buf equal to the input "data" parameter and sets the pointer to the scratch buffer,
     *      if one is provided.
     * \param data Vector that \ref buf will be set equal to.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    template <typename U>
    RealFixedPtDspBuffer<T>(std::vector<U> data, std::vector<T> *scratch = NULL) : RealDspBuffer<T>(data, scratch) {}
    
    /**
     * \brief Array constructor.
     *
     * Sets buf equal to the input "data" array and sets the pointer to the scratch buffer,
     *      if one is provided.
     * \param data Array that \ref buf will be set equal to.
     * \param dataLen Length of "data".
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    template <typename U>
    RealFixedPtDspBuffer<T>(U *data, unsigned dataLen, std::vector<T> *scratch = NULL) :
            RealDspBuffer<T>(data, dataLen, scratch) {}
    
    /**
     * \brief Copy constructor.
     */
    RealFixedPtDspBuffer<T>(const RealFixedPtDspBuffer<T>& other) {this->buf = other.buf;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    RealFixedPtDspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    /**
     * \brief Pre-increment operator.
     */
    RealFixedPtDspBuffer<T> & operator++();
    
    /**
     * \brief Post-increment operator.
     */
    RealFixedPtDspBuffer<T> operator++(int);
    
    /**
     * \brief Pre-decrement operator.
     */
    RealFixedPtDspBuffer<T> & operator--();
    
    /**
     * \brief Post-decrement operator.
     */
    RealFixedPtDspBuffer<T> operator--(int);
    
    /**
     * \brief Buffer modulo/assignment operator.
     */
    template <class U>
    RealFixedPtDspBuffer<T> & operator%=(const RealFixedPtDspBuffer<U> &rhs);
    
    /**
     * \brief Scalar modulo/assignment operator.
     */
    RealFixedPtDspBuffer<T> & operator%=(const T &rhs);
    
    /**
     * \brief Bit-wise negation operator.
     */
    RealFixedPtDspBuffer<T> & operator~();
    
    /**
     * \brief Buffer bit-wise and/assignment operator.
     */
    template <class U>
    RealFixedPtDspBuffer<T> & operator&=(const RealFixedPtDspBuffer<U> &rhs);
    
    /**
     * \brief Scalar bit-wise and/assignment operator.
     */
    RealFixedPtDspBuffer<T> & operator&=(const T &rhs);
    
    /**
     * \brief Buffer bit-wise or/assignment operator.
     */
    template <class U>
    RealFixedPtDspBuffer<T> & operator|=(const RealFixedPtDspBuffer<U> &rhs);
    
    /**
     * \brief Scalar bit-wise or/assignment operator.
     */
    RealFixedPtDspBuffer<T> & operator|=(const T &rhs);
    
    /**
     * \brief Buffer bit-wise xor/assignment operator.
     */
    template <class U>
    RealFixedPtDspBuffer<T> & operator^=(const RealFixedPtDspBuffer<U> &rhs);
    
    /**
     * \brief Scalar bit-wise xor/assignment operator.
     */
    RealFixedPtDspBuffer<T> & operator^=(const T &rhs);
    
    /**
     * \brief Buffer right shift/assignment operator.
     */
    template <class U>
    RealFixedPtDspBuffer<T> & operator>>=(const RealFixedPtDspBuffer<U> &rhs);
    
    /**
     * \brief Scalar right shift/assignment operator.
     */
    RealFixedPtDspBuffer<T> & operator>>=(const T &rhs);
    
    /**
     * \brief Buffer left shift/assignment operator.
     */
    template <class U>
    RealFixedPtDspBuffer<T> & operator<<=(const RealFixedPtDspBuffer<U> &rhs);
    
    /**
     * \brief Scalar left shift/assignment operator.
     */
    RealFixedPtDspBuffer<T> & operator<<=(const T &rhs);
    
    /*****************************************************************************************
                                             Methods
    *****************************************************************************************/
    /**
     * \brief Sets each element of \ref buf equal to its value to the power of "exponent".
     *
     * \param exponent Exponent to use.
     * \return Reference to "this".
     */
    RealDspBuffer<T> & pow(const SLICKDSP_FLOAT_TYPE exponent);
    
    /**
     * \brief Returns the mode of the data in \ref buf.
     */
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

/**
 * \brief Buffer modulo operator.
 */
template <class T, class U>
inline RealFixedPtDspBuffer<T> operator%(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs %= rhs;
    return lhs;
}

/**
 * \brief Scalar modulo operator.
 */
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

/**
 * \brief Buffer bit-wise and operator.
 */
template <class T, class U>
inline RealFixedPtDspBuffer<T> operator&(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs &= rhs;
    return lhs;
}

/**
 * \brief Scalar bit-wise and operator.
 */
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

/**
 * \brief Buffer bit-wise or operator.
 */
template <class T, class U>
inline RealFixedPtDspBuffer<T> operator|(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs |= rhs;
    return lhs;
}

/**
 * \brief Scalar bit-wise or operator.
 */
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

/**
 * \brief Buffer bit-wise xor operator.
 */
template <class T, class U>
inline RealFixedPtDspBuffer<T> operator^(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs ^= rhs;
    return lhs;
}

/**
 * \brief Scalar bit-wise xor operator.
 */
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

/**
 * \brief Buffer right shift operator.
 */
template <class T, class U>
inline RealFixedPtDspBuffer<T> operator>>(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs >>= rhs;
    return lhs;
}

/**
 * \brief Scalar right shift operator.
 */
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

/**
 * \brief Buffer left shift operator.
 */
template <class T, class U>
inline RealFixedPtDspBuffer<T> operator<<(RealFixedPtDspBuffer<T> lhs, const RealFixedPtDspBuffer<U>& rhs)
{
    lhs <<= rhs;
    return lhs;
}

/**
 * \brief Scalar left shift operator.
 */
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

/**
 * \brief Returns the mode of the data in \ref buf.
 */
template <class T>
const T mode(RealFixedPtDspBuffer<T> & buffer) {
    return buffer.mode();
}

};


#endif
