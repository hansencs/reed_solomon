#ifndef _GALOIS__GALOIS_FIELD_H_
#define _GALOIS__GALOIS_FIELD_H_

namespace reed_solomon {
namespace galois {

#include <iostream>
// precondition: 0 < Q <= 32
template <uint32_t Q = 1>
class GF {
	/*
public:
	static const uint64_t P = 1 << Q;

	GF(void) : _value { 0 } {};

	GF(uint32_t value) : _value { (uint32_t) (value % P) } {};

	uint32_t value(void) const {
		return _value;
	}

	// EQUALITY

	inline friend bool operator==(const GF<Q> &lhs, const GF<Q> &rhs) {
		return lhs._value == rhs._value;
	}

	inline friend bool operator!=(const GF<Q> &lhs, const GF<Q> &rhs) {
		return !(lhs == rhs);
	}

	inline friend bool operator==(const GF<Q> &lhs, uint32_t rhs) {
		return lhs._value == rhs;
	}

	inline friend bool operator!=(const GF<Q> &lhs, uint32_t rhs) {
		return !(lhs == rhs);
	}

	inline friend bool operator==(uint32_t lhs, const GF<Q> &rhs) {
		return lhs == rhs._value;
	}

	inline friend bool operator!=(uint32_t lhs, const GF<Q> &rhs) {
		return !(lhs == rhs);
	}

	// BINARY OPS

	inline friend GF<Q> operator+(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs._value + rhs._value };
	}

	inline friend GF<Q> operator+=(GF<Q> &lhs, const GF<Q> &rhs) {
		lhs = { lhs._value + rhs._value };
		return lhs;
	}

	inline friend GF<Q> operator*(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs._value * rhs._value };
	}

	inline friend GF<Q> operator*=(GF<Q> &lhs, const GF<Q> &rhs) {
		lhs = { lhs._value * rhs._value };
		return lhs;
	}

private:
	uint32_t _value;
	*/
};

} // namespace galois
} // namespace reed_solomon

#endif // _GALOIS__GALOIS_FIELD_H_
