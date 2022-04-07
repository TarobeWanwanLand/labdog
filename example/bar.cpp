#include <cstdio>
#include <labdog/logging/log.hpp>
#include <labdog/util/assert.hpp>
#include <labdog/core/string.hpp>
#include <labdog/core/string_view.hpp>

int main(int argc, char *argv[])
{
	labdog::string str(U"☺");
	labdog::string str2(U"😂あいうえ");
	labdog::string_view view(str);
	labdog::string_view view2(str2.begin(), str2.begin() + 2);

	bool res = view == view2;

	getchar();

	return 0;
}
