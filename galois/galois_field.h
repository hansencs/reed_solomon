namespace reed_solomon {
namespace galois {

// precondition: P is a prime power
template <unsigned P = 2>
class GF {
public:
	const unsigned value;

	GF(void) : value { 0 } {};

	GF(unsigned value) : value { value % P } {};

	inline friend bool operator==(const GF<P> &lhs, const GF<P> &rhs) {
		return lhs.value == rhs.value;
	}

	inline friend bool operator!=(const GF<P> &lhs, const GF<P> &rhs) {
		return !(lhs == rhs);
	}

	inline friend GF<P> operator+(const GF<P> &lhs, const GF<P> &rhs) {
		return { lhs.value + rhs.value };
	}

	inline friend GF<P> operator*(const GF<P> &lhs, const GF<P> &rhs) {
		return { lhs.value * rhs.value };
	}
};

} // namespace galois
} // namespace reed_solomon
