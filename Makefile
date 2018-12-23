target: a.out

a.out:
	clang 0.8.3.c

.PHONY : clean
clean :
	rm a.out
