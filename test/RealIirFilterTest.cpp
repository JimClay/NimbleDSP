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

#include "RealIirFilter.h"
#include <vector>
#include "gtest/gtest.h"

using namespace NimbleDSP;

extern bool FloatsEqual(double float1, double float2);

TEST(RealIirFilter, ConstructorSize) {
    RealIirFilter<double> filt(5);
    
    EXPECT_EQ(6, filt.numerator.size());
    EXPECT_EQ(6, filt.denominator.size());
}

TEST(RealIirFilter, ConstructorVector) {
    double den[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double num[] = {1, 2, 3};
    std::vector<double> denominator(den, den + sizeof(den) / sizeof(den[0]));
    std::vector<double> numerator(num, num + sizeof(num) / sizeof(num[0]));
    
    RealIirFilter<double> filt(numerator, denominator);
    
    EXPECT_EQ(8, filt.denominator.size());
    for (unsigned i=0; i<filt.denominator.size(); i++) {
        EXPECT_EQ(den[i], filt.denominator[i]);
    }
    
    EXPECT_EQ(3, filt.numerator.size());
    for (unsigned i=0; i<filt.numerator.size(); i++) {
        EXPECT_EQ(num[i], filt.numerator[i]);
    }
}

TEST(RealIirFilter, ConstructorArray) {
    double den[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double num[] = {1, 2, 3};
    
    NimbleDSP::RealIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    EXPECT_EQ(8, filt.denominator.size());
    for (unsigned i=0; i<filt.denominator.size(); i++) {
        EXPECT_EQ(den[i], filt.denominator[i]);
    }
    
    EXPECT_EQ(3, filt.numerator.size());
    for (unsigned i=0; i<filt.numerator.size(); i++) {
        EXPECT_EQ(num[i], filt.numerator[i]);
    }
}

TEST(RealIirFilter, Filter1) {
    double den[] = {1, .1};
    double num[] = {1, .001};
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double expectedData[] = {1.00000000, -0.09900000, -0.99010000, -1.90199000, -2.81180100, -3.72181990, -4.63181801, -5.54181820, -6.45181818};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    RealIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealIirFilter, Filter2) {
    double den[] = {1, .2, .1, .05, .02};
    double num[] = {1, .05, .04, .03, .01};
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double expectedData[] = {1.00000000, -0.15000000, -1.03000000, -1.84900000, -2.66970000, -3.48666000, -4.31264800, -5.13833940, -5.96334032};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    RealIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealIirFilter, Filter3) {
    double den[] = {1, .2, .1, .05, .02};
    double num[] = {1, .05, .04};
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double expectedData[] = {1.00000000, -0.15000000, -1.03000000, -1.87900000, -2.67370000, -3.45286000, -4.24750800, -5.04394740, -5.84034272};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    RealIirFilter<double> filt(num, sizeof(num) / sizeof(num[0]), den, sizeof(den) / sizeof(den[0]));
    
    filter(buf, filt);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}


