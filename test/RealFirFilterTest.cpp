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
