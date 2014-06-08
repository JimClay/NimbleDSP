#include "ComplexDspBuffer.h"
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
	ComplexDspBuffer< std::complex<double> > buf(50);
    
    EXPECT_EQ(50, buf.buf.size());
}

TEST(ComplexDspBufferInit, Array) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

TEST(ComplexDspBufferInit, Vector) {
    std::complex<double> array[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::vector< std::complex<double> > inputData (array, array + sizeof(array) / sizeof(array[0]) );
	ComplexDspBuffer< std::complex<double> > buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.buf.size());
    for (unsigned i=0; i<buf.buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf.buf[i]);
    }
}

// Operator tests
TEST(ComplexDspBufferOperators, PlusEqualsBuf) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData, numElements);
    ComplexDspBuffer< std::complex<double> > buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(2.0*inputData[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, PlusScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(0);
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
    ComplexDspBuffer< std::complex<double> > buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MinusScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(0);
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
    ComplexDspBuffer< std::complex<double> > buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, MultiplyScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(0);
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
    ComplexDspBuffer< std::complex<double> > buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.buf.size());
    for (unsigned i=0; i<buf3.buf.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.buf[i]);
    }
}

TEST(ComplexDspBufferOperators, DivideScalar) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(0);
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf1(inputData, numElements);
	ComplexDspBuffer< std::complex<double> > buf2(inputData2, numElements);
	ComplexDspBuffer< std::complex<double> > buf3(inputData3, numElements3);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    EXPECT_EQ(true, ComplexEqual(std::complex<double>(0.767751, -0.661230333333333), buf.mean()));
}

TEST(ComplexDspBufferStatistics, Var) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    EXPECT_EQ(true, ComplexEqual(std::complex<double>(7.335490751497001,0), buf.var()));
}

TEST(ComplexDspBufferStatistics, StdDev) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    EXPECT_EQ(true, ComplexEqual(std::complex<double>(2.708411111980048,0), buf.stdDev()));
}

TEST(ComplexDspBufferMethods, Rotate) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    EXPECT_EQ(-1, buf.find(std::complex<double>(1,1)));
    EXPECT_EQ(3, buf.find(std::complex<double>(0.932867, -1.972880)));
}

TEST(ComplexDspBufferMethods, Pow) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.pow(3.0);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(inputData[i]*inputData[i]*inputData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Saturate) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(1, 1.546441), std::complex<double>(1, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1, -2), std::complex<double>(-1, -2), std::complex<double>(-1, 1.940747), std::complex<double>(1, -1.097403), std::complex<double>(1, -2)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.saturate(std::complex<double>(1, 2));
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(ComplexDspBufferMethods, Abs) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double> expectedData[] = {std::complex<double>(3.341958851311159, 0), std::complex<double>(1.881899338275562, 0), std::complex<double>(1.595689053377569, 0), std::complex<double>(2.182314444366118, 0), std::complex<double>(3.069019171451687, 0), std::complex<double>(3.034148486516110, 0), std::complex<double>(3.099902944882307, 0), std::complex<double>(1.603367980593663, 0), std::complex<double>(3.885853000719405, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.abs();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Resize) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
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
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.exp();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Log) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(2.441779605764140, 0.183744530739123), std::complex<double>(2.079441541679836, 1.570796326794897), std::complex<double>(-8.863766781696210, 0.785398163397448)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.log();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Ln) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(2.441779605764140, 0.183744530739123), std::complex<double>(2.079441541679836, 1.570796326794897), std::complex<double>(-8.863766781696210, 0.785398163397448)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.ln();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}

TEST(ComplexDspBufferMethods, Log10) {
    std::complex<double> inputData[] = {std::complex<double>(1, 0), std::complex<double>(11.3, 2.1), std::complex<double>(0, 8), std::complex<double>(.0001, .0001)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(1.060451408807264, 0.079799235779903), std::complex<double>(0.903089986991944, 0.682188176920921), std::complex<double>(-3.849485002168009, 0.341094088460460)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    buf.log10();
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(true, ComplexEqual(expectedData[i], buf[i]));
    }
}
/*
TEST(ComplexDspBufferMethods, FFT) {
    std::complex<double> inputData[] = {std::complex<double>(2.094776, 2.603959), std::complex<double>(1.072411, 1.546441), std::complex<double>(1.458795, -0.646638), std::complex<double>(0.932867, -1.972880), std::complex<double>(1.236277, -2.809003), std::complex<double>(-1.338462, -2.722972), std::complex<double>(-2.417209, 1.940747), std::complex<double>(1.168972, -1.097403), std::complex<double>(2.701332, -2.793324)};
    std::complex<double>  expectedData[] = {std::complex<double>(0, 0), std::complex<double>(1.060451408807264, 0.079799235779903), std::complex<double>(0.903089986991944, 0.682188176920921), std::complex<double>(-3.849485002168009, 0.341094088460460)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	ComplexDspBuffer< std::complex<double> > buf(inputData, numElements);
    
    fft(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}
*/
