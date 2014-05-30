#include <vector>
#include "DspBuffer.h"
#include "gtest/gtest.h"

using namespace SmartDsp;

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

// Operator tests
TEST(DspBufferOperators, PreIncrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = ++buf * 2;
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((expectedData[i]+1)*2, buf.buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}

TEST(DspBufferOperators, PostIncrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf++ * 2;
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*2, buf2[i]);
        EXPECT_EQ(expectedData[i]+1, buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}

TEST(DspBufferOperators, PreDecrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = --buf * 2;
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((expectedData[i]-1)*2, buf.buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}

TEST(DspBufferOperators, PostDecrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf-- * 2;
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*2, buf2[i]);
        EXPECT_EQ(expectedData[i]-1, buf[i]);
    }
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
}

TEST(DspBufferOperators, PlusEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (int i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(2*expectedData[i], buf1.buf[i]);
        EXPECT_EQ(expectedData[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, PlusEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]+5, buf.buf[i]);
    }
}

TEST(DspBufferOperators, PlusBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData, numElements);
    DspBuffer<int> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (int i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2*expectedData[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, PlusScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    buf2 = buf1 + 32;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (int i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] + 32, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MinusEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (int i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(1, buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MinusEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]-11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, MinusBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    DspBuffer<int> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (int i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(1, buf3.buf[i]);
    }
}

TEST(DspBufferOperators, MinusScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    buf2 = buf1 - 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (int i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] - 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (int i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    DspBuffer<int> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (int i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*expectedData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    buf2 = buf1 * 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (int i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] * 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, DivideEqualsBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (int i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, DivideEqualsScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, DivideBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    DspBuffer<int> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (int i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/expectedData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, DivideScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    buf2 = buf1 / 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (int i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] / 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, ModuloEqualsBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 %= buf2;
    for (int i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]%expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, ModuloEqualsScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf %= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]%11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, ModuloBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
    DspBuffer<int> buf3(0);
    
    buf3 = buf1 % buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (int i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]%expectedData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, ModuloScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(0);
    
    buf2 = buf1 % 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (int i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] % 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, UnaryMinus) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-expectedData[i], buf.buf[i]);
    }
}

TEST(DspBufferOperators, Indexing) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(numElements);
    
    for (int i=0; i<numElements; i++) {
        buf[i] = expectedData[i];
    }
    
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(DspBufferOperators, Equality) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int expectedData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    int numElements3 = sizeof(expectedData3)/sizeof(expectedData3[0]);
	DspBuffer<int> buf1(expectedData, numElements);
	DspBuffer<int> buf2(expectedData2, numElements);
	DspBuffer<int> buf3(expectedData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(DspBufferStatistics, Mean) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(450, buf.mean());
}

TEST(DspBufferStatistics, Var) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(60000, buf.var());
}

TEST(DspBufferStatistics, StdDev) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(244, buf.stdDev());
}

TEST(DspBufferStatistics, Median) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(450, buf.median());
    buf.buf.push_back(-10000);
    EXPECT_EQ(400, buf.median());
}

TEST(DspBufferMethods, Rotate) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    buf.rotate(numElements);
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    buf.rotate(3);
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[((numElements - 3) + i) % numElements], buf[i]);
    }
    
    buf.rotate(-1);
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[((numElements - 2) + i) % numElements], buf[i]);
    }
}

TEST(DspBufferMethods, Reverse) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    buf.reverse();
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[numElements-i-1], buf[i]);
    }
    buf.reverse();
    for (int i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(DspBufferMethods, Max) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(8, buf.max());
    int maxLoc;
    EXPECT_EQ(8, buf.max(&maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(DspBufferMethods, Min) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(2, buf.min());
    int minLoc;
    EXPECT_EQ(2, buf.min(&minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(DspBufferMethods, Find) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    int numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(-1, buf.find(9));
    EXPECT_EQ(4, buf.find(3));
}
