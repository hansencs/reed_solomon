#include "galois/polynomial.h"

namespace reed_solomon {
namespace galois {

Polynomial::Polynomial(const std::vector<GF> &c) {
	auto last = c.end();
	for (; last != c.begin(); last--) {
		if (*(last - 1) != 0) break;
	}
	coefficients = { c.begin(), last };
}

int Polynomial::degree(void) const {
	return coefficients.size() - 1;
}

GF Polynomial::operator[](unsigned i) const {
	return i < coefficients.size() ? coefficients[i] : 0;
}

} // namespace galois
} // namespace reed_solomon
