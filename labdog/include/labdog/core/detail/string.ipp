//=========================================================
//
//	string.ipp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_STRING_IPP
#define LABDOG_STRING_IPP

#include "../string.hpp" // �s�v

namespace labdog
{
	template <class Iterator>
	inline string::string(Iterator first, Iterator last)
		: string_(first, last)
	{}
}

#endif // LABDOG_STRING_IPP