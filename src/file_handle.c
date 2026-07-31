#include <include/utilities.h>

FILE *open_binary_file()
{
	FILE *in = fopen(FILENAME, 'rb');
	if (!in) {
		return NULL;
	}

	return in;
}
