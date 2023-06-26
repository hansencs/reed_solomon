#include "galois/galois_field.h"

namespace reed_solomon {
namespace galois {

GF::GF(void) : _value { 0 } {};

GF::GF(uint8_t value) : _value { value } {};

uint8_t GF::value(void) const {
	return _value;
}

} // namespace galois
} // namespace reed_solomon
