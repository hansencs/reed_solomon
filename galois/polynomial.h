#ifndef _GALOIS__POLYNOMIAL_H_
#define _GALOIS__POLYNOMIAL_H_

#include <vector>

#include "galois/galois_field.h"

namespace reed_solomon {
namespace galois {

class Polynomial {
public:
	Polynomial(const std::vector<GF> &coefficients);

	int degree(void) const;

	GF operator[](unsigned i) const;

	/*
	const unsigned degree;
	
	Polynomial(const std::vector<GF<Q>> &coefficients) :
		degree { find_degree(coefficients) },
		coefficients { copy_coefficients(coefficients) }
	{ }

	inline GF<Q> operator[](unsigned i) const {
		if (i >= coefficients.size())
			return { 0 };
		else
			return coefficients[i];
	}

	inline const GF<Q> operator()(GF<Q> x) const {
		GF<Q> result = 0;
		GF<Q> xp = 1;
		std::cout << "eval: x = " << x.value() << " len = " << coefficients.size() << std::endl;

		std::cout << "result: " << result.value() << " xp: " << xp.value() << std::endl;
		for (GF<Q> c : coefficients) {
			result += xp * c;
			xp *= x;
			std::cout << "result: " << result.value() << " xp: " << xp.value() << std::endl;
		}
		return result;
	}
	*/

private:
	std::vector<const GF> coefficients;

	/*
	const std::vector<const GF<Q>> coefficients;

	static unsigned find_degree(const std::vector<GF<Q>> &coefficients) {
		int d;
		for (d = coefficients.size() - 1; d > 0 && coefficients[d] == 0; d--);
		return d >= 0 ? d : 0;
	}

	static std::vector<const GF<Q>> copy_coefficients(
		const std::vector<GF<Q>> &coefficients)
	{
		for (auto it = coefficients.end(); it != coefficients.begin(); it--) {
			if (*(it - 1) != 0)
				return { coefficients.begin(), it };
		}
		return { };

	}
	*/
};

} // namespace galois
} // namespace reed_solomon

#endif // _GALOIS__POLYNOMIAL_H_
