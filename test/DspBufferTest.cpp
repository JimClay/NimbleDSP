#include "DspBuffer.h"
#include "gtest/gtest.h"

using namespace SmartDsp;

bool FloatsEqual(double float1, double float2) {
    double epsilon = .00000001;
    if ((float1 < float2 + epsilon) && (float1 > float2 - epsilon))
        return true;
    return false;
}


TEST(DspBufferInit, Size) {
	DspBuffer<double> buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
}

TEST(DspBufferInit, Array) {
    short expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf.buf[i]);
    }
}

TEST(DspBufferInit, Vector) {
    short array[] = {1, 3, 5, 7, 2, 4, 6, 9};
    std::vector<double> expectedData (array, array + sizeof(array) / sizeof(array[0]) );
	DspBuffer<double> buf(expectedData);
    
    EXPECT_EQ(expectedData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(DspBufferOperators, PlusEqualsBuf) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(2*expectedData[i], buf1.buf[i]);
        EXPECT_EQ(expectedData[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, PlusEqualsScalar) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]+5, buf.buf[i]);
    }
}

TEST(DspBufferOperators, PlusBuf) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2*expectedData[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, PlusScalar) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 + 32.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] + 32.0, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MinusEqualsBuf) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    double expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(1, buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MinusEqualsScalar) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]-11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, MinusBuf) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    double expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(1, buf3.buf[i]);
    }
}

TEST(DspBufferOperators, MinusScalar) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 - 15.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] - 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyEqualsBuf) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    double expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyEqualsScalar) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyBuf) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    double expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]*expectedData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyScalar) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 * 15.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] * 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, DivideEqualsBuf) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    double expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/expectedData2[i], buf1.buf[i]);
        EXPECT_EQ(expectedData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, DivideEqualsScalar) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, DivideBuf) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    double expectedData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(expectedData[i]/expectedData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, DivideScalar) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 / 15.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(expectedData[i] / 15.0, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, UnaryMinus) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-expectedData[i], buf.buf[i]);
    }
}

TEST(DspBufferOperators, Indexing) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = expectedData[i];
    }
    
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(DspBufferOperators, Equality) {
    double expectedData[] = {1, 3, 5, 7, 2, 4, 6, 8};
    double expectedData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    double expectedData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
    unsigned numElements3 = sizeof(expectedData3)/sizeof(expectedData3[0]);
	DspBuffer<double> buf1(expectedData, numElements);
	DspBuffer<double> buf2(expectedData2, numElements);
	DspBuffer<double> buf3(expectedData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(DspBufferStatistics, Mean) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(450, buf.mean());
}

TEST(DspBufferStatistics, Var) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(60000, buf.var());
}

TEST(DspBufferStatistics, StdDev) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(244.9489742783178, buf.stdDev()));
}

TEST(DspBufferStatistics, Median) {
    double expectedData[] = {100, 300, 500, 700, 200, 400, 600, 800};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(450, buf.median());
    buf.buf.push_back(-10000);
    EXPECT_EQ(400, buf.median());
}

TEST(DspBufferMethods, Rotate) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
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

TEST(DspBufferMethods, Reverse) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 9};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[numElements-i-1], buf[i]);
    }
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(DspBufferMethods, Max) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(8, buf.max());
    unsigned maxLoc;
    EXPECT_EQ(8, buf.max(&maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(DspBufferMethods, Min) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(2, buf.min());
    unsigned minLoc;
    EXPECT_EQ(2, buf.min(&minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(DspBufferMethods, Find) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    EXPECT_EQ(-1, buf.find(9));
    EXPECT_EQ(4, buf.find(3));
}

TEST(DspBufferMethods, Pow) {
    double expectedData[] = {2, 4, 6, 8, 3, 5, 7, 3};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	DspBuffer<double> buf(expectedData, numElements);
    
    buf.pow(3);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i]*expectedData[i]*expectedData[i], buf[i]);
    }
}

//TEST(DspBufferMethods, FFT) {
//    double input[] = {-275, -75, 125, 325, -175, 25, 225, -175};
//    double expectedReal[] = {0, -525, -800, 324, -200};
//    double expectedImag[] = {0, -183, 200, -383, 0};
//    unsigned numElements = sizeof(input)/sizeof(input[0]);
//	DspBuffer<double> buf(input, numElements);
//    
//    DspBuffer< std::complex<double> > fftResult(0);
//    fftResult = buf.fft();
//    
//    EXPECT_EQ(numElements/2, fftResult.size());
//}
