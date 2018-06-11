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

#include "RealFirFilter.h"
#include "gtest/gtest.h"

using namespace NimbleDSP;

extern bool FloatsEqual(double float1, double float2);

TEST(RealFirFilter, ConvStream1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double inputData2[] = {-8, -9, -10, -11, -12, -13, -14};
    double inputData3[] = {-15, -16, -17, -18, -19, -20, -21, -22, -23, -24, -25, -26, -27, -28};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 2, 0, -5, -20, -35, -50, -65};
    double expectedData2[] = {-80, -95, -110, -125, -140, -155, -170};
    double expectedData3[] = {-185, -200, -215, -230, -245, -260, -275, -290, -305, -320, -335, -350, -365, -380};
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData3, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData3[i], buf[i]);
    }
}


TEST(RealFirFilter, ConvOneShot) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double inputData2[] = {-3, -4, -5, -6, -7, -8, -9};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 2, 0, -5, -20, -35, -50, -65, -72, -70, -58, -35};
    double expectedData2[] = {-3, -10, -22, -40, -65, -80, -95, -100, -94, -76, -45};
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
}

TEST(RealFirFilter, ConvOneShotTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double inputData2[] = {-3, -4, -5, -6, -7, -8, -9};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {2, 0, -5, -20, -35, -50, -65, -72, -70};
    double expectedData2[] = {-22, -40, -65, -80, -95, -100, -94};
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
}

TEST(RealFirFilter, ConvComplexOneShot) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 7), std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80), std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-72, 114), std::complex<double>(-70, 106), std::complex<double>(-58, 85), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, ConvComplexOneShotTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80), std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-72, 114), std::complex<double>(-70, 106)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    conv(buf, filter);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, ConvComplexStream1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8)};
    std::complex<double> inputData2[] = {std::complex<double>(-6, 9), std::complex<double>(-7, 10), std::complex<double>(-8, 11), std::complex<double>(-9, 12)};
    std::complex<double> inputData3[] = {std::complex<double>(-10, 13), std::complex<double>(-11, 14), std::complex<double>(-12, 15), std::complex<double>(-13, 16), std::complex<double>(-14, 17), std::complex<double>(-15, 18), std::complex<double>(-16, 19), std::complex<double>(-17, 20), std::complex<double>(-18, 21), std::complex<double>(-19, 22), std::complex<double>(-20, 23), std::complex<double>(-21, 24), std::complex<double>(-22, 25), std::complex<double>(-23, 26)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 7), std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80)};
    std::complex<double> expectedData2[] = {std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-80, 125), std::complex<double>(-95, 140)};
    std::complex<double> expectedData3[] = {std::complex<double>(-110, 155), std::complex<double>(-125, 170), std::complex<double>(-140, 185), std::complex<double>(-155, 200), std::complex<double>(-170, 215), std::complex<double>(-185, 230), std::complex<double>(-200, 245), std::complex<double>(-215, 260), std::complex<double>(-230, 275), std::complex<double>(-245, 290), std::complex<double>(-260, 305), std::complex<double>(-275, 320), std::complex<double>(-290, 335), std::complex<double>(-305, 350)};
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    conv(buf, filter);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData2, numElements);
    input = buf;
    conv(buf, filter);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData3, numElements);
    input = buf;
    conv(buf, filter);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData3[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateComplexOneShot) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 16), std::complex<double>(-5, 50), std::complex<double>(-35, 80), std::complex<double>(-65, 110), std::complex<double>(-70, 106), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 2;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() + rate - 1)/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateComplexOneShotTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(2, 16), std::complex<double>(-5, 50), std::complex<double>(-35, 80), std::complex<double>(-65, 110), std::complex<double>(-70, 106)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 2;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + rate - 1)/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateComplexStream1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8)};
    std::complex<double> inputData2[] = {std::complex<double>(-6, 9), std::complex<double>(-7, 10), std::complex<double>(-8, 11), std::complex<double>(-9, 12)};
    std::complex<double> inputData3[] = {std::complex<double>(-10, 13), std::complex<double>(-11, 14), std::complex<double>(-12, 15), std::complex<double>(-13, 16), std::complex<double>(-14, 17), std::complex<double>(-15, 18), std::complex<double>(-16, 19), std::complex<double>(-17, 20), std::complex<double>(-18, 21), std::complex<double>(-19, 22), std::complex<double>(-20, 23), std::complex<double>(-21, 24), std::complex<double>(-22, 25), std::complex<double>(-23, 26)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(0, 30), std::complex<double>(-35, 80)};
    std::complex<double> expectedData2[] = {std::complex<double>(-80, 125)};
    std::complex<double> expectedData3[] = {std::complex<double>(-125, 170), std::complex<double>(-170, 215), std::complex<double>(-215, 260), std::complex<double>(-260, 305), std::complex<double>(-305, 350)};
    int rate = 3;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(3, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData2, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData3, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(5, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData3[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateOneShot) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, -5, -35, -65, -70, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int rate = 2;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() + rate - 1)/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateOneShotTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {2, -5, -35, -65, -70};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int rate = 2;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + rate - 1)/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateStream1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5};
    double inputData2[] = {-6, -7, -8, -9};
    double inputData3[] = {-10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20, -21, -22, -23};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 0, -35};
    double expectedData2[] = {-80};
    double expectedData3[] = {-125, -170, -215, -260, -305};
    int rate = 3;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(3, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData2, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData3, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(5, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData3[i], buf[i]);
    }
}

