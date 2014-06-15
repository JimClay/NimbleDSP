//
//  RealFirFilter.h
//  SlickDsp
//
//  Created by Jim Clay on 6/1/14.
//
//

#ifndef SlickDsp_RealFirFilter_h
#define SlickDsp_RealFirFilter_h

#include <math.h>
#include "RealDspBuffer.h"


namespace SlickDsp {


template <class T>
class RealFirFilter : public RealDspBuffer<T> {
 protected:
    std::vector<T> state;
    
 public:
    // Constructors
    RealFirFilter<T>(void) : RealDspBuffer<T>() {state = std::vector<T>(0);}
    RealFirFilter<T>(unsigned size) : RealDspBuffer<T>(size) {state = std::vector<T>(size-1);}
    template <typename U>
    RealFirFilter<T>(std::vector<U> data) : RealDspBuffer<T>(data) {state = std::vector<T>(data.size()-1);}
    template <typename U>
    RealFirFilter<T>(U *data, unsigned dataLen) : RealDspBuffer<T>(data, dataLen) {state = std::vector<T>(dataLen-1);}
    
    RealFirFilter<T>(const RealFirFilter<T>& other) {this->buf = other.buf; state = other.state;}
    RealFirFilter<T>& operator=(const DspBuffer<T>& rhs);
    
    
};


template <class T>
RealFirFilter<T>& RealFirFilter<T>::operator=(const DspBuffer<T>& rhs)
{
    this->buf = rhs.buf;
    state = rhs.state;
    return *this;
}

};


#endif
