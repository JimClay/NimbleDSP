#ifndef SMART_DSP_DSPBUFFER
#define SMART_DSP_DSPBUFFER


#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include "kiss_fft.h"
#include "kiss_fftr.h"


namespace SmartDsp {

const unsigned DEFAULT_BUF_LEN = 0;

#ifndef SMARTDSP_FLOAT_TYPE
#define SMARTDSP_FLOAT_TYPE    double
#endif

//#define VECTOR_TO_ARRAY(x)      (&x[0])
#define VECTOR_TO_ARRAY(x)      (&((x)[0]))

    
template <class T>
class DspBuffer {

protected:
    std::vector<T> scratchBuf;
    
    void initSize(unsigned size) {buf = std::vector<T>(size); scratchBuf = std::vector<T>(0);}
    template <class U>
    void initArray(U *array, unsigned arrayLen);
    
public:
    // Members
	std::vector<T> buf;
    
    // Constructors
    DspBuffer<T>(void) {initSize(DEFAULT_BUF_LEN);}
    DspBuffer<T>(unsigned size) {initSize(size);}
    template <typename U>
    DspBuffer<T>(std::vector<U> data) {initArray(VECTOR_TO_ARRAY(data), data.size());}
    template <typename U>
    DspBuffer<T>(U *data, unsigned dataLen) {initArray(data, dataLen);}
    
    DspBuffer<T>(const DspBuffer<T>& other) {buf = other.buf;}
    DspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    // Operators
    DspBuffer<T> & operator-();
    
    template <class U>
    DspBuffer<T> & operator+=(const DspBuffer<U> &rhs);
    DspBuffer<T> & operator+=(const T &rhs);
    template <class U>
    DspBuffer<T> & operator-=(const DspBuffer<U> &rhs);
    DspBuffer<T> & operator-=(const T &rhs);
    
    template <class U>
    DspBuffer<T> & operator*=(const DspBuffer<U> &rhs);
    DspBuffer<T> & operator*=(const T &rhs);
    template <class U>
    DspBuffer<T> & operator/=(const DspBuffer<U> &rhs);
    DspBuffer<T> & operator/=(const T &rhs);
    
    T& operator[](unsigned index) {return buf[index];};
    const T& operator[](unsigned index) const {return buf[index];};
    
    // Methods
    const unsigned size() const {return buf.size();};
    
    DspBuffer<T> & rotate(int numToShift);
    DspBuffer<T> & reverse();
    
    const int find(const T val) const;
    DspBuffer<T> & abs();
    DspBuffer<T> & exp();
    DspBuffer<T> & log();
    DspBuffer<T> & ln() {return log();}
    DspBuffer<T> & log10();
    
    DspBuffer<T> & resize(unsigned len, T val = (T) 0) {buf.resize(len, val); return *this;}
    DspBuffer<T> & pad(unsigned len, T val = (T) 0) {buf.resize(size()+len, val); return *this;}
    DspBuffer<T> & upsample(int rate, int phase = 0);
    DspBuffer<T> & downsample(int rate, int phase = 0);
	T sum() const;
	DspBuffer<T> & diff();
    DspBuffer<T> & diff(T & previousVal);
    
