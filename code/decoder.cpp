#include <cassert>
//#include <vector>

#include "code/decoder.h"

namespace reed_solomon {
namespace code {

using namespace galois;
using namespace std;

static inline LinearSystem init_ls(unsigned n, unsigned k) {
	vector<vector<GF>> ls_terms;
	for (int i = 0; i < n; i++) {
		vector<GF> equation_terms;
		const GF x = static_cast<uint8_t>(i);
		GF px = 1;
		for (int j = 0; j < k; j++) {
			equation_terms.push_back(px);
			px *= x;
		}
		ls_terms.push_back(equation_terms);
	}
	return { n, k, move(ls_terms) };
}

Decoder::Decoder(unsigned n, unsigned k) :
	n { n },
	k { k },
	ls { init_ls(n, k) }
{
	assert(n <= 256);
	assert(k <= n);
}

void Decoder::decode(const uint8_t *data_in, uint8_t *data_out) const {
	vector<optional<GF>> values;
	for (int i = 0; i < n; i++)
		values.push_back({ data_in[i] });
	vector<GF> result = ls.solve(move(values));
	GF::to_bytes(result, data_out);
}

void Decoder::decode(
	const uint8_t *data_in,
	const uint8_t *missing_flags,
	uint8_t *data_out) const
{
	vector<optional<GF>> values;
	for (int i = 0; i < n; i++) {
		if (missing_flags[i])
			values.push_back({ });
		else
			values.push_back({ data_in[i] });
	}
	vector<GF> result = ls.solve(move(values));
	GF::to_bytes(result, data_out);
}

} // namespace code
} // namespace reed_solomon
