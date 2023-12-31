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

TEST(GaloisFieldTest, Inverse) {
	for (int i = 1; i < 256; i++) {
		GF gf = i;
		EXPECT_EQ(gf.inv() * gf, 1);
	}
}

TEST(GaloisFieldTest, FromBytes) {
	uint8_t buff0[] = { 0x00, 0x01, 0x02, 0xff, 0xfe, 0x00 };

	std::vector<GF> r0 = GF::from_bytes(1, buff0);
	EXPECT_EQ(r0.size(), 1);
	EXPECT_EQ(r0[0], 0);

	std::vector<GF> r1 = GF::from_bytes(6, buff0);
	EXPECT_EQ(r1.size(), 6);
	EXPECT_EQ(r1[0], 0);
	EXPECT_EQ(r1[1], 1);
	EXPECT_EQ(r1[2], 2);
	EXPECT_EQ(r1[3], 0xff);
	EXPECT_EQ(r1[4], 0xfe);
	EXPECT_EQ(r1[5], 0);

	std::vector<GF> r2 = GF::from_bytes(3, buff0 + 3);
	EXPECT_EQ(r2.size(), 3);
	EXPECT_EQ(r2[0], 0xff);
	EXPECT_EQ(r2[1], 0xfe);
	EXPECT_EQ(r2[2], 0);
}

TEST(GaloisFieldTest, ToBytes) {
	uint8_t buff0[4];

	std::vector<GF> v0 = { 0x00 };
	GF::to_bytes(v0, buff0);
	EXPECT_EQ(buff0[0], 0);

	std::vector<GF> v1 = { 0x00, 0xff, 0xfe, 0x00 };
	GF::to_bytes(v1, buff0);
	EXPECT_EQ(buff0[0], 0);
	EXPECT_EQ(buff0[1], 0xff);
	EXPECT_EQ(buff0[2], 0xfe);
	EXPECT_EQ(buff0[3], 0);

	std::vector<GF> v2 = { 0x01, 0x10 };
	GF::to_bytes(v2, buff0 + 2);
	EXPECT_EQ(buff0[2], 1);
	EXPECT_EQ(buff0[3], 0x10);
}

} // namespace test
} // namespace galois
} // namespace reed_solomon