TEST(VectorFilter, InterpNoTrim1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 3, 4, 5, 0, -1, -2, -3, -6, -9, -6, -11, -16, -9, -16, -23, -12, -21, -30, -15, -26, -37, -18, -31, -44, -21, -28, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::RealVector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int rate = 3;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpTrim1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {3, 4, 5, 0, -1, -2, -3, -6, -9, -6, -11, -16, -9, -16, -23, -12, -21, -30, -15, -26, -37, -18, -31, -44, -21, -28, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::RealVector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int rate = 3;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, InterpStream1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5};
    double inputData2[] = {-6};
    double inputData3[] = {-7, -8, -9, -10, -11, -12, -13, -14, -15, -16};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 3, 4, 5, 0, -1, -2, -3, -6, -9, -6, -11, -16, -9, -16, -23, -12, -21, -30, -15, -26, -37, -18, -31, -44, -21, -36, -51, -24, -41, -58, -27, -46, -65, -30, -51, -72, -33, -56, -79, -36, -61, -86, -39, -66, -93, -42, -71, -100, -45, -76, -107, -48, -64, -80};
    int rate = 3;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    int numResults = 0;
    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    interp(buf, rate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    interp(buf, rate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData3, numElements);
    interp(buf, rate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    EXPECT_LT(18*rate - (filter.size() - 1), numResults);
}

TEST(RealFirFilter, InterpComplex1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 4), std::complex<double>(3, 6), std::complex<double>(4, 11), std::complex<double>(5, 16), std::complex<double>(0, 9), std::complex<double>(-1, 16), std::complex<double>(-2, 23), std::complex<double>(-3, 12), std::complex<double>(-6, 21), std::complex<double>(-9, 30), std::complex<double>(-6, 15), std::complex<double>(-11, 26), std::complex<double>(-16, 37), std::complex<double>(-9, 18), std::complex<double>(-16, 31), std::complex<double>(-23, 44), std::complex<double>(-12, 21), std::complex<double>(-21, 36), std::complex<double>(-30, 51), std::complex<double>(-15, 24), std::complex<double>(-26, 41), std::complex<double>(-37, 58), std::complex<double>(-18, 27), std::complex<double>(-31, 46), std::complex<double>(-44, 65), std::complex<double>(-21, 30), std::complex<double>(-28, 40), std::complex<double>(-35, 50), std::complex<double>(0, 0), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 3;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, InterpComplexTrim1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(3, 6), std::complex<double>(4, 11), std::complex<double>(5, 16), std::complex<double>(0, 9), std::complex<double>(-1, 16), std::complex<double>(-2, 23), std::complex<double>(-3, 12), std::complex<double>(-6, 21), std::complex<double>(-9, 30), std::complex<double>(-6, 15), std::complex<double>(-11, 26), std::complex<double>(-16, 37), std::complex<double>(-9, 18), std::complex<double>(-16, 31), std::complex<double>(-23, 44), std::complex<double>(-12, 21), std::complex<double>(-21, 36), std::complex<double>(-30, 51), std::complex<double>(-15, 24), std::complex<double>(-26, 41), std::complex<double>(-37, 58), std::complex<double>(-18, 27), std::complex<double>(-31, 46), std::complex<double>(-44, 65), std::complex<double>(-21, 30), std::complex<double>(-28, 40), std::complex<double>(-35, 50), std::complex<double>(0, 0), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 3;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, InterpComplexStream1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8)};
    std::complex<double> inputData2[] = {std::complex<double>(-6, 9)};
    std::complex<double> inputData3[] = {std::complex<double>(-7, 10), std::complex<double>(-8, 11), std::complex<double>(-9, 12), std::complex<double>(-10, 13), std::complex<double>(-11, 14), std::complex<double>(-12, 15), std::complex<double>(-13, 16), std::complex<double>(-14, 17), std::complex<double>(-15, 18), std::complex<double>(-16, 19)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 4), std::complex<double>(3, 6), std::complex<double>(4, 8), std::complex<double>(5, 13), std::complex<double>(0, 6), std::complex<double>(0, 9), std::complex<double>(0, 12), std::complex<double>(-1, 19), std::complex<double>(-2, 8), std::complex<double>(-3, 12), std::complex<double>(-4, 16), std::complex<double>(-7, 25), std::complex<double>(-4, 10), std::complex<double>(-6, 15), std::complex<double>(-8, 20), std::complex<double>(-13, 31), std::complex<double>(-6, 12), std::complex<double>(-9, 18), std::complex<double>(-12, 24), std::complex<double>(-19, 37), std::complex<double>(-8, 14), std::complex<double>(-12, 21), std::complex<double>(-16, 28), std::complex<double>(-25, 43), std::complex<double>(-10, 16), std::complex<double>(-15, 24), std::complex<double>(-20, 32), std::complex<double>(-31, 49), std::complex<double>(-12, 18), std::complex<double>(-18, 27), std::complex<double>(-24, 36), std::complex<double>(-37, 55), std::complex<double>(-14, 20), std::complex<double>(-21, 30), std::complex<double>(-28, 40), std::complex<double>(-43, 61), std::complex<double>(-16, 22), std::complex<double>(-24, 33), std::complex<double>(-32, 44), std::complex<double>(-49, 67), std::complex<double>(-18, 24), std::complex<double>(-27, 36), std::complex<double>(-36, 48), std::complex<double>(-55, 73), std::complex<double>(-20, 26), std::complex<double>(-30, 39), std::complex<double>(-40, 52), std::complex<double>(-61, 79), std::complex<double>(-22, 28), std::complex<double>(-33, 42), std::complex<double>(-44, 56), std::complex<double>(-67, 85), std::complex<double>(-24, 30), std::complex<double>(-36, 45), std::complex<double>(-48, 60), std::complex<double>(-73, 91), std::complex<double>(-26, 32), std::complex<double>(-39, 48), std::complex<double>(-52, 64), std::complex<double>(-79, 97), std::complex<double>(-28, 34), std::complex<double>(-42, 51), std::complex<double>(-56, 68), std::complex<double>(-85, 103), std::complex<double>(-30, 36), std::complex<double>(-45, 54), std::complex<double>(-60, 72), std::complex<double>(-91, 109), std::complex<double>(-32, 38), std::complex<double>(-48, 57), std::complex<double>(-64, 76), std::complex<double>(-80, 95)};
    int rate = 4;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    int numResults = 0;
    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    interp(buf, rate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData2, numElements);
    interp(buf, rate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData3, numElements);
    interp(buf, rate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    EXPECT_LE(18*rate - (filter.size() - 1), numResults);
}

