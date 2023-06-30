#include "gtest/gtest.h"
#include <vector>

#include "galois/solve.h"

namespace reed_solomon {
namespace galois {
namespace solve_test {

typedef std::vector<std::vector<GF>> EV;
typedef std::vector<std::optional<GF>> OV;
typedef std::vector<GF> GV;

TEST(LinearSystemTest, SolveTrivial) {
	EV e0 = { { 1 } };
	LinearSystem s0 = { 1, 1, e0 };

	OV v0 = { { 0 } };
	GV r0 = s0.solve(v0);
	EXPECT_EQ(r0.size(), 1);
	EXPECT_EQ(r0[0], 0);

	OV v1 = { { 1 } };
	GV r1 = s0.solve(v1);
	EXPECT_EQ(r1.size(), 1);
	EXPECT_EQ(r1[0], 1);

	OV v2 = { { 2 } };
	GV r2 = s0.solve(v2);
	EXPECT_EQ(r2.size(), 1);
	EXPECT_EQ(r2[0], 2);
}

TEST(LinearSystemTest, SolveN1K1) {
	EV e0 = { { 2 } };
	LinearSystem s0 = { 1, 1, e0 };

	OV v0 = { { 0 } };
	GV r0 = s0.solve(v0);
	EXPECT_EQ(r0.size(), 1);
	EXPECT_EQ(r0[0], 0);

	OV v1 = { { 4 } };
	GV r1 = s0.solve(v1);
	EXPECT_EQ(r1.size(), 1);
	EXPECT_EQ(r1[0], 2);

	OV v2 = { { 0x1b } };
	GV r2 = s0.solve(v2);
	EXPECT_EQ(r2.size(), 1);
	EXPECT_EQ(r2[0], 0x80);

	EV e1 = { { 6 } };
	LinearSystem s1 = { 1, 1, e1 };

	OV v3 = { { 0 } };
	GV r3 = s1.solve(v3);
	EXPECT_EQ(r3.size(), 1);
	EXPECT_EQ(r3[0], 0);

	OV v4 = { { 0xc } };
	GV r4 = s1.solve(v4);
	EXPECT_EQ(r4.size(), 1);
	EXPECT_EQ(r4[0], 2);

	OV v5 = { { 0xa } };
	GV r5 = s1.solve(v5);
	EXPECT_EQ(r5.size(), 1);
	EXPECT_EQ(r5[0], 3);
}

TEST(LinearSystemTest, SolveN2K2) {
	EV e0 = { { 1, 1 }, { 1, 2 } };
	LinearSystem s0 = { 2, 2, e0 };

	OV v0 = { { 0 }, { 0 } };
	GV r0 = s0.solve(v0);
	EXPECT_EQ(r0.size(), 2);
	EXPECT_EQ(r0[0], 0);
	EXPECT_EQ(r0[1], 0);

	OV v1 = { { 1 }, { 1 } };
	GV r1 = s0.solve(v1);
	EXPECT_EQ(r1.size(), 2);
	EXPECT_EQ(r1[0], 1);
	EXPECT_EQ(r1[1], 0);

	OV v2 = { { 0x7f }, { 0xef } };
	GV r2 = s0.solve(v2);
	EXPECT_EQ(r2.size(), 2);
	EXPECT_EQ(r2[0], 0xf);
	EXPECT_EQ(r2[1], 0x70);
}

TEST(LinearSystemTest, SolveN2K1) {
	EV e0 = { { 1 }, { 2 } };
	LinearSystem s0 = { 2, 1, e0 };

	OV v0 = { { 3 }, { 6 } };
	GV r0 = s0.solve(v0);
	EXPECT_EQ(r0.size(), 1);
	EXPECT_EQ(r0[0], 3);

	OV v1 = { { 3 }, { } };
	GV r1 = s0.solve(v1);
	EXPECT_EQ(r1.size(), 1);
	EXPECT_EQ(r1[0], 3);

	OV v2 = { { }, { 6 } };
	GV r2 = s0.solve(v2);
	EXPECT_EQ(r2.size(), 1);
	EXPECT_EQ(r2[0], 3);
}

} // namespace polynomial_test
} // namespace galois
} // namespace reed_solomon
