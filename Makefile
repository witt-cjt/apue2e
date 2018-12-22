target: a.out echoall

a.out:
	clang 8.10.c
echoall:
	clang -o echoall 8.10.1.c

.PHONY : clean
clean :
	rm a.out echoall
