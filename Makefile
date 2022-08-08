#

EXECUTABLE=test-sorts
SOURCES=test_sort.c ts_options.c qsort_ints.c silly_sorts.c

CC=gcc
STD_CFLAGS=-std=c89
NOISY_CFLAGS=-Werror -Wall -Wextra -pedantic
OPTIMIZER_CFLAGS=-ggdb -O2 -fomit-frame-pointer

CFLAGS=$(STD_CFLAGS) $(OPTIMIZER_CFLAGS) $(NOISY_CFLAGS) -pipe

LDFLAGS=
LDADD=-pthread

OBJECTS=$(SOURCES:.c=.o)

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

# $@ : target label
# $< : the first prerequisite after the colon
# $^ : all of the prerequisite files
# $* : wildcard matched part

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) \
		$(LDFLAGS) \
		$(OBJECTS) -o $@ \
		$(LDADD)

.c.o:
	$(CC) -c $(CFLAGS) \
		$^ -o $@

tidy:
	$(LINDENT) \
		-T FILE \
		-T size_t \
		-T pthread_t \
		-T pthread_mutex_t \
		-T ts_options \
		-T int_list \
		-T int_list_head \
		-T pthread_push_context \
		*.h *.c

clean:
	rm -rf *.o $(EXECUTABLE)

check: all
	./$(EXECUTABLE)
