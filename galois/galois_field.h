namespace reed_solomon {
namespace galois {

#define P (1 << Q)

template <unsigned Q = 1>
class GF {
public:
	const unsigned value;

	GF(void) : value { 0 } {};

	GF(unsigned value) : value { value % P } {};

	inline friend bool operator==(const GF<Q> &lhs, const GF<Q> &rhs) {
		return lhs.value == rhs.value;
	}

	inline friend bool operator!=(const GF<Q> &lhs, const GF<Q> &rhs) {
		return !(lhs == rhs);
	}

	inline friend GF<Q> operator+(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs.value + rhs.value };
	}

	inline friend GF<Q> operator*(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs.value * rhs.value };
	}
};

} // namespace galois
} // namespace reed_solomon
