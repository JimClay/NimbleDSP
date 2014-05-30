#ifndef SMART_DSP_DSPBUFFER
#define SMART_DSP_DSPBUFFER


#include <vector>
#include <cassert>
#include <cmath>

namespace SmartDsp {

const int DEFAULT_BUF_LEN = 0;
enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};


#define VECTOR_TO_ARRAY(x)      (&x[0])


template <class T>
class DspBuffer {

private:
    std::vector<T> scratchBuf;
    
    void initSize(int size, DomainType dataDomain = TIME_DOMAIN) {buf = std::vector<T>(size); domain = dataDomain;
        scratchBuf = std::vector<T>(0);}
    template <class U>
    void initArray(U *array, int arrayLen, DomainType dataDomain = TIME_DOMAIN);
    
public:
    // Members
	std::vector<T> buf;
    DomainType domain;
    
    // Constructors
    DspBuffer<T>(void) {initSize(DEFAULT_BUF_LEN);}
    DspBuffer<T>(int size) {initSize(size);}
    template <typename U>
    DspBuffer<T>(std::vector<U> data, DomainType dataDomain = TIME_DOMAIN) {initArray(VECTOR_TO_ARRAY(data), data.size(), dataDomain);}
    template <typename U>
    DspBuffer<T>(U *data, int dataLen, DomainType dataDomain = TIME_DOMAIN) {initArray(data, dataLen, dataDomain);}
    
    DspBuffer<T>(const DspBuffer<T>& other) {buf = other.buf; domain = other.domain;}
    DspBuffer<T>& operator=(const DspBuffer<T>& rhs);
    
    // Operators
    DspBuffer<T> & operator++();
    DspBuffer<T> operator++(int);
    DspBuffer<T> & operator--();
    DspBuffer<T> operator--(int);
    
    DspBuffer<T> & operator-();
    
    DspBuffer<T> & operator+=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator+=(const T &rhs);
    DspBuffer<T> & operator-=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator-=(const T &rhs);
    
    DspBuffer<T> & operator*=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator*=(const T &rhs);
    DspBuffer<T> & operator/=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator/=(const T &rhs);
    DspBuffer<T> & operator%=(const DspBuffer<T> &rhs);
    DspBuffer<T> & operator%=(const T &rhs);
    
    T& operator[](int index) {return buf[index];};
    const T& operator[](int index) const {return buf[index];};
    
    // Methods
    const int size() const {return buf.size();};
    const T mean() const;
    const T var() const;
    const T stdDev() const;
    const T median();
    
    void rotate(int numToShift);
    void reverse();
    
    const T max(int *maxLoc = NULL) const;
    const T min(int *minLoc = NULL) const;
    const int find(int val) const;
};


template <class T>
template <class U>
void DspBuffer<T>::initArray(U *array, int arrayLen, DomainType dataDomain) {
    buf = std::vector<T>(arrayLen);
    for (int i=0; i<arrayLen; i++) {
        buf[i] = (T) array[i];
    }
    domain = dataDomain;
    scratchBuf = std::vector<T>(0);
}

template <class T>
DspBuffer<T>& DspBuffer<T>::operator=(const DspBuffer<T>& rhs)
{
    buf = rhs.buf;
    domain = rhs.domain;
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator++()
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] = buf[i] + 1;
    }
    return *this;
}

template <class T>
DspBuffer<T> DspBuffer<T>::operator++(int)
{
    DspBuffer<T> tmp(*this);
    operator++();
    return tmp;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator--()
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] = buf[i] - 1;
    }
    return *this;
}

template <class T>
DspBuffer<T> DspBuffer<T>::operator--(int)
{
    DspBuffer<T> tmp(*this);
    operator--();
    return tmp;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-()
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] = -buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator+=(const DspBuffer<T> &rhs)
{
    assert(size() == rhs.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] += rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator+=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] += rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator+(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
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
DspBuffer<T> & DspBuffer<T>::operator-=(const DspBuffer<T> &rhs)
{
    assert(size() == rhs.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] -= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator-=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] -= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator-(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
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
DspBuffer<T> & DspBuffer<T>::operator*=(const DspBuffer<T> &rhs)
{
    assert(size() == rhs.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] *= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator*=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] *= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator*(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
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
DspBuffer<T> & DspBuffer<T>::operator/=(const DspBuffer<T> &rhs)
{
    assert(size() == rhs.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] /= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator/=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] /= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator/(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
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
DspBuffer<T> & DspBuffer<T>::operator%=(const DspBuffer<T> &rhs)
{
    assert(size() == rhs.size());
    assert(domain == rhs.domain);
    for (int i=0; i<buf.size(); i++) {
        buf[i] %= rhs.buf[i];
    }
    return *this;
}

template <class T>
DspBuffer<T> & DspBuffer<T>::operator%=(const T &rhs)
{
    for (int i=0; i<buf.size(); i++) {
        buf[i] %= rhs;
    }
    return *this;
}

template <class T>
inline DspBuffer<T> operator%(DspBuffer<T> lhs, const DspBuffer<T>& rhs)
{
    assert(lhs.size() == rhs.size());
    lhs %= rhs;
    return lhs;
}

template <class T>
inline DspBuffer<T> operator%(DspBuffer<T> lhs, const T& rhs)
{
    lhs %= rhs;
    return lhs;
}

template <class T>
inline bool operator==(const DspBuffer<T>& lhs, const DspBuffer<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    
    for (int i=0; i<lhs.size(); i++) {
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
    for (int i=0; i<buf.size(); i++) {
        sum += buf[i];
    }
    return sum / buf.size();
}

template <class T>
const T DspBuffer<T>::var() const {
    assert(buf.size() > 1);
    T meanVal = mean();
    T sum = 0;
    for (int i=0; i<buf.size(); i++) {
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
        int topHalfIndex = size()/2;
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
const T DspBuffer<T>::max(int *maxLoc) const {
    assert(size() > 0);
    T maxVal = buf[0];
    int maxIndex = 0;
    
    for (int i=1; i<size(); i++) {
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
const T DspBuffer<T>::min(int *minLoc) const {
    assert(size() > 0);
    T minVal = buf[0];
    int minIndex = 0;
    
    for (int i=1; i<size(); i++) {
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
const int DspBuffer<T>::find(int val) const {
    for (int i=0; i<size(); i++) {
        if (buf[i] == val) {
            return i;
        }
    }
    return -1;
}

};

#endif
