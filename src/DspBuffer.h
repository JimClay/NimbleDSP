#ifndef SMART_DSP_DSPBUFFER
#define SMART_DSP_DSPBUFFER


#include <vector>

const int DEFAULT_BUF_LEN = 0;
enum DomainType {TIME_DOMAIN, FREQUENCY_DOMAIN};


#define VECTOR_TO_ARRAY(x)      (&x[0])


template <class T>
class DspBuffer {

private:
    void initSize(int size, DomainType dataDomain = TIME_DOMAIN) {buf = std::vector<T>(size); domain = dataDomain;}
    template <class U>
    void initArray(U *array, int arrayLen, DomainType dataDomain = TIME_DOMAIN);
    
public:
    // Members
	std::vector<T> buf;
    DomainType domain;
    
    // Constructors
    DspBuffer<T>(int size = DEFAULT_BUF_LEN) {initSize(size);}
    template <typename U>
    DspBuffer<T>(std::vector<U> data, DomainType dataDomain = TIME_DOMAIN) {initArray(VECTOR_TO_ARRAY(data), data.size(), dataDomain);}
    template <typename U>
    DspBuffer<T>(U *data, int dataLen, DomainType dataDomain = TIME_DOMAIN) {initArray(data, dataLen, dataDomain);}
    
    DspBuffer<T>(DspBuffer<T>& other) {buf = other.buf; domain = other.domain;}
    
    // Operators
    DspBuffer<T> & operator++();
    DspBuffer<T> operator++(int dummy);
    
};


template <class T>
template <class U>
void DspBuffer<T>::initArray(U *array, int arrayLen, DomainType dataDomain) {
    buf = std::vector<T>(arrayLen);
    for (int i=0; i<arrayLen; i++) {
        buf[i] = (T) array[i];
    }
    domain = dataDomain;
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
DspBuffer<T> DspBuffer<T>::operator++(int dummy)
{
    DspBuffer<T> tmp(*this);
    operator++();
    return tmp;
}



#endif
