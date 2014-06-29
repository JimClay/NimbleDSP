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
 * @file RealFixedPtVector.h
 *
 * Definition of the template class RealFixedPtVector.
 */

#ifndef NimbleDSP_RealFixedPtVector_h
#define NimbleDSP_RealFixedPtVector_h

#include <math.h>
#include "RealVector.h"


namespace NimbleDSP {


/**
 * \brief Vector class for real, fixed point (i.e. short's, int's, etc.) numbers.
 */
template <class T>
class RealFixedPtVector : public RealVector<T> {
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
    RealFixedPtVector<T>(unsigned size = DEFAULT_BUF_LEN, std::vector<T> *scratch = NULL) :
            RealVector<T>(size, scratch) {}
            
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
    RealFixedPtVector<T>(std::vector<U> data, std::vector<T> *scratch = NULL) : RealVector<T>(data, scratch) {}
    
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
    RealFixedPtVector<T>(U *data, unsigned dataLen, std::vector<T> *scratch = NULL) :
            RealVector<T>(data, dataLen, scratch) {}
    
    /**
     * \brief Copy constructor.
     */
    RealFixedPtVector<T>(const RealFixedPtVector<T>& other) {this->vec = other.vec;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    RealFixedPtVector<T>& operator=(const Vector<T>& rhs);
    
    /**
     * \brief Pre-increment operator.
     */
    RealFixedPtVector<T> & operator++();
    
    /**
     * \brief Post-increment operator.
     */
    RealFixedPtVector<T> operator++(int);
    
    /**
     * \brief Pre-decrement operator.
     */
    RealFixedPtVector<T> & operator--();
    
    /**
     * \brief Post-decrement operator.
     */
    RealFixedPtVector<T> operator--(int);
    
    /**
     * \brief Buffer modulo/assignment operator.
     */
    template <class U>
    RealFixedPtVector<T> & operator%=(const RealFixedPtVector<U> &rhs);
    
    /**
     * \brief Scalar modulo/assignment operator.
     */
    RealFixedPtVector<T> & operator%=(const T &rhs);
    
    /**
     * \brief Bit-wise negation operator.
     */
    RealFixedPtVector<T> & operator~();
    
    /**
     * \brief Buffer bit-wise and/assignment operator.
     */
    template <class U>
    RealFixedPtVector<T> & operator&=(const RealFixedPtVector<U> &rhs);
    
    /**
     * \brief Scalar bit-wise and/assignment operator.
     */
    RealFixedPtVector<T> & operator&=(const T &rhs);
    
    /**
     * \brief Buffer bit-wise or/assignment operator.
     */
    template <class U>
    RealFixedPtVector<T> & operator|=(const RealFixedPtVector<U> &rhs);
    
    /**
     * \brief Scalar bit-wise or/assignment operator.
     */
    RealFixedPtVector<T> & operator|=(const T &rhs);
    
    /**
     * \brief Buffer bit-wise xor/assignment operator.
     */
    template <class U>
    RealFixedPtVector<T> & operator^=(const RealFixedPtVector<U> &rhs);
    
    /**
     * \brief Scalar bit-wise xor/assignment operator.
     */
    RealFixedPtVector<T> & operator^=(const T &rhs);
    
    /**
     * \brief Buffer right shift/assignment operator.
     */
    template <class U>
    RealFixedPtVector<T> & operator>>=(const RealFixedPtVector<U> &rhs);
    
    /**
     * \brief Scalar right shift/assignment operator.
     */
    RealFixedPtVector<T> & operator>>=(const T &rhs);
    
    /**
     * \brief Buffer left shift/assignment operator.
     */
    template <class U>
    RealFixedPtVector<T> & operator<<=(const RealFixedPtVector<U> &rhs);
    
    /**
     * \brief Scalar left shift/assignment operator.
     */
    RealFixedPtVector<T> & operator<<=(const T &rhs);
    
    /*****************************************************************************************
                                             Methods
    *****************************************************************************************/
    /**
     * \brief Sets each element of \ref buf equal to its value to the power of "exponent".
     *
     * \param exponent Exponent to use.
     * \return Reference to "this".
     */
    RealVector<T> & pow(const SLICKDSP_FLOAT_TYPE exponent);
    
    /**
     * \brief Returns the mode of the data in \ref buf.
     */
    const T mode();
};


template <class T>
RealFixedPtVector<T>& RealFixedPtVector<T>::operator=(const Vector<T>& rhs)
{
    this->vec = rhs.vec;
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator++()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = this->vec[i] + 1;
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> RealFixedPtVector<T>::operator++(int)
{
    RealFixedPtVector<T> tmp(*this);
    operator++();
    return tmp;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator--()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = this->vec[i] - 1;
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> RealFixedPtVector<T>::operator--(int)
{
    RealFixedPtVector<T> tmp(*this);
    operator--();
    return tmp;
}

template <class T>
template <class U>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator%=(const RealFixedPtVector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] %= rhs.vec[i];
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator%=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] %= rhs;
    }
    return *this;
}

/**
 * \brief Buffer modulo operator.
 */
template <class T, class U>
inline RealFixedPtVector<T> operator%(RealFixedPtVector<T> lhs, const RealFixedPtVector<U>& rhs)
{
    lhs %= rhs;
    return lhs;
}

/**
 * \brief Scalar modulo operator.
 */
template <class T>
inline RealFixedPtVector<T> operator%(RealFixedPtVector<T> lhs, const T& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator~()
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = ~(this->vec[i]);
    }
    return *this;
}

