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
 * @file ComplexIirFilter.h
 *
 * Definition of the template class ComplexIirFilter.
 */


#ifndef NimbleDSP_ComplexIirFilter_h
#define NimbleDSP_ComplexIirFilter_h

#include <vector>
#include "ComplexVector.h"


namespace NimbleDSP {

/**
 * \brief Class for complex IIR filters.
 */
template <class T>
class ComplexIirFilter {
 protected:
    std::vector< std::complex<T> > state;

    /** 
     * \brief Initializes numerator and denominator with the size and contents of "num" and "den".
     *
     * \param array Array to set vec equal to.
     * \param arrayLen Number of elements in array.
     */
    template <class U>
    void initArray(U *num, unsigned numLen, U *den, unsigned denLen);
    
 public:
    std::vector< std::complex<T> > numerator;
    std::vector< std::complex<T> > denominator;
    
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
    ComplexIirFilter<T>(unsigned order = 2) {numerator = std::vector< std::complex<T> >(order + 1);
            denominator = std::vector< std::complex<T> >(order + 1); state = std::vector< std::complex<T> >(order + 1);}
    
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
    ComplexIirFilter<T>(std::vector< std::complex<U> > & num, std::vector< std::complex<U> > & den) {
            initArray(VECTOR_TO_ARRAY(num), (unsigned) num.size(), VECTOR_TO_ARRAY(den), (unsigned) den.size());}
    
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
    ComplexIirFilter<T>(U *num, unsigned numLen, U *den, unsigned denLen) {initArray(num, numLen, den, denLen);}
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
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
    template <class U>
    ComplexVector<U> & filter(ComplexVector<U> & data);
    
};


template <class T>
template <class U>
void ComplexIirFilter<T>::initArray(U *num, unsigned numLen, U *den, unsigned denLen) {
    numerator = std::vector< std::complex<T> >(numLen);
    for (unsigned i=0; i<numLen; i++) {
        numerator[i] = (std::complex<T>) num[i];
    }
    
    denominator = std::vector< std::complex<T> >(denLen);
    for (unsigned i=0; i<denLen; i++) {
        denominator[i] = (std::complex<T>) den[i];
    }
    
    state = std::vector< std::complex<T> >(std::max(numLen, denLen));
}

template <class T>
template <class U>
ComplexVector<U> & ComplexIirFilter<T>::filter(ComplexVector<U> & data) {
    unsigned resultIndex, i;
    std::complex<U> newState0;
    
    for (resultIndex=0; resultIndex<data.size(); resultIndex++) {
        newState0 = data[resultIndex];
        
        // Update the state
        for (i=(unsigned) state.size()-1; i>=denominator.size(); i--) {
            state[i] = state[i - 1];
        }
        // Update the state and apply the feedback
        for (i=(unsigned) denominator.size()-1; i>0; i--) {
            state[i] = state[i - 1];
            newState0 -= denominator[i] * state[i];
        }
        state[0] = newState0;

        // Calculate the output
        data[resultIndex] = 0;
        for (i=0; i<numerator.size(); i++) {
            data[resultIndex] += numerator[i] * state[i];
        }
    }
    return data;
}

template <class T, class U>
ComplexVector<U> & filter(ComplexVector<U> & data, ComplexIirFilter<T> & filt) {
    return filt.filter(data);
}

};

#endif
