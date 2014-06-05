#include "FixedPtDspBuffer.h"
#include "gtest/gtest.h"

using namespace SmartDsp;


extern bool FloatsEqual(double float1, double float2);


TEST(FixedPtDspBufferInit, Size) {
	FixedPtDspBuffer<int> buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
}

TEST(FixedPtDspBufferInit, Array) {
    short inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

TEST(FixedPtDspBufferInit, Vector) {
    short array[] = {1, 3, 5, 7, 2, 4, 6, 9};
    std::vector<int> inputData (array, array + sizeof(array) / sizeof(array[0]) );
	FixedPtDspBuffer<int> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(FixedPtDspBufferOperators, PreIncrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = ++buf * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((inputData[i]+1)*2, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PostIncrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf++ * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*2, buf2[i]);
        EXPECT_EQ(inputData[i]+1, buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PreDecrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = --buf * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ((inputData[i]-1)*2, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PostDecrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf2 = buf-- * 2;
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*2, buf2[i]);
        EXPECT_EQ(inputData[i]-1, buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf1.buf[i]);
        EXPECT_EQ(inputData[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]+5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, PlusScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 + 32;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] + 32, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(1, buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]-11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(1, buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MinusScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 - 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, MultiplyScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 * 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] * 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideEqualsBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideEqualsScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, DivideScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 / 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] / 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloEqualsBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 %= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]%inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloEqualsScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf %= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]%11, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 % buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]%inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, ModuloScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 % 15;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] % 15, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 &= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]&inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf &= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]&5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 & buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]&inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitAndScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 & 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] & 4, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 |= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]|inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf |= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]|5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 | buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]|inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitOrScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 | 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] | 4, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 ^= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]^inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf ^= 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]^5, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 ^ buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]^inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitXorScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 ^ 4;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] ^ 4, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 >>= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]>>inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf >>= 1;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]>>1, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 >> buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]>>inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftRightScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 >> 1;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] >> 1, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 <<= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]<<inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf <<= 1;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]<<1, buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
    FixedPtDspBuffer<int> buf3(0);
    
    buf3 = buf1 << buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]<<inputData2[i], buf3.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, BitShiftLeftScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(0);
    
    buf2 = buf1 << 1;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] << 1, buf2.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, UnaryMinus) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, Indexing) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferOperators, Equality) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int inputData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	FixedPtDspBuffer<int> buf1(inputData, numElements);
	FixedPtDspBuffer<int> buf2(inputData2, numElements);
	FixedPtDspBuffer<int> buf3(inputData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(FixedPtDspBufferStatistics, Mean) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(4.5, buf.mean()));
}

TEST(FixedPtDspBufferStatistics, Var) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(60000.0, buf.var()));
}

TEST(FixedPtDspBufferStatistics, StdDev) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(244.9489742783178, buf.stdDev()));
}

TEST(FixedPtDspBufferStatistics, Median) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(450, buf.median());
    buf.buf.push_back(-10000);
    EXPECT_EQ(400, buf.median());
}

TEST(FixedPtDspBufferStatistics, Mode) {
    int inputData[] = {7, 3, 2, 8, 3, 6, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(3, buf.mode());
}

TEST(FixedPtDspBufferMethods, Rotate) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.rotate(numElements);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    
    buf.rotate(3);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[((numElements - 3) + i) % numElements], buf[i]);
    }
    
    buf.rotate(-1);
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[((numElements - 2) + i) % numElements], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Reverse) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Max) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(8, buf.max());
    unsigned maxLoc;
    EXPECT_EQ(8, buf.max(&maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(FixedPtDspBufferMethods, Min) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    EXPECT_EQ(2, buf.min());
    unsigned minLoc;
    EXPECT_EQ(2, buf.min(&minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(FixedPtDspBufferMethods, Find) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
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

TEST(FixedPtDspBufferMethods, Saturate) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    int expectedData[] = {1, -5, 5, 3, 5, -2, -5, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<int> buf(inputData, numElements);
    
    buf.saturate(5);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Abs) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    int expectedData[] = {1, 10, 8, 3, 6, 2, 9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<int> buf(inputData, numElements);
    
    buf.abs();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Resize) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.resize(11);
    EXPECT_EQ(11, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
    
    buf.resize(4);
    EXPECT_EQ(4, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Pad) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.pad(5);
    EXPECT_EQ(13, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
}

TEST(FixedPtDspBufferMethods, Exp) {
    int inputData[] = {1, -10, 8, 0, 7, -2, -9, 1};
    int expectedData[] = {2, 0, 2980, 1, 1096, 0, 0, 2};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.exp();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(FixedPtDspBufferMethods, Log) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 9, 2, 5, 1, 0, 2, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.log();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(FixedPtDspBufferMethods, Ln) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 9, 2, 5, 1, 0, 2, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.ln();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(FixedPtDspBufferMethods, Log10) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 4, 0, 2, 0, 0, 0, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	FixedPtDspBuffer<int> buf(inputData, numElements);
    
    buf.log10();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}
