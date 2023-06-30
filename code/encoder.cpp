#include <cassert>

#include "code/encoder.h"

namespace reed_solomon {
namespace code {

Encoder::Encoder(unsigned n, unsigned k) {
	assert(n <= 256);
	assert(k <= n);
}

void Encoder::encode(const uint8_t *data_in, uint8_t *data_out) const {
	*data_out = *data_in;
}

} // namespace code
} // namespace reed_solomon
