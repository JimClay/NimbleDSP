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

#include "ComplexIirFilter.h"
#include <vector>
#include "gtest/gtest.h"

using namespace NimbleDSP;

extern bool ComplexEqual(std::complex<double> float1, std::complex<double> float2);

TEST(ComplexIirFilter, ConstructorSize) {
    ComplexIirFilter<double> filt(5);
    
    EXPECT_EQ(6, filt.numerator.size());
    EXPECT_EQ(6, filt.denominator.size());
}

TEST(ComplexIirFilter, ConstructorVector) {
    std::complex<double> den[] = {1, 2, 3, 4, 5, 6, 7, 8};
    std::complex<double> num[] = {1, 2, 3};
    std::vector< std::complex<double> > denominator(den, den + sizeof(den) / sizeof(den[0]));
    std::vector< std::complex<double> > numerator(num, num + sizeof(num) / sizeof(num[0]));
    
    ComplexIirFilter<double> filt(numerator, denominator);
    
    EXPECT_EQ(8, filt.denominator.size());
    for (unsigned i=0; i<filt.denominator.size(); i++) {
        EXPECT_EQ(den[i], filt.denominator[i]);
    }
    
    EXPECT_EQ(3, filt.numerator.size());
    for (unsigned i=0; i<filt.numerator.size(); i++) {
        EXPECT_EQ(num[i], filt.numerator[i]);
    }
}

TEST(ComplexIirFilter, ConstructorArray) {
    std::complex<double> den[] = {1, 2, 3, 4, 5, 6, 7, 8};
    std::complex<double> num[] = {1, 2, 3};
    
    NimbleDSP::ComplexIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    EXPECT_EQ(8, filt.denominator.size());
    for (unsigned i=0; i<filt.denominator.size(); i++) {
        EXPECT_EQ(den[i], filt.denominator[i]);
    }
    
    EXPECT_EQ(3, filt.numerator.size());
    for (unsigned i=0; i<filt.numerator.size(); i++) {
        EXPECT_EQ(num[i], filt.numerator[i]);
    }
}

TEST(ComplexIirFilter, Filter1) {
    std::complex<double> den[] = {std::complex<double>(1, 0), std::complex<double>(.1, .05)};
    std::complex<double> num[] = {std::complex<double>(1, 0), std::complex<double>(.001, .001)};
    std::complex<double> inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    std::complex<double> expectedData[] = {std::complex<double>(1.00000000, 0.00000000), std::complex<double>(-0.09900000, -0.04900000), std::complex<double>(-0.99255000, 0.00985000), std::complex<double>(-1.90125250, 0.04764250), std::complex<double>(-2.80949262, 0.08829838), std::complex<double>(-3.71763582, 0.12864479), std::complex<double>(-4.62580418, 0.16901731), std::complex<double>(-5.53396872, 0.20938848), std::complex<double>(-6.44213370, 0.24975959)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    ComplexIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexIirFilter, Filter2) {
    std::complex<double> den[] = {1, .2, .1, .05, .02};
    std::complex<double> num[] = {1, .05, .04, .03, .01};
    std::complex<double> inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    std::complex<double> expectedData[] = {1.00000000, -0.15000000, -1.03000000, -1.84900000, -2.66970000, -3.48666000, -4.31264800, -5.13833940, -5.96334032};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    ComplexIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexIirFilter, Filter3) {
    std::complex<double> den[] = {1, .2, .1, .05, .02};
    std::complex<double> num[] = {1, .05, .04};
    std::complex<double> inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    std::complex<double> expectedData[] = {1.00000000, -0.15000000, -1.03000000, -1.87900000, -2.67370000, -3.45286000, -4.24750800, -5.04394740, -5.84034272};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    ComplexIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexIirFilter, Filter4) {
    std::complex<double> den[] = {1, .2};
    std::complex<double> num[] = {1, .05, .04, .03, .01};
    std::complex<double> inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    std::complex<double> expectedData[] = {1.00000000, -0.15000000, -0.93000000, -1.83400000, -2.76320000, -3.70736000, -4.64852800, -5.59029440, -6.53194112};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    ComplexIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}


