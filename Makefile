all : magic.c
	gcc -Wall -Werror -fsanitize=address -o magic magic.c
clean :
	rm -rf magic
