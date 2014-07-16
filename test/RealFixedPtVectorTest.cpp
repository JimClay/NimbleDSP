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

#include "RealFixedPtVector.h"
#include "gtest/gtest.h"


extern bool FloatsEqual(double float1, double float2);


TEST(RealFixedPtVectorInit, Size) {
	NimbleDSP::RealFixedPtVector<int> buf(50);
    
    EXPECT_EQ(50, buf.vec.size());
}

TEST(RealFixedPtVectorInit, Array) {
    short inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

TEST(RealFixedPtVectorInit, Vector) {
    short array[] = {1, 3, 5, 7, 2, 4, 6, 9};
    std::vector<int> inputData (array, array + sizeof(array) / sizeof(array[0]) );
	NimbleDSP::RealFixedPtVector<int> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

// Operator tests
TEST(RealFixedPtVectorOperators, PreIncrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf = ++buf * 2;
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ((inputData[i]+1)*2, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, PostIncrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf2 = buf++ * 2;
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*2, buf2[i]);
        EXPECT_EQ(inputData[i]+1, buf[i]);
    }
}

TEST(RealFixedPtVectorOperators, PreDecrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf = --buf * 2;
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ((inputData[i]-1)*2, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, PostDecrement) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf2 = buf-- * 2;
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*2, buf2[i]);
        EXPECT_EQ(inputData[i]-1, buf[i]);
    }
}

TEST(RealFixedPtVectorOperators, PlusEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf1.vec[i]);
        EXPECT_EQ(inputData[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, PlusEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]+5, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, PlusBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, PlusScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 + 32;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] + 32, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MinusEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(1, buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MinusEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]-11, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MinusBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(1, buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MinusScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 - 15;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - 15, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MultiplyEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MultiplyEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*11, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MultiplyBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, MultiplyScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 * 15;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] * 15, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, DivideEqualsBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, DivideEqualsScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/11, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, DivideBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, DivideScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 / 15;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] / 15, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, ModuloEqualsBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 %= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]%inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, ModuloEqualsScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf %= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]%11, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, ModuloBuf) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 % buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]%inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, ModuloScalar) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 % 15;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] % 15, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitAndEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 &= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]&inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitAndEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf &= 5;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]&5, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitAndBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 & buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]&inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitAndScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 & 4;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] & 4, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitOrEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 |= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]|inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitOrEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf |= 5;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]|5, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitOrBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 | buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]|inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitOrScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 | 4;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] | 4, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitXorEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 ^= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]^inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitXorEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf ^= 5;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]^5, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitXorBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 ^ buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]^inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitXorScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 ^ 4;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] ^ 4, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftRightEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 >>= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]>>inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftRightEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf >>= 1;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]>>1, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftRightBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 >> buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]>>inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftRightScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 >> 1;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] >> 1, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftLeftEqualsBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 <<= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]<<inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftLeftEqualsScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf <<= 1;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]<<1, buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftLeftBuf) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
    NimbleDSP::RealFixedPtVector<int> buf3(0);
    
    buf3 = buf1 << buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]<<inputData2[i], buf3.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, BitShiftLeftScalar) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(0);
    
    buf2 = buf1 << 1;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] << 1, buf2.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, UnaryMinus) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.vec[i]);
    }
}

TEST(RealFixedPtVectorOperators, Indexing) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealFixedPtVectorOperators, Equality) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    int inputData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	NimbleDSP::RealFixedPtVector<int> buf1(inputData, numElements);
	NimbleDSP::RealFixedPtVector<int> buf2(inputData2, numElements);
	NimbleDSP::RealFixedPtVector<int> buf3(inputData3, numElements3);
    
    EXPECT_FALSE(buf1 == buf2);
    EXPECT_TRUE(buf1 != buf2);
    EXPECT_FALSE(buf3 == buf2);
    EXPECT_TRUE(buf3 != buf2);
    EXPECT_TRUE(buf1 == buf1);
    EXPECT_FALSE(buf1 != buf1);
}

TEST(RealFixedPtVectorStatistics, Mean) {
    int inputData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_TRUE(FloatsEqual(4.5, mean(buf)));
}

TEST(RealFixedPtVectorStatistics, Var) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_TRUE(FloatsEqual(60000.0, var(buf)));
}

TEST(RealFixedPtVectorStatistics, StdDev) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_TRUE(FloatsEqual(244.9489742783178, stdDev(buf)));
}

TEST(RealFixedPtVectorStatistics, Median) {
    int inputData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(450, median(buf));
    buf.vec.push_back(-10000);
    EXPECT_EQ(400, median(buf));
}

TEST(RealFixedPtVectorStatistics, Mode) {
    int inputData[] = {7, 8, 3, 2, 3, 6, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(3, mode(buf));
}

TEST(RealFixedPtVectorStatistics, ModeScratch) {
    int inputData[] = {7, 8, 3, 2, 8, 3, 6, 1, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<int> scratchBuf;
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements, &scratchBuf);
    
    EXPECT_EQ(8, mode(buf));
}

TEST(RealFixedPtVectorMethods, Rotate) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    rotate(buf, numElements);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    
    rotate(buf, 3);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[(3 + i) % numElements], buf[i]);
    }
    
    rotate(buf, -1);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[(2 + i) % numElements], buf[i]);
    }
}

TEST(RealFixedPtVectorMethods, Reverse) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealFixedPtVectorMethods, Max) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(8, max(buf));
    unsigned maxLoc;
    EXPECT_EQ(8, max(buf, &maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(RealFixedPtVectorMethods, Min) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(2, min(buf));
    unsigned minLoc;
    EXPECT_EQ(2, min(buf, &minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(RealFixedPtVectorMethods, Find) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    EXPECT_EQ(-1, find(buf, 9));
    EXPECT_EQ(4, find(buf, 3));
}

TEST(RealFixedPtVectorMethods, Pow) {
    int inputData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    int expectedData[] = {16, 256, 1296, 4096, 81, 625, 2401, 81};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    pow(buf, 4);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFixedPtVectorMethods, Saturate) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    int expectedData[] = {1, -5, 5, 3, 5, -2, -5, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    saturate(buf, 5);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFixedPtVectorMethods, Abs) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    int expectedData[] = {1, 10, 8, 3, 6, 2, 9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    abs(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealFixedPtVectorMethods, Resize) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
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

TEST(RealFixedPtVectorMethods, Pad) {
    int inputData[] = {1, -10, 8, 3, 6, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    pad(buf, 5);
    EXPECT_EQ(13, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
}

TEST(RealFixedPtVectorMethods, Exp) {
    int inputData[] = {1, -10, 8, 0, 7, -2, -9, 1};
    int expectedData[] = {2, 0, 2980, 1, 1096, 0, 0, 2};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    exp(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealFixedPtVectorMethods, Log) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 9, 2, 5, 1, 0, 2, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    log(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealFixedPtVectorMethods, Log10) {
    int inputData[] = {1, 10001, 8, 203, 7, 2, 9, 1};
    int expectedData[] = {0, 4, 0, 2, 0, 0, 0, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealFixedPtVector<int> buf(inputData, numElements);
    
    log10(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}
