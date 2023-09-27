
#include <stdbool.h>

bool isdigit(unsigned char c)
{
	return (unsigned char)(c - '0') < 10;
}
