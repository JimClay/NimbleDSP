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
 * @file ComplexFirFilter.h
 *
 * Definition of the template class ComplexFirFilter.
 */

#ifndef NimbleDSP_ComplexFirFilter_h
#define NimbleDSP_ComplexFirFilter_h

#include <complex>
#include <math.h>
#include "ComplexVector.h"


namespace NimbleDSP {
    
/**
 * \brief Class for complex FIR filters.
 */
template <class T>
class ComplexFirFilter : public ComplexVector<T> {
 protected:
    /**
     * \brief Saved data that is used for stream filtering.
     */
    std::vector<char> savedData;
    
    /**
     * \brief Indicates how many samples are in \ref savedData.  Used for stream filtering.
     */
    int numSavedSamples;
    
    /**
     * \brief Indicates the filter phase.  Used for stream filtering.
     */
    int phase;
    
 public:
    /**
     * \brief Determines how the filter should filter.
     *
     * NimbleDSP::ONE_SHOT_RETURN_ALL_RESULTS is equivalent to "trimTails = false" of the Vector convolution methods.
     * NimbleDSP::ONE_SHOT_TRIM_TAILS is equivalent to "trimTails = true" of the Vector convolution methods.
     * NimbleDSP::STREAMING maintains the filter state from call to call so it can produce results as if it had
     *      filtered one continuous set of data.
     */
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
    ComplexFirFilter<T>(unsigned size = DEFAULT_BUF_LEN, FilterOperationType operation = STREAMING, std::vector<T> *scratch = NULL) : ComplexVector<T>(size, scratch)
            {if (size > 0) {savedData.resize((size - 1) * sizeof(std::complex<T>)); numSavedSamples = size - 1;}
             else {savedData.resize(0); numSavedSamples = 0;} phase = 0; filtOperation = operation;}
    
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
    ComplexFirFilter<T>(std::vector<U> data, FilterOperationType operation = STREAMING, std::vector<T> *scratch = NULL) : ComplexVector<T>(data, scratch)
            {savedData.resize((data.size() - 1) * sizeof(std::complex<T>)); numSavedSamples = data.size() - 1; phase = 0; filtOperation = operation;}
    
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
    ComplexFirFilter<T>(U *data, unsigned dataLen, FilterOperationType operation = STREAMING, std::vector< std::complex<T> > *scratch = NULL) : ComplexVector<T>(data, dataLen, NimbleDSP::TIME_DOMAIN, scratch)
            {savedData.resize((dataLen - 1) * sizeof(std::complex<T>)); numSavedSamples = dataLen - 1; phase = 0; filtOperation = operation;}
    
    /**
     * \brief Copy constructor.
     */
    ComplexFirFilter<T>(const ComplexFirFilter<T>& other) {this->vec = other.vec; savedData = other.savedData;
            numSavedSamples = other.numSavedSamples; phase = other.phase; filtOperation = other.filtOperation;}
    
    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Assignment operator.
     */
    ComplexFirFilter<T>& operator=(const Vector<T>& rhs) {this->vec = rhs.vec; savedData.resize(this->size() - 1); phase = 0; filtOperation = STREAMING; return *this;}
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Convolution method.
     *
     * \param data The buffer that will be filtered.
     * \param trimTails This parameter is ignored.  The operation of the filter is determined by how
     *      \ref filtOperation is set.
     * \return Reference to "data", which holds the result of the convolution.
     */
    virtual ComplexVector<T> & conv(ComplexVector<T> & data, bool trimTails = false);
    
    /**
     * \brief Decimate method.
     *
     * This method is equivalent to filtering with the \ref conv method and downsampling
     * with the \ref downsample method, but much more efficient.
     *
     * \param data The buffer that will be filtered.
     * \param rate Indicates how much to downsample.
     * \param trimTails This parameter is ignored.  The operation of the filter is determined by how
     *      \ref filtOperation is set.
     * \return Reference to "data", which holds the result of the decimation.
     */
    virtual ComplexVector<T> & decimate(ComplexVector<T> & data, int rate, bool trimTails = false);
    
    /**
     * \brief Interpolation method.
     *
     * This method is equivalent to upsampling followed by filtering, but is much more efficient.
     *
     * \param data The buffer that will be filtered.
     * \param rate Indicates how much to upsample.
     * \param trimTails This parameter is ignored.  The operation of the filter is determined by how
     *      \ref filtOperation is set.
     * \return Reference to "data", which holds the result of the interpolation.
     */
    virtual ComplexVector<T> & interp(ComplexVector<T> & data, int rate, bool trimTails = false);
    
