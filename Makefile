target: a.out

a.out:
	cc 0.10.2.c

.PHONY : clean
clean :
	rm a.out