template <class T>
template <class U>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator&=(const RealFixedPtVector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] &= rhs.vec[i];
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator&=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] &= rhs;
    }
    return *this;
}

/**
 * \brief Buffer bit-wise and operator.
 */
template <class T, class U>
inline RealFixedPtVector<T> operator&(RealFixedPtVector<T> lhs, const RealFixedPtVector<U>& rhs)
{
    lhs &= rhs;
    return lhs;
}

/**
 * \brief Scalar bit-wise and operator.
 */
template <class T>
inline RealFixedPtVector<T> operator&(RealFixedPtVector<T> lhs, const T& rhs)
{
    lhs &= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator|=(const RealFixedPtVector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] |= rhs.vec[i];
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator|=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] |= rhs;
    }
    return *this;
}

/**
 * \brief Buffer bit-wise or operator.
 */
template <class T, class U>
inline RealFixedPtVector<T> operator|(RealFixedPtVector<T> lhs, const RealFixedPtVector<U>& rhs)
{
    lhs |= rhs;
    return lhs;
}

/**
 * \brief Scalar bit-wise or operator.
 */
template <class T>
inline RealFixedPtVector<T> operator|(RealFixedPtVector<T> lhs, const T& rhs)
{
    lhs |= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator^=(const RealFixedPtVector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] ^= rhs.vec[i];
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator^=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] ^= rhs;
    }
    return *this;
}

/**
 * \brief Buffer bit-wise xor operator.
 */
template <class T, class U>
inline RealFixedPtVector<T> operator^(RealFixedPtVector<T> lhs, const RealFixedPtVector<U>& rhs)
{
    lhs ^= rhs;
    return lhs;
}

/**
 * \brief Scalar bit-wise xor operator.
 */
template <class T>
inline RealFixedPtVector<T> operator^(RealFixedPtVector<T> lhs, const T& rhs)
{
    lhs ^= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator>>=(const RealFixedPtVector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] >>= rhs.vec[i];
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator>>=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] >>= rhs;
    }
    return *this;
}

/**
 * \brief Buffer right shift operator.
 */
template <class T, class U>
inline RealFixedPtVector<T> operator>>(RealFixedPtVector<T> lhs, const RealFixedPtVector<U>& rhs)
{
    lhs >>= rhs;
    return lhs;
}

/**
 * \brief Scalar right shift operator.
 */
template <class T>
inline RealFixedPtVector<T> operator>>(RealFixedPtVector<T> lhs, const T& rhs)
{
    lhs >>= rhs;
    return lhs;
}

template <class T>
template <class U>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator<<=(const RealFixedPtVector<U> &rhs)
{
    assert(this->size() == rhs.size());
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] <<= rhs.vec[i];
    }
    return *this;
}

template <class T>
RealFixedPtVector<T> & RealFixedPtVector<T>::operator<<=(const T &rhs)
{
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] <<= rhs;
    }
    return *this;
}

/**
 * \brief Buffer left shift operator.
 */
template <class T, class U>
inline RealFixedPtVector<T> operator<<(RealFixedPtVector<T> lhs, const RealFixedPtVector<U>& rhs)
{
    lhs <<= rhs;
    return lhs;
}

/**
 * \brief Scalar left shift operator.
 */
template <class T>
inline RealFixedPtVector<T> operator<<(RealFixedPtVector<T> lhs, const T& rhs)
{
    lhs <<= rhs;
    return lhs;
}

template <class T>
RealVector<T> & RealFixedPtVector<T>::pow(const SLICKDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->vec[i] = (T) std::round(std::pow(this->vec[i], exponent));
    }
    return *this;
}
    
template <class T>
const T RealFixedPtVector<T>::mode() {
    assert(this->size() > 0);
    std::vector<T> tempScratch;
    std::vector<T> *scratch;

    if (this->scratchBuf == NULL) {
        scratch = &tempScratch;
    }
    else {
        scratch = this->scratchBuf;
    }
    *scratch = this->vec;
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
const T mode(RealFixedPtVector<T> & buffer) {
    return buffer.mode();
}

};


#endif
