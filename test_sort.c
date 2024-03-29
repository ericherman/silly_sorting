/*
   test_sort.c: execute and compare sorts
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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ts_options.h"
#include "qsort_ints.h"
#include "silly_sorts.h"

#define NUM_FUNCS 4
struct sort_func_s {
	const char *name;
	void (*sort_func)(int *elements, size_t num_elements);
};

int main(int argc, char *argv[])
{
	int *array, *vals;
	struct sort_func_s sort_funcs[NUM_FUNCS];
	int j, last, negate, sorted;
	unsigned int i;
	clock_t start, end;
	double elapsed;
	struct ts_options options;

	parse_cmdline_args(&options, argc, argv);

	if (options.version) {
		printf("%s version 1\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	if (options.help) {
		show_usage(stdout, argv[0]);
		exit(EXIT_SUCCESS);
	}

	array = (int *)malloc(options.num_elements * sizeof(int));
	vals = (int *)malloc(options.num_elements * sizeof(int));

	sort_funcs[0].name = "qsort";
	sort_funcs[0].sort_func = qsort_ints;

	sort_funcs[1].name = "random_sort";
	sort_funcs[1].sort_func = random_sort;

	sort_funcs[2].name = "sleep_sort";
	sort_funcs[2].sort_func = sleep_sort;

	sort_funcs[3].name = "random_sleep_sort";
	sort_funcs[3].sort_func = random_sleep_sort;

	printf("%25s: { ", "un-sorted");
	for (i = 0; i < options.num_elements; i++) {

		negate = rand() % options.negate_one_in;
		vals[i] = rand() % options.element_max_value;
		if (negate == 1) {
			vals[i] *= -1;
		}
		printf("%d, ", vals[i]);
	}
	printf("}\n");

	sorted = 1;
	for (j = 0; j < NUM_FUNCS; j++) {
		memcpy(array, vals, options.num_elements * sizeof(int));

		printf("%18s sorted: { ", sort_funcs[j].name);
		fflush(stdout);

		start = clock();
		sort_funcs[j].sort_func(array, options.num_elements);
		end = clock();
		elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

		last = array[0];
		for (i = 0; i < options.num_elements; i++) {
			if (array[i] < last) {
				sorted = 0;
			}
			last = array[i];
			printf("%d, ", array[i]);
		}
		printf("} elapsed: %9.2f\n", elapsed * 10000);
	}

	free(array);
	free(vals);

	exit(sorted ? EXIT_SUCCESS : EXIT_FAILURE);
}
