
#include <stdbool.h>

bool tlu_isdigit(unsigned char c)
{
	return (unsigned char)(c - '0') < 10;
}
