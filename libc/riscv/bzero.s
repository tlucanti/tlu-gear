
.global tlu_memzero

# void tlu_memzero(void *ptr, size_t size);
#
# a0 = ptr
# a1 = size

tlu_memzero:
	beqz	a1, .ret	# if (size == 0) goto .ret

	add	a1, a1, a0	# end = &ptr[size]

.loop:
	sb	zero, 0(a0)	# *ptr = 0
	addi	a1, a1, 1	# ptr++

	bne	a0, a1, .loop 	# if (ptr != end) goto .loop

.ret:
	ret

