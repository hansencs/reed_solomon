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
}

TEST(GaloisFieldTest, Multiplication) {
	/*
	GF<4> gf16_0;
	GF<4> gf16_1 = 1;
	GF<4> gf16_3 = 3;
	GF<4> gf16_7 = 7;
	GF<4> gf16_24 = 24;

	EXPECT_EQ(gf16_0 * gf16_1, gf16_0);
	EXPECT_EQ(gf16_0 * gf16_7, gf16_0);
	EXPECT_EQ(gf16_1 * gf16_1, gf16_1);
	EXPECT_EQ(gf16_1 * gf16_7, gf16_7);
	EXPECT_EQ(gf16_7 * gf16_7, gf16_1);

	GF<4> x = 5;

	EXPECT_EQ(x * 3, 15);
	EXPECT_EQ(3 * x, 15);

	EXPECT_EQ(x *= 4, 4);
	EXPECT_EQ(x, 4);

	EXPECT_EQ(x *= GF<4>(2), 8);
	EXPECT_EQ(x, 8);
	*/
}

} // namespace test
} // namespace galois
} // namespace reed_solomon