TEST(RealFirFilter, Resample1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 3, 5, -1, -3, -9, -11, -9, -23, -21, -15, -37, -31, -21, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::RealVector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, ResampleTrim1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {3, 5, -1, -3, -9, -11, -9, -23, -21, -15, -37, -31, -21, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, ResampleStream1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5};
    double inputData2[] = {-6};
    double inputData3[] = {-7, -8, -9, -10, -11, -12, -13, -14, -15, -16};
    double filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 3, 5, -1, -3, -9, -11, -9, -23, -21, -15, -37, -31, -21, -51, -41, -27, -65, -51, -33, -79, -61, -39, -93, -71, -45, -107, -64};
    int interpRate = 3;
    int decimateRate = 2;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    int numResults = 0;
    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData3, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    EXPECT_LE(18*interpRate / decimateRate, numResults);
}

TEST(RealFirFilter, ResampleStream2) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5};
    double inputData2[] = {-6};
    double inputData3[] = {-7, -8, -9, -10, -11, -12, -13, -14, -15, -16};
    double filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    double expectedData[] = {1, 5, 9, 13, 17, 18, 18, -15, -27, -42, -66, -63, -99, -83, -126, -174, -147, -207, -162, -234, -171, -255, -183, -270, -366, -279, -387, -282, -402, -279, -411, -283, -414, -558, -411, -567, -402, -570, -387, -567, -383, -507, -631, -320, -384};
    int interpRate = 9;
    int decimateRate = 4;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    int numResults = 0;
    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData3, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    EXPECT_LE(18*interpRate / decimateRate, numResults);
}

