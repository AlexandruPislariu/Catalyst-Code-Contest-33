#include "Domain.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Flight& ob)
{
	os << ob.from <<" "<< ob.to;
	return os;
}