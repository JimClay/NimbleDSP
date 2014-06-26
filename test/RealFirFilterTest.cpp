#include "RealFirFilter.h"
#include "gtest/gtest.h"

using namespace SlickDsp;


TEST(RealFirFilter, ConvStream1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double inputData2[] = {-8, -9, -10, -11, -12, -13, -14};
    double inputData3[] = {-15, -16, -17, -18, -19, -20, -21, -22, -23, -24, -25, -26, -27, -28};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 2, 0, -5, -20, -35, -50, -65};
    double expectedData2[] = {-80, -95, -110, -125, -140, -155, -170};
    double expectedData3[] = {-185, -200, -215, -230, -245, -260, -275, -290, -305, -320, -335, -350, -365, -380};
    
    unsigned numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    RealFirFilter<double> filter(filterTaps, numElements);

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = DspBuffer<double>(inputData2, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = DspBuffer<double>(inputData3, numElements);
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
    RealFirFilter<double> filter(filterTaps, numElements);
    filter.filtOperation = ONE_SHOT_RETURN_ALL_RESULTS;

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = DspBuffer<double>(inputData2, numElements);
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
    RealFirFilter<double> filter(filterTaps, numElements);
    filter.filtOperation = ONE_SHOT_TRIM_TAILS;

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = DspBuffer<double>(inputData2, numElements);
    conv(buf, filter);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
}

TEST(RealFirFilter, DecimateComplexOneShot) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 16), std::complex<double>(-5, 50), std::complex<double>(-35, 80), std::complex<double>(-65, 110), std::complex<double>(-70, 106), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    RealFirFilter<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
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
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    RealFirFilter<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
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
    RealFirFilter<double> filter(filterTaps, numElements);

    numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(3, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    numElements = sizeof(inputData2)/sizeof(inputData[0]);
	buf = ComplexDspBuffer<double>(inputData2, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData2[i], buf[i]);
    }
    
    numElements = sizeof(inputData3)/sizeof(inputData[0]);
	buf = ComplexDspBuffer<double>(inputData3, numElements);
    decimate(buf, rate, filter);
    EXPECT_EQ(5, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData3[i], buf[i]);
    }
}
