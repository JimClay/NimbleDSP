#include <vector>
#include "DspBuffer.h"
#include "gtest/gtest.h"


TEST(DspBufferInit, Size) {
	DspBuffer<int> buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}

TEST(DspBufferInit, Array) {
    short expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements, FREQUENCY_DOMAIN);
    
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf.buf[i]);
    }
    EXPECT_EQ(FREQUENCY_DOMAIN, buf.domain);
}

TEST(DspBufferInit, Vector) {
    short array[] = {1, 3, 5, 7, 2, 4, 6, 9};
    std::vector<int> expectedData (array, array + sizeof(array) / sizeof(array[0]) );
	DspBuffer<int> buf(expectedData);
    
    EXPECT_EQ(expectedData.size(), buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf.buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}


TEST(DspBufferOperators, PreIncrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    ++buf;
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]+1, buf.buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}

TEST(DspBufferOperators, PostIncrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf++;
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]+1, buf.buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}
