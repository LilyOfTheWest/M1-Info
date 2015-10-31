CC=gcc

# uncomment to compile in 32bits mode (require gcc-*-multilib packages
# on Debian/Ubuntu)
#HOST32= -m32

CPPFLAGS= -I.
CFLAGS= $(HOST32) -Wall -Werror -std=c99 -g -fPIC -DMEMORY_SIZE=128000
LDFLAGS= $(HOST32) -pthread


.PHONY: clean dist

all: memshell memtest test_fit test_debordement test_thread libmalloc.so

# dépendences des binaires
memshell: mem.o
memtest: mem.o
test_fit: mem.o
test_debordement: mem.o
test_thread: mem.o

tests:
	./memtest
	./test_fit 1
	./test_fit 2
	./test_fit 3
	-./test_debordement # On met un '-' pour ignorer le code de retour
	./test_thread

# nettoyage
clean::
	rm -f *.o memshell memtest test_fit test_debordement test_thread libmalloc.so leak_test .*.deps

# dépendances des fichiers objects
$(patsubst %.c,%.o,$(wildcard *.c)): %.o: .%.deps

.%.deps: %.c
	$(CC) $(CPPFLAGS) -MM $< | sed -e 's/\(.*\).o: /.\1.deps \1.o: /' > $@

-include $(wildcard .*.deps)

# seconde partie du sujet
part2: leak_test libmalloc.so
	./leak_test
	$(MAKE) test_ls

libmalloc.so: malloc_stub.o mem.o
	$(CC) -shared -Wl,-soname,$@ $^ -o $@

test_ls: libmalloc.so
	LD_PRELOAD=./libmalloc.so ls

leak_test: malloc_stub.o mem.o

