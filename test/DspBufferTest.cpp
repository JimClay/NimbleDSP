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
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

TEST(DspBufferInit, Vector) {
    double array[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    std::vector<double> inputData (array, array + sizeof(array) / sizeof(array[0]) );
	DspBuffer<double> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(DspBufferOperators, PlusEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf1.buf[i]);
        EXPECT_EQ(inputData[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, PlusEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]+5, buf.buf[i]);
    }
}

TEST(DspBufferOperators, PlusBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, PlusScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 + 32.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] + 32.0, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MinusEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MinusEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]-11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, MinusBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, MinusScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 - 15.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, MultiplyScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 * 15.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] * 15, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, DivideEqualsBuf) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    double inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(DspBufferOperators, DivideEqualsScalar) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/11, buf.buf[i]);
    }
}

TEST(DspBufferOperators, DivideBuf) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    double inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
    DspBuffer<double> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.buf[i]);
    }
}

TEST(DspBufferOperators, DivideScalar) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(0);
    
    buf2 = buf1 / 15.0;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] / 15.0, buf2.buf[i]);
    }
}

TEST(DspBufferOperators, UnaryMinus) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.buf[i]);
    }
}

TEST(DspBufferOperators, Indexing) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(DspBufferOperators, Equality) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    double inputData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	DspBuffer<double> buf1(inputData, numElements);
	DspBuffer<double> buf2(inputData2, numElements);
	DspBuffer<double> buf3(inputData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(DspBufferStatistics, Mean) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(450.015, buf.mean()));
}

TEST(DspBufferStatistics, Var) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(60008.57322857144, buf.var()));
}

TEST(DspBufferStatistics, StdDev) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(true, FloatsEqual(244.9664736827704, buf.stdDev()));
}

TEST(DspBufferStatistics, Median) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(450, buf.median());
    buf.buf.push_back(-10000);
    EXPECT_EQ(400, buf.median());
}

TEST(DspBufferMethods, Rotate) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
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

TEST(DspBufferMethods, Reverse) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(DspBufferMethods, Max) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(8.37, buf.max());
    unsigned maxLoc;
    EXPECT_EQ(8.37, buf.max(&maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(DspBufferMethods, Min) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(2, buf.min());
    unsigned minLoc;
    EXPECT_EQ(2, buf.min(&minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(DspBufferMethods, Find) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(-1, buf.find(9));
    EXPECT_EQ(4, buf.find(3));
}

TEST(DspBufferMethods, Pow) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    buf.pow(3);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i]*inputData[i]*inputData[i], buf[i]);
    }
}

TEST(DspBufferMethods, Saturate) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    double expectedData[] = {1, -5, 5, 3, 5, -2, -5, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    buf.saturate(5);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(DspBufferMethods, Abs) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    double expectedData[] = {1, 10, 8, 3, 6.92, 2, 9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	DspBuffer<double> buf(inputData, numElements);
    
    buf.abs();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
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