    template <class U>
    DspBuffer<T> & convolve(DspBuffer<U> & filter, bool trimTails = false, DspBuffer<T> *scratchBuf = NULL);
    template <class U>
    DspBuffer<T> & decimate(int rate, DspBuffer<U> & filter, bool trimTails = false, DspBuffer<T> *scratchBuf = NULL);
};


template <class T>
template <class U>
void DspBuffer<T>::initArray(U *array, unsigned arrayLen) {
    buf = std::vector<T>(arrayLen);
    for (unsigned i=0; i<arrayLen; i++) {
        buf[i] = (T) array[i];
    }
    scratchBuf = std::vector<T>(0);
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
    numToShift = size() - numToShift;
    while (numToShift < 0)
        numToShift += size();
    
    while (numToShift >= (int) size())
        numToShift -= size();
    
    if (numToShift == 0)
        return *this;

    std::rotate(buf.begin(), buf.begin()+numToShift, buf.end());
    return *this;
}

template <class T>
DspBuffer<T> & rotate(DspBuffer<T> & buffer, int numToShift) {
    return buffer.rotate(numToShift);
}

template <class T>
DspBuffer<T> & DspBuffer<T>::reverse() {
    std::reverse(buf.begin(), buf.end());
    return *this;
}

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

template <class T>
DspBuffer<T> & log(DspBuffer<T> & buffer) {
    return buffer.log();
}

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

template <class T>
DspBuffer<T> & log10(DspBuffer<T> & buffer) {
    return buffer.log10();
}

template <class T>
DspBuffer<T> & resize(DspBuffer<T> & buffer, int val) {
    return buffer.resize(val);
}

template <class T>
DspBuffer<T> & pad(DspBuffer<T> & buffer, int val) {
    return buffer.pad(val);
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

template <class T>
DspBuffer<T> & diff(DspBuffer<T> & buffer, T & previousVal) {
    return buffer.diff(previousVal);
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::convolve(DspBuffer<U> & filter, bool trimTails, DspBuffer<T> *scratchBuf) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    DspBuffer<T> scratch;
    DspBuffer<T> *data;
    
    if (scratchBuf == NULL) {
        data = &scratch;
    }
    else {
        data = scratchBuf;
    }
    *data = *this;
    
    if (trimTails) {
        // Initial partial overlap
        int initialTrim = (filter.size() - 1) / 2;
        for (resultIndex=0; resultIndex<(filter.size()-1) - initialTrim; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<data->size() - initialTrim; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex - ((filter.size()-1) - initialTrim), filterIndex=filter.size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex - ((filter.size()-1) - initialTrim), filterIndex=filter.size()-1;
                 dataIndex<data->size(); dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
    }
    else {
        this->resize(this->size() + filter.size() - 1);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<filter.size()-1; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex; filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<data->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex - (filter.size()-1), filterIndex=filter.size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex - (filter.size()-1), filterIndex=filter.size()-1;
                 dataIndex<data->size(); dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
    }
    return *this;
}
 
template <class T, class U>
inline DspBuffer<T> & convolve(DspBuffer<T> & data, DspBuffer<U> & filter, bool trimTails = false, DspBuffer<T> *scratchBuf = NULL) {
    return data.convolve(filter, trimTails, scratchBuf);
}

template <class T, class U>
inline DspBuffer<T> & conv(DspBuffer<T> & data, DspBuffer<U> & filter, bool trimTails = false, DspBuffer<T> *scratchBuf = NULL) {
    return data.convolve(filter, trimTails, scratchBuf);
}

template <class T>
template <class U>
DspBuffer<T> & DspBuffer<T>::decimate(int rate, DspBuffer<U> & filter, bool trimTails, DspBuffer<T> *scratchBuf) {
    int resultIndex;
    int filterIndex;
    int dataIndex;
    DspBuffer<T> scratch;
    DspBuffer<T> *data;
    
    if (scratchBuf == NULL) {
        data = &scratch;
    }
    else {
        data = scratchBuf;
    }
    *data = *this;
    
    if (trimTails) {
        this->resize((this->size() + rate - 1) / rate);
        
        // Initial partial overlap
        int initialTrim = (filter.size() - 1) / 2;
        for (resultIndex=0; resultIndex<((filter.size()-1) - initialTrim + rate - 1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=initialTrim + resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(data->size() - initialTrim + rate - 1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((filter.size()-1) - initialTrim), filterIndex=filter.size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - ((filter.size()-1) - initialTrim), filterIndex=filter.size()-1;
                 dataIndex<data->size(); dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
    }
    else {
        this->resize(((this->size() + filter.size() - 1) + (rate - 1)) / rate);
        
        // Initial partial overlap
        for (resultIndex=0; resultIndex<(filter.size()-1+rate-1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=0, filterIndex=resultIndex*rate; filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
        
        // Middle full overlap
        for (; resultIndex<(data->size()+rate-1)/rate; resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (filter.size()-1), filterIndex=filter.size()-1;
                 filterIndex>=0; dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }

        // Final partial overlap
        for (; resultIndex<this->size(); resultIndex++) {
            buf[resultIndex] = 0;
            for (dataIndex=resultIndex*rate - (filter.size()-1), filterIndex=filter.size()-1;
                 dataIndex<data->size(); dataIndex++, filterIndex--) {
                buf[resultIndex] += (*data)[dataIndex] * filter[filterIndex];
            }
        }
    }
    return *this;
}
 
template <class T, class U>
inline DspBuffer<T> & decimate(DspBuffer<T> & data, int rate, DspBuffer<U> & filter, bool trimTails = false, DspBuffer<T> *scratchBuf = NULL) {
    return data.decimate(rate, filter, trimTails, scratchBuf);
}

};

#endif
