#include <cassert>
#include <vector>

#include "code/encoder.h"
#include "galois/polynomial.h"


namespace reed_solomon {
namespace code {

using namespace galois;

Encoder::Encoder(unsigned n, unsigned k) : n { n }, k { k } {
	assert(n <= 256);
	assert(k <= n);
}

void Encoder::encode(const uint8_t *data_in, uint8_t *data_out) const {
	Polynomial message_poly { GF::from_bytes(k, data_in) };
	for (int i = 0; i < n; i++)
		data_out[i] = message_poly(static_cast<uint8_t>(i)).value();
}

} // namespace code
} // namespace reed_solomon
