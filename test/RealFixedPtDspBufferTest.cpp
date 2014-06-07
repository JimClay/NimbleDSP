#include "RealFixedPtDspBuffer.h"
#include "gtest/gtest.h"

using namespace SmartDsp;


extern bool FloatsEqual(double float1, double float2);


TEST(RealFixedPtDspBufferInit, Size) {
	RealFixedPtDspBuffer<int> buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
}

TEST(RealFixedPtDspBufferInit, Array) {
    short inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferInit, Vector) {
    short array[] = {1, 3, 5, 7, 2, 4, 6, 9};
    std::vector<int> inputData (array, array + sizeof(array) / sizeof(array[0]) );
	RealFixedPtDspBuffer<int> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(RealFixedPtDspBufferOperators, PreIncrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = ++buf * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((inputData[i]+1)*2, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PostIncrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf++ * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*2, buf2[i]);
        EXPECT_EQ(inputData[i]+1, buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PreDecrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = --buf * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((inputData[i]-1)*2, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PostDecrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf-- * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*2, buf2[i]);
        EXPECT_EQ(inputData[i]-1, buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PlusEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf1.buf[i]);
        EXPECT_EQ(inputData[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PlusEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]+5, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PlusBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, PlusScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 + 32;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] + 32, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MinusEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(1, buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MinusEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]-11, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MinusBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(1, buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MinusScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 - 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - 15, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MultiplyEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MultiplyEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*11, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MultiplyBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, MultiplyScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 * 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] * 15, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, DivideEqualsBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, DivideEqualsScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/11, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, DivideBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, DivideScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 / 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] / 15, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, ModuloEqualsBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 %= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]%inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, ModuloEqualsScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf %= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]%11, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, ModuloBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 % buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]%inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, ModuloScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 % 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] % 15, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitAndEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 &= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]&inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitAndEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf &= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]&5, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitAndBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 & buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]&inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitAndScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 & 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] & 4, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitOrEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 |= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]|inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitOrEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf |= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]|5, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitOrBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 | buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]|inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitOrScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 | 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] | 4, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitXorEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 ^= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]^inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitXorEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf ^= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]^5, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitXorBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 ^ buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]^inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitXorScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 ^ 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] ^ 4, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftRightEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 >>= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]>>inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftRightEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf >>= 1;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]>>1, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftRightBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 >> buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]>>inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftRightScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 >> 1;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] >> 1, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftLeftEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 <<= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]<<inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftLeftEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf <<= 1;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]<<1, buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftLeftBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
    RealFixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 << buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]<<inputData2[i], buf3.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, BitShiftLeftScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 << 1;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] << 1, buf2.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, UnaryMinus) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, Indexing) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealFixedPtDspBufferOperators, Equality) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int inputData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	RealFixedPtDspBuffer<int> buf1(inputData, numElements);
	RealFixedPtDspBuffer<int> buf2(inputData2, numElements);
	RealFixedPtDspBuffer<int> buf3(inputData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(RealFixedPtDspBufferStatistics, Mean) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(4.5, meanF(buf)));
}

TEST(RealFixedPtDspBufferStatistics, Var) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(60000.0, varF(buf)));
}

TEST(RealFixedPtDspBufferStatistics, StdDev) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(244.9489742783178, stdDevF(buf)));
}

TEST(RealFixedPtDspBufferStatistics, Median) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(450, median(buf));
    buf.buf.push_back(-10000);
    EXPECT_EQ(400, median(buf));
}

TEST(RealFixedPtDspBufferStatistics, Mode) {
    int inputData[] = {7, 3, 2, 8, 3, 6, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(3, mode(buf));
}

TEST(RealFixedPtDspBufferMethods, Rotate) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    rotate(buf, numElements);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    
    rotate(buf, 3);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[((numElements - 3) + i) % numElements], buf[i]);
    }
    
    rotate(buf, -1);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[((numElements - 2) + i) % numElements], buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Reverse) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    reverse(buf);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    reverse(buf);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Max) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(8, max(buf));
    unsigned maxLoc;
    EXPECT_EQ(8, max(buf, &maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(RealFixedPtDspBufferMethods, Min) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(2, min(buf));
    unsigned minLoc;
    EXPECT_EQ(2, min(buf, &minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(RealFixedPtDspBufferMethods, Find) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(-1, find(buf, 9));
    EXPECT_EQ(4, find(buf, 3));
}

TEST(RealFixedPtDspBufferMethods, Pow) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    int expectedData[] = {16, 256, 1296, 4096, 81, 625, 2401, 81};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    pow(buf, 4);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Saturate) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    int expectedData[] = {1, -5, 5, 3, 5, -2, -5, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    saturate(buf, 5);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Abs) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    int expectedData[] = {1, 10, 8, 3, 6, 2, 9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<int> buf(inputData, numElements);
    
    abs(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Resize) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    resize(buf, 11);
    EXPECT_EQ(11, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
    
    resize(buf, 4);
    EXPECT_EQ(4, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Pad) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    pad(buf, 5);
    EXPECT_EQ(13, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
}

TEST(RealFixedPtDspBufferMethods, Exp) {
    int inputData[] = {1, -10, 8, 0, 7, -2, -9, 1};
    int expectedData[] = {2, 0, 2980, 1, 1096, 0, 0, 2};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    exp(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealFixedPtDspBufferMethods, Log) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 9, 2, 5, 1, 0, 2, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    log(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealFixedPtDspBufferMethods, Ln) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 9, 2, 5, 1, 0, 2, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    ln(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealFixedPtDspBufferMethods, Log10) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 4, 0, 2, 0, 0, 0, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	RealFixedPtDspBuffer<int> buf(inputData, numElements);
    
    log10(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}
