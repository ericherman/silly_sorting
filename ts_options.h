#ifndef TS_OPTIONS_H
#define TS_OPTIONS_H

#include <stdio.h>
#include <stdint.h>

typedef struct ts_options_s {
	unsigned int num_elements;
	unsigned int element_max_value;
	unsigned int negate_one_in;
	uint8_t help;
	uint8_t version;
} ts_options;

void parse_cmdline_args(ts_options *options, int argc, char *argv[]);
void show_usage(FILE *stream, char *argv0);

#endif /* TS_OPTIONS_H */