TEST(RealFirFilter, ResampleComplex1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10), std::complex<double>(-8, 11), std::complex<double>(-9, 12), std::complex<double>(-10, 13), std::complex<double>(-11, 14), std::complex<double>(-12, 15), std::complex<double>(-13, 16), std::complex<double>(-14, 17), std::complex<double>(-15, 18), std::complex<double>(-16, 19), std::complex<double>(-17, 20), std::complex<double>(-18, 21), std::complex<double>(-19, 22), std::complex<double>(-20, 23), std::complex<double>(-21, 24), std::complex<double>(-22, 25), std::complex<double>(-23, 26), std::complex<double>(-24, 27), std::complex<double>(-25, 28)};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(6, 12), std::complex<double>(11, 37), std::complex<double>(-4, 46), std::complex<double>(-15, 51), std::complex<double>(-36, 108), std::complex<double>(-51, 114), std::complex<double>(-60, 114), std::complex<double>(-69, 117), std::complex<double>(-74, 116), std::complex<double>(-75, 111), std::complex<double>(-156, 228), std::complex<double>(-156, 219), std::complex<double>(-150, 204), std::complex<double>(-149, 197), std::complex<double>(-144, 186), std::complex<double>(-135, 171), std::complex<double>(-276, 348), std::complex<double>(-261, 324), std::complex<double>(-240, 294), std::complex<double>(-229, 277), std::complex<double>(-214, 256), std::complex<double>(-195, 231), std::complex<double>(-396, 468), std::complex<double>(-366, 429), std::complex<double>(-330, 384), std::complex<double>(-309, 357), std::complex<double>(-284, 326), std::complex<double>(-255, 291), std::complex<double>(-516, 588), std::complex<double>(-471, 534), std::complex<double>(-420, 474), std::complex<double>(-389, 437), std::complex<double>(-250, 280)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 6;
    int decimateRate = 5;
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, ResampleComplexTrim1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10), std::complex<double>(-8, 11), std::complex<double>(-9, 12), std::complex<double>(-10, 13), std::complex<double>(-11, 14), std::complex<double>(-12, 15), std::complex<double>(-13, 16), std::complex<double>(-14, 17), std::complex<double>(-15, 18), std::complex<double>(-16, 19), std::complex<double>(-17, 20), std::complex<double>(-18, 21), std::complex<double>(-19, 22), std::complex<double>(-20, 23), std::complex<double>(-21, 24), std::complex<double>(-22, 25), std::complex<double>(-23, 26), std::complex<double>(-24, 27), std::complex<double>(-25, 28)};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    std::complex<double> expectedData[] = {std::complex<double>(7, 14), std::complex<double>(10, 20), std::complex<double>(13, 32), std::complex<double>(0, 15), std::complex<double>(0, 24), std::complex<double>(0, 33), std::complex<double>(-3, 54), std::complex<double>(-6, 24), std::complex<double>(-9, 36), std::complex<double>(-14, 53), std::complex<double>(-8, 20), std::complex<double>(-14, 35), std::complex<double>(-20, 50), std::complex<double>(-32, 77), std::complex<double>(-15, 30), std::complex<double>(-24, 48), std::complex<double>(-33, 66), std::complex<double>(-54, 105), std::complex<double>(-24, 42), std::complex<double>(-36, 63), std::complex<double>(-53, 92), std::complex<double>(-20, 32), std::complex<double>(-35, 56), std::complex<double>(-50, 80), std::complex<double>(-77, 122), std::complex<double>(-30, 45), std::complex<double>(-48, 72), std::complex<double>(-66, 99), std::complex<double>(-105, 156), std::complex<double>(-42, 60), std::complex<double>(-63, 90), std::complex<double>(-92, 131), std::complex<double>(-32, 44), std::complex<double>(-56, 77), std::complex<double>(-80, 110), std::complex<double>(-122, 167), std::complex<double>(-45, 60), std::complex<double>(-72, 96), std::complex<double>(-99, 132), std::complex<double>(-156, 207), std::complex<double>(-60, 78), std::complex<double>(-90, 117), std::complex<double>(-131, 170), std::complex<double>(-44, 56), std::complex<double>(-77, 98), std::complex<double>(-110, 140), std::complex<double>(-167, 212), std::complex<double>(-60, 75), std::complex<double>(-96, 120), std::complex<double>(-132, 165), std::complex<double>(-207, 258), std::complex<double>(-78, 96), std::complex<double>(-117, 144), std::complex<double>(-170, 209), std::complex<double>(-56, 68), std::complex<double>(-98, 119), std::complex<double>(-140, 170), std::complex<double>(-212, 257), std::complex<double>(-75, 90), std::complex<double>(-120, 144), std::complex<double>(-165, 198), std::complex<double>(-258, 309), std::complex<double>(-96, 114), std::complex<double>(-144, 171), std::complex<double>(-209, 248), std::complex<double>(-68, 80), std::complex<double>(-119, 140), std::complex<double>(-170, 200), std::complex<double>(-257, 302), std::complex<double>(-90, 105), std::complex<double>(-144, 168), std::complex<double>(-198, 231), std::complex<double>(-309, 360), std::complex<double>(-114, 132), std::complex<double>(-171, 198), std::complex<double>(-248, 287), std::complex<double>(-80, 92), std::complex<double>(-140, 161), std::complex<double>(-200, 230), std::complex<double>(-302, 347), std::complex<double>(-105, 120), std::complex<double>(-168, 192), std::complex<double>(-231, 264), std::complex<double>(-360, 411), std::complex<double>(-132, 150), std::complex<double>(-198, 225), std::complex<double>(-287, 326), std::complex<double>(-92, 104), std::complex<double>(-161, 182), std::complex<double>(-230, 260), std::complex<double>(-347, 392), std::complex<double>(-120, 135), std::complex<double>(-192, 216), std::complex<double>(-264, 297), std::complex<double>(-411, 462), std::complex<double>(-150, 168), std::complex<double>(-225, 252), std::complex<double>(-300, 336), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 11;
    int decimateRate = 3;
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFirFilter, ResampleComplexStream1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8)};
    std::complex<double> inputData2[] = {std::complex<double>(-6, 9)};
    std::complex<double> inputData3[] = {std::complex<double>(-7, 10)};
    std::complex<double> inputData4[] = {std::complex<double>(-8, 11)};
    std::complex<double> inputData5[] = {std::complex<double>(-9, 12)};
    std::complex<double> inputData6[] = {std::complex<double>(-10, 13)};
    std::complex<double> inputData7[] = {std::complex<double>(-11, 14), std::complex<double>(-12, 15), std::complex<double>(-13, 16), std::complex<double>(-14, 17), std::complex<double>(-15, 18), std::complex<double>(-16, 19), std::complex<double>(-17, 20), std::complex<double>(-18, 21), std::complex<double>(-19, 22), std::complex<double>(-20, 23), std::complex<double>(-21, 24), std::complex<double>(-22, 25), std::complex<double>(-23, 26)};
    std::complex<double> inputData8[] = {std::complex<double>(-24, 27), std::complex<double>(-25, 28), std::complex<double>(-26, 29), std::complex<double>(-27, 30), std::complex<double>(-28, 31), std::complex<double>(-29, 32), std::complex<double>(-30, 33), std::complex<double>(-31, 34), std::complex<double>(-32, 35), std::complex<double>(-33, 36), std::complex<double>(-34, 37), std::complex<double>(-35, 38)};
    double filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(6, 12), std::complex<double>(11, 22), std::complex<double>(0, 15), std::complex<double>(0, 30), std::complex<double>(-4, 16), std::complex<double>(-9, 36), std::complex<double>(-20, 71), std::complex<double>(-16, 40), std::complex<double>(-32, 77), std::complex<double>(-21, 42), std::complex<double>(-40, 79), std::complex<double>(-24, 42), std::complex<double>(-44, 77), std::complex<double>(-25, 40), std::complex<double>(-50, 80), std::complex<double>(-24, 36), std::complex<double>(-54, 81), std::complex<double>(-105, 156), std::complex<double>(-56, 80), std::complex<double>(-107, 152), std::complex<double>(-56, 77), std::complex<double>(-105, 144), std::complex<double>(-54, 72), std::complex<double>(-99, 132), std::complex<double>(-50, 65), std::complex<double>(-100, 130), std::complex<double>(-44, 56), std::complex<double>(-99, 126), std::complex<double>(-190, 241), std::complex<double>(-96, 120), std::complex<double>(-182, 227), std::complex<double>(-91, 112), std::complex<double>(-170, 209), std::complex<double>(-84, 102), std::complex<double>(-154, 187), std::complex<double>(-75, 90), std::complex<double>(-150, 180), std::complex<double>(-64, 76), std::complex<double>(-144, 171), std::complex<double>(-275, 326), std::complex<double>(-136, 160), std::complex<double>(-257, 302), std::complex<double>(-126, 147), std::complex<double>(-235, 274), std::complex<double>(-114, 132), std::complex<double>(-209, 242), std::complex<double>(-100, 115), std::complex<double>(-200, 230), std::complex<double>(-84, 96), std::complex<double>(-189, 216), std::complex<double>(-360, 411), std::complex<double>(-176, 200), std::complex<double>(-332, 377), std::complex<double>(-161, 182), std::complex<double>(-300, 339), std::complex<double>(-144, 162), std::complex<double>(-264, 297), std::complex<double>(-125, 140), std::complex<double>(-250, 280), std::complex<double>(-104, 116), std::complex<double>(-234, 261), std::complex<double>(-445, 496), std::complex<double>(-216, 240), std::complex<double>(-407, 452), std::complex<double>(-196, 217), std::complex<double>(-365, 404), std::complex<double>(-174, 192), std::complex<double>(-319, 352), std::complex<double>(-150, 165), std::complex<double>(-300, 330), std::complex<double>(-124, 136), std::complex<double>(-279, 306), std::complex<double>(-530, 581), std::complex<double>(-256, 280), std::complex<double>(-482, 527), std::complex<double>(-231, 252), std::complex<double>(-430, 469), std::complex<double>(-204, 222), std::complex<double>(-374, 407), std::complex<double>(-175, 190), std::complex<double>(-350, 380)};
    int interpRate = 11;
    int decimateRate = 5;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    int numResults = 0;
    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData2, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData3, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData4)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData4, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData5)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData5, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData6)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData6, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData7)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData7, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData8)/sizeof(inputData[0]);
	buf = NimbleDSP::ComplexVector<double>(inputData8, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    EXPECT_LT((37*interpRate - (filter.size()-1)) / decimateRate, numResults);
}

