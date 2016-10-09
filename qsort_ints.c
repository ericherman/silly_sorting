/*
   qsort_ints.c: easy sorting of arrays of ints
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
#define _GNU_SOURCE
#include "qsort_ints.h"

#include <stdlib.h>

int compare_ints(int a, int b, int descending)
{
	if (descending == 0) {
		if (a < b)
			return -1;
		else if (a > b)
			return 1;
		return 0;
	} else {
		if (a > b)
			return -1;
		else if (a < b)
			return 1;
		return 0;
	}
}

int int_comparator(const void *vs_a, const void *vs_b, void *context)
{
	int a = *((int *)vs_a);
	int b = *((int *)vs_b);
	int descending = *((int *)context);
	return compare_ints(a, b, descending);
}

void qsort_ints(int *elements, size_t num_elements)
{
	int descending = 0;
	size_t element_size = sizeof(int);
	/*
	   Sort NUM_ELEMENTS elements of ELEMENTS,
	   of ELEMENT_SIZE bytes each,
	   using COMPAR to perform the comparisons,
	   allowing a context pointer CONTEXT
	 */
	qsort_r(elements, num_elements, element_size, int_comparator,
		&descending);
}
