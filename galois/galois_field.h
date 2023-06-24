#ifndef _GALOIS__GALOIS_FIELD_H_
#define _GALOIS__GALOIS_FIELD_H_

namespace reed_solomon {
namespace galois {

#include <iostream>
// precondition: 0 < Q <= 32
template <uint32_t Q = 1>
class GF {
public:
	static const uint64_t P = 1 << Q;

	static GF load(const void *data, uint32_t index) {
		const uint8_t *const byte_data = (const uint8_t *) data;
		const uint32_t bit_offset = Q * index;
		const uint32_t byte_offset = bit_offset % 8;

		uint32_t byte_index = bit_offset / 8;
		uint32_t result = 0;
		int loaded = 8 - byte_offset;
		uint32_t next_byte = byte_data[byte_index++];
		result |= next_byte >> byte_offset;
		while (loaded < Q) {
			uint32_t next_byte = byte_data[byte_index++];
			result |= next_byte << loaded;
			loaded += 8;
		}

		const uint32_t mask = ~(((uint32_t ) 0xffffffff) << Q);
		return { result & mask };
	}

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
};

} // namespace galois
} // namespace reed_solomon

#endif // _GALOIS__GALOIS_FIELD_H_
