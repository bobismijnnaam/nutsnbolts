#include "../headers/nnb/utils/macros.hpp"

//UNPACK(src, a, b, c, d);


#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

int main() {
	int a = 3;

	decltype(a) b;

	b = 4;

	std::cout << b << "\n";

	std::tuple<int, std::string, bool> aTuple = std::make_tuple(43, "hanna", false);

	NNB_UNPACK(aTuple, theInt, theString, theBool);

	int a;
	string b;
	bool c;
	std::tie(a, b, c) = aTuple;

	std::cout << "The int: " << theInt << "\n";
	std::cout << "The string: " << theString << "\n";
	std::cout << "The bool: " << theBool << "\n";

	return b;
}
