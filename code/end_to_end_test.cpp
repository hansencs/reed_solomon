#include <cstring>
#include "gtest/gtest.h"

#include "code/encoder.h"
#include "code/decoder.h"

namespace reed_solomon {
namespace code {
namespace end_to_end_test {

using namespace galois;

TEST(EndToEndTest, N1K1) {
	Encoder e { 1, 1 };
	Decoder d { 1, 1 };
	uint8_t data_in, code, data_out;
	for (int i = 0; i < 256; i++) {
		data_in = i;
		e.encode(&data_in, &code);
		d.decode(&code, &data_out);

		EXPECT_EQ(data_in, data_out);
	}
}

static inline void test_erasures(
	unsigned n,
	unsigned k,
	uint8_t *message,
	int num_erasures,
	int *erasure_locs)
{
	Encoder e { n, k };
	Decoder d { n, k };
	uint8_t code[n];
	uint8_t missing_flags[n];
	e.encode(message, code);
	memset(missing_flags, 0, sizeof(uint8_t) * n);
	for (int i = 0; i < num_erasures; i++) {
		code[erasure_locs[i]] ^= 0xff;
		missing_flags[erasure_locs[i]] = 1;
	}
	uint8_t result[k];
	d.decode(code, missing_flags, result);
	for (int i = 0; i < k; i++)
		EXPECT_EQ(result[i], message[i]);
}

static void generate_erasures(
	unsigned n,
	unsigned k,
	uint8_t *message,
	int num_erasures,
	int *erasure_locs,
	int erasure_idx)
{
	if (erasure_idx == num_erasures) {
		test_erasures(n, k, message, num_erasures, erasure_locs);
	} else {
		for (
			int loc = erasure_idx == 0 ? 0 : erasure_locs[erasure_idx - 1] + 1;
			loc < n;
			loc++)
		{
			erasure_locs[erasure_idx] = loc;
			generate_erasures(
				n, k, message, num_erasures, erasure_locs, erasure_idx + 1);
		}
	}
}

static inline void test_all_erasures(unsigned n, unsigned k, uint8_t *message) {
	for (int num_erasures = 0; num_erasures <= n - k; num_erasures++) {
		int erasure_locs[num_erasures];
		generate_erasures(n, k, message, num_erasures, erasure_locs, 0);
	}
}

TEST(EndToEndTest, N2K1) {
	for (int i = 0; i < 256; i++) {
		uint8_t message = i;
		test_all_erasures(2, 1, &message);
	}
}

TEST(EndToEndTest, N3K2) {
	uint8_t message[2];
	for (int i = 0; i < 256; i++) {
		message[0] = i;
		for (int j = 0; j < 256; j++) {
			message[1] = j;
			test_all_erasures(3, 2, message);
		}
	}
}

TEST(EndToEndTest, N10K1) {
	uint8_t message = 0x7b;
	test_all_erasures(10, 1, &message);
}

TEST(EndToEndTest, N256K254) {
	uint8_t message[254];

	for (int i = 0; i < 254; i++)
		message[i] = i;
	test_all_erasures(150, 149, message);

	/*
	for (int i = 0; i < 254; i++)
		message[i] = i / 10;
	test_all_erasures(256, 254, message);

	memset(message, 0x33, sizeof(uint8_t) * 254);
	test_all_erasures(256, 254, message);
	*/
}

} // namespace encoder_test
} // namespace code
} // namespace reed_solomon
