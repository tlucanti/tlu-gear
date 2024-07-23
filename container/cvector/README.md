
# interface

## init / fini funcitons

### cvector_init
```c
void cvector_init(void)
```
Initialize cvector data type. Should be called once before any other cvector
function.
> example
> ```c
> int main()
> {
> 	cvector_init();
> 	// some code using cvector
> 	cvector_fini();
> 	return 0;
> }
> ```


### cvector_fini
```c
void cvector_fini(void)
```
Finalize usage of cvector data type. Should be caleed once before exiting the
process.
> example
> ```c
> int main()
> {
> 	cvector_init();
> 	// some code using cvector
> 	cvector_fini();
> 	return 0;
> }
> ```



## create / destroy functions

### cvector_create
```c
type *cvector_create(type, uint64 size, cvector_create_flags_t flags)
```
| cvector_create_flags_t       | description |
|:---------------------------- |:------------|
| CVECTOR_CREATE_EXACT_SIZE    |             |
| CVECTOR_CREATE_ZERO          |             |
| CVECTOR_CREATE_ONLY_PREALLOC |             |


### cvector_destroy
```c
void cvector_destroy(type *vector)
```

### cvector_copy
```c
type *cvector_copy(type *vector)
```




--------------------------------------------------------------------------------
```c
// =============================================================================
void cvector_init(void); /* done */
void cvector_fini(void); /* done */

// =============================================================================
type *cvector_create(type, size, flags); /* done */
flags = {
	CVECTOR_CREATE_EXACT_SIZE
	CVECTOR_CREATE_ZERO
	CVECTOR_CREATE_ONLY_PREALLOC
};

void cvector_destroy(type *vector); /* done */

type *cvector_copy(const type *vector, flags) /* done */
flags = {
	CVECTOR_COPY_EXACT_SIZE
};

// int *a = cvector_create_from(flags, (int[]){1, 2, 3, 4, 5});
type *cvector_create_from_list(flags, {initializer_list}) /* skipped */
flags = {
	CVECTOR_CREATE_FROM_EXACT_SIZE
};
type *cvector_create_from(flags, type *begin, type *end) /* done */

// =============================================================================
type = cvector[index]; /* done */

type cvector_at(const type *vector, idx); /* done */
type cvector_rat(const type *vector, idx) /* done */
type cvector_front(const type *vector); /* done */
type cvector_back(const type *vector); /* done */

// =============================================================================
bool cvector_empty(const type *vector); /* done */
uint64 cvector_size(const type *vector); /* done */
uint64 cvector_capacity(const type *vector); /* done */

// =============================================================================
#define cvector_for_each(type *vector, type val) /* done */
#define cvector_for_each_reverse(type *cvector, type val) /* done */

type *cvector_find(const type *vector, type val); /* done */
type *cvector_rfind(const type *vector, type val); /* done */

bool cvector_contains(const type *vector, type val); /* done */
uint64 cvector_count(const type *vector, type val); /* done */

// =============================================================================
type *cvector_insert(type **vector, type *pos, type value); /* done */
type *cvector_push_back(type **vector, type value); /* done */
type *cvector_push_front(type **vector, type value); /* done */

type *cvector_erase(type **vector, type *pos);
type *cvector_pop_front(type **vector);
type *cvector_pop_back(type **vector);

// =============================================================================
cvector_resize
cvector_reserve
int cvector_extend(type **vector, type *other);

// =============================================================================
type *cvector_begin(const type *vector); /* done */
type *cvector_end(const type *vector); /* done */
const type *cvector_cbegin(type *vector);
const type *cvector_cend(type *vector);

type *cvector_rbegin(const type *vector); /* begin */
type *cvector_rend(const type *vector); /* begin */
const type *cvector_crbegin(const type *vector);
const type *cvector_crend(const type *vector);

// =============================================================================
```