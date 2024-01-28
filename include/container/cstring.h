
#ifndef _CONTAINER_CSTRING_H_
#define _CONTAINER_CSTRING_H_

#include <stdbool.h>

#include <core/compiler.h>

struct cstring {
	char *data;
	unsigned long size;
	unsigned long alloc;
};

#define CSTRING_INIT() (struct cstring){.data = NULL, .size=0, .alloc = 0};

#if CONFIG_CONTAINER_ALLOC_FAIL && !defined(__may_alloc)
# define __may_alloc __must_check
#else
# define __may_alloc /* empty */
#endif

/**
 * constructors and destructors
 */
__may_alloc int cstring_init(struct cstring *cstring, const char *init);
void cstring_destroy(struct cstring *cstring);

/**
 * string informaion
 */
unsigned long cstring_size(const struct cstring *cstring);
char cstring_at(const struct cstring *cstring, unsigned long pos);

/**
 * string moditication
 */
void cstring_set(struct cstring *cstring, unsigned long pos, char c);
__may_alloc int cstring_append(struct cstring *cstring, char c);
__may_alloc int cstring_extend(struct cstring *cstring, const char *other);

/**
 * string lookups
 */
bool cstring_contains(const struct cstring *cstring, const char *pattern);
bool cstring_starts_with(const struct cstring *cstring, const char *pattern);
bool cstring_ends_with(const struct cstring *cstring, const char *pattern);
unsigned long cstring_count(const struct cstring *cstring, const char *pattern);
long cstring_find(const struct cstring *cstring, const char *pattern);
unsigned long cstring_rfind(const struct cstring *cstring, const char *pattern);

/**
 * string character informaion
 */
bool cstring_isalpha(const struct cstring *cstring);
bool cstring_isdigit(const struct cstring *cstring);
bool cstring_isalnum(const struct cstring *cstring);
bool cstring_islower(const struct cstring *cstring);
bool cstring_isupper(const struct cstring *cstring);
bool cstring_isspace(const struct cstring *cstring);

/**
 * cstring formattings
 */
void cstring_tolwer(struct cstring *cstring);
void cstring_toupper(const struct cstring *cstring);
void cstring_remove_prefix(const struct cstring *cstring, const char *pattern);
void cstring_remove_suffix(const struct cstring *cstring, const char *pattern);
__may_alloc int cstring_replace(const struct cstring *cstring, const char *from, const char *to);
void cstring_lstrip(const struct cstring *cstring);
void cstring_rstrip(const struct cstring *cstring);
void cstring_reverse(const struct cstring *cstring);

#endif /* _CONTAINER_CSTRING_H_ */

