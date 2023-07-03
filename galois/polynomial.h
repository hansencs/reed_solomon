#ifndef _GALOIS__POLYNOMIAL_H_
#define _GALOIS__POLYNOMIAL_H_

#include <vector>

#include "galois/galois_field.h"

namespace reed_solomon {
namespace galois {

class Polynomial {
public:
	Polynomial(const std::vector<GF> &coefficients);
	int degree(void) const;
	GF operator[](unsigned i) const;
	GF operator()(GF x) const;

private:
	std::vector<GF> coefficients;
};

} // namespace galois
} // namespace reed_solomon

#endif // _GALOIS__POLYNOMIAL_H_
