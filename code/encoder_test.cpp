#include "gtest/gtest.h"

#include "code/encoder.h"

namespace reed_solomon {
namespace code {
namespace encoder_test {

TEST(EncoderTest, N1K1) {
	Encoder e { 1, 1 };

	uint8_t data_in, data_out;
	for (int i = 0; i < 256; i++) {
		data_in = i;
		// polynomial: x^0 * i
		// evaluate at: x = 0
		e.encode(&data_in, &data_out);

		EXPECT_EQ(data_out, data_in);
	}
}

} // namespace encoder_test
} // namespace code
} // namespace reed_solomon
