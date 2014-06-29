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

#include "Vector.h"
#include "gtest/gtest.h"

//using namespace NimbleDSP;

bool FloatsEqual(double float1, double float2) {
    double epsilon = .00000001;
    if ((float1 < float2 + epsilon) && (float1 > float2 - epsilon))
        return true;
    return false;
}


TEST(VectorInit, Size) {
	NimbleDSP::Vector<double> buf(50);
    
    EXPECT_EQ(50, buf.vec.size());
}

TEST(VectorInit, Array) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

TEST(VectorInit, Vector) {
    double array[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    std::vector<double> inputData (array, array + sizeof(array) / sizeof(array[0]) );
	NimbleDSP::Vector<double> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

// Operator tests
TEST(VectorOperators, PlusEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf1.vec[i]);
        EXPECT_EQ(inputData[i], buf2.vec[i]);
    }
}

TEST(VectorOperators, PlusEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]+5, buf.vec[i]);
    }
}

TEST(VectorOperators, PlusBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData, numElements);
    NimbleDSP::Vector<double> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData[i], buf2[i]);
    }
}

TEST(VectorOperators, PlusScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(0);
    
    buf2 = buf1 + 32.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] + 32.0, buf2.vec[i]);
    }
}

TEST(VectorOperators, MinusEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(VectorOperators, MinusEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]-11, buf.vec[i]);
    }
}

TEST(VectorOperators, MinusBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
    NimbleDSP::Vector<double> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData2[i], buf2[i]);
    }
}

TEST(VectorOperators, MinusScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(0);
    
    buf2 = buf1 - 15.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - 15, buf2.vec[i]);
    }
}

TEST(VectorOperators, MultiplyEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(VectorOperators, MultiplyEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*11, buf.vec[i]);
    }
}

TEST(VectorOperators, MultiplyBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
    NimbleDSP::Vector<double> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData2[i], buf2[i]);
    }
}

TEST(VectorOperators, MultiplyScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(0);
    
    buf2 = buf1 * 15.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] * 15, buf2.vec[i]);
    }
}

TEST(VectorOperators, DivideEqualsBuf) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    double inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(VectorOperators, DivideEqualsScalar) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/11, buf.vec[i]);
    }
}

TEST(VectorOperators, DivideBuf) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    double inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
    NimbleDSP::Vector<double> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData2[i], buf2[i]);
    }
}

TEST(VectorOperators, DivideScalar) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(0);
    
    buf2 = buf1 / 15.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] / 15.0, buf2.vec[i]);
    }
}

TEST(VectorOperators, UnaryMinus) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.vec[i]);
    }
}

TEST(VectorOperators, Indexing) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(VectorOperators, Equality) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    double inputData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	NimbleDSP::Vector<double> buf1(inputData, numElements);
	NimbleDSP::Vector<double> buf2(inputData2, numElements);
	NimbleDSP::Vector<double> buf3(inputData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(VectorMethods, Rotate) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
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

TEST(VectorMethods, Reverse) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    buf.reverse();
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(VectorMethods, Find) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(-1, find(buf, 9.0));
    EXPECT_EQ(4, find(buf, 3.0));
}