    /**
     * \brief Resample method.
     *
     * This method is equivalent to upsampling by "interpRate", filtering, and downsampling
     *      by "decimateRate", but is much more efficient.
     *
     * \param data The buffer that will be filtered.
     * \param interpRate Indicates how much to upsample.
     * \param decimateRate Indicates how much to downsample.
     * \param trimTails This parameter is ignored.  The operation of the filter is determined by how
     *      \ref filtOperation is set.
     * \return Reference to "data", which holds the result of the resampling.
     */
    virtual ComplexVector<T> & resample(ComplexVector<T> & data, int interpRate, int decimateRate, bool trimTails = false);
};


template <class T>
ComplexVector<T> & ComplexFirFilter<T>::conv(ComplexVector<T> & data, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    std::complex<T> *savedDataArray = (std::complex<T> *) VECTOR_TO_ARRAY(savedData);
    
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
            (*dataTmp)[i] = savedDataArray[i];
        }
        for (int i=0; i<data.size(); i++) {
            (*dataTmp)[i + this->size() - 1] = data[i];
        }
        
        for (resultIndex=0; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex, filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        for (int i=0; i<this->size()-1; i++) {
            savedDataArray[i] = (*dataTmp)[i + data.size()];
        }
        break;

    case ONE_SHOT_RETURN_ALL_RESULTS:
        *dataTmp = data.vec;
        data.resize(data.size() + this->size() - 1);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<(int)this->size()-1; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        break;

    case ONE_SHOT_TRIM_TAILS:
        *dataTmp = data.vec;

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0; resultIndex<((int)this->size()-1) - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(int)dataTmp->size() - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        break;
    }
    return data;
}

template <class T>
ComplexVector<T> & ComplexFirFilter<T>::decimate(ComplexVector<T> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    std::complex<T> *savedDataArray = (std::complex<T> *) VECTOR_TO_ARRAY(savedData);
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }

    switch (filtOperation) {

    case STREAMING: {
        dataTmp->resize(numSavedSamples + data.size());
        for (int i=0; i<numSavedSamples; i++) {
            (*dataTmp)[i] = savedDataArray[i];
        }
        for (int i=0; i<data.size(); i++) {
            (*dataTmp)[i + numSavedSamples] = data[i];
        }
        
        data.resize((data.size() + numSavedSamples - (this->size() - 1) + rate - 1)/rate);
        for (resultIndex=0; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate, filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        int nextResultDataPoint = resultIndex * rate;
        numSavedSamples = dataTmp->size() - nextResultDataPoint;

        for (int i=0; i<numSavedSamples; i++) {
            savedDataArray[i] = (*dataTmp)[i + nextResultDataPoint];
        }
        }
        break;

    case ONE_SHOT_RETURN_ALL_RESULTS:
        *dataTmp = data.vec;
        data.resize(((data.size() + this->size() - 1) + (rate - 1)) / rate);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<((int)this->size()-1+rate-1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size()+rate-1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (this->size()-1), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (this->size()-1), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        break;

    case ONE_SHOT_TRIM_TAILS:
        *dataTmp = data.vec;
        data.resize((data.size() + rate - 1) / rate);
        
        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0; resultIndex<(((int)this->size()-1) - initialTrim + rate - 1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<((int)dataTmp->size() - initialTrim + rate - 1)/rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<(int)data.size(); resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((this->size()-1) - initialTrim), filterIndex=this->size()-1;
                 dataIndex<(int)dataTmp->size(); dataIndex++, filterIndex--) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        break;
    }
    return data;
}

template <class T>
ComplexVector<T> & ComplexFirFilter<T>::interp(ComplexVector<T> & data, int rate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    std::complex<T> *savedDataArray = (std::complex<T> *) VECTOR_TO_ARRAY(savedData);
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }

    switch (filtOperation) {

    case STREAMING: {
        int numTaps = (this->size() + rate - 1) / rate;
        if (numSavedSamples >= numTaps) {
            // First call to interp, have too many "saved" (really just the initial zeros) samples
            numSavedSamples = numTaps - 1;
            phase = (numTaps - 1) * rate;
        }
        
        dataTmp->resize(numSavedSamples + data.size());
        for (int i=0; i<numSavedSamples; i++) {
            (*dataTmp)[i] = savedDataArray[i];
        }
        for (int i=0; i<data.size(); i++) {
            (*dataTmp)[i + numSavedSamples] = data[i];
        }
        
        data.resize(dataTmp->size() * rate);
        bool keepGoing = true;
        for (resultIndex=0, dataStart=0, filterStart=phase; keepGoing; ++resultIndex) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
                if (dataTmp->size() - dataStart == numSavedSamples) {
                    keepGoing = false;
                    phase = filterStart;
                }
            }
        }
        data.resize(resultIndex);

        int i;
        for (i=0; dataStart<dataTmp->size(); i++, dataStart++) {
            savedDataArray[i] = (*dataTmp)[dataStart];
        }
        numSavedSamples = i;
        }
        break;

    case ONE_SHOT_RETURN_ALL_RESULTS:
        *dataTmp = data.vec;
        data.resize(data.size() * rate + this->size() - 1 - (rate - 1));
        
        // Initial partial overlap
        for (resultIndex=0, dataStart=0; resultIndex<(int)this->size()-1; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
        
        // Middle full overlap
        for (dataStart=0, filterStart=resultIndex; resultIndex<(int)dataTmp->size()*rate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int) this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }
        break;

    case ONE_SHOT_TRIM_TAILS:
        *dataTmp = data.vec;
        data.resize(data.size() * rate);

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0, dataStart=0; resultIndex<(int)this->size()-1 - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
        }
       
        // Middle full overlap
        for (dataStart=0, filterStart=(int)this->size()-1; resultIndex<(int)dataTmp->size()*rate - initialTrim; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=rate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
            ++filterStart;
            if (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= rate;
                ++dataStart;
            }
        }
        break;
    }
    return data;
}

