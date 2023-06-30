#ifndef _CODE__DECODER_H_
#define _CODE__DECODER_H_

#include "galois/solve.h"

namespace reed_solomon {
namespace code {

class Decoder {
public:
	// precondition: k <= n <= 256
	Decoder(unsigned n, unsigned k);

	// precondition: length data_in >= n, length data_out >= k
	void decode(const uint8_t *data_in, uint8_t *data_out) const;

	// precondition:
	//	length data_in >= n,
	//	length data_out >= k,
	//	length missing_flags >= n
	//	missing_flags has at most n - k nonzero entries
	void decode(
		const uint8_t *data_in,
		const uint8_t *missing_flags,
		uint8_t *data_out) const;

private:
	unsigned n;
	unsigned k;
	galois::LinearSystem ls;
};

} // namespace code
} // namespace reed_solomon

#endif // _CODE__DECODER_H_
