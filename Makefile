target: a.out

a.out:
	clang 8.2.c

.PHONY : clean
clean :
	rm a.out
