target: a.out

a.out:
	clang 10.9.c

.PHONY : clean
clean :
	rm a.out
