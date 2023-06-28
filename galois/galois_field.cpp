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

GF GF::euc_alg(const GF &other) const {
	assert(*this != 0);
	assert(other != 0);

	GF a = *this, b = other;
	do {
		DivResult result = a / b;
		a = b;
		b = result.r;
	} while (b != 0);
	return a;
}

} // namespace galois
} // namespace reed_solomon