TEST(RealFirFilter, ResampleComplexStream2) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5};
    double inputData2[] = {-6};
    double inputData3[] = {-7, -8, -9, -10, -11, -12, -13, -14, -15, -16};
    double filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    double expectedData[] = {1, 5, 9, 13, 17, 18, 18, -15, -27, -42, -66, -63, -99, -83, -126, -174, -147, -207, -162, -234, -171, -255, -183, -270, -366, -279, -387, -282, -402, -279, -411, -283, -414, -558, -411, -567, -402, -570, -387, -567, -383, -507, -631, -320, -384};
    int interpRate = 9;
    int decimateRate = 4;
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);

    int numResults = 0;
    numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = NimbleDSP::RealVector<double>(inputData3, numElements);
    resample(buf, interpRate, decimateRate, filter);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i + numResults], buf[i]);
    }
    numResults += buf.size();
    EXPECT_LE(18*interpRate / decimateRate, numResults);
}

TEST(RealFirFilter, ParksMcClellan) {
    double expectedData[] = {-0.00000274,0.00000426,0.00000862,-0.00000356,-0.00001809,-0.00000045,0.00003270,0.00001405,-0.00004941,-0.00004244,0.00006228,0.00009027,-0.00006069,-0.00015870,0.00002984,0.00024233,0.00004740,-0.00032622,-0.00018662,0.00038398,0.00039623,-0.00037813,-0.00067058,0.00026359,0.00098324,0.00000491,-0.00128217,-0.00046184,0.00148876,0.00111730,-0.00150250,-0.00194299,0.00121252,0.00286056,-0.00051574,-0.00373546,-0.00065955,0.00437930,0.00232772,-0.00456252,-0.00442124,0.00403776,0.00677193,-0.00257219,-0.00910186,-0.00001488,0.01102582,0.00381468,-0.01206450,-0.00879804,0.01166221,0.01479712,-0.00919520,-0.02150456,0.00393951,0.02849227,0.00507755,-0.03524934,-0.01957400,0.04123492,0.04380521,-0.04593941,-0.09361452,0.04894534,0.31404787,0.45002093,0.31404787,0.04894534,-0.09361452,-0.04593941,0.04380521,0.04123492,-0.01957400,-0.03524934,0.00507755,0.02849227,0.00393951,-0.02150456,-0.00919520,0.01479712,0.01166221,-0.00879804,-0.01206450,0.00381468,0.01102582,-0.00001488,-0.00910186,-0.00257219,0.00677193,0.00403776,-0.00442124,-0.00456252,0.00232772,0.00437930,-0.00065955,-0.00373546,-0.00051574,0.00286056,0.00121252,-0.00194299,-0.00150250,0.00111730,0.00148876,-0.00046184,-0.00128217,0.00000491,0.00098324,0.00026359,-0.00067058,-0.00037813,0.00039623,0.00038398,-0.00018662,-0.00032622,0.00004740,0.00024233,0.00002984,-0.00015870,-0.00006069,0.00009027,0.00006228,-0.00004244,-0.00004941,0.00001405,0.00003270,-0.00000045,-0.00001809,-0.00000356,0.00000862,0.00000426,-0.00000274};
    
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> filter;

    double edge[] = {.0, .4, .5, 1.0};
    double fx[] = {1.0, 0};
    double wtx[] = {1.0, 1.0};
    
    //EXPECT_TRUE(filter.firpm(numElements - 1, 2, &(edge[0]), fx, wtx));
    EXPECT_TRUE(filter.firpm(numElements - 1, 2, edge, fx, wtx));
    EXPECT_EQ(numElements, filter.size());
    for (int i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], filter[i]));
    }
}

