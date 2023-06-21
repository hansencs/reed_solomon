#ifndef _GALOIS__GALOIS_FIELD_H_
#define _GALOIS__GALOIS_FIELD_H_

namespace reed_solomon {
namespace galois {

#define P (1 << Q)

// precondition: 0 < Q <= 32
template <unsigned Q = 1>
class GF {
public:
	const unsigned value;

	GF(void) : value { 0 } {};

	GF(unsigned value) : value { value % P } {};

	// EQUALITY

	inline friend bool operator==(const GF<Q> &lhs, const GF<Q> &rhs) {
		return lhs.value == rhs.value;
	}

	inline friend bool operator!=(const GF<Q> &lhs, const GF<Q> &rhs) {
		return !(lhs == rhs);
	}

	inline friend bool operator==(const GF<Q> &lhs, unsigned rhs) {
		return lhs.value == rhs;
	}

	inline friend bool operator!=(const GF<Q> &lhs, unsigned rhs) {
		return !(lhs == rhs);
	}

	inline friend bool operator==(unsigned lhs, const GF<Q> &rhs) {
		return lhs == rhs.value;
	}

	inline friend bool operator!=(unsigned lhs, const GF<Q> &rhs) {
		return !(lhs == rhs);
	}

	// BINARY OPS

	inline friend GF<Q> operator+(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs.value + rhs.value };
	}

	inline friend GF<Q> operator*(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs.value * rhs.value };
	}
};

} // namespace galois
} // namespace reed_solomon

#endif // _GALOIS__GALOIS_FIELD_H_
