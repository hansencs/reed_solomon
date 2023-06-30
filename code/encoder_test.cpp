#include "gtest/gtest.h"

#include "code/encoder.h"
#include "galois/galois_field.h"

namespace reed_solomon {
namespace code {
namespace encoder_test {

using namespace galois;

TEST(EncoderTest, N1K1) {
	Encoder e { 1, 1 };
	uint8_t data_in, data_out;
	for (int i = 0; i < 256; i++) {
		data_in = i;
		// polynomial: x^0 * i
		// evaluate at: x = 0
		e.encode(&data_in, &data_out);

		EXPECT_EQ(data_out, i);
	}
}

TEST(EncoderTest, N2K1) {
	Encoder e { 2, 1 };
	uint8_t data_in;
	uint8_t data_out[2];
	for (int i = 0; i < 256; i++) {
		data_in = i;
		// polynomial x^0 * i
		// evalute at: x = 0, 1
		e.encode(&data_in, data_out);

		EXPECT_EQ(data_out[0], i);
		EXPECT_EQ(data_out[1], i);
	}
}

TEST(EncoderTest, N2K2) {
	Encoder e { 2, 2 };
	uint8_t data_in[2];
	uint8_t data_out[2];
	for (int i = 0; i < 256; i++) {
		data_in[0] = i;
		for (int j = 0; j < 256; j++) {
			data_in[1] = j;
			// polynomial x^1 * j + x^0 * i
			// evalute at: x = 0, 1
			e.encode(data_in, data_out);

			EXPECT_EQ(data_out[0], i);
			EXPECT_EQ(data_out[1], (GF(i) + GF(j)).value());
		}
	}
}

} // namespace encoder_test
} // namespace code
} // namespace reed_solomon