TEST(RealFirFilter, ParksMcClellanBandPass) {
    double expectedData[] = {0.00000451,-0.00001136,-0.00003826,0.00001169,0.00002015,-0.00000227,0.00011193,0.00006758,-0.00015140,-0.00005021,-0.00007680,-0.00030264,0.00020251,0.00048988,-0.00001774,0.00029825,0.00020432,-0.00116773,-0.00061443,0.00038431,-0.00049273,0.00098871,0.00244901,-0.00057151,-0.00102358,0.00009848,-0.00354825,-0.00192770,0.00389979,0.00124132,0.00148600,0.00557458,-0.00343858,-0.00780801,0.00026640,-0.00389173,-0.00259063,0.01401095,0.00705071,-0.00428040,0.00490433,-0.00963080,-0.02315341,0.00522995,0.00932870,-0.00083219,0.02986073,0.01613239,-0.03250166,-0.01055839,-0.01217084,-0.04745394,0.03038418,0.07315251,-0.00269974,0.04270308,0.03386333,-0.23352294,-0.17885711,0.29897250,0.29897250,-0.17885711,-0.23352294,0.03386333,0.04270308,-0.00269974,0.07315251,0.03038418,-0.04745394,-0.01217084,-0.01055839,-0.03250166,0.01613239,0.02986073,-0.00083219,0.00932870,0.00522995,-0.02315341,-0.00963080,0.00490433,-0.00428040,0.00705071,0.01401095,-0.00259063,-0.00389173,0.00026640,-0.00780801,-0.00343858,0.00557458,0.00148600,0.00124132,0.00389979,-0.00192770,-0.00354825,0.00009848,-0.00102358,-0.00057151,0.00244901,0.00098871,-0.00049273,0.00038431,-0.00061443,-0.00116773,0.00020432,0.00029825,-0.00001774,0.00048988,0.00020251,-0.00030264,-0.00007680,-0.00005021,-0.00015140,0.00006758,0.00011193,-0.00000227,0.00002015,0.00001169,-0.00003826,-0.00001136,0.00000451};
    
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> filter;

    double edge[] = {.0, .2, .3, .6, .7, 1.0};
    double fx[] = {0, 1, 0};
    double wtx[] = {1.0, 1.0, 1.0};
    
    EXPECT_TRUE(filter.firpm(numElements - 1, 3, edge, fx, wtx));
    EXPECT_EQ(numElements, filter.size());
    for (int i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], filter[i]));
    }
}

