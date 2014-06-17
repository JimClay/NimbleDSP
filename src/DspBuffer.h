
/**
 * @file DspBuffer.h
 *
 * Definition of the template class DspBuffer.
 */

#ifndef SlickDsp_DspBuffer_h
#define SlickDsp_DspBuffer_h


#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include "kiss_fft.h"
#include "kiss_fftr.h"


namespace SlickDsp {

const unsigned DEFAULT_BUF_LEN = 0;

#ifndef SLICKDSP_FLOAT_TYPE
#define SLICKDSP_FLOAT_TYPE    double
#endif

#define VECTOR_TO_ARRAY(x)      (&((x)[0]))


/**
 * \brief Base class for SlickDsp.
 *
 * Although you can instantiate objects of this type, that's not what this class is intended for.  It is the
 * base class that all of the other classes descend from which allows for a great deal of flexibility
 * through polymorphism.  It also reduces the amount of code because we don't have to replicate the same
 * functionality in each class.
 *
 * Derived classes: RealDspBuffer and ComplexDspBuffer.
 */
template <class T>
class DspBuffer {

protected:
    /** 
     * \brief Buffer to store intermediate calculations when needed.
     */
    std::vector<T> *scratchBuf;
    
    /** 
     * \brief Initializes buf to a given size and fills it with zeros.
     */
    void initSize(unsigned size) {buf = std::vector<T>(size);}
    
    /** 
     * \brief Initializes buf with the size and contents of "array".
     *
     * \param array Array to set buf equal to.
     * \param arrayLen Number of elements in array.
     */
    template <class U>
    void initArray(U *array, unsigned arrayLen);
    
public:
    /*************************************************************************************//**
     * \brief Vector that holds the object's data.
     *
     * The class is built around this member.  Std::vector's were used because they handle the 
     * dynamic memory, have a rich set of support functions, are fast and efficient, and can
     * be accessed like a normal array when that is convenient.
     *****************************************************************************************/
	std::vector<T> buf;
    
    template <class U> friend class DspBuffer;
    
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
    DspBuffer<T>(unsigned size = 0, std::vector<T> *scratch = NULL) {initSize(size); scratchBuf = scratch;}
    
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
    DspBuffer<T>(std::vector<U> data, std::vector<T> *scratch = NULL) {initArray(VECTOR_TO_ARRAY(data), data.size()); scratchBuf = scratch;}
    
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
    DspBuffer<T>(U *data, unsigned dataLen, std::vector<T> *scratch = NULL) {initArray(data, dataLen); scratchBuf = scratch;}
    
