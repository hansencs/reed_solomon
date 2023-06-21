namespace reed_solomon {
namespace galois {

#define P (1 << Q)

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
