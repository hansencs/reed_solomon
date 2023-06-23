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
		std::cout << "load" << std::endl;
		const uint8_t *const byte_data = (const uint8_t *) data;
		const uint32_t bit_offset = Q * index;
		const uint32_t byte_offset = bit_offset % 8;
		std::cout << "bit off " << bit_offset << " byte off: " << byte_offset << std::endl;

		uint32_t byte_index = bit_offset / 8;
		uint32_t result = 0;
		int loaded = 8 - byte_offset;
		std::cout << "initial byte index: " << byte_index << std::endl;
		uint32_t next_byte = byte_data[byte_index++];
		std::cout << "initial loaded: " << loaded << " initial byte: "<< next_byte << std::endl;
		result |= next_byte >> byte_offset;
		while (loaded < Q) {
			uint32_t next_byte = byte_data[byte_index++];
			result |= next_byte << loaded;
			loaded += 8;
		}

		const uint32_t mask = ~(((uint32_t ) 0xffffffff) << Q);
		return { result & mask };
	}

	const uint32_t value;

	GF(void) : value { 0 } {};

	GF(uint32_t value) : value { (uint32_t) (value % P) } {};

	// EQUALITY

	inline friend bool operator==(const GF<Q> &lhs, const GF<Q> &rhs) {
		return lhs.value == rhs.value;
	}

	inline friend bool operator!=(const GF<Q> &lhs, const GF<Q> &rhs) {
		return !(lhs == rhs);
	}

	inline friend bool operator==(const GF<Q> &lhs, uint32_t rhs) {
		return lhs.value == rhs;
	}

	inline friend bool operator!=(const GF<Q> &lhs, uint32_t rhs) {
		return !(lhs == rhs);
	}

	inline friend bool operator==(uint32_t lhs, const GF<Q> &rhs) {
		return lhs == rhs.value;
	}

	inline friend bool operator!=(uint32_t lhs, const GF<Q> &rhs) {
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
