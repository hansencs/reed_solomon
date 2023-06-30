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

} // namespace polynomial_test
} // namespace galois
} // namespace reed_solomon
