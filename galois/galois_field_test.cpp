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

	GF gf255 = 255;

	EXPECT_EQ(gf255, 255);
	EXPECT_EQ(gf255.value(), 255);
}

TEST(GaloisFieldTest, PrimitiveEquality) {
	/*
	EXPECT_EQ(GF<>(0), 0);
	EXPECT_NE(GF<>(0), 1);
	EXPECT_NE(GF<>(0), 2);

	EXPECT_EQ(0, GF<>(0));
	EXPECT_NE(1, GF<>(0));
	EXPECT_NE(2, GF<>(0));

	EXPECT_EQ(GF<3>(7), 7);
	EXPECT_NE(GF<3>(7), 6);
	EXPECT_NE(GF<3>(7), 15);

	EXPECT_EQ(7, GF<3>(7));
	EXPECT_NE(6, GF<3>(7));
	EXPECT_NE(15, GF<3>(7));
	*/
}

TEST(GaloisFieldTest, Addition) {
	/*
	GF<3> gf8_0;
	GF<3> gf8_1 = 1;
	GF<3> gf8_3 = 3;
	GF<3> gf8_6 = 6;

	EXPECT_EQ(gf8_0 + gf8_1, gf8_1);
	EXPECT_EQ(gf8_3 + gf8_6, gf8_1);

	GF<3> x = 4;

	EXPECT_EQ(x + 3, 7);
	EXPECT_EQ(3 + x, 7);

	EXPECT_EQ(x += 3, 7);
	EXPECT_EQ(x, 7);

	EXPECT_EQ(x += GF<3>(2), 1);
	EXPECT_EQ(x, 1);
	*/
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
