#include "ComplexDspBuffer.h"
#include "RealDspBuffer.h"
#include "gtest/gtest.h"

using namespace SmartDsp;

extern bool FloatsEqual(double float1, double float2);

bool ComplexEqual(std::complex<double> c1, std::complex<double> c2) {
    double epsilon = .00000001;
    if ((c1.real() < c2.real() + epsilon) && (c1.real() > c2.real() - epsilon) &&
        (c1.imag() < c2.imag() + epsilon) && (c1.imag() > c2.imag() - epsilon))
        return true;
    return false;
}


TEST(ComplexDspBufferInit, Size) {
	ComplexDspBuffer<double> buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
}

TEST(ComplexDspBufferInit, Array) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

TEST(ComplexDspBufferInit, Vector) {
    std::complex<double> array[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::vector< std::complex<double> > inputData (array, array + sizeof(array) / sizeof(array[0]) );
	ComplexDspBuffer<double> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(ComplexDspBufferOperators, PlusEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(true, ComplexEqual(inputData[i]*2.0, buf1.buf[i]));
        EXPECT_EQ(inputData[i], buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, PlusEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    std::complex<double> operand(1.1, 3.5);
    
    buf += operand;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]+operand, buf.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, PlusBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData, numElements);
    ComplexDspBuffer<double> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2.0*inputData[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, PlusScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 + operand;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] + operand, buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MinusEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MinusEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    std::complex<double> operand(1.1, 3.5);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf -= operand;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]-operand, buf.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MinusBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
    ComplexDspBuffer<double> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MinusScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 - operand;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - operand, buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MultiplyEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MultiplyEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    std::complex<double> operand(1.1, 3.5);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf *= operand;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*operand, buf.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MultiplyBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
    ComplexDspBuffer<double> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MultiplyScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 * operand;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] * operand, buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, DivideEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.buf.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.buf[i]);
        EXPECT_EQ(inputData2[i], buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, DivideEqualsScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    std::complex<double> operand(1.1, 3.5);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf /= operand;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/operand, buf.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, DivideBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
    ComplexDspBuffer<double> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, DivideScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(0);
    std::complex<double> operand(1.1, 3.5);
    
    buf2 = buf1 / operand;
    EXPECT_EQ(numElements, buf2.buf.size());
    for (unsigned i=0; i<buf2.buf.size(); i++) {
        EXPECT_EQ(inputData[i] / operand, buf2.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, UnaryMinus) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, Indexing) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(ComplexDspBufferOperators, Equality) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> inputData2[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585), std::complex<double>(0.298342, 2.503162)};
    std::complex<double> inputData3[] = {std::complex<double>(-2.168253, -2.104236), std::complex<double>(-1.454950, 2.044304), std::complex<double>(-1.474307, 1.885709), std::complex<double>(-1.538850, 2.575582), std::complex<double>(-0.900097, -1.820428), std::complex<double>(-1.493497, 0.696268), std::complex<double>(-0.160267, -0.890043), std::complex<double>(1.984972, 0.511585)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	ComplexDspBuffer<double> buf1(inputData, numElements);
	ComplexDspBuffer<double> buf2(inputData2, numElements);
	ComplexDspBuffer<double> buf3(inputData3, numElements3);
    
    EXPECT_EQ(false, buf1 == buf2);
    EXPECT_EQ(true, buf1 != buf2);
    EXPECT_EQ(false, buf3 == buf2);
    EXPECT_EQ(true, buf3 != buf2);
    EXPECT_EQ(true, buf1 == buf1);
    EXPECT_EQ(false, buf1 != buf1);
}

TEST(ComplexDspBufferStatistics, Mean) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(true, ComplexEqual(std::complex<double>(0.767751, -0.661230333333333), buf.mean()));
}

TEST(ComplexDspBufferStatistics, Var) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(true, ComplexEqual(std::complex<double>(7.335490751497001,0), buf.var()));
}

TEST(ComplexDspBufferStatistics, StdDev) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(true, ComplexEqual(std::complex<double>(2.708411111980048,0), buf.stdDev()));
}

