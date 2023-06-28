#include "gtest/gtest.h"

#include "galois/galois_field.h"

namespace reed_solomon {
namespace galois {
namespace field_test {

TEST(GaloisFieldTest, Construction) {
	GF gf0;

	EXPECT_EQ(gf0, 0);
	EXPECT_EQ(gf0.value(), 0);
	
	GF gf1 = 1;

	EXPECT_EQ(gf1, 1);
	EXPECT_EQ(gf1.value(), 1);

	GF gf2 = 255;

	EXPECT_EQ(gf2, 255);
	EXPECT_EQ(gf2.value(), 255);
}

TEST(GaloisFieldTest, Addition) {
	GF gf0;
	GF gf1 = 1;
	GF gf2 = 0x52;
	GF gf3 = 0x43;

	EXPECT_EQ(gf0 + gf0, gf0);
	EXPECT_EQ(gf1 + gf0, gf1);
	EXPECT_EQ(gf2 + gf0, gf2);
	EXPECT_EQ(gf3 + gf0, gf3);

	EXPECT_EQ(gf2 + gf1, 0x53);
	EXPECT_EQ(gf3 + gf1, 0x42);

	EXPECT_EQ(gf2 + gf3, 0x11);

	EXPECT_EQ(gf3 + 0, gf3);
	EXPECT_EQ(gf3 + 1, gf3 + gf1);
	EXPECT_EQ(gf3 + 0x52, gf3 + gf2);

	GF gf4 = 7;
	EXPECT_EQ(gf4 += 3, 4);
	EXPECT_EQ(gf4, 4);
	EXPECT_EQ(gf4 += gf1, 5);
	EXPECT_EQ(gf4, 5);
	EXPECT_EQ(gf1, 1);
}

TEST(GaloisFieldTest, Multiplication) {
	GF gf0;
	GF gf1 = 1;
	GF gf2 = 2;
	GF gf3 = 3;
	GF gf4 = 4;
	GF gf5 = 0x22;
	GF gf6 = 0x44;
	GF gf7 = 0x80;

	EXPECT_EQ(gf0 * gf0, gf0);
	EXPECT_EQ(gf1 * gf0, gf0);
	EXPECT_EQ(gf5 * gf0, gf0);

	EXPECT_EQ(gf0 * gf1, gf0);
	EXPECT_EQ(gf1 * gf1, gf1);
	EXPECT_EQ(gf5 * gf1, gf5);

	EXPECT_EQ(gf0 * gf2, gf0);
	EXPECT_EQ(gf1 * gf2, gf2);
	EXPECT_EQ(gf2 * gf2, gf4);
	EXPECT_EQ(gf5 * gf2, gf6);
	EXPECT_EQ(gf3 * gf3, 5);

	EXPECT_EQ(gf7 * gf2, 0x1b);
	EXPECT_EQ(gf7 * gf3, 0x9b);

	GF gf8 = 3;
	EXPECT_EQ(gf8 *= 3, 5);
	EXPECT_EQ(gf8, 5);
	EXPECT_EQ(gf8 *= gf2, 0x0a);
	EXPECT_EQ(gf8, 0x0a);
	EXPECT_EQ(gf2, 2);
}

TEST(GaloisFieldTest, Division) {
	GF gf0;
	GF gf1 = 1;
	GF gf2 = 2;
	GF gf3 = 3;
	GF gf4 = 4;

	DivResult r0 = gf0 / gf1;
	EXPECT_EQ(r0.q, gf0);
	EXPECT_EQ(r0.r, gf0);
	DivResult r1 = gf0 / gf2;
	EXPECT_EQ(r1.q, gf0);
	EXPECT_EQ(r1.r, gf0);

	DivResult r2 = gf1 / gf1;
	EXPECT_EQ(r2.q, gf1);
	EXPECT_EQ(r2.r, gf0);
	DivResult r3 = gf3 / gf1;
	EXPECT_EQ(r3.q, gf3);
	EXPECT_EQ(r3.r, gf0);

	DivResult r4 = gf4 / gf2;
	EXPECT_EQ(r4.q, gf2);
	EXPECT_EQ(r4.r, gf0);

	DivResult r5 = gf3 / gf2;
	EXPECT_EQ(r5.q, gf1);
	EXPECT_EQ(r5.r, gf1);

	DivResult r6 = gf4 / gf3;
	EXPECT_EQ(r6.q, gf3);
	EXPECT_EQ(r6.r, gf1);

	DivResult r7 = gf3 / gf4;
	EXPECT_EQ(r7.q, gf0);
	EXPECT_EQ(r7.r, gf3);
}

TEST(GaloisFieldTest, EuclideanAlgorithm) {
	GF gf1 = 1;
	GF gf2 = 2;
	GF gf3 = 3;
	GF gf4 = 4;
	GF gf7 = 7;

	GF r0 = gf1.euc_alg(gf1);
	EXPECT_EQ(r0, gf1);
	GF r1 = gf2.euc_alg(gf2);
	EXPECT_EQ(r1, gf2);
	GF r2 = gf3.euc_alg(gf3);
	EXPECT_EQ(r2, gf3);

	GF r3 = gf2.euc_alg(gf1);
	EXPECT_EQ(r3, gf1);
	GF r4 = gf1.euc_alg(gf2);
	EXPECT_EQ(r4, gf1);
	GF r5 = gf3.euc_alg(gf1);
	EXPECT_EQ(r5, gf1);

	GF r6 = gf3.euc_alg(gf3 * gf4);
	EXPECT_EQ(r6, gf3);
	GF r7 = (gf3 * gf4).euc_alg(gf3);
	EXPECT_EQ(r7, gf3);

	GF r8 = (gf3 * gf4).euc_alg(gf3 * gf7 * gf2);
	EXPECT_EQ(r8, gf3 * gf2);
	GF r9 = (gf3 * gf7 * gf2).euc_alg(gf3 * gf4);
	EXPECT_EQ(r9, gf3 * gf2);
}

} // namespace test
} // namespace galois
} // namespace reed_solomon
