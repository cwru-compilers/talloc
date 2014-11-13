%.o:%.c
	gcc -c -g -m32 -o $@ $<

main: main.o talloc.o
	gcc -g -m32 -o $@ $^

main.o: main.c talloc.h

talloc.o : talloc.c

.PHONY: clean
clean:
	-@rm *.o main &> /dev/null

