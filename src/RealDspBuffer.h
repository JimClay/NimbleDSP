
/**
 * @file RealDspBuffer.h
 *
 * Definition of the template class RealDspBuffer.
 */

#ifndef SlickDsp_RealDspBuffer_h
#define SlickDsp_RealDspBuffer_h

#include "DspBuffer.h"
#include "ComplexDspBuffer.h"

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
     * \param val Limiting value for the data in \ref buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.
     * \return Reference to "this".
     */
    RealDspBuffer<T> & saturate(T val);
    
    virtual ComplexDspBuffer<T> & convComplex(ComplexDspBuffer<T> & data, bool trimTails);
    
    /**
     * \brief Decimate method.
     *
     * This method is equivalent to filtering with the \ref conv method and downsampling
     * with the \ref downsample method, but much more efficient.
     *
     * \param data The buffer that will be filtered.
     * \param rate Indicates how much to downsample.
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "this" be trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "this", which holds the result of the decimation.
     */
    virtual ComplexDspBuffer<T> & decimateComplex(ComplexDspBuffer<T> & data, int rate, bool trimTails = false);
    
    /**
     * \brief Interpolation method.
     *
     * This method is equivalent to upsampling followed by filtering, but is much more efficient.
     *
     * \param data The buffer that will be filtered.
     * \param rate Indicates how much to upsample.
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "this" be trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "this", which holds the result of the interpolation.
     */
    virtual ComplexDspBuffer<T> & interpComplex(ComplexDspBuffer<T> & data, int rate, bool trimTails = false);
    
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
 * \param val Limiting value for the data in \ref buf.  Any values that
 *      are greater than "val" are made equal to "val", and
 *      any that are less than -val are made equal to -val.
 * \return Reference to "buffer".
 */
template <class T>
RealDspBuffer<T> & saturate(RealDspBuffer<T> & buffer, T val) {
    return buffer.saturate(val);
}

template <class T>
ComplexDspBuffer<T> & RealDspBuffer<T>::convComplex(ComplexDspBuffer<T> & data, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size() - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
    }
    else {
        data.resize(data.size() + this->size() - 1);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<(int)this->size()-1; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
 * \return Reference to "data", which holds the result of the convolution.
 */
template <class T>
inline ComplexDspBuffer<T> & conv(ComplexDspBuffer<T> & data, RealDspBuffer<T> & filter, bool trimTails = false) {
    return filter.convComplex(data, trimTails);
}

template <class T>
ComplexDspBuffer<T> & RealDspBuffer<T>::decimateComplex(ComplexDspBuffer<T> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.buf;
    
    if (trimTails) {
        data.resize((data.size() + rate - 1) / rate);
        
        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0; resultIndex<(((int)this->size()-1) - initialTrim + rate - 1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size() - initialTrim + rate - 1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
    }
    else {
        data.resize(((data.size() + this->size() - 1) + (rate - 1)) / rate);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<((int)this->size()-1+rate-1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size()+rate-1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
 * \param filter The filter that will convolve "this".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "this" be trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "data", which holds the result of the decimation.
 */
template <class T>
inline ComplexDspBuffer<T> & decimate(ComplexDspBuffer<T> & data, int rate, RealDspBuffer<T> & filter, bool trimTails = false) {
    return filter.decimateComplex(data, rate, trimTails);
}

template <class T>
ComplexDspBuffer<T> & RealDspBuffer<T>::interpComplex(ComplexDspBuffer<T> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }
    *dataTmp = data.buf;
    
    if (trimTails) {
        data.resize(data.size() * rate);

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0, dataStart=0; resultIndex<(int)this->size()-1 - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
       
        // Middle full overlap
        for (dataStart=0, filterStart=(int)this->size()-1; resultIndex<(int)dataTmp->size()*rate - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        
        // Middle full overlap
        for (dataStart=0, filterStart=resultIndex; resultIndex<(int)dataTmp->size()*rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
 * \param filter The filter that will convolve "this".
 * \param trimTails "False" tells the function to return the entire convolution.  "True"
 *      tells the function to retain the size of "this" be trimming the tails at both
 *      ends of the convolution.
 * \return Reference to "data", which holds the result of the interpolation.
 */
template <class T>
inline ComplexDspBuffer<T> & interp(ComplexDspBuffer<T> & data, int rate, RealDspBuffer<T> & filter, bool trimTails = false) {
    return filter.interpComplex(data, rate, trimTails);
}

};

#endif
