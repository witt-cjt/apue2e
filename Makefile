target: a.out

a.out:
	clang 10.10.c

.PHONY : clean
clean :
	rm a.out