TEST(RealFirFilter, ParksMcClellanBandPass2) {
    double expectedData[] = {0.00000251,-0.00003228,-0.00002125,0.00003186,-0.00000174,0.00004392,0.00013521,-0.00005942,-0.00014538,0.00000039,-0.00023292,-0.00014110,0.00049233,0.00023828,0.00000598,0.00047919,-0.00050910,-0.00124080,0.00014701,-0.00001450,-0.00019985,0.00225511,0.00122696,-0.00153733,0.00001616,-0.00146863,-0.00404797,0.00158220,0.00349152,-0.00000018,0.00444724,0.00250006,-0.00802914,-0.00362554,-0.00003028,-0.00621846,0.00624004,0.01443003,-0.00162160,0.00005455,0.00198867,-0.02159948,-0.01137621,0.01384373,-0.00004615,0.01244093,0.03387959,-0.01311560,-0.02900263,0.00000046,-0.03733359,-0.02166486,0.07267056,0.03507570,0.00005567,0.07430294,-0.09066655,-0.28651968,0.05846240,0.39991929,0.05846240,-0.28651968,-0.09066655,0.07430294,0.00005567,0.03507570,0.07267056,-0.02166486,-0.03733359,0.00000046,-0.02900263,-0.01311560,0.03387959,0.01244093,-0.00004615,0.01384373,-0.01137621,-0.02159948,0.00198867,0.00005455,-0.00162160,0.01443003,0.00624004,-0.00621846,-0.00003028,-0.00362554,-0.00802914,0.00250006,0.00444724,-0.00000018,0.00349152,0.00158220,-0.00404797,-0.00146863,0.00001616,-0.00153733,0.00122696,0.00225511,-0.00019985,-0.00001450,0.00014701,-0.00124080,-0.00050910,0.00047919,0.00000598,0.00023828,0.00049233,-0.00014110,-0.00023292,0.00000039,-0.00014538,-0.00005942,0.00013521,0.00004392,-0.00000174,0.00003186,-0.00002125,-0.00003228,0.00000251};
    
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> filter;

    double edge[] = {.0, .2, .3, .6, .7, 1.0};
    double fx[] = {0, 1, 0};
    double wtx[] = {1.0, 1.0, 1.0};
    
    EXPECT_TRUE(filter.firpm(numElements - 1, 3, edge, fx, wtx));
    EXPECT_EQ(numElements, filter.size());
    for (int i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], filter[i]));
    }
}

TEST(RealFirFilter, FractionalDelay) {
    double expectedData[] = {-0.00116094,0.00486943,-0.00748928,-0.00026934,0.02406753,-0.04510960,0.02197806,0.07024028,-0.19289691,0.22224736,0.98196301,0.49981301,-0.17929342,-0.00203095,0.06591779,-0.04789988,0.00909337,0.01074650,-0.00972201,0.00302875,0.00119630};
    
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> filter;

    filter.fractionalDelayFilter(numElements, 0.7, 0.15);
    EXPECT_EQ(numElements, filter.size());
    for (int i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], filter[i]));
    }
}

TEST(RealFirFilter, CorrOneShot) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double inputData2[] = {-3, -4, -5, -6, -7, -8, -9};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {5, 4, -2, -12, -25, -40, -55, -70, -85, -60, -38, -20, -7};
    double expectedData2[] = {-15, -32, -50, -68, -85, -100, -115, -80, -50, -26, -9};
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealFirFilter<double> filter(filterTaps, numElements);
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;

    numElements = sizeof(inputData)/sizeof(inputData[0]);
    NimbleDSP::RealVector<double> buf(inputData, numElements);
    corr(buf, filter);
    EXPECT_EQ(numElements + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
    buf = NimbleDSP::RealVector<double>(inputData2, numElements);
    corr(buf, filter);
    EXPECT_EQ(numElements + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
}

TEST(RealFirFilter, Hamming) {
    double expectedData[] = {0.08000000, 0.08092613, 0.08370079, 0.08831280, 0.09474360, 0.10296729, 0.11295075, 0.12465379, 0.13802929, 0.15302337, 0.16957568, 0.18761956, 0.20708234, 0.22788567, 0.24994577, 0.27317382, 0.29747628, 0.32275531, 0.34890909, 0.37583234, 0.40341663, 0.43155089, 0.46012184, 0.48901443, 0.51811232, 0.54729834, 0.57645498, 0.60546483, 0.63421107, 0.66257795, 0.69045126, 0.71771876, 0.74427064, 0.77000000, 0.79480323, 0.81858046, 0.84123594, 0.86267845, 0.88282165, 0.90158442, 0.91889123, 0.93467237, 0.94886431, 0.96140989, 0.97225861, 0.98136677, 0.98869770, 0.99422189, 0.99791708, 0.99976841, 0.99976841, 0.99791708, 0.99422189, 0.98869770, 0.98136677, 0.97225861, 0.96140989, 0.94886431, 0.93467237, 0.91889123, 0.90158442, 0.88282165, 0.86267845, 0.84123594, 0.81858046, 0.79480323, 0.77000000, 0.74427064, 0.71771876, 0.69045126, 0.66257795, 0.63421107, 0.60546483, 0.57645498, 0.54729834, 0.51811232, 0.48901443, 0.46012184, 0.43155089, 0.40341663, 0.37583234, 0.34890909, 0.32275531, 0.29747628, 0.27317382, 0.24994577, 0.22788567, 0.20708234, 0.18761956, 0.16957568, 0.15302337, 0.13802929, 0.12465379, 0.11295075, 0.10296729, 0.09474360, 0.08831280, 0.08370079, 0.08092613, 0.08000000};
    
    unsigned windowLen = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> window;
    
    window.hamming(windowLen);
    EXPECT_EQ(window.size(), windowLen);

    for (unsigned i=0; i<windowLen; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], window[i]));
    }
}

