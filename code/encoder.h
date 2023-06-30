#ifndef _CODE__ENCODER_H_
#define _CODE__ENCODER_H_

namespace reed_solomon {
namespace code {

class Encoder {
public:
	// precondition: k <= n <= 256
	Encoder(unsigned n, unsigned k);

	// precondition length data_in >= k, length data_out >= n
	void encode(const uint8_t *data_in, uint8_t *data_out) const;

private:
	unsigned n;
	unsigned k;
};

} // namespace code
} // namespace reed_solomon

#endif // _CODE__ENCODER_H_
