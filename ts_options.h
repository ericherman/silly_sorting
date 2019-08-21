#ifndef TS_OPTIONS_H
#define TS_OPTIONS_H
/*
   ts_options.h: options structure for test sorts
   Copyright (C) 2015, 2016 Eric Herman <eric@freesa.org>

   This work is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This work is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License and the GNU General Public License for
   more details.

   You should have received a copy of the GNU Lesser General Public
   License (COPYING) and the GNU General Public License (COPYING.GPL3).
   If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdint.h>

struct ts_options {
	unsigned int num_elements;
	unsigned int element_max_value;
	unsigned int negate_one_in;
	uint8_t help;
	uint8_t version;
};

void parse_cmdline_args(struct ts_options *options, int argc, char *argv[]);
void show_usage(FILE *stream, char *argv0);

#endif /* TS_OPTIONS_H */
