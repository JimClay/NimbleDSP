#include "FixedPtDspBuffer.h"
#include "gtest/gtest.h"

using namespace SmartDsp;


extern bool FloatsEqual(double float1, double float2);


TEST(FixedPtDspBufferInit, Size) {
	FixedPtDspBuffer<int> buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
}

TEST(FixedPtDspBufferInit, Array) {
    short expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf.buf[i]);
    }
}

TEST(FixedPtDspBufferInit, Vector) {
    short array[] = {1, 3, 5, 7, 2, 4, 6, 9};
    std::vector<int> expectedData (array, array + sizeof(array) / sizeof(array[0]) );
	FixedPtDspBuffer<int> buf(expectedData);
    
    EXPECT_EQ(expectedData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(FixedPtDspBufferOperators, PreIncrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = ++buf * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((expectedData[i]+1)*2, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PostIncrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf++ * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*2, buf2[i]);
        EXPECT_EQ(expectedData[i]+1, buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PreDecrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = --buf * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((expectedData[i]-1)*2, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PostDecrement) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf-- * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*2, buf2[i]);
        EXPECT_EQ(expectedData[i]-1, buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(2*expectedData[i], buf1.buf[i]);
        EXPECT_EQ(expectedData[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]+5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2*expectedData[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 + 32;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] + 32, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(1, buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]-11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(1, buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 - 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] - 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 * 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] * 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideEqualsBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideEqualsScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 / 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] / 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloEqualsBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 %= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]%expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloEqualsScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf %= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]%11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloBuf) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 % buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]%expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloScalar) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 % 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] % 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 &= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]&expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf &= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]&5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 & buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]&expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 & 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] & 4, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 |= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]|expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf |= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]|5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 | buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]|expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 | 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] | 4, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 ^= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]^expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf ^= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]^5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 ^ buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]^expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 ^ 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] ^ 4, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 >>= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]>>expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf >>= 1;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]>>1, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 >> buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]>>expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 >> 1;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] >> 1, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftEqualsBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 <<= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]<<expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftEqualsScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf <<= 1;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]<<1, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftBuf) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 << buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]<<expectedData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftScalar) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 << 1;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] << 1, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, UnaryMinus) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-expectedData[i], buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, Indexing) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = expectedData[i];
    }
    
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, Equality) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int expectedData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    unsigned numElements3 = sizeof(expectedData3)/sizeof(expectedData3[0]);
	FixedPtDspBuffer<int> buf1(expectedData, numElements);
	FixedPtDspBuffer<int> buf2(expectedData2, numElements);
	FixedPtDspBuffer<int> buf3(expectedData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(FixedPtDspBufferStatistics, Mean) {
    int expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(4.5, buf.mean()));
}

TEST(FixedPtDspBufferStatistics, Var) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(60000.0, buf.var()));
}

TEST(FixedPtDspBufferStatistics, StdDev) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(244.9489742783178, buf.stdDev()));
}

TEST(FixedPtDspBufferStatistics, Median) {
    int expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(450, buf.median());
    buf.buf.push_back(-10000);
    EXPECT_EQ(400, buf.median());
}

TEST(FixedPtDspBufferStatistics, Mode) {
    int expectedData[] = {7, 3, 2, 8, 3, 6, 1};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(3, buf.mode());
}

TEST(FixedPtDspBufferMethods, Rotate) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    buf.rotate(numElements);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
    
    buf.rotate(3);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[((numElements - 3) + i) % numElements], buf[i]);
    }
    
    buf.rotate(-1);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[((numElements - 2) + i) % numElements], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Reverse) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[numElements-i-1], buf[i]);
    }
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Max) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(8, buf.max());
    unsigned maxLoc;
    EXPECT_EQ(8, buf.max(&maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(FixedPtDspBufferMethods, Min) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(2, buf.min());
    unsigned minLoc;
    EXPECT_EQ(2, buf.min(&minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(FixedPtDspBufferMethods, Find) {
    int expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	FixedPtDspBuffer<int> buf(expectedData, numElements);
    
    EXPECT_EQ(-1, buf.find(9));
    EXPECT_EQ(4, buf.find(3));
}

TEST(FixedPtDspBufferMethods, Pow) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    int expectedData[] = {20, 388, 2218, 7643, 113, 1013, 4304, 113};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.pow(4.3);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}
