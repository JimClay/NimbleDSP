//
//  RealFirFilter.h
//  SlickDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

#ifndef SlickDsp_RealFirFilter_h
#define SlickDsp_RealFirFilter_h

#include <complex>
#include <math.h>
#include "RealDspBuffer.h"


namespace SlickDsp {
    
enum FilterOperationType {STREAMING, ONE_SHOT_RETURN_ALL_RESULTS, ONE_SHOT_TRIM_TAILS};
const size_t LARGEST_DATA_TYPE = sizeof(std::complex<long double>);

template <class T>
class ComplexDspBuffer;

template <class T>
class RealFirFilter : public RealDspBuffer<T> {
 protected:
    std::vector<char> state;
    
 public:
     FilterOperationType filtOperation;

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
    RealFirFilter<T>(unsigned size = DEFAULT_BUF_LEN, FilterOperationType operation = STREAMING, std::vector<T> *scratch = NULL) : RealDspBuffer<T>(size, scratch)
            {state.resize((size - 1) * sizeof(std::complex<T>)); filtOperation = operation;}
    
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
    RealFirFilter<T>(std::vector<U> data, FilterOperationType operation = STREAMING, std::vector<T> *scratch = NULL) : RealDspBuffer<T>(data, scratch)
            {state.resize((data.size() - 1) * sizeof(std::complex<T>)); filtOperation = operation;}
    
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
    RealFirFilter<T>(U *data, unsigned dataLen, FilterOperationType operation = STREAMING, std::vector<T> *scratch = NULL) : RealDspBuffer<T>(data, dataLen, scratch)
            {state.resize((dataLen - 1) * sizeof(std::complex<T>)); filtOperation = operation;}
    
    /**
     * \brief Copy constructor.
     */
    RealFirFilter<T>(const RealFirFilter<T>& other) {this->buf = other.buf; state = other.state; filtOperation = other.filtOperation;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    RealFirFilter<T>& operator=(const DspBuffer<T>& rhs) {this->buf = rhs.buf; state.resize(this->size() - 1); filtOperation = STREAMING; return *this;}
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Convolution method.
     *
     * \param data The buffer that will be filtered.
     * \param trimTails "False" tells the method to return the entire convolution, which is
     *      the length of "this" plus the length of "filter" - 1.  "True" tells the
     *      method to retain the size of "this" be trimming the tails at both ends of
     *      the convolution.
     * \return Reference to "this", which holds the result of the convolution.
     */
    virtual DspBuffer<T> & conv(DspBuffer<T> & data, bool trimTails = false);
    virtual ComplexDspBuffer<T> & convComplex(ComplexDspBuffer<T> & data, bool trimTails = false);
    
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
    template <class U>
    DspBuffer<U> & decimate(DspBuffer<U> & data, int rate, bool trimTails = false);
    
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
    template <class U>
    DspBuffer<U> & interp(DspBuffer<U> & data, int rate, bool trimTails = false);
    
    /**
     * \brief Resample method.
     *
     * This method is equivalent to upsampling by "interpRate", filtering, and downsampling
     *      by "decimateRate", but is much more efficient.
     *
     * \param data The buffer that will be filtered.
     * \param interpRate Indicates how much to upsample.
     * \param decimateRate Indicates how much to downsample.
     * \param trimTails "False" tells the method to return the entire convolution.  "True"
     *      tells the method to retain the size of "this" be trimming the tails at both
     *      ends of the convolution.
     * \return Reference to "this", which holds the result of the resampling.
     */
    template <class U>
    DspBuffer<U> & resample(DspBuffer<U> & data, int interpRate, int decimateRate, bool trimTails = false);
};


template <class T>
DspBuffer<T> & RealFirFilter<T>::conv(DspBuffer<T> & data, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector<T> scratch;
    std::vector<T> *dataTmp;
    T *stateArray = (T *) VECTOR_TO_ARRAY(state);
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }

    switch (filtOperation) {

    case STREAMING:
        dataTmp->resize((this->size() - 1) + data.size());
        for (int i=0; i<this->size()-1; i++) {
            (*dataTmp)[i] = stateArray[i];
        }
        for (int i=0; i<data.size(); i++) {
            (*dataTmp)[i + this->size() - 1] = data[i];
        }
        
        for (resultIndex=0; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex, filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        for (int i=0; i<this->size()-1; i++) {
            stateArray[i] = (*dataTmp)[i + data.size()];
        }
        break;

    case ONE_SHOT_RETURN_ALL_RESULTS:
        *dataTmp = data.buf;
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
        break;

    case ONE_SHOT_TRIM_TAILS:
        *dataTmp = data.buf;

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
        break;
    }
    return data;
}

template <class T>
ComplexDspBuffer<T> & RealFirFilter<T>::convComplex(ComplexDspBuffer<T> & data, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    std::complex<T> *stateArray = (std::complex<T> *) VECTOR_TO_ARRAY(state);
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }

    switch (filtOperation) {

    case STREAMING:
        dataTmp->resize((this->size() - 1) + data.size());
        for (int i=0; i<this->size()-1; i++) {
            (*dataTmp)[i] = stateArray[i];
        }
        for (int i=0; i<data.size(); i++) {
            (*dataTmp)[i + this->size() - 1] = data[i];
        }
        
        for (resultIndex=0; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex, filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
            }
        }
        for (int i=0; i<this->size()-1; i++) {
            stateArray[i] = (*dataTmp)[i + data.size()];
        }
        break;

    case ONE_SHOT_RETURN_ALL_RESULTS:
        *dataTmp = data.buf;
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
        break;

    case ONE_SHOT_TRIM_TAILS:
        *dataTmp = data.buf;

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
        break;
    }
    return data;
}

template <class T>
template <class U>
DspBuffer<U> & RealFirFilter<T>::decimate(DspBuffer<U> & data, int rate, bool trimTails) {
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

template <class T>
template <class U>
DspBuffer<U> & RealFirFilter<T>::interp(DspBuffer<U> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
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

template <class T>
template <class U>
DspBuffer<U> & RealFirFilter<T>::resample(DspBuffer<U> & data, int interpRate, int decimateRate,  bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
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
        int interpLen = data.size() * interpRate;
        int resampLen = (interpLen + decimateRate - 1) / decimateRate;
        data.resize(resampLen);

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0, dataStart=0, filterStart=initialTrim;
             resultIndex<((int)this->size()-1 - initialTrim + decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->buf[filterIndex];
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


};


#endif