TEST(RealFirFilter, Hann) {
    double expectedData[] = {0.00000000, 0.00121797, 0.00486597, 0.01092620, 0.01936915, 0.03015369, 0.04322727, 0.05852620, 0.07597595, 0.09549150, 0.11697778, 0.14033010, 0.16543470, 0.19216926, 0.22040355, 0.25000000, 0.28081443, 0.31269670, 0.34549150, 0.37903905, 0.41317591, 0.44773577, 0.48255025, 0.51744975, 0.55226423, 0.58682409, 0.62096095, 0.65450850, 0.68730330, 0.71918557, 0.75000000, 0.77959645, 0.80783074, 0.83456530, 0.85966990, 0.88302222, 0.90450850, 0.92402405, 0.94147380, 0.95677273, 0.96984631, 0.98063085, 0.98907380, 0.99513403, 0.99878203, 1.00000000, 0.99878203, 0.99513403, 0.98907380, 0.98063085, 0.96984631, 0.95677273, 0.94147380, 0.92402405, 0.90450850, 0.88302222, 0.85966990, 0.83456530, 0.80783074, 0.77959645, 0.75000000, 0.71918557, 0.68730330, 0.65450850, 0.62096095, 0.58682409, 0.55226423, 0.51744975, 0.48255025, 0.44773577, 0.41317591, 0.37903905, 0.34549150, 0.31269670, 0.28081443, 0.25000000, 0.22040355, 0.19216926, 0.16543470, 0.14033010, 0.11697778, 0.09549150, 0.07597595, 0.05852620, 0.04322727, 0.03015369, 0.01936915, 0.01092620, 0.00486597, 0.00121797, 0.00000000};
    
    unsigned windowLen = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> window;
    
    window.hann(windowLen);
    EXPECT_EQ(window.size(), windowLen);

    for (unsigned i=0; i<windowLen; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], window[i]));
    }
}

TEST(RealFirFilter, Blackman) {
    double expectedData[] = {0.00000000, 0.00375165, 0.01563845, 0.03740270, 0.07146461, 0.12028646, 0.18564672, 0.26795497, 0.36573504, 0.47537854, 0.59122860, 0.70600079, 0.81149328, 0.89949043, 0.96273070, 0.99579706, 0.99579706, 0.96273070, 0.89949043, 0.81149328, 0.70600079, 0.59122860, 0.47537854, 0.36573504, 0.26795497, 0.18564672, 0.12028646, 0.07146461, 0.03740270, 0.01563845, 0.00375165, 0.00000000};
    
    unsigned windowLen = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> window;
    
    window.blackman(windowLen);
    EXPECT_EQ(window.size(), windowLen);

    for (unsigned i=0; i<windowLen; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], window[i]));
    }
}

TEST(RealFirFilter, BlackmanHarris) {
    double expectedData[] = {0.00006000, 0.00030188, 0.00113918, 0.00290634, 0.00615793, 0.01165966, 0.02036792, 0.03339172, 0.05193269, 0.07720064, 0.11030663, 0.15213882, 0.20323136, 0.26363912, 0.33283350, 0.40963421, 0.49219007, 0.57801767, 0.66410116, 0.74704989, 0.82330370, 0.88936977, 0.94207047, 0.97877919, 0.99762146, 0.99762146, 0.97877919, 0.94207047, 0.88936977, 0.82330370, 0.74704989, 0.66410116, 0.57801767, 0.49219007, 0.40963421, 0.33283350, 0.26363912, 0.20323136, 0.15213882, 0.11030663, 0.07720064, 0.05193269, 0.03339172, 0.02036792, 0.01165966, 0.00615793, 0.00290634, 0.00113918, 0.00030188, 0.00006000};
    
    unsigned windowLen = sizeof(expectedData)/sizeof(expectedData[0]);
    NimbleDSP::RealFirFilter<double> window;
    
    window.blackmanHarris(windowLen);
    EXPECT_EQ(window.size(), windowLen);

    for (unsigned i=0; i<windowLen; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], window[i]));
    }
}
