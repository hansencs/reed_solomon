#include <cassert>

#include "galois/galois_field.h"

#define P 0x011b

namespace reed_solomon {
namespace galois {

static inline uint8_t modulus(uint16_t v) {
	for (int i = 7; i >= 0; i--) {
		if (1 & (v >> (8 + i))) {
			v ^= P << i;
		}
	}
	return static_cast<uint8_t>(v);
}

GF::GF(void) : _value { 0 } {};

GF::GF(uint8_t value) : _value { value } {};

uint8_t GF::value(void) const {
	return _value;
}

GF GF::operator*(const GF &rhs) const {
	uint16_t result = 0;
	for (int i = 0; i < 8; i++) {
		if (1 & (_value >> i))
			result ^= rhs._value << i;
	}
	return modulus(result);
}

GF GF::operator*=(const GF &rhs) {
	*this = *this * rhs;
	return *this;
}

static inline int degree(uint8_t v) {
	int d = 7;
	for (; !(1 & (v >> d)) && d >= 0; d--);
	return d;
}

DivResult GF::operator/(const GF &rhs) const {
	assert(rhs != 0);

	uint8_t q = 0, r = _value;
	int d = degree(rhs._value);
	for (int i = 7; i >= d; i--) {
		if (1 & (r >> i)) {
			int j = i - d;
			q ^= 1 << j;
			r ^= rhs._value << j;
		}
	}
	return { q, r };
}

// precondition: divisor has degree 7 or lower
static inline void div16(
		uint16_t dividend, uint16_t divisor, uint16_t &q_out, uint16_t &r_out)
{
	assert(divisor != 0);

	uint16_t q = 0, r = dividend;
	int d = degree(static_cast<uint8_t>(divisor));
	for (int i = 8; i >= d; i--) {
		if (1 & (r >> i)) {
			int j = i - d;
			q ^= 1 << j;
			r ^= divisor << j;
		}
	}
	q_out = q;
	r_out = r;
}

GF GF::inv(void) const {
	// special case 1 as the quotient does not fit in a GF element
	if (_value == 1) return _value;

	// logical i = 0
	uint16_t ri = P, rip1 = _value, divq, divr;
	div16(ri, rip1, divq, divr);

	// logical i = 1
	ri = rip1;
	rip1 = divr;
	GF tim1 = 0, ti = 1, tip1 = tim1 + ti * GF(static_cast<uint8_t>(divq));

	while (rip1 != 0) {
		div16(ri, rip1, divq, divr);

		// logical increment i
		ri = rip1;
		rip1 = divr;
		tim1 = ti;
		ti = tip1;
		tip1 = tim1 + ti * GF(static_cast<uint8_t>(divq));
	} 

	return ti;
}

} // namespace galois
} // namespace reed_solomon
