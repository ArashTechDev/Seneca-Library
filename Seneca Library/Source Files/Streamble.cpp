//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#include <iostream>
#include "Streamable.h"

using namespace std;

namespace sdds {

	Streamable::~Streamable() {}

	std::ostream& operator<<(std::ostream& os, const Streamable& stream) {
		if (stream) {
			return stream.write(os);
		}
		return os;
	}
	std::istream& operator>>(std::istream& is, Streamable& stream) {
		return stream.read(is);
	}
}