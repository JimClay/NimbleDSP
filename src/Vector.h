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
 * @file Vector.h
 *
 * Definition of the template class Vector.
 */

#ifndef NimbleDSP_Vector_h
#define NimbleDSP_Vector_h


#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <complex>
#include "kiss_fft.h"
#include "kiss_fftr.h"


namespace NimbleDSP {

const unsigned DEFAULT_BUF_LEN = 0;

#ifndef SLICKDSP_FLOAT_TYPE
#define SLICKDSP_FLOAT_TYPE    double
#endif

#define VECTOR_TO_ARRAY(x)      (&((x)[0]))


/**
 * \brief Base class for NimbleDSP.
 *
 * Although you can instantiate objects of this type, that's not what this class is intended for.  It is the
 * base class that all of the other classes descend from which allows for a great deal of flexibility
 * through polymorphism.  It also reduces the amount of code because we don't have to replicate the same
 * functionality in each class.
 *
 * Derived classes: RealVector and ComplexVector.
 */
template <class T>
class Vector {

 protected:
    /** 
     * \brief Buffer to store intermediate calculations when needed.
     */
    std::vector<T> *scratchBuf;
    
    /** 
     * \brief Initializes vec to a given size and fills it with zeros.
     */
    void initSize(unsigned size) {vec = std::vector<T>(size);}
    
