#include <cassert>

#include "galois/solve.h"

using namespace std;

namespace reed_solomon {
namespace galois {

LinearSystem::LinearSystem(
	unsigned n,
	unsigned k,
	const vector<vector<GF>> &terms)
	: k { k },
	terms { terms }
{
	assert(terms.size() == n);
	for (auto cv : terms)
		assert(cv.size() == k);
}

typedef struct equation_s {
	vector<GF> terms;
	GF value;
} Equation;

static inline void remove_entry(
	unsigned idx, const Equation &update_equation, Equation &target_equation)
{
	GF multiplier =
		update_equation.terms[idx].inv() * target_equation.terms[idx];
	for (int i = idx; i < target_equation.terms.size(); i++)
		target_equation.terms[i] += multiplier * update_equation.terms[i];
	target_equation.value += multiplier * update_equation.value;
}

static inline void plug_in_solve(
	unsigned idx, vector<GF> &solutions, const Equation &equation)
{
	auto value = equation.value;
	for (int i = equation.terms.size() - 1; i > idx; i--)
		value += solutions[i] * equation.terms[i];
	solutions[idx] = value * equation.terms[idx].inv();
}

// PUT VALUE AND TERMS IN ONE OBJECT
vector<GF> LinearSystem::solve(vector<optional<GF>> values) const {
	vector<Equation> equations;
	for (int i = 0; equations.size() < k; i++) {
		if (values[i].has_value())
			equations.push_back({ .terms = terms[i], .value = *values[i] });
	}
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; equations[i].terms[i] == 0; j++) {
			if (equations[j].terms[i] != 0) {
				auto temp_e = std::move(equations[i]);
				equations[i] = std::move(equations[j]);
				equations[j] = std::move(temp_e);
			}
		}
		for (int j = i + 1; j < k; j++)
			remove_entry(i, equations[i], equations[j]);
	}
	vector<GF> solutions;
	solutions.resize(k);
	for (int i = k - 1; i >= 0; i--)
		plug_in_solve(i, solutions, equations[i]);
	return solutions;
}

} // namespace galois
} // namespace reed_solomon
