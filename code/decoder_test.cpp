#include "gtest/gtest.h"

#include "code/decoder.h"
#include "galois/galois_field.h"

namespace reed_solomon {
namespace code {
namespace decoder_test {

using namespace galois;

TEST(DecoderTest, N1K1) {
	Decoder d { 1, 1 };
	uint8_t data_in, data_out;
	for (int i = 0; i < 256; i++) {
		data_in = i;
		// solve: 0^0 * a = i
		d.decode(&data_in, &data_out);

		EXPECT_EQ(data_out, i);
	}
}

TEST(EncoderTest, N2K1) {
	Decoder d { 2, 1 };
	uint8_t missing_flags[2];
	uint8_t data_in[2];
	uint8_t data_out[1];
	for (int i = 0; i < 256; i++) {
		// solve:
		// 0^0 * a = i
		// 1^0 * a = i

		// only first equation
		data_in[0] = i;
		data_in[1] = 0;
		missing_flags[0] = 0;
		missing_flags[1] = 1;
		d.decode(data_in, missing_flags, data_out);

		EXPECT_EQ(data_out[0], i);

		// only second equation
		data_in[0] = 0;
		data_in[1] = i;
		missing_flags[0] = 1;
		missing_flags[1] = 0;
		d.decode(data_in, missing_flags, data_out);

		EXPECT_EQ(data_out[0], i);

		// both equations
		data_in[0] = i;
		data_in[1] = i;
		missing_flags[0] = 0;
		missing_flags[1] = 0;
		d.decode(data_in, missing_flags, data_out);

		EXPECT_EQ(data_out[0], i);
	}
}

TEST(DecoderTest, N2K2) {
	Decoder d { 2, 2 };
	uint8_t data_in[2];
	uint8_t data_out[2];
	for (int i = 0; i < 256; i++) {
		data_in[0] = i;
		for (int j = 0; j < 256; j++) {
			data_in[1] = j;
			// solve:
			// 0^1 * b + 0^0 * a = i
			// 1^1 * b + 1^0 * a = j
			d.decode(data_in, data_out);

			EXPECT_EQ(data_out[0], i);
			EXPECT_EQ(data_out[1], (GF(i) + GF(j)).value());
		}
	}
}

} // namespace encoder_test
} // namespace code
} // namespace reed_solomon
