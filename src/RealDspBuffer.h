
/**
 * @file RealDspBuffer.h
 *
 * Definition of the template class RealDspBuffer.
 */

#ifndef SlickDsp_RealDspBuffer_h
#define SlickDsp_RealDspBuffer_h

#include "DspBuffer.h"

using namespace SlickDsp;

namespace SlickDsp {

/**
 * \brief DspBuffer class for real numbers.
 */
template <class T>
class RealDspBuffer : public DspBuffer<T> {
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
    RealDspBuffer<T>(unsigned size = DEFAULT_BUF_LEN, std::vector<T> *scratch = NULL) : DspBuffer<T>(size, scratch) {}
    
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
    RealDspBuffer<T>(std::vector<U> data, std::vector<T> *scratch = NULL) : DspBuffer<T>(data, scratch) {}
    
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
    RealDspBuffer<T>(U *data, unsigned dataLen, std::vector<T> *scratch = NULL) : DspBuffer<T>(data, dataLen, scratch) {}
    
    /**
     * \brief Copy constructor.
     */
    RealDspBuffer<T>(const RealDspBuffer<T>& other) {this->buf = other.buf;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    RealDspBuffer<T>& operator=(const DspBuffer<T>& rhs) {this->buf = rhs.buf; return *this;}
    
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
     * \brief Returns the mean (average) of the data in \ref buf.
     */
    const SLICKDSP_FLOAT_TYPE mean() const;
    
    /**
     * \brief Returns the variance of the data in \ref buf.
     */
    const SLICKDSP_FLOAT_TYPE var() const;
    
    /**
     * \brief Returns the standard deviation of the data in \ref buf.
     */
    const SLICKDSP_FLOAT_TYPE stdDev() const {return std::sqrt(this->var());}
    
    /**
     * \brief Returns the median element of \ref buf.
     */
    const T median();
    
    /**
     * \brief Returns the maximum element in \ref buf.
     *
     * \param maxLoc If it isn't equal to NULL the index of the maximum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the maximum value the index of the first will be returned.
     *      Defaults to NULL.
     */
    const T max(unsigned *maxLoc = NULL) const;
    
    /**
     * \brief Returns the minimum element in \ref buf.
     *
     * \param minLoc If it isn't equal to NULL the index of the minimum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the minimum value the index of the first will be returned.
     *      Defaults to NULL.
     */
    const T min(unsigned *minLoc = NULL) const;
    
    /**
     * \brief Sets the upper and lower limit of the values in \ref buf.
     *
     * \param Limiting value for the data in \ref buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.
     * \return Reference to "this".
     */
    RealDspBuffer<T> & saturate(T val);
};

template <class T>
RealDspBuffer<T> & RealDspBuffer<T>::pow(const SLICKDSP_FLOAT_TYPE exponent) {
    for (unsigned i=0; i<this->size(); i++) {
        this->buf[i] = (T) std::pow(this->buf[i], exponent);
    }
    return *this;
}

/**
 * \brief Sets each element of "buffer" equal to its value to the power of "exponent".
 *
 * \param buffer The buffer to operate on.
 * \param exponent Exponent to use.
 * \return Reference to "buffer".
 */
template <class T>
RealDspBuffer<T> & pow(RealDspBuffer<T> & buffer, const SLICKDSP_FLOAT_TYPE exponent) {
    return buffer.pow(exponent);
}

template <class T>
const SLICKDSP_FLOAT_TYPE RealDspBuffer<T>::mean() const {
    assert(this->size() > 0);
    SLICKDSP_FLOAT_TYPE sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        sum += this->buf[i];
    }
    return sum / this->size();
}

/**
 * \brief Returns the mean (average) of the data in "buffer".
 * \param buffer The buffer to operate on.
 */
template <class T>
const SLICKDSP_FLOAT_TYPE mean(RealDspBuffer<T> & buffer) {
    return buffer.mean();
}

template <class T>
const SLICKDSP_FLOAT_TYPE RealDspBuffer<T>::var() const {
    assert(this->size() > 1);
    SLICKDSP_FLOAT_TYPE meanVal = mean();
    SLICKDSP_FLOAT_TYPE sum = 0;
    for (unsigned i=0; i<this->size(); i++) {
        SLICKDSP_FLOAT_TYPE varDiff = ((SLICKDSP_FLOAT_TYPE) this->buf[i]) - meanVal;
        sum += varDiff * varDiff;
    }
    return sum / (this->size() - 1);
}

/**
 * \brief Returns the variance of the data in "buffer".
 * \param buffer The buffer to operate on.
 */
template <class T>
const SLICKDSP_FLOAT_TYPE var(RealDspBuffer<T> & buffer) {
    return buffer.var();
}

/**
 * \brief Returns the standard deviation of the data in "buffer".
 * \param buffer The buffer to operate on.
 */
template <class T>
const SLICKDSP_FLOAT_TYPE stdDev(RealDspBuffer<T> & buffer) {
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

/**
 * \brief Returns the median element of "buffer".
 * \param buffer The buffer to operate on.
 */
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

/**
 * \brief Returns the maximum element in "buffer".
 *
 * \param buffer The buffer to search.
 * \param maxLoc If it isn't equal to NULL the index of the maximum element
 *      will be returned via this pointer.  If more than one element is equal
 *      to the maximum value the index of the first will be returned.
 *      Defaults to NULL.
 */
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

/**
 * \brief Returns the minimum element in "buffer".
 *
 * \param buffer The buffer to search.
 * \param minLoc If it isn't equal to NULL the index of the minimum element
 *      will be returned via this pointer.  If more than one element is equal
 *      to the minimum value the index of the first will be returned.
 *      Defaults to NULL.
 */
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

/**
 * \brief Sets the upper and lower limit of the values in "buffer".
 *
 * \param buffer The buffer to operate on.
 * \param Limiting value for the data in \ref buf.  Any values that
 *      are greater than "val" are made equal to "val", and
 *      any that are less than -val are made equal to -val.
 * \return Reference to "buffer".
 */
template <class T>
RealDspBuffer<T> & saturate(RealDspBuffer<T> & buffer, T val) {
    return buffer.saturate(val);
}

};

#endif
