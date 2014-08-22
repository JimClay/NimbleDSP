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

#include "ComplexVector.h"
#include "RealVector.h"
#include "gtest/gtest.h"


extern bool FloatsEqual(double float1, double float2);

bool ComplexEqual(std::complex<double> c1, std::complex<double> c2) {
    double epsilon = .00000001;
    if ((c1.real() < c2.real() + epsilon) && (c1.real() > c2.real() - epsilon) &&
        (c1.imag() < c2.imag() + epsilon) && (c1.imag() > c2.imag() - epsilon))
        return true;
    return false;
}


TEST(ComplexVectorInit, Size) {
	NimbleDSP::ComplexVector<double> buf(50);
    
    EXPECT_EQ(50, buf.vec.size());
}

TEST(ComplexVectorInit, Array) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

TEST(ComplexVectorInit, Vector) {
    std::complex<double> array[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::vector< std::complex<double> > inputData (array, array + sizeof(array) / sizeof(array[0]) );
	NimbleDSP::ComplexVector<double> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

// Operator tests
TEST(ComplexVectorOperators, PlusEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_TRUE(ComplexEqual(inputData[i]*2.0, buf1.vec[i]));
        EXPECT_EQ(inputData[i], buf2.vec[i]);
    }
}

TEST(ComplexVectorOperators, PlusEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    std::complex<double> operand(1.1, 3.5);
    
    buf += operand;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]+operand, buf.vec[i]);
    }
}

TEST(ComplexVectorOperators, PlusBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData, numElements);
    NimbleDSP::ComplexVector<double> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(2.0*inputData[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData[i], buf2[i]);
    }
}

TEST(ComplexVectorOperators, PlusScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 + operand;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] + operand, buf2[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
    }
}

TEST(ComplexVectorOperators, MinusEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(ComplexVectorOperators, MinusEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    std::complex<double> operand(1.1, 3.5);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf -= operand;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]-operand, buf.vec[i]);
    }
}

TEST(ComplexVectorOperators, MinusBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
    NimbleDSP::ComplexVector<double> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData2[i], buf2[i]);
    }
}

TEST(ComplexVectorOperators, MinusScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 - operand;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - operand, buf2.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
    }
}

TEST(ComplexVectorOperators, MultiplyEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(ComplexVectorOperators, MultiplyEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    std::complex<double> operand(1.1, 3.5);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf *= operand;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*operand, buf.vec[i]);
    }
}

TEST(ComplexVectorOperators, MultiplyBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
    NimbleDSP::ComplexVector<double> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData2[i], buf2[i]);
    }
}

TEST(ComplexVectorOperators, MultiplyScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 * operand;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] * operand, buf2.vec[i]);
    }
}

TEST(ComplexVectorOperators, DivideEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(ComplexVectorOperators, DivideEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    std::complex<double> operand(1.1, 3.5);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf /= operand;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/operand, buf.vec[i]);
    }
}

TEST(ComplexVectorOperators, DivideBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
    NimbleDSP::ComplexVector<double> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.vec[i]);
        EXPECT_EQ(inputData[i], buf1[i]);
        EXPECT_EQ(inputData2[i], buf2[i]);
    }
}

TEST(ComplexVectorOperators, DivideScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 / operand;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] / operand, buf2.vec[i]);
    }
}

TEST(ComplexVectorOperators, UnaryMinus) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.vec[i]);
    }
}

TEST(ComplexVectorOperators, Indexing) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(ComplexVectorOperators, Equality) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    std::complex<double> inputData3[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	NimbleDSP::ComplexVector<double> buf1(inputData, numElements);
	NimbleDSP::ComplexVector<double> buf2(inputData2, numElements);
	NimbleDSP::ComplexVector<double> buf3(inputData3, numElements3);
    
    EXPECT_FALSE(buf1 == buf2);
    EXPECT_TRUE(buf1 != buf2);
    EXPECT_FALSE(buf3 == buf2);
    EXPECT_TRUE(buf3 != buf2);
    EXPECT_TRUE(buf1 == buf1);
    EXPECT_FALSE(buf1 != buf1);
}

