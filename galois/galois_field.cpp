#include "galois/galois_field.h"

namespace reed_solomon {
namespace galois {

template <unsigned P>
GF<2>::GF(void) : value { 0 } {}

/*
inline bool operator==(const GF<P> &lhs, const GF<P> &rhs) {
	return lhs.value == rhs.value;
}

bool operator!=(const GF<P> &lhs, const GF<P> &rhs) {
	return !(lhs == rhs);
}
*/
int f(void) { return 1; }
} // namespace galois
} // namespace reed_solomon