template <class T>
ComplexVector<T> & ComplexFirFilter<T>::resample(ComplexVector<T> & data, int interpRate, int decimateRate, bool trimTails) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    int dataStart, filterStart;
    int interpLen, resampLen;
    std::vector< std::complex<T> > scratch;
    std::vector< std::complex<T> > *dataTmp;
    std::complex<T> *savedDataArray = (std::complex<T> *) VECTOR_TO_ARRAY(savedData);
    
    if (data.scratchBuf == NULL) {
        dataTmp = &scratch;
    }
    else {
        dataTmp = data.scratchBuf;
    }

    switch (filtOperation) {

    case STREAMING: {
        int numTaps = (this->size() + interpRate - 1) / interpRate;
        if (numSavedSamples >= numTaps) {
            // First call to interp, have too many "saved" (really just the initial zeros) samples
            numSavedSamples = numTaps - 1;
            phase = (numTaps - 1) * interpRate;
        }
        
        dataTmp->resize(numSavedSamples + data.size());
        for (int i=0; i<numSavedSamples; i++) {
            (*dataTmp)[i] = savedDataArray[i];
        }
        for (int i=0; i<data.size(); i++) {
            (*dataTmp)[i + numSavedSamples] = data[i];
        }
        
        interpLen = dataTmp->size() * interpRate;
        resampLen = (interpLen + decimateRate - 1) / decimateRate;
        data.resize(resampLen);
        bool keepGoing = true;
        for (resultIndex=0, dataStart=0, filterStart=phase; keepGoing; ++resultIndex) {
            data[resultIndex] = 0;
            for (dataIndex=dataStart, filterIndex=filterStart;
                 filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
            if (dataTmp->size() - dataStart == numSavedSamples) {
                keepGoing = false;
                phase = filterStart;
            }
        }
        data.resize(resultIndex);
        
        int i;
        for (i=0; dataStart<dataTmp->size(); i++, dataStart++) {
            savedDataArray[i] = (*dataTmp)[dataStart];
        }
        numSavedSamples = i;
        }
        break;

    case ONE_SHOT_RETURN_ALL_RESULTS:
        *dataTmp = data.vec;
        interpLen = data.size() * interpRate + this->size() - 1 - (interpRate - 1);
        resampLen = (interpLen + decimateRate - 1) / decimateRate;
        data.resize(resampLen);
        
        // Initial partial overlap
        for (resultIndex=0, dataStart=0, filterStart=0; resultIndex<((int)this->size()-1+decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        break;

    case ONE_SHOT_TRIM_TAILS:
        *dataTmp = data.vec;
        interpLen = data.size() * interpRate;
        resampLen = (interpLen + decimateRate - 1) / decimateRate;
        data.resize(resampLen);

        // Initial partial overlap
        int initialTrim = (this->size() - 1) / 2;
        for (resultIndex=0, dataStart=0, filterStart=initialTrim;
             resultIndex<((int)this->size()-1 - initialTrim + decimateRate-1)/decimateRate; resultIndex++) {
            data[resultIndex] = 0;
            for (dataIndex=0, filterIndex=filterStart; filterIndex>=0; dataIndex++, filterIndex-=interpRate) {
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
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
                data[resultIndex] += (*dataTmp)[dataIndex] * this->vec[filterIndex];
            }
            filterStart += decimateRate;
            while (filterStart >= (int)this->size()) {
                // Filter no longer overlaps with this data sample, so the first overlap sample is the next one.  We thus
                // increment the data index and decrement the filter index.
                filterStart -= interpRate;
                ++dataStart;
            }
        }
        break;
    }
    return data;
}


};


#endif