TEST(ComplexVectorStatistics, Mean) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_TRUE(ComplexEqual(std::complex<double>(0.767751, -0.661230333333333), mean(buf)));
}

TEST(ComplexVectorStatistics, Var) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_TRUE(ComplexEqual(std::complex<double>(7.335490751497001,0), var(buf)));
}

TEST(ComplexVectorStatistics, StdDev) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_TRUE(ComplexEqual(std::complex<double>(2.708411111980048,0), stdDev(buf)));
}

TEST(ComplexVectorMethods, Rotate) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
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

TEST(ComplexVectorMethods, Reverse) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, Find) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(-1, find(buf, std::complex<double>(1,1)));
    EXPECT_EQ(3, find(buf, std::complex<double>(0.932867, -1.972880)));
}

TEST(ComplexVectorMethods, Pow) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    pow(buf, 3.0);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(inputData[i]*inputData[i]*inputData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, Saturate) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(1, 1.546441), std::complex<double>(1, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1, -2), std::complex<double>(-1, -2), std::complex<double>(-1, 1.940747), std::complex<double>(1, -1.097403), std::complex<double>(1, -2)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    saturate(buf, std::complex<double>(1, 2));
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, Abs) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(3.341958851311159, 0), std::complex<double>(1.881899338275562, 0), std::complex<double>(1.595689053377569, 0), std::complex<double>(2.182314444366118, 0), std::complex<double>(3.069019171451687, 0), std::complex<double>(3.034148486516110, 0), std::complex<double>(3.099902944882307, 0), std::complex<double>(1.603367980593663, 0), std::complex<double>(3.885853000719405, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    abs(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, Resize) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    buf.resize(11);
    EXPECT_EQ(11, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(inputData[i], buf[i]));
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(0, buf[i]));
    }
    
    buf.resize(0);
    EXPECT_EQ(0, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(inputData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, Pad) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    buf.pad(5);
    EXPECT_EQ(numElements + 5, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(std::complex<double>(0,0), buf[i]);
    }
}

TEST(ComplexVectorMethods, Exp) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(2.71828182846, 0), std::complex<double>(-40802.48887960893, 69765.99455269895), std::complex<double>(-0.14550003381, 0.98935824662), std::complex<double>(1.00010000000, 0.00010001000)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    exp(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, Log) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(2.441779605764140, 0.183744530739123), std::complex<double>(2.079441541679836, 1.570796326794897), std::complex<double>(-8.863766781696210, 0.785398163397448)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    log(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, Log10) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(1.060451408807264, 0.079799235779903), std::complex<double>(0.903089986991944, 0.682188176920921), std::complex<double>(-3.849485002168009, 0.341094088460460)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    log10(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, FFT) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double>  expectedData[] = {std::complex<double>(6.9097590000, -5.9510730000), std::complex<double>(6.0948705961, 3.5401310272), std::complex<double>(8.8172840764, 5.8659402629), std::complex<double>(0.7542392638, 6.2651671652), std::complex<double>(-0.8240048974, 1.8728723957), std::complex<double>(3.3960661360, 1.1172915239), std::complex<double>(-5.8326962638, 7.4013838348), std::complex<double>(-6.9279259075, -6.2566796847), std::complex<double>(6.4653919964, 9.5805974749)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    fft(buf);
    EXPECT_EQ(NimbleDSP::FREQUENCY_DOMAIN, buf.domain);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, IFFT) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double>  expectedData[] = {std::complex<double>(6.9097590000, -5.9510730000), std::complex<double>(6.4653919964, 9.5805974749), std::complex<double>(-6.9279259075, -6.2566796847), std::complex<double>(-5.8326962638, 7.4013838348), std::complex<double>(3.3960661360, 1.1172915239), std::complex<double>(-0.8240048974, 1.8728723957), std::complex<double>(0.7542392638, 6.2651671652), std::complex<double>(8.8172840764, 5.8659402629), std::complex<double>(6.0948705961, 3.5401310272)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::FREQUENCY_DOMAIN);
    
    ifft(buf);
    EXPECT_EQ(NimbleDSP::TIME_DOMAIN, buf.domain);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
        //EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, Conj) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(2.094776, -2.603959), std::complex<double>(1.072411, -1.546441), std::complex<double>(1.458795, 0.646638), std::complex<double>(0.932867, 1.972880), std::complex<double>(1.236277, 2.809003), std::complex<double>(-1.338462, 2.722972), std::complex<double>(-2.417209, -1.940747), std::complex<double>(1.168972, 1.097403), std::complex<double>(2.701332, 2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    conj(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, MagSq) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(11.1686889639, 0), std::complex<double>(3.5415451194, 0), std::complex<double>(2.5462235551, 0), std::complex<double>(4.7624963341, 0), std::complex<double>(9.4188786747, 0), std::complex<double>(9.2060570382, 0), std::complex<double>(9.6093982677, 0), std::complex<double>(2.5707888812, 0), std::complex<double>(15.0998535432, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    magSq(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, Sum) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(std::complex<double>(-27, 54), sum(buf));
}

