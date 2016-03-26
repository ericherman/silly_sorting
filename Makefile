#

EXECUTABLE=test-sorts
SOURCES=test_sort.c ts_options.c qsort_ints.c silly_sorts.c

CC=gcc
STD_CFLAGS=-std=c89
NOISY_CFLAGS=-Werror -Wall -Wextra -pedantic
OPTIMIZER_CFLAGS=-ggdb -O0

CFLAGS=$(STD_CFLAGS) $(OPTIMIZER_CFLAGS) $(NOISY_CFLAGS)

LDFLAGS=-pthread

OBJECTS=$(SOURCES:.c=.o)

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $^ -o $@

tidy:
	$(LINDENT) \
		-T FILE \
		-T size_t \
		-T ts_options \
		-T int_list \
		-T int_list_head \
		-T pthread_push_context \
		*.h *.c

clean:
	rm -rf *.o $(EXECUTABLE)

check: all
	./$(EXECUTABLE)
