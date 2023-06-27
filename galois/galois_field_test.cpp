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
}

TEST(GaloisFieldTest, Multiplication) {
	GF gf0;
	GF gf1 = 1;
	GF gf2 = 2;
	GF gf3 = 4;
	GF gf4 = 0x22;
	GF gf5 = 0x44;
	GF gf6 = 3;
	GF gf7 = 0x80;

	EXPECT_EQ(gf0 * gf0, gf0);
	EXPECT_EQ(gf1 * gf0, gf0);
	EXPECT_EQ(gf4 * gf0, gf0);

	EXPECT_EQ(gf0 * gf1, gf0);
	EXPECT_EQ(gf1 * gf1, gf1);
	EXPECT_EQ(gf4 * gf1, gf4);

	EXPECT_EQ(gf0 * gf2, gf0);
	EXPECT_EQ(gf1 * gf2, gf2);
	EXPECT_EQ(gf2 * gf2, gf3);
	EXPECT_EQ(gf4 * gf2, gf5);
	EXPECT_EQ(gf6 * gf6, 5);

	EXPECT_EQ(gf7 * gf2, 0x1b);
	EXPECT_EQ(gf7 * gf6, 0x9b);
}

} // namespace test
} // namespace galois
} // namespace reed_solomon
