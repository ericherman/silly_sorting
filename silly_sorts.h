#ifndef SILLY_SORTS_H
#define SILLY_SORTS_H
/*
   silly_sorts: "random sort", "sleep sort", and even "random sleep sort"
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

#include <stdlib.h>

void sleep_sort(int *elements, size_t num_elements);
void random_sort(int *elements, size_t num_elements);
void random_sleep_sort(int *elements, size_t num_elements);

#endif /* SILLY_SORTS_H */