    /**
     * \brief Copy constructor.
     */
    DspBuffer<T>(const DspBuffer<T>& other) {buf = other.buf; scratchBuf = other.scratchBuf;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    DspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    /**
     * \brief Unary minus (negation) operator.
     */
    DspBuffer<T> & operator-();
    
    /**
     * \brief Add Buffer/Assignment operator.
     */
    template <class U>
    DspBuffer<T> & operator+=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Add Scalar/Assignment operator.
     */
    DspBuffer<T> & operator+=(const T &rhs);
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     */
    template <class U>
    DspBuffer<T> & operator-=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     */
    DspBuffer<T> & operator-=(const T &rhs);
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     */
    template <class U>
    DspBuffer<T> & operator*=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     */
    DspBuffer<T> & operator*=(const T &rhs);
    
    /**
     * \brief Divide Buffer/Assignment operator.
     */
    template <class U>
    DspBuffer<T> & operator/=(const DspBuffer<U> &rhs);
    
    /**
     * \brief Divide Scalar/Assignment operator.
     */
    DspBuffer<T> & operator/=(const T &rhs);
    
    /**
     * \brief Index assignment operator.
     */
    T& operator[](unsigned index) {return buf[index];};
    
    /**
     * \brief Index operator.
     */
    const T& operator[](unsigned index) const {return buf[index];};
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Returns the size of \ref buf.
     */
    const unsigned size() const {return buf.size();};
    
    /**
     * \brief Circular rotation.
     *
     * \param numToShift Number of positions to shift in the circular rotation.  numToShift
     *      can be positive or negative.  If you visualize the 0 index value at the left and
     *      the end of the array at the right, positive numToShift values shift the array to
     *      the left, and negative values shift it to the right.
     * \return Reference to "this".
     */
    DspBuffer<T> & rotate(int numToShift);
    
    /**
     * \brief Reverses the order of the elements in \ref buf.
     *
     * \return Reference to "this".
     */
    DspBuffer<T> & reverse();
    
    /**
     * \brief Finds the first instance of "val" in \ref buf.
     *
     * \param val The value to look for in \ref buf.
     * \return Index of first instance of "val".  If there aren't any elements equal to "val"
     *      it returns -1.
     */
    const int find(const T val) const;
    
    /**
     * \brief Changes the elements of \ref buf to their absolute value.
     *
     * \return Reference to "this".
     */
    DspBuffer<T> & abs();
    
    /**
     * \brief Sets each element of \ref buf to e^(element).
     *
     * \return Reference to "this".
     */
    DspBuffer<T> & exp();
    
    /**
     * \brief Sets each element of \ref buf to the natural log of the element.
     *
     * \return Reference to "this".
     */
    DspBuffer<T> & log();
    
    /**
     * \brief Sets each element of \ref buf to the natural log of the element.
     *
     * \return Reference to "this".
     */
    DspBuffer<T> & ln() {return log();}
    
    /**
     * \brief Sets each element of \ref buf to the base 10 log of the element.
     *
     * \return Reference to "this".
     */
    DspBuffer<T> & log10();
    
    /**
     * \brief Sets the length of \ref buf to "len".
     *
     * \param len The new length for \ref buf.  If len is longer than buf's current size, the
     *      new elements will be set to "val".  If len is less than buf's current size the extra
     *      elements will be cut off and the other elements will remain the same.
     * \param val The value to set any new elements to.  Defaults to 0.
     * \return Reference to "this".
     */
    DspBuffer<T> & resize(unsigned len, T val = (T) 0) {buf.resize(len, val); return *this;}
    
    /**
     * \brief Lengthens \ref buf by "len" elements.
     *
     * \param len The number of elements to add to \ref buf.
     * \param val The value to set the new elements to.  Defaults to 0.
     * \return Reference to "this".
     */
    DspBuffer<T> & pad(unsigned len, T val = (T) 0) {buf.resize(size()+len, val); return *this;}
    
    /**
     * \brief Inserts rate-1 zeros between samples.
     *
     * \param rate Indicates how many zeros should be inserted between samples.
     * \param phase Indicates how many of the zeros should be before the samples (as opposed to
     *      after).  Valid values are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    DspBuffer<T> & upsample(int rate, int phase = 0);
    
    /**
     * \brief Removes rate-1 samples out of every rate samples.
     *
     * \param rate Indicates how many samples should be removed.
     * \param phase Tells the method which sample should be the first to be kept.  Valid values
     *      are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    DspBuffer<T> & downsample(int rate, int phase = 0);
    
    /**
     * \brief Returns the sum of all the elements in \ref buf.
     */
	T sum() const;
    
    /**
     * \brief Replaces \ref buf with the difference between successive samples in buf.
     *
     * The resulting \ref buf is one element shorter than it was previously.
     * \return Reference to "this".
     */
	DspBuffer<T> & diff();
    
    /**
     * \brief Replaces \ref buf with the difference between successive samples in buf.
     *
     * \param previousVal The last value in the sample stream before the current contents
     *      of \ref buf.  previousVal allows the resulting buf to be the same size as the
     *      previous buf.
     * \return Reference to "this".
     */
    DspBuffer<T> & diff(T & previousVal);
    
    /**
     * \brief Convolution method.
     *
     * \param filter The filter that will convolve "this".
     * \param trimTails "False" tells the method to return the entire convolution, which is
     *      the length of "this" plus the length of "filter" - 1.  "True" tells the
     *      method to retain the size of "this" be trimming the tails at both ends of
     *      the convolution.
     * \return Reference to "this", which holds the result of the convolution.
     */
    template <class U>
    DspBuffer<U> & conv(DspBuffer<U> & data, bool trimTails = false);
    
    /**
     * \brief Decimate method.
     *
     * This method is equivalent to filtering with the \ref conv method and downsampling
     * with the \ref downsample method, but much more efficient.
     *
     * \param rate Indicates how much to downsample.
     * \param filter The filter that will convolve "this".
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "this" be trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "this", which holds the result of the decimation.
     */
    template <class U>
    DspBuffer<T> & decimate(int rate, DspBuffer<U> & filter, bool trimTails = false);
    
    /**
     * \brief Interpolation method.
     *
     * This method is equivalent to upsampling followed by filtering, but is much more efficient.
     *
     * \param rate Indicates how much to upsample.
     * \param filter The filter that will convolve "this".
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "this" be trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "this", which holds the result of the interpolation.
     */
    template <class U>
    DspBuffer<T> & interp(int rate, DspBuffer<U> & filter, bool trimTails = false);
    
    /**
     * \brief Resample method.
     *
     * This method is equivalent to upsampling by "interpRate", filtering, and downsampling
     *      by "decimateRate", but is much more efficient.
     *
     * \param interpRate Indicates how much to upsample.
     * \param decimateRate Indicates how much to downsample.
     * \param filter The filter that will convolve "this".
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "this" be trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "this", which holds the result of the resampling.
     */
    template <class U>
    DspBuffer<T> & resample(int interpRate, int decimateRate, DspBuffer<U> & filter, bool trimTails = false);
};


template <class T>
template <class U>
void DspBuffer<T>::initArray(U *array, unsigned arrayLen) {
    buf = std::vector<T>(arrayLen);
    for (unsigned i=0; i<arrayLen; i++) {
        buf[i] = (T) array[i];
    }
}

template <class T>
DspBuffer<T>& DspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    buf = rhs.buf;
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-()
{
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] = -buf[i];
    }
    return *this;
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::operator+=(const DspBuffer<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] += rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator+=(const T &rhs)
{
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] += rhs;
    }
    return *this;
}

