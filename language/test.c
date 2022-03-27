
int func() { return 0; }

#define func(...) __VA_ARGS__

void *lol(int (*f)())
{
	return (void *)f;
}

int main()
{
	lol(func);
}