TEST(ComplexDspBufferMethods, Rotate) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
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

TEST(ComplexDspBufferMethods, Reverse) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    buf.reverse();
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, Find) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(-1, buf.find(std::complex<double>(1,1)));
    EXPECT_EQ(3, buf.find(std::complex<double>(0.932867, -1.972880)));
}

TEST(ComplexDspBufferMethods, Pow) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.pow(3.0);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(inputData[i]*inputData[i]*inputData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Saturate) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(1, 1.546441), std::complex<double>(1, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1, -2), std::complex<double>(-1, -2), std::complex<double>(-1, 1.940747), std::complex<double>(1, -1.097403), std::complex<double>(1, -2)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.saturate(std::complex<double>(1, 2));
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, Abs) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(3.341958851311159, 0), std::complex<double>(1.881899338275562, 0), std::complex<double>(1.595689053377569, 0), std::complex<double>(2.182314444366118, 0), std::complex<double>(3.069019171451687, 0), std::complex<double>(3.034148486516110, 0), std::complex<double>(3.099902944882307, 0), std::complex<double>(1.603367980593663, 0), std::complex<double>(3.885853000719405, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.abs();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Resize) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.resize(11);
    EXPECT_EQ(11, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(inputData[i], buf[i]));
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(true, ComplexEqual(0, buf[i]));
    }
    
    buf.resize(0);
    EXPECT_EQ(0, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(true, ComplexEqual(inputData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Pad) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.pad(5);
    EXPECT_EQ(numElements + 5, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(std::complex<double>(0,0), buf[i]);
    }
}

TEST(ComplexDspBufferMethods, Exp) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(2.71828182846, 0), std::complex<double>(-40802.48887960893, 69765.99455269895), std::complex<double>(-0.14550003381, 0.98935824662), std::complex<double>(1.00010000000, 0.00010001000)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.exp();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Log) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(2.441779605764140, 0.183744530739123), std::complex<double>(2.079441541679836, 1.570796326794897), std::complex<double>(-8.863766781696210, 0.785398163397448)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.log();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Ln) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(2.441779605764140, 0.183744530739123), std::complex<double>(2.079441541679836, 1.570796326794897), std::complex<double>(-8.863766781696210, 0.785398163397448)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.ln();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Log10) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(1.060451408807264, 0.079799235779903), std::complex<double>(0.903089986991944, 0.682188176920921), std::complex<double>(-3.849485002168009, 0.341094088460460)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.log10();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, FFT) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double>  expectedData[] = {std::complex<double>(6.9097590000, -5.9510730000), std::complex<double>(6.0948705961, 3.5401310272), std::complex<double>(8.8172840764, 5.8659402629), std::complex<double>(0.7542392638, 6.2651671652), std::complex<double>(-0.8240048974, 1.8728723957), std::complex<double>(3.3960661360, 1.1172915239), std::complex<double>(-5.8326962638, 7.4013838348), std::complex<double>(-6.9279259075, -6.2566796847), std::complex<double>(6.4653919964, 9.5805974749)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    fft(buf);
    EXPECT_EQ(FREQUENCY_DOMAIN, buf.domain);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, IFFT) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double>  expectedData[] = {std::complex<double>(6.9097590000, -5.9510730000), std::complex<double>(6.4653919964, 9.5805974749), std::complex<double>(-6.9279259075, -6.2566796847), std::complex<double>(-5.8326962638, 7.4013838348), std::complex<double>(3.3960661360, 1.1172915239), std::complex<double>(-0.8240048974, 1.8728723957), std::complex<double>(0.7542392638, 6.2651671652), std::complex<double>(8.8172840764, 5.8659402629), std::complex<double>(6.0948705961, 3.5401310272)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements, FREQUENCY_DOMAIN);
    
    ifft(buf);
    EXPECT_EQ(TIME_DOMAIN, buf.domain);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
        //EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, Conj) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(2.094776, -2.603959), std::complex<double>(1.072411, -1.546441), std::complex<double>(1.458795, 0.646638), std::complex<double>(0.932867, 1.972880), std::complex<double>(1.236277, 2.809003), std::complex<double>(-1.338462, 2.722972), std::complex<double>(-2.417209, -1.940747), std::complex<double>(1.168972, 1.097403), std::complex<double>(2.701332, 2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.conj();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, MagSq) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(11.1686889639, 0), std::complex<double>(3.5415451194, 0), std::complex<double>(2.5462235551, 0), std::complex<double>(4.7624963341, 0), std::complex<double>(9.4188786747, 0), std::complex<double>(9.2060570382, 0), std::complex<double>(9.6093982677, 0), std::complex<double>(2.5707888812, 0), std::complex<double>(15.0998535432, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    buf.magSq();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, FilterOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 7), std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80), std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-72, 114), std::complex<double>(-70, 106), std::complex<double>(-58, 85), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    DspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, FilterEven) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5, 6};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 7), std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-14, 77), std::complex<double>(-35, 98), std::complex<double>(-56, 119), std::complex<double>(-77, 140), std::complex<double>(-90, 150), std::complex<double>(-94, 148), std::complex<double>(-88, 133), std::complex<double>(-71, 104), std::complex<double>(-42, 60)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    DspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, FilterOddTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80), std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-72, 114), std::complex<double>(-70, 106)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    DspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, FilterEvenTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5, 6};
    std::complex<double> expectedData[] = {std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-14, 77), std::complex<double>(-35, 98), std::complex<double>(-56, 119), std::complex<double>(-77, 140), std::complex<double>(-90, 150), std::complex<double>(-94, 148)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    DspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, Sum) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    EXPECT_EQ(std::complex<double>(-27, 54), sum(buf));
}