TEST(ComplexVectorMethods, Diff) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> expectedData[] = {std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    diff(buf);
    EXPECT_EQ(numElements-1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, RunningDiff) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> expectedData[] = {std::complex<double>(-2, 2), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    std::complex<double> previousVal = std::complex<double>(3, 0);
    
    diff(buf, previousVal);
    EXPECT_EQ(numElements, buf.size());
    EXPECT_EQ(std::complex<double>(-7, 10), previousVal);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, Angle) {
    std::complex<double> inputData[] = {std::complex<double>(0.814723686, 0), std::complex<double>(0.861459324, 0.279905102), std::complex<double>(0.102734492, 0.074640978), std::complex<double>(0.536868858, 0.738936590), std::complex<double>(0.195409754, 0.601409382), std::complex<double>(0, 0.097540405), std::complex<double>(-0.086060683, 0.264867546), std::complex<double>(-0.321448892, 0.442436443), std::complex<double>(-0.774639302, 0.562808397), std::complex<double>(-0.917663529, 0.298166955), std::complex<double>(-0.157613082, 0), std::complex<double>(-0.923088590, -0.299929664), std::complex<double>(-0.774364328, -0.562608616), std::complex<double>(-0.285296648, -0.392677148), std::complex<double>(-0.247300265, -0.761111955), std::complex<double>(0, -0.141886339), std::complex<double>(0.130331404, -0.401118816), std::complex<double>(0.538255837, -0.740845602), std::complex<double>(0.640909193, -0.465647785), std::complex<double>(0.912531524, -0.296499466), std::complex<double>(0.655740699, 0), std::complex<double>(0, 0)};
    std::complex<double> expectedData[] = {std::complex<double>(0), std::complex<double>(0.314159265), std::complex<double>(0.628318531), std::complex<double>(0.942477796), std::complex<double>(1.256637061), std::complex<double>(1.570796327), std::complex<double>(1.884955592), std::complex<double>(2.199114858), std::complex<double>(2.513274123), std::complex<double>(2.827433388), std::complex<double>(3.141592654), std::complex<double>(-2.827433388), std::complex<double>(-2.513274123), std::complex<double>(-2.199114858), std::complex<double>(-1.884955592), std::complex<double>(-1.570796327), std::complex<double>(-1.256637061), std::complex<double>(-0.942477796), std::complex<double>(-0.628318531), std::complex<double>(-0.314159265), std::complex<double>(0), std::complex<double>(0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    angle(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorMethods, IndividualAngle) {
    std::complex<double> inputData[] = {std::complex<double>(0.814723686, 0), std::complex<double>(0.861459324, 0.279905102), std::complex<double>(0.102734492, 0.074640978), std::complex<double>(0.536868858, 0.738936590), std::complex<double>(0.195409754, 0.601409382), std::complex<double>(0, 0.097540405), std::complex<double>(-0.086060683, 0.264867546), std::complex<double>(-0.321448892, 0.442436443), std::complex<double>(-0.774639302, 0.562808397), std::complex<double>(-0.917663529, 0.298166955), std::complex<double>(-0.157613082, 0), std::complex<double>(-0.923088590, -0.299929664), std::complex<double>(-0.774364328, -0.562608616), std::complex<double>(-0.285296648, -0.392677148), std::complex<double>(-0.247300265, -0.761111955), std::complex<double>(0, -0.141886339), std::complex<double>(0.130331404, -0.401118816), std::complex<double>(0.538255837, -0.740845602), std::complex<double>(0.640909193, -0.465647785), std::complex<double>(0.912531524, -0.296499466), std::complex<double>(0.655740699, 0), std::complex<double>(0, 0)};
    std::complex<double> expectedData[] = {std::complex<double>(0), std::complex<double>(0.314159265), std::complex<double>(0.628318531), std::complex<double>(0.942477796), std::complex<double>(1.256637061), std::complex<double>(1.570796327), std::complex<double>(1.884955592), std::complex<double>(2.199114858), std::complex<double>(2.513274123), std::complex<double>(2.827433388), std::complex<double>(3.141592654), std::complex<double>(-2.827433388), std::complex<double>(-2.513274123), std::complex<double>(-2.199114858), std::complex<double>(-1.884955592), std::complex<double>(-1.570796327), std::complex<double>(-1.256637061), std::complex<double>(-0.942477796), std::complex<double>(-0.628318531), std::complex<double>(-0.314159265), std::complex<double>(0), std::complex<double>(0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], std::complex<double>(NimbleDSP::angle(buf[i]))));
    }
}

//TEST(BogusTest, BogusTest) {
//    NimbleDSP::ComplexVector<double> buf(50);
//    NimbleDSP::ComplexVector<double> buf2(10);
 
    //buf2 = conv(reverse(rotate(saturate(fft(buf), std::complex<double>(1,1)), 1)), buf) * std::complex<double>(0,1);
    //buf = log10(abs(fft(buf2)));
//}

TEST(ComplexVectorMethods, ComplexFilterOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-5, 5), std::complex<double>(-15, 11), std::complex<double>(-32, 18), std::complex<double>(-58, 26), std::complex<double>(-95, 35), std::complex<double>(-135, 25), std::complex<double>(-175, 15), std::complex<double>(-215, 5), std::complex<double>(-255, -5), std::complex<double>(-254, -2), std::complex<double>(-230, 0), std::complex<double>(-181, 1), std::complex<double>(-105, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, ComplexFilterEven) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7), std::complex<double>(6, 8)};
    std::complex<double> expectedData[] = {std::complex<double>(-5, 5), std::complex<double>(-15, 11), std::complex<double>(-32, 18), std::complex<double>(-58, 26), std::complex<double>(-95, 35), std::complex<double>(-145, 45), std::complex<double>(-199, 33), std::complex<double>(-253, 21), std::complex<double>(-307, 9), std::complex<double>(-320, 10), std::complex<double>(-310, 10), std::complex<double>(-275, 9), std::complex<double>(-213, 7), std::complex<double>(-122, 4)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, ComplexFilterOddTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-32, 18), std::complex<double>(-58, 26), std::complex<double>(-95, 35), std::complex<double>(-135, 25), std::complex<double>(-175, 15), std::complex<double>(-215, 5), std::complex<double>(-255, -5), std::complex<double>(-254, -2), std::complex<double>(-230, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorMethods, ComplexFilterEvenTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7), std::complex<double>(6, 8)};
    std::complex<double> expectedData[] = {std::complex<double>(-32, 18), std::complex<double>(-58, 26), std::complex<double>(-95, 35), std::complex<double>(-145, 45), std::complex<double>(-199, 33), std::complex<double>(-253, 21), std::complex<double>(-307, 9), std::complex<double>(-320, 10), std::complex<double>(-310, 10)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexDecimateEvenOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-5, 5), std::complex<double>(-58, 26), std::complex<double>(-175, 15), std::complex<double>(-254, -2), std::complex<double>(-105, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexDecimateEvenOddTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-32, 18), std::complex<double>(-95, 35), std::complex<double>(-175, 15), std::complex<double>(-255, -5), std::complex<double>(-230, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 2;
    
    decimate(buf, rate, filter, true);
    EXPECT_EQ((input.size() + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexInterpEvenOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-5, 5), std::complex<double>(-6, 8), std::complex<double>(-7, 11), std::complex<double>(-17, 17), std::complex<double>(-21, 23), std::complex<double>(-15, 9), std::complex<double>(-31, 13), std::complex<double>(-39, 19), std::complex<double>(-23, 7), std::complex<double>(-45, 9), std::complex<double>(-57, 15), std::complex<double>(-31, 5), std::complex<double>(-59, 5), std::complex<double>(-75, 11), std::complex<double>(-39, 3), std::complex<double>(-73, 1), std::complex<double>(-93, 7), std::complex<double>(-47, 1), std::complex<double>(-87, -3), std::complex<double>(-111, 3), std::complex<double>(-55, -1), std::complex<double>(-101, -7), std::complex<double>(-129, -1), std::complex<double>(-63, -3), std::complex<double>(-115, -11), std::complex<double>(-147, -5), std::complex<double>(-71, -5), std::complex<double>(-88, -2), std::complex<double>(-105, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexInterpEvenOddTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-16, 14), std::complex<double>(-20, 20), std::complex<double>(-37, 27), std::complex<double>(-36, 16), std::complex<double>(-61, 21), std::complex<double>(-52, 12), std::complex<double>(-85, 15), std::complex<double>(-68, 8), std::complex<double>(-109, 9), std::complex<double>(-84, 4), std::complex<double>(-133, 3), std::complex<double>(-100, 0), std::complex<double>(-157, -3), std::complex<double>(-116, -4), std::complex<double>(-181, -9), std::complex<double>(-132, -8), std::complex<double>(-164, -2), std::complex<double>(-88, -2)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 2;
    
    interp(buf, rate, filter, true);
    EXPECT_EQ(input.size()*rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexResample1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-5, 5), std::complex<double>(-7, 11), std::complex<double>(-21, 23), std::complex<double>(-31, 13), std::complex<double>(-23, 7), std::complex<double>(-57, 15), std::complex<double>(-59, 5), std::complex<double>(-39, 3), std::complex<double>(-93, 7), std::complex<double>(-87, -3), std::complex<double>(-55, -1), std::complex<double>(-129, -1), std::complex<double>(-115, -11), std::complex<double>(-71, -5), std::complex<double>(-105, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexResampleTrim1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-7, 11), std::complex<double>(-21, 23), std::complex<double>(-31, 13), std::complex<double>(-23, 7), std::complex<double>(-57, 15), std::complex<double>(-59, 5), std::complex<double>(-39, 3), std::complex<double>(-93, 7), std::complex<double>(-87, -3), std::complex<double>(-55, -1), std::complex<double>(-129, -1), std::complex<double>(-115, -11), std::complex<double>(-71, -5), std::complex<double>(-105, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexResample2) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-5, 5), std::complex<double>(-12, 6), std::complex<double>(-23, 7), std::complex<double>(-38, 8), std::complex<double>(-57, 9), std::complex<double>(0, 0), std::complex<double>(-33, -9), std::complex<double>(-54, -8), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 6;
    int decimateRate = 7;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexVectorFilter, ComplexResampleTrim2) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> filterTaps[] = {std::complex<double>(1, 3), std::complex<double>(2, 4), std::complex<double>(3, 5), std::complex<double>(4, 6), std::complex<double>(5, 7)};
    std::complex<double> expectedData[] = {std::complex<double>(-7, 11), std::complex<double>(-18, 12), std::complex<double>(-33, 13), std::complex<double>(0, 0), std::complex<double>(-25, -5), std::complex<double>(-42, -4), std::complex<double>(-63, -3), std::complex<double>(-88, -2)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::ComplexVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 6;
    int decimateRate = 7;
    
    resample(buf, interpRate, decimateRate, filter, true);
    EXPECT_EQ((input.size()*interpRate + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}


TEST(ComplexVectorDataGen, Tone0) {
    std::complex<double> expectedData[] = {std::complex<double>(0.54030231, 0.84147098), std::complex<double>(0.91070914, -0.41304825), std::complex<double>(-0.27712533, -0.96083378), std::complex<double>(-0.99079290, 0.13538625), std::complex<double>(-0.00919426, 0.99995773), std::complex<double>(0.98813594, 0.15358181), std::complex<double>(0.29474605, -0.95557562), std::complex<double>(-0.90296014, -0.42972431), std::complex<double>(-0.55568372, 0.83139377), std::complex<double>(0.74237851, 0.66998070), std::complex<double>(0.77021646, -0.63778257), std::complex<double>(-0.51980116, -0.85428728), std::complex<double>(-0.92042873, 0.39091040), std::complex<double>(0.25381541, 0.96725267), std::complex<double>(0.99377638, -0.11139347), std::complex<double>(0.03336635, -0.99944319), std::complex<double>(-0.98413416, -0.17742589), std::complex<double>(-0.31776171, 0.94817061), std::complex<double>(0.89230730, 0.45142849), std::complex<double>(0.57562091, -0.81771668), std::complex<double>(-0.72596422, -0.68773247), std::complex<double>(-0.78541024, 0.61897557), std::complex<double>(0.49899615, 0.86660420)};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	NimbleDSP::ComplexVector<double> buf(numElements);
    
    tone(buf, -10007.3, 44100.0, 1.0);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexVectorDataGen, Tone) {
    std::complex<double> expectedData[] = {std::complex<double>(0.87758256, 0.47942554), std::complex<double>(0.83974239, 0.54298501), std::complex<double>(0.79730741, 0.60357344), std::complex<double>(0.75050982, 0.66085930), std::complex<double>(0.69960567, 0.71452915), std::complex<double>(0.64487350, 0.76428932), std::complex<double>(0.58661279, 0.80986754), std::complex<double>(0.52514232, 0.85101442), std::complex<double>(0.46079843, 0.88750482), std::complex<double>(0.39393320, 0.91913907), std::complex<double>(0.32491249, 0.94574408), std::complex<double>(0.25411397, 0.96717428), std::complex<double>(0.18192501, 0.98331241), std::complex<double>(0.10874061, 0.99407016), std::complex<double>(0.03496122, 0.99938867), std::complex<double>(-0.03900946, 0.99923884), std::complex<double>(-0.11276670, 0.99362149), std::complex<double>(-0.18590692, 0.98256736), std::complex<double>(-0.25802991, 0.96613693), std::complex<double>(-0.32874104, 0.94442010), std::complex<double>(-0.39765341, 0.91753570), std::complex<double>(-0.46438994, 0.88563084), std::complex<double>(-0.52858547, 0.84888009), std::complex<double>(-0.58988875, 0.80748452), std::complex<double>(-0.64796435, 0.76167066), std::complex<double>(-0.70249449, 0.71168918)};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	NimbleDSP::ComplexVector<double> buf;
    
    tone(buf, 519.3, 44100.0, 0.5, 26);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(ComplexEqual(expectedData[i], buf[i]));
    }
}



