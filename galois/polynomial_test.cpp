#include "gtest/gtest.h"
#include <vector>

#include "galois/polynomial.h"

namespace reed_solomon {
namespace galois {
namespace polynomial_test {

TEST(PolynomialTest, Construction) {
	std::vector<GF<>> c0;
	Polynomial<> p0 { c0 };

	EXPECT_EQ(p0.degree, 0);
	EXPECT_EQ(p0[0], 0);
	EXPECT_EQ(p0[1], 0);

	std::vector<GF<>> c1 = { 0 };
	Polynomial<> p1 { c1 };

	EXPECT_EQ(p1.degree, 0);
	EXPECT_EQ(p1[0], 0);
	EXPECT_EQ(p1[1], 0);

	std::vector<GF<>> c2 = { 1 };
	Polynomial<> p2 { c2 };

	EXPECT_EQ(p2.degree, 0);
	EXPECT_EQ(p2[0], 1);
	EXPECT_EQ(p2[1], 0);

	std::vector<GF<>> c3 = { 1, 0 };
	Polynomial<> p3 { c3 };

	EXPECT_EQ(p3.degree, 0);
	EXPECT_EQ(p3[0], 1);
	EXPECT_EQ(p3[1], 0);
	EXPECT_EQ(p3[2], 0);

	std::vector<GF<>> c4 = { 1, 1 };
	Polynomial<> p4 { c4 };

	EXPECT_EQ(p4.degree, 1);
	EXPECT_EQ(p4[0], 1);
	EXPECT_EQ(p4[1], 1);
	EXPECT_EQ(p4[2], 0);

	std::vector<GF<9>> c5 = { 511, 0, 512, 1, 0, 17, 0};
	Polynomial<9> p5 { c5 };

	EXPECT_EQ(p5.degree, 5);
	EXPECT_EQ(p5[0], 511);
	EXPECT_EQ(p5[1], 0);
	EXPECT_EQ(p5[2], 0);
	EXPECT_EQ(p5[3], 1);
	EXPECT_EQ(p5[4], 0);
	EXPECT_EQ(p5[5], 17);
	EXPECT_EQ(p5[6], 0);
	EXPECT_EQ(p5[7], 0);
}

TEST(PolynomialTest, Evaluation) {
	std::vector<GF<>> c0;
	Polynomial<> p0 { c0 };

	EXPECT_EQ(p0(0), 0);
	EXPECT_EQ(p0(1), 0);
	EXPECT_EQ(p0(2), 0);

	std::vector<GF<>> c1 = { 0, 1 };
	Polynomial<> p1 { c1 };

	EXPECT_EQ(p1(0), 0);
	EXPECT_EQ(p1(1), 1);
	EXPECT_EQ(p1(2), 0);

	std::vector<GF<2>> c2 = { 0, 1, 2, 3 };
	Polynomial<2> p2 { c2 };

	EXPECT_EQ(p2(0), 0);
	EXPECT_EQ(p2(1), 2);
	EXPECT_EQ(p2(2), 2);
	EXPECT_EQ(p2(3), 2);
	EXPECT_EQ(p2(4), 0);

	std::vector<GF<8>> c3 = { 253, 1, 2 };
	Polynomial<8> p3 { c3 };

	EXPECT_EQ(p3(0), 253);
	EXPECT_EQ(p3(1), 0);
	EXPECT_EQ(p3(2), 7);
	EXPECT_EQ(p3(256), 253);
}

} // namespace test
} // namespace galois
} // namespace reed_solomon