TEST(ComplexDspBufferMethods, Diff) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> expectedData[] = {std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    
    diff(buf);
    EXPECT_EQ(numElements-1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, RunningDiff) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    std::complex<double> expectedData[] = {std::complex<double>(-2, 2), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1), std::complex<double>(-1, 1)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    std::complex<double> previousVal = std::complex<double>(3, 0);
    
    diff(buf, previousVal);
    EXPECT_EQ(numElements, buf.size());
    EXPECT_EQ(std::complex<double>(-7, 10), previousVal);
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferFilter, DecimateEvenOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(0, 30), std::complex<double>(-35, 80), std::complex<double>(-72, 114), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    RealDspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferFilter, InterpEvenOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 4), std::complex<double>(3, 6), std::complex<double>(4, 11), std::complex<double>(5, 16), std::complex<double>(0, 9), std::complex<double>(-1, 16), std::complex<double>(-2, 23), std::complex<double>(-3, 12), std::complex<double>(-6, 21), std::complex<double>(-9, 30), std::complex<double>(-6, 15), std::complex<double>(-11, 26), std::complex<double>(-16, 37), std::complex<double>(-9, 18), std::complex<double>(-16, 31), std::complex<double>(-23, 44), std::complex<double>(-12, 21), std::complex<double>(-21, 36), std::complex<double>(-30, 51), std::complex<double>(-15, 24), std::complex<double>(-26, 41), std::complex<double>(-37, 58), std::complex<double>(-18, 27), std::complex<double>(-31, 46), std::complex<double>(-44, 65), std::complex<double>(-21, 30), std::complex<double>(-28, 40), std::complex<double>(-35, 50), std::complex<double>(0, 0), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    RealDspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferFilter, Resample1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(3, 6), std::complex<double>(5, 16), std::complex<double>(-1, 16), std::complex<double>(-3, 12), std::complex<double>(-9, 30), std::complex<double>(-11, 26), std::complex<double>(-9, 18), std::complex<double>(-23, 44), std::complex<double>(-21, 36), std::complex<double>(-15, 24), std::complex<double>(-37, 58), std::complex<double>(-31, 46), std::complex<double>(-21, 30), std::complex<double>(-35, 50), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    ComplexDspBuffer<double> filter(filterTaps, numElements);
    ComplexDspBuffer<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}