template <class T, class U>
inline DspBuffer<T> operator+(DspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator+(DspBuffer<T> lhs, const T& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::operator-=(const DspBuffer<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] -= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-=(const T &rhs)
{
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] -= rhs;
    }
    return *this;
}

template <class T, class U>
inline DspBuffer<T> operator-(DspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator-(DspBuffer<T> lhs, const T& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::operator*=(const DspBuffer<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] *= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator*=(const T &rhs)
{
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] *= rhs;
    }
    return *this;
}

template <class T, class U>
inline DspBuffer<T> operator*(DspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator*(DspBuffer<T> lhs, const T& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::operator/=(const DspBuffer<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] /= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator/=(const T &rhs)
{
    for (unsigned i=0; i<buf.size(); i++) {
        buf[i] /= rhs;
    }
    return *this;
}

template <class T, class U>
inline DspBuffer<T> operator/(DspBuffer<T> lhs, const DspBuffer<U>& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator/(DspBuffer<T> lhs, const T& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline bool operator==(const DspBuffer<T>& lhs, const DspBuffer<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    
    for (unsigned i=0; i<lhs.size(); i++) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <class T>
inline bool operator!=(const DspBuffer<T>& lhs, const DspBuffer<T>& rhs) {return !(lhs == rhs);}

template <class T>
DspBuffer<T> & DspBuffer<T>::rotate(int numToShift) {
    while (numToShift < 0)
        numToShift += size();
    
    while (numToShift >= (int) size())
        numToShift -= size();
    
    if (numToShift == 0)
        return *this;

    std::rotate(buf.begin(), buf.begin()+numToShift, buf.end());
    return *this;
}

/**
 * \brief Circular rotation.
 *
 * \param buffer Buffer to rotate.
 * \param numToShift Number of positions to shift in the circular rotation.  numToShift
 *      can be positive or negative.  If you visualize the 0 index value at the left and
 *      the end of the array at the right, positive numToShift values shift the array to
 *      the left, and negative values shift it to the right.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & rotate(DspBuffer<T> & buffer, int numToShift) {
    return buffer.rotate(numToShift);
}

template <class T>
DspBuffer<T> & DspBuffer<T>::reverse() {
    std::reverse(buf.begin(), buf.end());
    return *this;
}

/**
 * \brief Reverses the order of the elements in \ref buf.
 *
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & reverse(DspBuffer<T> & buffer) {
    return buffer.reverse();
}

template <class T>
const int DspBuffer<T>::find(const T val) const {
    for (unsigned i=0; i<size(); i++) {
        if (buf[i] == val) {
            return (int) i;
        }
    }
    return -1;
}

/**
 * \brief Finds the first instance of "val" in \ref buf.
 *
 * \param buffer Buffer to operate on.
 * \param val The value to look for in \ref buf.
 * \return Index of first instance of "val".  If there aren't any elements equal to "val"
 *      it returns -1.
 */
template <class T>
const int find(DspBuffer<T> & buffer, const T val) {
    return buffer.find(val);
}

template <class T>
DspBuffer<T> & DspBuffer<T>::abs() {
    for (unsigned i=0; i<size(); i++) {
        buf[i] = (T) std::abs(buf[i]);
    }
    return *this;
}

/**
 * \brief Changes the elements of \ref buf to their absolute value.
 *
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & abs(DspBuffer<T> & buffer) {
    return buffer.abs();
}

template <class T>
DspBuffer<T> & DspBuffer<T>::exp() {
    for (unsigned i=0; i<size(); i++) {
        buf[i] = (T) std::exp(buf[i]);
    }
    return *this;
}

/**
 * \brief Sets each element of \ref buf to e^(element).
 *
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & exp(DspBuffer<T> & buffer) {
    return buffer.exp();
}

template <class T>
DspBuffer<T> & DspBuffer<T>::log() {
    for (unsigned i=0; i<size(); i++) {
		buf[i] = (T) std::log(buf[i]);
    }
    return *this;
}

/**
 * \brief Sets each element of \ref buf to the natural log of the element.
 *
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & log(DspBuffer<T> & buffer) {
    return buffer.log();
}

/**
 * \brief Sets each element of \ref buf to the natural log of the element.
 *
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & ln(DspBuffer<T> & buffer) {
    return buffer.log();
}

template <class T>
DspBuffer<T> & DspBuffer<T>::log10() {
    for (unsigned i=0; i<size(); i++) {
		buf[i] = (T) std::log10(buf[i]);
    }
    return *this;
}

/**
 * \brief Sets each element of \ref buf to the base 10 log of the element.
 *
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & log10(DspBuffer<T> & buffer) {
    return buffer.log10();
}

/**
 * \brief Sets the length of \ref buf to "len".
 *
 * \param buffer Buffer to operate on.
 * \param len The new length for \ref buf.  If len is longer than buf's current size, the
 *      new elements will be set to "val".  If len is less than buf's current size the extra
 *      elements will be cut off and the other elements will remain the same.
 * \param val The value to set any new elements to.  Defaults to 0.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & resize(DspBuffer<T> & buffer, int len, T val = 0) {
    return buffer.resize(len, val);
}

/**
 * \brief Lengthens \ref buf by "len" elements.
 *
 * \param buffer Buffer to operate on.
 * \param len The number of elements to add to \ref buf.
 * \param val The value to set the new elements to.  Defaults to 0.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & pad(DspBuffer<T> & buffer, int len, T val = 0) {
    return buffer.pad(len, val);
}
    
template <class T>
DspBuffer<T> & DspBuffer<T>::upsample(int rate, int phase) {
	assert(rate > 0);
	assert(phase >= 0 && phase < rate);
	if (rate == 1)
		return *this;

	int originalSize = buf.size();
	buf.resize(originalSize*rate);
	int from, to;
	for (from = originalSize - 1, to = buf.size() - (rate - phase); to > 0; from--, to -= rate) {
		buf[to] = buf[from];
		buf[from] = 0;
	}
	return *this;
}

/**
 * \brief Inserts rate-1 zeros between samples.
 *
 * \param buffer Buffer to operate on.
 * \param rate Indicates how many zeros should be inserted between samples.
 * \param phase Indicates how many of the zeros should be before the samples (as opposed to
 *      after).  Valid values are 0 to "rate"-1.  Defaults to 0.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & upsample(DspBuffer<T> & buffer, int rate, int phase = 0) {
    return buffer.upsample(rate, phase);
}

template <class T>
DspBuffer<T> & DspBuffer<T>::downsample(int rate, int phase) {
	assert(rate > 0);
	assert(phase >= 0 && phase < rate);
	if (rate == 1)
		return *this;

	int newSize = buf.size() / rate;
	int from, to;
	for (from = phase, to = 0; to < newSize; from += rate, to++) {
		buf[to] = buf[from];
	}
	buf.resize(newSize);
	return *this;
}

/**
 * \brief Removes rate-1 samples out of every rate samples.
 *
 * \param buffer Buffer to operate on.
 * \param rate Indicates how many samples should be removed.
 * \param phase Tells the function which sample should be the first to be kept.  Valid values
 *      are 0 to "rate"-1.  Defaults to 0.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & downsample(DspBuffer<T> & buffer, int rate, int phase = 0) {
    return buffer.downsample(rate, phase);
}

template <class T>
T DspBuffer<T>::sum() const {
	assert(buf.size() > 0);
	T bufferSum = 0;
	for (unsigned i=0; i<buf.size(); i++) {
		bufferSum += buf[i];
	}
	return bufferSum;
}

/**
 * \brief Returns the sum of all the elements in \ref buf.
 *
 * \param buffer Buffer to operate on.
 */
template <class T>
T sum(const DspBuffer<T> & buffer) {
	return buffer.sum();
}

template <class T>
DspBuffer<T> & DspBuffer<T>::diff() {
	assert(buf.size() > 1);
	for (unsigned i=0; i<(buf.size()-1); i++) {
		buf[i] = buf[i + 1] - buf[i];
	}
    buf.resize(buf.size()-1);
    return *this;
}

/**
 * \brief Replaces \ref buf with the difference between successive samples in buf.
 *
 * The resulting \ref buf is one element shorter than it was previously.
 * \param buffer Buffer to operate on.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & diff(DspBuffer<T> & buffer) {
    return buffer.diff();
}

template <class T>
DspBuffer<T> & DspBuffer<T>::diff(T & previousVal) {
	assert(buf.size() > 0);
    T nextPreviousVal = buf[buf.size()-1];
	for (unsigned i=buf.size()-1; i>0; i--) {
		buf[i] = buf[i] - buf[i - 1];
	}
    buf[0] = buf[0] - previousVal;
    previousVal = nextPreviousVal;
    return *this;
}

/**
 * \brief Replaces \ref buf with the difference between successive samples in buf.
 *
 * \param buffer Buffer to operate on.
 * \param previousVal The last value in the sample stream before the current contents
 *      of \ref buf.  previousVal allows the resulting buf to be the same size as the
 *      previous buf.
 * \return Reference to "buffer".
 */
template <class T>
DspBuffer<T> & diff(DspBuffer<T> & buffer, T & previousVal) {
    return buffer.diff(previousVal);
}

template <class T>
template <class U>
DspBuffer<U> & DspBuffer<T>::conv(DspBuffer<U> & data, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector<U> scratch;
    std::vector<U> *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.buf;
    
    if (trimTails) {
        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0; resultIndex<((int)this->size()-1) - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size() - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * buf[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * buf[filterIndex];
            }
        }
    }
    else {
        data.resize(data.size() + this->size() - 1);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<(int)this->size()-1; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * buf[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * buf[filterIndex];
            }
        }
    }
    return data;
}

/**
 * \brief Convolution function.
 *
 * \param data Buffer to operate on.
 * \param filter The filter that will convolve "this".
 * \param trimTails "False" tells the function to return the entire convolution, which is
 *      the length of "this" plus the length of "filter" - 1.  "True" tells the
 *      function to retain the size of "this" be trimming the tails at both ends of
 *      the convolution.
 * \return Reference to "buffer", which holds the result of the convolution.
 */
template <class T, class U>
inline DspBuffer<T> & conv(DspBuffer<T> & data, DspBuffer<U> & filter, bool trimTails = false) {
    return filter.conv(data, trimTails);
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::decimate(int rate, DspBuffer<U> & filter, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector<T> scratch;
    std::vector<T> *data;
    
    if (scratchBuf == NULL) {
        data = &scratch;
    }
    else {
        data = scratchBuf;
    }
    *data = this->buf;
    
    if (trimTails) {
        this->resize((this->size() + rate - 1) / rate);
        
        // Initial partial overlap
        int initialTrim = (filter.size() - 1) / 2;
        for (resultIndex=0; resultIndex<(((int)filter.size()-1) - initialTrim + rate - 1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)data->size() - initialTrim + rate - 1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((filter.size()-1) - initialTrim), filterIndex=filter.size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((filter.size()-1) - initialTrim), filterIndex=filter.size()-1;
                 dataIndex<(int)data->size(); dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
    }
    else {
        this->resize(((this->size() + filter.size() - 1) + (rate - 1)) / rate);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<((int)filter.size()-1+rate-1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)data->size()+rate-1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (filter.size()-1), filterIndex=filter.size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (filter.size()-1), filterIndex=filter.size()-1;
                 dataIndex<(int)data->size(); dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
    }
    return *this;
}

/**
 * \brief Decimate function.
 *
 * This function is equivalent to filtering with the \ref conv function and downsampling
 * with the \ref downsample function, but much more efficient.
 *
 * \param data Buffer to operate on.
 * \param rate Indicates how much to downsample.
 * \param filter The filter that will convolve "this".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "this" be trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "buffer", which holds the result of the decimation.
 */
template <class T, class U>
inline DspBuffer<T> & decimate(DspBuffer<T> & data, int rate, DspBuffer<U> & filter, bool trimTails = false) {
    return data.decimate(rate, filter, trimTails);
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::interp(int rate, DspBuffer<U> & filter, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    std::vector<T> scratch;
    std::vector<T> *data;
    
    if (scratchBuf == NULL) {
        data = &scratch;
    }
    else {
        data = scratchBuf;
    }
    *data = this->buf;
    
    if (trimTails) {
        this->resize(this->size() * rate);

        // Initial partial overlap
        int initialTrim = (filter.size() - 1) / 2;
        for (resultIndex=0, dataStart=0; resultIndex<(int)filter.size()-1 - initialTrim; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
       
        // Middle full overlap
        for (dataStart=0, filterStart=(int)filter.size()-1; resultIndex<(int)data->size()*rate - initialTrim; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)data->size(); dataIndex++, filterIndex-=rate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }
    }
    else {
        this->resize(this->size() * rate + filter.size() - 1 - (rate - 1));
        
        // Initial partial overlap
        for (resultIndex=0, dataStart=0; resultIndex<(int)filter.size()-1; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (dataStart=0, filterStart=resultIndex; resultIndex<(int)data->size()*rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)data->size(); dataIndex++, filterIndex-=rate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int) filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }
    }
    return *this;
}

/**
 * \brief Interpolation function.
 *
 * This function is equivalent to upsampling followed by filtering, but is much more efficient.
 *
 * \param data Buffer to operate on.
 * \param rate Indicates how much to upsample.
 * \param filter The filter that will convolve "this".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "this" be trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "buffer", which holds the result of the interpolation.
 */
template <class T, class U>
inline DspBuffer<T> & interp(DspBuffer<T> & data, int rate, DspBuffer<U> & filter, bool trimTails = false) {
    return data.interp(rate, filter, trimTails);
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::resample(int interpRate, int decimateRate, DspBuffer<U> & filter, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    std::vector<T> scratch;
    std::vector<T> *data;
    
    if (scratchBuf == NULL) {
        data = &scratch;
    }
    else {
        data = scratchBuf;
    }
    *data = this->buf;
    
    if (trimTails) {
        int interpLen = this->size() * interpRate;
        int resampLen = (interpLen + decimateRate - 1) / decimateRate;
        this->resize(resampLen);

        // Initial partial overlap
        int initialTrim = (filter.size() - 1) / 2;
        for (resultIndex=0, dataStart=0, filterStart=initialTrim;
             resultIndex<((int)filter.size()-1 - initialTrim + decimateRate-1)/decimateRate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)data->size()*interpRate - initialTrim + decimateRate-1)/decimateRate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Final partial overlap
        for (; resultIndex<(int)this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)data->size(); dataIndex++, filterIndex-=interpRate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
    }
    else {
        int interpLen = this->size() * interpRate + filter.size() - 1 - (interpRate - 1);
        int resampLen = (interpLen + decimateRate - 1) / decimateRate;
        this->resize(resampLen);
        
        // Initial partial overlap
        for (resultIndex=0, dataStart=0, filterStart=0; resultIndex<((int)filter.size()-1+decimateRate-1)/decimateRate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)data->size()*interpRate + decimateRate-1)/decimateRate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Final partial overlap
        for (; resultIndex<(int)this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)data->size(); dataIndex++, filterIndex-=interpRate) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)filter.size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
    }
    return *this;
}

/**
 * \brief Resample function.
 *
 * This function is equivalent to upsampling by "interpRate", filtering, and downsampling
 *      by "decimateRate", but is much more efficient.
 *
 * \param data Buffer to operate on.
 * \param interpRate Indicates how much to upsample.
 * \param decimateRate Indicates how much to downsample.
 * \param filter The filter that will convolve "this".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "this" be trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "buffer", which holds the result of the resampling.
 */
template <class T, class U>
inline DspBuffer<T> & resample(DspBuffer<T> & data, int interpRate, int decimateRate, DspBuffer<U> & filter, bool trimTails = false) {
    return data.resample(interpRate, decimateRate, filter, trimTails);
}

};

#endif
