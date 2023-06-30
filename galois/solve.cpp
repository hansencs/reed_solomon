#include <cassert>

#include "galois/solve.h"

namespace reed_solomon {
namespace galois {

LinearSystem::LinearSystem(
		unsigned n,
		unsigned k,
		const std::vector<std::vector<GF>> &equations)
	: equations{ equations }
{
	assert(equations.size() == n);
	for (auto cv : equations)
		assert(cv.size() == k);
}

std::vector<GF> LinearSystem::solve(std::vector<std::optional<GF>> values) {
	return { *values[0] };
}

} // namespace galois
} // namespace reed_solomon
