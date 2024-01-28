
#include <container/cstring.h>

#include <core/compiler.h>
#include <core/error.h>
#include <core/panic.h>

#include <libc/allocator.h>
#include <libc/mem.h>
#include <libc/string.h>

#define nosys panic("not implemented");

#define CLEAR_LAST_2_BITS (~(unsigned long)0x3u)

__may_alloc
static int __check_realloc(struct cstring *cstring, unsigned long want_size)
{
	char *data;

	if (likely(cstring->alloc >= want_size)) {
		return 0;
	}

	want_size = cstring->alloc + want_size;
	want_size &= CLEAR_LAST_2_BITS;
	want_size += 16;

	data = tlu_malloc(want_size);
	if (unlikely(data == NULL)) {
#if CONFIG_CONTAINER_ALLOC_FAIL == 1
		panic("cstring::__check_realloc: no memory to allocate");
#else
		return TLU_ENOMEM;
#endif
	}

	tlu_memcpy(data, cstring->data, cstring->size + 1);
	cstring->alloc = want_size;

	return 0;
}

__may_alloc
int cstring_init(struct cstring *cstring, const char *init)
{
	cstring->size = tlu_strlen(init);
	cstring->alloc = cstring->size;

	cstring->data = tlu_malloc(cstring->size + 1);
	if (unlikely(cstring->data == NULL)) {
#if CONFIG_CONTAINER_ALLOC_FAIL == 1
		panic("cstring::cstring_init: no memory to allocate");
#else
		return TLU_ENOMEM;
#endif
	}

	tlu_memcpy(cstring->data, init, cstring->size + 1);

	return 0;
}

void cstring_destroy(struct cstring *cstring)
{
	tlu_free(cstring);
}

unsigned long cstring_size(const struct cstring *cstring)
{
	return cstring->size;
}

char cstring_at(const struct cstring *cstring, unsigned long pos)
{
	panic_on(pos >= cstring->size, "cstring_at: out of bounds");

	return cstring->data[pos];
}

void cstring_set(struct cstring *cstring, unsigned long pos, char c)
{
	panic_on(pos >= cstring->size, "cstring_set: out of bounds");

	cstring->data[pos] = c;
}

__may_alloc
int cstring_append(struct cstring *cstring, char c)
{
	if (unlikely(__check_realloc(cstring, cstring->size + 1))) {
		return TLU_ENOMEM;
	}

	cstring->data[cstring->size] = c;
	cstring->size++;

	return 0;
}

__may_alloc
int cstring_extend(struct cstring *cstring, const char *other)
{
	unsigned long size = tlu_strlen(other);

	if (unlikely(__check_realloc(cstring, cstring->alloc + size))) {
		return TLU_ENOMEM;
	}

	tlu_memcpy(cstring->data + cstring->size, other, size + 1);
	cstring->size += size;

	return 0;
}

bool cstring_contains(const struct cstring *cstring, const char *pattern)
{
	if (unlikely(pattern[0] == '\0')) {
		return false;
	} else if (pattern[1] == '\0') {
		return tlu_memnchr(cstring->data, pattern[0],
				   cstring->size + 1) != NULL;
	} else {
		return tlu_strstr(cstring->data, pattern) != NULL;
	}
}

bool cstring_startswith(const struct cstring *cstring, const char *pattern)
{
	return tlu_sstartswith(cstring->data, pattern);
}

bool cstring_endswith(const struct cstring *cstring, const char *pattern)
{
	return tlu_sendswith(cstring->data, pattern);
}

unsigned long cstring_count(const struct cstring *cstring, const char *pattern)
{
	if (unlikely(pattern[0] == '\0')) {
		return 0;
	} else if (pattern[1] == '\0') {
		return tlu_memcnt(cstring->data, pattern[0], cstring->size + 1);
	} else {
		return tlu_strcnt(cstring->data, pattern);
	}
}

long cstring_find(const struct cstring *cstring, const char *pattern)
{
	const char *ret;

	if (unlikely(pattern[0] == '\0')) {
		return -1;
	} else if (pattern[1] == '\0') {
		ret = tlu_memnchr(cstring->data, pattern[0], cstring->size);
	} else {
		ret = tlu_strstr(cstring->data, pattern);
	}

	if (ret == NULL) {
		return -1;
	} else {
		return ret - cstring->data;
	}
}

unsigned long cstring_rfind(const struct cstring *cstring, const char *pattern)
{
	const char *ret;

	if (unlikely(pattern[0] == '\0')) {
		return -1;
	} else if (pattern[1] == '\0') {
		ret = tlu_memnrchr(cstring->data, pattern[0], cstring->size);
	} else {
		ret = tlu_strrstr(cstring->data, pattern);
	}

	if (ret == NULL) {
		return -1;
	} else {
		return ret - cstring->data;
	}
}

bool cstring_isalpha(const struct cstring *cstring)
{
	nosys;
}

bool cstring_isdigit(const struct cstring *cstring)
{
	nosys;
}

bool cstring_isalnum(const struct cstring *cstring)
{
	nosys;
}

bool cstring_islower(const struct cstring *cstring)
{
	nosys;
}

bool cstring_isupper(const struct cstring *cstring)
{
	nosys;
}

bool cstring_isspace(const struct cstring *cstring)
{
	nosys;
}

void cstring_tolwer(struct cstring *cstring)
{
	nosys;
}

void cstring_toupper(struct cstring *cstring)
{
	nosys;
}

void cstring_remove_prefix(struct cstring *cstring, const char *pattern)
{
	if (tlu_sstartswith(cstring->data, pattern)) {
		unsigned long len = tlu_strlen(pattern);

		tlu_memmove(cstring->data, cstring->data + len, cstring->size - len);
	}
}

void cstring_remove_suffix(struct cstring *cstring, const char *pattern)
{
	if (tlu_sendswith(cstring->data, pattern)) {
		unsigned long len = tlu_strlen(pattern);

		cstring->size -= len;
		cstring->data[cstring->size] = '\0';
	}
}

__may_alloc
int cstring_replace(struct cstring *cstring, const char *from, const char *to)
{
	nosys;
}

void cstring_lstrip(struct cstring *cstring)
{
	nosys;
}

void cstring_rstrip(struct cstring *cstring)
{
	nosys;
}

void cstring_strip(struct cstring *cstring)
{
	nosys;
}

void cstring_reverse(struct cstring *cstring)
{
	nosys;
}

