#ifndef _GALOIS__GALOIS_FIELD_H_
#define _GALOIS__GALOIS_FIELD_H_

#include <stdint.h>

namespace reed_solomon {
namespace galois {

struct DivResult;

class GF {
public:
	GF(void);

	GF(uint8_t value);

	uint8_t value(void) const;

	/*
	static const uint64_t P = 1 << Q;


	GF(uint32_t value) : _value { (uint32_t) (value % P) } {};
	*/

	// EQUALITY

	inline friend bool operator==(const GF &lhs, const GF &rhs) {
		return lhs._value == rhs._value;
	}

	inline friend bool operator!=(const GF &lhs, const GF &rhs) {
		return !(lhs == rhs);
	}

	/*
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
	*/

	// BINARY OPS

	inline friend GF operator+(const GF &lhs, const GF &rhs) {
		return { static_cast<uint8_t>(lhs._value ^ rhs._value) };
	}

	inline friend GF operator+=(GF &lhs, const GF &rhs) {
		lhs = lhs + rhs;
		return lhs;
	}

	GF operator*(const GF &rhs) const;

	GF operator*=(const GF &rhs);

	DivResult operator/(const GF &rhs) const;

	GF euc_alg(const GF &other) const;

	/*
	inline friend GF<Q> operator*(const GF<Q> &lhs, const GF<Q> &rhs) {
		return { lhs._value * rhs._value };
	}

	inline friend GF<Q> operator*=(GF<Q> &lhs, const GF<Q> &rhs) {
		lhs = { lhs._value * rhs._value };
		return lhs;
	}

	*/
private:
	uint8_t _value;
};

struct DivResult {
	GF q;
	GF r;
};

} // namespace galois
} // namespace reed_solomon

#endif // _GALOIS__GALOIS_FIELD_H_
