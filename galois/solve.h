#ifndef _GALOIS__SOLVE_H_
#define _GALOIS__SOLVE_H_

#include <optional>
#include <vector>

#include "galois/galois_field.h"

namespace reed_solomon {
namespace galois {

class LinearSystem {
public:
	LinearSystem(
		unsigned n,
		unsigned k,
		const std::vector<std::vector<GF>> &terms);

	std::vector<GF> solve(std::vector<std::optional<GF>> values);

private:
	unsigned k;
	std::vector<std::vector<GF>> terms;
};

} // namespace galois
} // namespace reed_solomon

#endif