    /** 
     * \brief Initializes vec with the size and contents of "array".
     *
     * \param array Array to set vec equal to.
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
	std::vector<T> vec;
    
    template <class U> friend class Vector;
    template <class U> friend class RealVector;
    template <class U> friend class RealFirFilter;
    
    /*****************************************************************************************
                                        Constructors
    *****************************************************************************************/
    /**
     * \brief Basic constructor.
     *
     * Just sets the size of \ref vec and the pointer to the scratch buffer, if one is provided.
     * \param size Size of \ref vec.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    Vector<T>(unsigned size = 0, std::vector<T> *scratch = NULL) {initSize(size); scratchBuf = scratch;}
    
    /**
     * \brief Vector constructor.
     *
     * Sets vec equal to the input "data" parameter and sets the pointer to the scratch buffer,
     *      if one is provided.
     * \param data Vector that \ref vec will be set equal to.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    template <typename U>
    Vector<T>(std::vector<U> data, std::vector<T> *scratch = NULL) {initArray(VECTOR_TO_ARRAY(data), data.size()); scratchBuf = scratch;}
    
    /**
     * \brief Array constructor.
     *
     * Sets vec equal to the input "data" array and sets the pointer to the scratch buffer,
     *      if one is provided.
     * \param data Array that \ref vec will be set equal to.
     * \param dataLen Length of "data".
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    template <typename U>
    Vector<T>(U *data, unsigned dataLen, std::vector<T> *scratch = NULL) {initArray(data, dataLen); scratchBuf = scratch;}
    
    /**
     * \brief Copy constructor.
     */
    Vector<T>(const Vector<T>& other) {vec = other.vec; scratchBuf = other.scratchBuf;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    Vector<T>& operator=(const Vector<T>& rhs);
    
    /**
     * \brief Unary minus (negation) operator.
     */
    Vector<T> & operator-();
    
    /**
     * \brief Add Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator+=(const Vector<U> &rhs);
    
    /**
     * \brief Add Scalar/Assignment operator.
     */
    Vector<T> & operator+=(const T &rhs);
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator-=(const Vector<U> &rhs);
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     */
    Vector<T> & operator-=(const T &rhs);
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator*=(const Vector<U> &rhs);
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     */
    Vector<T> & operator*=(const T &rhs);
    
    /**
     * \brief Divide Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator/=(const Vector<U> &rhs);
    
    /**
     * \brief Divide Scalar/Assignment operator.
     */
    Vector<T> & operator/=(const T &rhs);
    
    /**
     * \brief Index assignment operator.
     */
    T& operator[](unsigned index) {return vec[index];};
    
    /**
     * \brief Index operator.
     */
    const T& operator[](unsigned index) const {return vec[index];};
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Returns the size of \ref vec.
     */
    const unsigned size() const {return vec.size();};
    
    /**
     * \brief Finds the first instance of "val" in \ref vec.
     *
     * \param val The value to look for in \ref vec.
     * \return Index of first instance of "val".  If there aren't any elements equal to "val"
     *      it returns -1.
     */
    const int find(const T val) const;
    
    /**
     * \brief Sets the length of \ref vec to "len".
     *
     * \param len The new length for \ref vec.  If len is longer than vec's current size, the
     *      new elements will be set to "val".  If len is less than vec's current size the extra
     *      elements will be cut off and the other elements will remain the same.
     * \param val The value to set any new elements to.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & resize(unsigned len, T val = (T) 0) {vec.resize(len, val); return *this;}
    
    /**
     * \brief Lengthens \ref vec by "len" elements.
     *
     * \param len The number of elements to add to \ref vec.
     * \param val The value to set the new elements to.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & pad(unsigned len, T val = (T) 0) {vec.resize(size()+len, val); return *this;}
    
    /**
     * \brief Inserts rate-1 zeros between samples.
     *
     * \param rate Indicates how many zeros should be inserted between samples.
     * \param phase Indicates how many of the zeros should be before the samples (as opposed to
     *      after).  Valid values are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & upsample(int rate, int phase = 0);
    
    /**
     * \brief Removes rate-1 samples out of every rate samples.
     *
     * \param rate Indicates how many samples should be removed.
     * \param phase Tells the method which sample should be the first to be kept.  Valid values
     *      are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & downsample(int rate, int phase = 0);
    
    /**
     * \brief Returns the sum of all the elements in \ref vec.
     */
	T sum() const;
    
    /**
     * \brief Replaces \ref vec with the cumulative sum of the samples in \ref vec.
     *
     * \param initialVal Initializing value for the cumulative sum.  Defaults to zero.
     * \return Reference to "this".
     */
	Vector<T> & cumsum(T initialVal = 0);
    
    /**
     * \brief Replaces \ref vec with the difference between successive samples in vec.
     *
     * The resulting \ref vec is one element shorter than it was previously.
     * \return Reference to "this".
     */
	Vector<T> & diff();
    
    /**
     * \brief Replaces \ref vec with the difference between successive samples in vec.
     *
     * \param previousVal The last value in the sample stream before the current contents
     *      of \ref vec.  previousVal allows the resulting vec to be the same size as the
     *      previous vec.
     * \return Reference to "this".
     */
    Vector<T> & diff(T & previousVal);
    
    /**
     * \brief Convolution method.
     *
     * \param data The vector that will be filtered.
     * \param trimTails "False" tells the method to return the entire convolution, which is
     *      the length of "data" plus the length of "this" (the filter) - 1.  "True" tells the
     *      method to retain the size of "data" by trimming the tails at both ends of
     *      the convolution.
     * \return Reference to "data", which holds the result of the convolution.
     */
    virtual Vector<T> & conv(Vector<T> & data, bool trimTails = false);
    
    /**
     * \brief Decimate method.
     *
     * This method is equivalent to filtering with the \ref conv method and downsampling
     * with the \ref downsample method, but is much more efficient.
     *
     * \param data The vector that will be filtered.
     * \param rate Indicates how much to downsample.
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "data" by trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "data", which holds the result of the decimation.
     */
    virtual Vector<T> & decimate(Vector<T> & data, int rate, bool trimTails = false);
    
    /**
     * \brief Interpolation method.
     *
     * This method is equivalent to upsampling followed by filtering, but is much more efficient.
     *
     * \param data The vector that will be filtered.
     * \param rate Indicates how much to upsample.
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "data" by trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "data", which holds the result of the interpolation.
     */
    virtual Vector<T> & interp(Vector<T> & data, int rate, bool trimTails = false);
    
    /**
     * \brief Resample method.
     *
     * This method is equivalent to upsampling by "interpRate", filtering, and downsampling
     *      by "decimateRate", but is much more efficient.
     *
     * \param data The vector that will be filtered.
     * \param interpRate Indicates how much to upsample.
     * \param decimateRate Indicates how much to downsample.
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "data" by trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "data", which holds the result of the resampling.
     */
    virtual Vector<T> & resample(Vector<T> & data, int interpRate, int decimateRate, bool trimTails = false);
};


template <class T>
template <class U>
void Vector<T>::initArray(U *array, unsigned arrayLen) {
    vec = std::vector<T>(arrayLen);
    for (unsigned i=0; i<arrayLen; i++) {
        vec[i] = (T) array[i];
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
    vec = rhs.vec;
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator-()
{
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] = -vec[i];
    }
    return *this;
}

template <class T>
template <class U>
Vector<T> & Vector<T>::operator+=(const Vector<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] += rhs.vec[i];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator+=(const T &rhs)
{
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] += rhs;
    }
    return *this;
}

