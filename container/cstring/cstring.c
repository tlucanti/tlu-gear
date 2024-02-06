
#include <container/cstring.h>

#include <core/compiler.h>
#include <core/error.h>
#include <core/panic.h>

#include <libc/allocator.h>
#include <libc/mem.h>
#include <libc/string.h>

#define CONFIG_CONTAINER_ALLOC_FAIL 1
#define nosys panic("TODO: not implemented");

__may_alloc
static int __do_realloc(struct cstring *cstring, unsigned long exact_size)
{
	char *data;

	data = tlu_malloc(exact_size);
	if (unlikely(data == NULL)) {
#if CONFIG_CONTAINER_ALLOC_FAIL == 1
		panic("(cstring): no memory to allocate");
#else
		return TLU_ENOMEM;
#endif
	}

	tlu_memcpy(data, cstring->data, cstring->size + 1);
	cstring->alloc = exact_size;

	tlu_free(cstring->data);
	cstring->data = data;

	return 0;
}

__may_alloc
static int check_realloc_more(struct cstring *cstring, unsigned long want_size)
{
	if (likely(cstring->alloc >= want_size)) {
		return 0;
	}

	if (cstring->alloc + want_size >= 4000) {
		want_size = cstring->alloc + want_size + 4096;
		want_size -= want_size % 4096;
	} else {
		want_size = cstring->alloc + want_size + 64;
		want_size -= want_size % 64;
	}

	return __do_realloc(cstring, want_size);
}

__may_alloc
static int check_realloc_less(struct cstring *cstring, unsigned long want_size)
{
	if (likely(cstring->alloc <= 64 || cstring->alloc / want_size < 4)) {
		return 0;
	}

	if (cstring->alloc + want_size >= 4000) {
		want_size = cstring->alloc + want_size + 4096;
		want_size -= want_size % 4096;
	} else {
		want_size = cstring->alloc + want_size + 64;
		want_size -= want_size % 64;
	}

	return __do_realloc(cstring, want_size);
}

__may_alloc
int cstring_init(struct cstring *cstring, const char *init)
{
	cstring->size = tlu_strlen(init);
	cstring->alloc = cstring->size;

	cstring->data = tlu_malloc(cstring->size + 1);
	if (unlikely(cstring->data == NULL)) {
#if CONFIG_CONTAINER_ALLOC_FAIL == 1
		panic("(cstring): no memory to allocate");
#else
		return TLU_ENOMEM;
#endif
	}

	tlu_memcpy(cstring->data, init, cstring->size + 1);

	return 0;
}

void cstring_destroy(struct cstring *cstring)
{
	tlu_free(cstring->data);
}

const char *cstring_data(const struct cstring *cstring)
{
	return cstring->data;
}

unsigned long cstring_size(const struct cstring *cstring)
{
	return cstring->size;
}

unsigned long cstring_alloc(const struct cstring *cstring)
{
	return cstring->alloc;
}

char cstring_at(const struct cstring *cstring, long pos)
{
	if (pos < 0) {
		panic_on((unsigned long)(-pos) > cstring->size, "(cstring): out of bounds");
		pos = cstring->size + pos;
	} else {
		panic_on((unsigned long)pos >= cstring->size, "(cstring): out of bounds");
	}

	return cstring->data[pos];
}

void cstring_set(struct cstring *cstring, long pos, char c)
{
	if (pos < 0) {
		panic_on((unsigned long)(-pos) > cstring->size, "(cstring): out of bounds");
		pos = cstring->size + pos;
	} else {
		panic_on((unsigned long)pos >= cstring->size, "(cstring): out of bounds");
	}

	cstring->data[pos] = c;
}

__may_alloc
int cstring_append(struct cstring *cstring, char c)
{
	int err;

	err = check_realloc_more(cstring, cstring->size + 1);
	if (unlikely(err)) {
		return err;
	}

	cstring->data[cstring->size] = c;
	cstring->size++;
	cstring->data[cstring->size] = '\0';

	return 0;
}

__may_alloc
int cstring_appfront(struct cstring *cstring, char c)
{
	(void)cstring;
	(void)c;
	nosys;
}

__may_alloc
int cstring_extend(struct cstring *cstring, const char *other)
{
	unsigned long size = tlu_strlen(other);
	int err;

	err = check_realloc_more(cstring, cstring->size + size);
	if (unlikely(err)) {
		return err;
	}

	tlu_memcpy(cstring->data + cstring->size, other, size + 1);
	cstring->size += size;

	return 0;
}

__may_alloc
int cstring_extfront(struct cstring *cstring, const char *other)
{
	(void)cstring;
	(void)other;
	nosys;
}

__may_alloc
int cstring_remove_suffix(struct cstring *cstring, unsigned long size)
{
	int err;

	if (size >= cstring->size) {
		cstring->size = 0;
		err = __do_realloc(cstring, 64);
		cstring->data[0] = '\0';
	} else {
		cstring->size = cstring->size - size;
		err = check_realloc_less(cstring, cstring->size);
		cstring->data[cstring->size] = '\0';
	}

	if (unlikely(err)) {
		return err;
	} else {
		return 0;
	}
}

__may_alloc
int cstring_remove_prefix(struct cstring *cstring, unsigned long size)
{
	(void)cstring;
	(void)size;
	nosys;
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

unsigned long cstring_find(const struct cstring *cstring, const char *pattern)
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
	(void)cstring;
	nosys;
}

bool cstring_isdigit(const struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

bool cstring_isalnum(const struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

bool cstring_islower(const struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

bool cstring_isupper(const struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

bool cstring_isspace(const struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

void cstring_tolwer(struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

void cstring_toupper(struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

__may_alloc
int cstring_replace(struct cstring *cstring, const char *from, const char *to)
{
	(void)cstring;
	(void)from;
	(void)to;
	nosys;
}

__may_alloc
int cstring_lstrip(struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

__may_alloc
int cstring_rstrip(struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

__may_alloc
int cstring_strip(struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

void cstring_reverse(struct cstring *cstring)
{
	(void)cstring;
	nosys;
}

