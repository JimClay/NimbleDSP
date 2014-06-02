#ifndef SMART_DSP_DSPBUFFER
#define SMART_DSP_DSPBUFFER


#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
//#include <complex>
#include "kiss_fft.h"
#include "kiss_fftr.h"


namespace SmartDsp {

const unsigned DEFAULT_BUF_LEN = 0;


#define VECTOR_TO_ARRAY(x)      (&x[0])


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
    void pow(const T exponent);
    
    T& operator[](unsigned index) {return buf[index];};
    const T& operator[](unsigned index) const {return buf[index];};
    
    // Methods
    const unsigned size() const {return buf.size();};
    const T mean() const;
    const T var() const;
    const T stdDev() const;
    const T median();
    
    void rotate(int numToShift);
    void reverse();
    
    const T max(unsigned *maxLoc = NULL) const;
    const T min(unsigned *minLoc = NULL) const;
    const int find(T val) const;
    void saturate(T val);
    void abs();
    
    //DspBuffer< std::complex<T> > fft(bool pad = false, bool scale = true);
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
const T DspBuffer<T>::mean() const {
    assert(buf.size() > 0);
    T sum = 0;
    for (unsigned i=0; i<buf.size(); i++) {
        sum += buf[i];
    }
    return sum / buf.size();
}

template <class T>
const T DspBuffer<T>::var() const {
    assert(buf.size() > 1);
    T meanVal = mean();
    T sum = 0;
    for (unsigned i=0; i<buf.size(); i++) {
        T varDiff = buf[i] - meanVal;
        sum += varDiff * varDiff;
    }
    return sum / (buf.size() - 1);
}

template <class T>
const T DspBuffer<T>::stdDev() const {
    return sqrt(var());
}

template <class T>
const T DspBuffer<T>::median() {
    assert(size() > 0);
    scratchBuf = buf;
    std::sort(scratchBuf.begin(), scratchBuf.end());
    if (size() & 1) {
        // Odd number of samples
        return scratchBuf[size()/2];
    }
    else {
        // Even number of samples.  Average the two in the middle.
        unsigned topHalfIndex = size()/2;
        return (scratchBuf[topHalfIndex] + scratchBuf[topHalfIndex-1]) / 2;
    }
}

template <class T>
void DspBuffer<T>::rotate(int numToShift) {
    numToShift = size() - numToShift;
    while (numToShift < 0)
        numToShift += size();
    
    while (numToShift >= size())
        numToShift -= size();
    
    if (numToShift == 0)
        return;

    std::rotate(buf.begin(), buf.begin()+numToShift, buf.end());
}

template <class T>
void DspBuffer<T>::reverse() {
    std::reverse(buf.begin(), buf.end());
}

template <class T>
const T DspBuffer<T>::max(unsigned *maxLoc) const {
    assert(size() > 0);
    T maxVal = buf[0];
    unsigned maxIndex = 0;
    
    for (unsigned i=1; i<size(); i++) {
        if (buf[i] > maxVal) {
            maxVal = buf[i];
            maxIndex = i;
        }
    }
    if (maxLoc != NULL) {
        *maxLoc = maxIndex;
    }
    return maxVal;
}

template <class T>
const T DspBuffer<T>::min(unsigned *minLoc) const {
    assert(size() > 0);
    T minVal = buf[0];
    unsigned minIndex = 0;
    
    for (unsigned i=1; i<size(); i++) {
        if (buf[i] < minVal) {
            minVal = buf[i];
            minIndex = i;
        }
    }
    if (minLoc != NULL) {
        *minLoc = minIndex;
    }
    return minVal;
}

template <class T>
const int DspBuffer<T>::find(T val) const {
    for (unsigned i=0; i<size(); i++) {
        if (buf[i] == val) {
            return (int) i;
        }
    }
    return -1;
}
    
template <class T>
void DspBuffer<T>::pow(const T exponent) {
    for (unsigned i=0; i<size(); i++) {
        buf[i] = std::pow(buf[i], exponent);
    }
}
   
template <class T>
void DspBuffer<T>::saturate(T val) {
    for (unsigned i=0; i<size(); i++) {
        if (buf[i] > val)
            buf[i] = val;
        else if (buf[i] < -val)
            buf[i] = -val;
    }
}
 
template <class T>
void DspBuffer<T>::abs() {
    for (unsigned i=0; i<size(); i++) {
        buf[i] = (T) std::abs(buf[i]);
    }
}

//template <class T>
//DspBuffer< std::complex<T> > DspBuffer<T>::fft(bool padForSpeed, bool scale)
//{
//    unsigned originalSize = size();
//    unsigned fftLen = originalSize;
//    
//    if (padForSpeed) {
//        fftLen = kiss_fftr_next_fast_size_real(originalSize);
//        if (fftLen > originalSize) {
//            buf.resize(fftLen, 0);
//        }
//    }
//    DspBuffer< std::complex<T> > fftResult(fftLen);
//    
//    if (size() & 1) {
//        // kissfft real FFT's (as opposed to complex) require even lengths.  If it isn't even
//        // then we'll have to do a complex FFT.
//        
////        kiss_fft_cfg fftConfig = kiss_fft_alloc(fftLen, 0, NULL, NULL);
////        kiss_fft(fftConfig, VECTOR_TO_ARRAY(buf), VECTOR_TO_ARRAY(fftResult));
////        kiss_fft_free(fftConfig);
//    }
//    else {
//        kiss_fftr_cfg fftConfig = kiss_fftr_alloc(fftLen, 0, NULL, NULL);
//        kiss_fftr(fftConfig, VECTOR_TO_ARRAY(buf), VECTOR_TO_ARRAY(fftResult));
//        kiss_fftr_free(fftConfig);
//    }
//    return fftResult;
//}

    
};

#endif
