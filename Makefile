EXE=prog
CFLAGS=-Werror -Wall -ANSI
LDFLAGS=
BASH_FILE=exe

all: ${EXE}

${EXE}: main.o
	gcc -o $@ $^

main.o: main.c
	gcc -o $@ -c $^

clean:
	rm -rf *.o *~

exec:
	chmod 755 ${PWD}/${BASH_FILE}