template <class T, class U>
inline Vector<T> operator+(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator+(Vector<T> lhs, const T& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
template <class U>
Vector<T> & Vector<T>::operator-=(const Vector<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] -= rhs.vec[i];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator-=(const T &rhs)
{
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] -= rhs;
    }
    return *this;
}

template <class T, class U>
inline Vector<T> operator-(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator-(Vector<T> lhs, const T& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
template <class U>
Vector<T> & Vector<T>::operator*=(const Vector<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] *= rhs.vec[i];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator*=(const T &rhs)
{
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] *= rhs;
    }
    return *this;
}

template <class T, class U>
inline Vector<T> operator*(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator*(Vector<T> lhs, const T& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
template <class U>
Vector<T> & Vector<T>::operator/=(const Vector<U> &rhs)
{
    assert(size() == rhs.size());
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] /= rhs.vec[i];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator/=(const T &rhs)
{
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] /= rhs;
    }
    return *this;
}

template <class T, class U>
inline Vector<T> operator/(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator/(Vector<T> lhs, const T& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    
    for (unsigned i=0; i<lhs.size(); i++) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <class T>
inline bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {return !(lhs == rhs);}

template <class T>
const int Vector<T>::find(const T val) const {
    for (unsigned i=0; i<size(); i++) {
        if (vec[i] == val) {
            return (int) i;
        }
    }
    return -1;
}

/**
 * \brief Finds the first instance of "val" in \ref vec.
 *
 * \param vector Buffer to operate on.
 * \param val The value to look for in \ref vec.
 * \return Index of first instance of "val".  If there aren't any elements equal to "val"
 *      it returns -1.
 */
template <class T>
const int find(Vector<T> & vector, const T val) {
    return vector.find(val);
}

/**
 * \brief Sets the length of \ref vec to "len".
 *
 * \param vector Buffer to operate on.
 * \param len The new length for \ref vec.  If len is longer than vec's current size, the
 *      new elements will be set to "val".  If len is less than vec's current size the extra
 *      elements will be cut off and the other elements will remain the same.
 * \param val The value to set any new elements to.  Defaults to 0.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & resize(Vector<T> & vector, int len, T val = 0) {
    return vector.resize(len, val);
}

/**
 * \brief Lengthens \ref vec by "len" elements.
 *
 * \param vector Buffer to operate on.
 * \param len The number of elements to add to \ref vec.
 * \param val The value to set the new elements to.  Defaults to 0.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & pad(Vector<T> & vector, int len, T val = 0) {
    return vector.pad(len, val);
}
    
template <class T>
Vector<T> & Vector<T>::upsample(int rate, int phase) {
	assert(rate > 0);
	assert(phase >= 0 && phase < rate);
	if (rate == 1)
		return *this;

	int originalSize = vec.size();
	vec.resize(originalSize*rate);
	int from, to;
	for (from = originalSize - 1, to = vec.size() - (rate - phase); to > 0; from--, to -= rate) {
		vec[to] = vec[from];
		vec[from] = 0;
	}
	return *this;
}

/**
 * \brief Inserts rate-1 zeros between samples.
 *
 * \param vector Buffer to operate on.
 * \param rate Indicates how many zeros should be inserted between samples.
 * \param phase Indicates how many of the zeros should be before the samples (as opposed to
 *      after).  Valid values are 0 to "rate"-1.  Defaults to 0.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & upsample(Vector<T> & vector, int rate, int phase = 0) {
    return vector.upsample(rate, phase);
}

template <class T>
Vector<T> & Vector<T>::downsample(int rate, int phase) {
	assert(rate > 0);
	assert(phase >= 0 && phase < rate);
	if (rate == 1)
		return *this;

	int newSize = vec.size() / rate;
	int from, to;
	for (from = phase, to = 0; to < newSize; from += rate, to++) {
		vec[to] = vec[from];
	}
	vec.resize(newSize);
	return *this;
}

/**
 * \brief Removes rate-1 samples out of every rate samples.
 *
 * \param vector Buffer to operate on.
 * \param rate Indicates how many samples should be removed.
 * \param phase Tells the function which sample should be the first to be kept.  Valid values
 *      are 0 to "rate"-1.  Defaults to 0.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & downsample(Vector<T> & vector, int rate, int phase = 0) {
    return vector.downsample(rate, phase);
}

template <class T>
T Vector<T>::sum() const {
	assert(vec.size() > 0);
	T vectorSum = 0;
	for (unsigned i=0; i<vec.size(); i++) {
		vectorSum += vec[i];
	}
	return vectorSum;
}

/**
 * \brief Returns the sum of all the elements in \ref vec.
 *
 * \param vector Buffer to operate on.
 */
template <class T>
T sum(const Vector<T> & vector) {
	return vector.sum();
}

template <class T>
Vector<T> & Vector<T>::cumsum(T initialVal) {
    T sum = initialVal;
    for (unsigned i=0; i<vec.size(); i++) {
        sum += vec[i];
        vec[i] = sum;
    }
    return *this;
}

/**
 * \brief Replaces "vector" with the cumulative sum of the samples in "vector".
 *
 * \param vector Data to operate on.
 * \param initialVal Initializing value for the cumulative sum.  Defaults to zero.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & cumsum(Vector<T> & vector, T initialVal = 0) {
    return vector.cumsum(initialVal);
}
    
template <class T>
Vector<T> & Vector<T>::diff() {
	assert(vec.size() > 1);
	for (unsigned i=0; i<(vec.size()-1); i++) {
		vec[i] = vec[i + 1] - vec[i];
	}
    vec.resize(vec.size()-1);
    return *this;
}

/**
 * \brief Replaces \ref vec with the difference between successive samples in vec.
 *
 * The resulting \ref vec is one element shorter than it was previously.
 * \param vector Buffer to operate on.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & diff(Vector<T> & vector) {
    return vector.diff();
}

template <class T>
Vector<T> & Vector<T>::diff(T & previousVal) {
	assert(vec.size() > 0);
    T nextPreviousVal = vec[vec.size()-1];
	for (unsigned i=vec.size()-1; i>0; i--) {
		vec[i] = vec[i] - vec[i - 1];
	}
    vec[0] = vec[0] - previousVal;
    previousVal = nextPreviousVal;
    return *this;
}

/**
 * \brief Replaces \ref vec with the difference between successive samples in vec.
 *
 * \param vector Buffer to operate on.
 * \param previousVal The last value in the sample stream before the current contents
 *      of \ref vec.  previousVal allows the resulting vec to be the same size as the
 *      previous vec.
 * \return Reference to "vector".
 */
template <class T>
Vector<T> & diff(Vector<T> & vector, T & previousVal) {
    return vector.diff(previousVal);
}

template <class T>
Vector<T> & Vector<T>::conv(Vector<T> & data, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector<T> scratch;
    std::vector<T> *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.vec;
    
    if (trimTails) {
        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0; resultIndex<((int)this->size()-1) - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size() - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
    }
    else {
        data.resize(data.size() + this->size() - 1);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<(int)this->size()-1; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
    }
    return data;
}

/**
 * \brief Convolution function.
 *
 * \param data Buffer to operate on.
 * \param filter The filter that will convolve "data".
 * \param trimTails "False" tells the function to return the entire convolution, which is
 *      the length of "data" plus the length of "filter" - 1.  "True" tells the
 *      function to retain the size of "data" by trimming the tails at both ends of
 *      the convolution.
 * \return Reference to "data", which holds the result of the convolution.
 */
template <class T>
inline Vector<T> & conv(Vector<T> & data, Vector<T> & filter, bool trimTails = false) {
    return filter.conv(data, trimTails);
}

template <class T>
Vector<T> & Vector<T>::decimate(Vector<T> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector<T> scratch;
    std::vector<T> *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.vec;
    
    if (trimTails) {
        data.resize((data.size() + rate - 1) / rate);
        
        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0; resultIndex<(((int)this->size()-1) - initialTrim + rate - 1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size() - initialTrim + rate - 1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
    }
    else {
        data.resize(((data.size() + this->size() - 1) + (rate - 1)) / rate);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<((int)this->size()-1+rate-1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size()+rate-1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
    }
    return data;
}

/**
 * \brief Decimate function.
 *
 * This function is equivalent to filtering with the \ref conv function and downsampling
 * with the \ref downsample function, but much more efficient.
 *
 * \param data Buffer to operate on.
 * \param rate Indicates how much to downsample.
 * \param filter The filter that will convolve "data".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "data" by trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "data", which holds the result of the decimation.
 */
template <class T>
inline Vector<T> & decimate(Vector<T> & data, int rate, Vector<T> & filter, bool trimTails = false) {
    return filter.decimate(data, rate, trimTails);
}

template <class T>
Vector<T> & Vector<T>::interp(Vector<T> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    std::vector<T> scratch;
    std::vector<T> *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.vec;
    
    if (trimTails) {
        data.resize(data.size() * rate);

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0, dataStart=0; resultIndex<(int)this->size()-1 - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
       
        // Middle full overlap
        for (dataStart=0, filterStart=(int)this->size()-1; resultIndex<(int)dataTmp->size()*rate - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }
    }
    else {
        data.resize(data.size() * rate + this->size() - 1 - (rate - 1));
        
        // Initial partial overlap
        for (resultIndex=0, dataStart=0; resultIndex<(int)this->size()-1; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (dataStart=0, filterStart=resultIndex; resultIndex<(int)dataTmp->size()*rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int) this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }
    }
    return data;
}

/**
 * \brief Interpolation function.
 *
 * This function is equivalent to upsampling followed by filtering, but is much more efficient.
 *
 * \param data Buffer to operate on.
 * \param rate Indicates how much to upsample.
 * \param filter The filter that will convolve "data".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "data" by trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "data", which holds the result of the interpolation.
 */
template <class T>
inline Vector<T> & interp(Vector<T> & data, int rate, Vector<T> & filter, bool trimTails = false) {
    return filter.interp(data, rate, trimTails);
}

template <class T>
Vector<T> & Vector<T>::resample(Vector<T> & data, int interpRate, int decimateRate,  bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    std::vector<T> scratch;
    std::vector<T> *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.vec;
    
    if (trimTails) {
        int interpLen = data.size() * interpRate;
        int resampLen = (interpLen + decimateRate - 1) / decimateRate;
        data.resize(resampLen);

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0, dataStart=0, filterStart=initialTrim;
             resultIndex<((int)this->size()-1 - initialTrim + decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size()*interpRate - initialTrim + decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
    }
    else {
        int interpLen = data.size() * interpRate + this->size() - 1 - (interpRate - 1);
        int resampLen = (interpLen + decimateRate - 1) / decimateRate;
        data.resize(resampLen);
        
        // Initial partial overlap
        for (resultIndex=0, dataStart=0, filterStart=0; resultIndex<((int)this->size()-1+decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size()*interpRate + decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        
        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
    }
    return data;
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
 * \param filter The filter that will convolve "data".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "data" by trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "data", which holds the result of the resampling.
 */
template <class T>
inline Vector<T> & resample(Vector<T> & data, int interpRate, int decimateRate,
            Vector<T> & filter, bool trimTails = false) {
    return filter.resample(data, interpRate, decimateRate, trimTails);
}

};

#endif