TEST(VectorMethods, Abs) {
    double inputData[] = {1, -10, 8, 0, 6.92, -2, -9, 1};
    double expectedData[] = {1, 10, 8, 0, 6.92, 2, 9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    abs(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorMethods, Resize) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    buf.resize(11);
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

TEST(VectorMethods, Pad) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    pad(buf, 5);
    EXPECT_EQ(13, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
}

TEST(VectorMethods, Exp) {
    double inputData[] = {1, -10, 8, 0, 6.92, -2, -9, 1};
    double expectedData[] = {2.71828183, 0.00004540, 2980.95798704, 1.00000000, 1012.31999453, 0.13533528, 0.00012341, 2.71828183};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    exp(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(VectorMethods, Log) {
    double inputData[] = {1, 10001.3, 8, .0001, 6.92, 2, 9, 1};
    double expectedData[] = {0, 9.21047036, 2.07944154, -9.21034037, 1.93441577, 0.69314718, 2.19722458, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    log(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(VectorMethods, Ln) {
    double inputData[] = {1, 10001.3, 8, .0001, 6.92, 2, 9, 1};
    double expectedData[] = {0, 9.21047036, 2.07944154, -9.21034037, 1.93441577, 0.69314718, 2.19722458, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    ln(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(VectorMethods, Log10) {
    double inputData[] = {1, 10001.3, 8, .0001, 6.92, 2, 9, 1};
    double expectedData[] = {0, 4.00005645, 0.90308999, -4.00000000, 0.84010609, 0.30103000, 0.95424251, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    log10(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(VectorMethods, Upsample) {
	double inputData[] = { 1, 10001, 8, -5, 6, 2, 9, 1 };
	double expectedData[] = { 1, 0, 0, 10001, 0, 0, 8, 0, 0, -5, 0, 0, 6, 0, 0, 2, 0, 0, 9, 0, 0, 1, 0, 0 };
	double expectedData2[] = { 0, 1, 0, 0, 10001, 0, 0, 8, 0, 0, -5, 0, 0, 6, 0, 0, 2, 0, 0, 9, 0, 0, 1, 0 };
	double expectedData3[] = { 0, 0, 0, 1, 0, 0, 0, 10001, 0, 0, 0, 8, 0, 0, 0, -5, 0, 0, 0, 6, 0, 0, 0, 2, 0, 0, 0, 9, 0, 0, 0, 1 };
	unsigned numElements = sizeof(inputData) / sizeof(inputData[0]);
	NimbleDSP::Vector<double> bufSave(inputData, numElements);
	NimbleDSP::Vector<double> buf(0);

	buf = bufSave;
	upsample(buf, 3);
	for (unsigned i = 0; i<numElements; i++) {
		EXPECT_EQ(expectedData[i], buf[i]);
	}

	buf = bufSave;
	upsample(buf, 3, 1);
	for (unsigned i = 0; i<numElements; i++) {
		EXPECT_EQ(expectedData2[i], buf[i]);
	}

	buf = bufSave;
	upsample(buf, 4, 3);
	for (unsigned i = 0; i<numElements; i++) {
		EXPECT_EQ(expectedData3[i], buf[i]);
	}
}

TEST(VectorMethods, Downsample) {
	double inputData[] = { 1, 2, 3, 10001, 10002, 10003, 8, 9, 10, -5, -6, -7, 6, 7, 8, 2, 3, 4, 9, 10, 11, 1, 2, 3 };
	double expectedData[] = { 1, 10001, 8, -5, 6, 2, 9, 1 };
	double expectedData2[] = { 2, 10002, 9, -6, 7, 3, 10, 2 };
	double expectedData3[] = { 3, 10003, 10, -7, 8, 4, 11, 3 };
	unsigned numElements = sizeof(inputData) / sizeof(inputData[0]);
	NimbleDSP::Vector<double> bufSave(inputData, numElements);
	NimbleDSP::Vector<double> buf(0);

	buf = bufSave;
	downsample(buf, 3);
    EXPECT_EQ(numElements/3, buf.size());
	for (unsigned i = 0; i<buf.size(); i++) {
		EXPECT_EQ(expectedData[i], buf[i]);
	}

	buf = bufSave;
	downsample(buf, 3, 1);
    EXPECT_EQ(numElements/3, buf.size());
	for (unsigned i = 0; i<buf.size(); i++) {
		EXPECT_EQ(expectedData2[i], buf[i]);
	}

	buf = bufSave;
	downsample(buf, 3, 2);
    EXPECT_EQ(numElements/3, buf.size());
	for (unsigned i = 0; i<buf.size(); i++) {
		EXPECT_EQ(expectedData3[i], buf[i]);
	}
}

TEST(VectorFilter, FilterOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 2, 0, -5, -20, -35, -50, -65, -72, -70, -58, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterEven) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 2, 2, 0, -5, -14, -35, -56, -77, -90, -94, -88, -71, -42};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterOddTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {2, 0, -5, -20, -35, -50, -65, -72, -70};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::Vector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterEvenTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {2, 0, -5, -14, -35, -56, -77, -90, -94};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterSameLen) {
    double inputData[] = {1, 0, -1, -2, -3, -4};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 2, 2, 0, -5, -14, -30, -40, -43, -38, -24};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterSameLenTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {2, 0, -5, -14, -30, -40};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterLonger) {
    double inputData[] = {1, 0, -1, -2, -3};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 2, 2, 0, -5, -10, -22, -28, -27, -18};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, FilterLongerTrim) {
    double inputData[] = {1, 0, -1, -2, -3};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {2, 0, -5, -10, -22};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorMethods, Sum) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    EXPECT_EQ(-27, sum(buf));
}

TEST(VectorMethods, Diff) {
    double inputData[] = {1, 1, 2, 4, 7, 11, 16, 22};
    double expectedData[] = {0, 1, 2, 3, 4, 5, 6};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    diff(buf);
    EXPECT_EQ(numElements-1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorMethods, RunningDiff) {
    double inputData[] = {1, 1, 2, 4, 7, 11, 16, 22};
    double expectedData[] = {-1, 0, 1, 2, 3, 4, 5, 6};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    
    double previousVal = 2;
    diff(buf, previousVal);
    EXPECT_EQ(numElements, buf.size());
    EXPECT_EQ(22, previousVal);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateEvenOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 0, -35, -72, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateEvenEven) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 0, -35, -90, -71};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::Vector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateOddEven) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {1, -5, -84, -166, -12};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 4;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateOddOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, -5, -75, -193, -75, 99};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 4;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateEvenOddTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {2, -20, -65};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateEvenEvenTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {2, -14, -77};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateOddEvenTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {0, -48, -172, -72};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 4;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateOddOddTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {-5, -75, -193, -75};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 4;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateFilterSame) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 2, -5, -28, -75, -140, -165, -142, -63};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateFilterSameTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {-5, -28, -75, -140, -165};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateFilterLonger) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 2, -5, -28, -68, -119, -130, -93};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, DecimateFilterLongerTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {-5, -28, -68, -119};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpEvenOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 3, 4, 5, 0, -1, -2, -3, -6, -9, -6, -11, -16, -9, -16, -23, -12, -21, -30, -15, -26, -37, -18, -31, -44, -21, -28, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::Vector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpEvenEven) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 2, 3, 4, 5, 6, -1, -2, -3, -6, -9, -12, -11, -16, -21, -16, -23, -30, -21, -30, -39, -26, -37, -48, -31, -44, -57, -28, -35, -42};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpOddEven) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {1, 2, 3, 4, 5, 6, 7, 8, -1, -2, -3, -4, -7, -10, -13, -16, -13, -18, -23, -28, -19, -26, -33, -40, -25, -34, -43, -52, -31, -42, -53, -64, -37, -50, -63, -76, -43, -58, -73, -88, -49, -66, -83, -100, -35, -34, -33, -32, 61, 82, 103, 124, 55, 66, 77, 88};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 4;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpOddOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, -2, -3, -4, -7, -10, -13, -16, -22, -18, -23, -28, -37, -26, -33, -40, -52, -34, -43, -52, -67, -42, -53, -64, -82, -50, -63, -76, -97, -58, -73, -88, -112, -66, -83, -100, -107, -34, -33, -32, -20, 82, 103, 124, 145, 66, 77, 88, 99};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 4;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpOddEvenRate2) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {1, 2, 3, 4, 4, 4, 2, 0, -14, -20, -30, -40, -46, -60, -62, -80, -78, -100, -94, -120, -110, -140, -106, -120, -60, -56, 20, 32, 125, 146, 77, 88};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpOddOddRate2) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 2, 3, 4, 4, 4, 2, 0, -5, -20, -30, -40, -55, -60, -80, -80, -105, -100, -130, -120, -155, -140, -160, -120, -123, -56, -52, 32, 44, 146, 167, 88, 99};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpEvenOddTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {3, 4, 5, 0, -1, -2, -3, -6, -9, -6, -11, -16, -9, -16, -23, -12, -21, -30, -15, -26, -37, -18, -31, -44, -21, -28, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpEvenEvenTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {3, 4, 5, 6, -1, -2, -3, -6, -9, -12, -11, -16, -21, -16, -23, -30, -21, -30, -39, -26, -37, -48, -31, -44, -57, -28, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpOddEvenRate2Trim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {4, 4, 4, 2, 0, -14, -20, -30, -40, -46, -60, -62, -80, -78, -100, -94, -120, -110, -140, -106, -120, -60, -56, 20, 32, 125};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpOddOddRate2Trim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {4, 4, 2, 0, -5, -20, -30, -40, -55, -60, -80, -80, -105, -100, -130, -120, -155, -140, -160, -120, -123, -56, -52, 32, 44, 146};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpFilterSame) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 2, 3, 4, 4, 4, 2, 0, -5, -20, -30, -40, -55, -60, -80, -80, -105, -100, -122, -104, -122, -90, -103, -56, -63};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpFilterSameTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {4, 4, 2, 0, -5, -20, -30, -40, -55, -60, -80, -80, -105, -100, -122, -104, -122, -90};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpFilterLonger) {
    double inputData[] = {-1, -2, -3, -4};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {-1, -2, -5, -8, -14, -20, -30, -40, -50, -50, -59, -48, -55, -32, -36};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, InterpFilterLongerTrim) {
    double inputData[] = {-1, -2, -3, -4};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {-14, -20, -30, -40, -50, -50, -59, -48};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 3, 5, -1, -3, -9, -11, -9, -23, -21, -15, -37, -31, -21, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector<double> scratchBuf;
	NimbleDSP::Vector<double> buf(inputData, numElements, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample2) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 5, -3, -11, -23, -39, -31, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 4;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample3) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {1, 4, 7, -2, -7, -16, -23, -26, -25, -52, -53, -50, -43, -88, -83, -34, 61, 124, 77};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 4;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample4) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, -2, -23, -52, -97, -34, 77};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 4;
    int decimateRate = 9;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample5) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {1, 4, -30, -80, -110, -56, 77};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 5;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample6) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 4, 2, -20, -55, -80, -130, -140, -123, 32, 167};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample7) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {3, 5, -1, -3, -9, -11, -9, -23, -21, -15, -37, -31, -21, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample8) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {3, -1, -9, -21, -21, -37, -57};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 4;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample9) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double expectedData[] = {4, 2, -20, -46, -80, -94, -140, -60, 32};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, Resample10) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {4, -60, -160};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 9;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, ResampleFilterSame) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 4, 2, -20, -55, -80, -122, -90, -63};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size() - 1 + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, ResampleFilterSameTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {4, 0, -30, -60, -105, -104};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, ResampleFilterLonger) {
    double inputData[] = {1, 0, -1, -2, -3, -4};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {1, 4, 2, -20, -50, -48, -36};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size() - 1 + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(VectorFilter, ResampleFilterLongerTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4};
    int filterTaps[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double expectedData[] = {4, 0, -30, -50};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::Vector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::Vector<double> filter(filterTaps, numElements);
    NimbleDSP::Vector<double> input = buf;
    int interpRate = 2;
    int decimateRate = 3;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}
