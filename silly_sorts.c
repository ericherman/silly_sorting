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

#include "silly_sorts.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

enum reorder { SORT, SHUFFLE };

typedef struct int_list_s {
	struct int_list_s *next_node;
	int val;
} int_list;

typedef struct int_list_head_s {
	int_list *first_node;
} int_list_head;

typedef struct pthread_push_context_s {
	int_list_head *head;
	pthread_mutex_t *mutex;
	int val;
	unsigned int sleep_time;
} pthread_push_context;

void *_pthread_push(void *arg)
{
	pthread_push_context *ctx;
	int_list_head *head;
	int_list *node;

	ctx = (pthread_push_context *)arg;

	head = ctx->head;

	sleep(ctx->sleep_time);

	pthread_mutex_lock(ctx->mutex);
	if (head->first_node == NULL) {
		node = (int_list *)malloc(sizeof(int_list));
		node->next_node = NULL;

		head->first_node = node;
	} else {
		node = head->first_node;
		while (node->next_node) {
			node = node->next_node;
		}
		node->next_node = (int_list *)malloc(sizeof(int_list));
		node->next_node->next_node = NULL;

		node = node->next_node;
	}

	node->val = ctx->val;
	pthread_mutex_unlock(ctx->mutex);

	free(arg);

	return NULL;
}

void _sleep_reorder(enum reorder order, int *elements, size_t num_elements)
{
	size_t i;
	int rv;
	pthread_push_context *ctx;
	pthread_t *threads;
	int_list_head *pos_list, *neg_list;
	int_list *node;
	pthread_mutex_t *mutex;
	const pthread_mutexattr_t *attr = NULL;

	threads = (pthread_t *) malloc(num_elements * sizeof(pthread_t));
	if (!threads) {
		exit(EXIT_FAILURE);
	}

	pos_list = (int_list_head *)malloc(sizeof(int_list_head));
	if (!pos_list) {
		exit(EXIT_FAILURE);
	}
	pos_list->first_node = NULL;

	neg_list = (int_list_head *)malloc(sizeof(int_list_head));
	if (!neg_list) {
		exit(EXIT_FAILURE);
	}
	neg_list->first_node = NULL;

	mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!mutex) {
		exit(EXIT_FAILURE);
	}
	rv = pthread_mutex_init(mutex, attr);
	if (rv) {
		fprintf(stderr, "pthread_mutex_init() returned: %d\n", rv);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < num_elements; i++) {
		ctx = (pthread_push_context *)
		    malloc(sizeof(pthread_push_context));
		ctx->mutex = mutex;

		ctx->val = elements[i];

		switch (order) {
		case SHUFFLE:
			ctx->head = pos_list;
			ctx->sleep_time = rand() % num_elements;
			break;
		case SORT:
			if (elements[i] >= 0) {
				ctx->head = pos_list;
				ctx->sleep_time = elements[i];
			} else {
				ctx->head = neg_list;
				ctx->sleep_time = -1 * elements[i];
			}
			break;
		}

		rv = pthread_create(&(threads[i]), NULL, _pthread_push, ctx);
		if (rv) {
			fprintf(stderr, "pthread_create() returned: %d\n", rv);
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < num_elements; i++) {
		pthread_join(threads[i], NULL);
	}
	free(threads);
	rv = pthread_mutex_destroy(mutex);
	if (rv) {
		fprintf(stderr, "pthread_mutex_destroy() returned: %d\n", rv);
	}
	free(mutex);

	while (neg_list->first_node) {
		node = neg_list->first_node;
		neg_list->first_node = node->next_node;
		node->next_node = pos_list->first_node;
		pos_list->first_node = node;
	}
	free(neg_list);

	if (pos_list->first_node) {
		node = pos_list->first_node;
		for (i = 0; i < num_elements; i++) {
			elements[i] = node->val;
			node = node->next_node;
		}

		while (pos_list->first_node->next_node) {
			node = pos_list->first_node->next_node;
			pos_list->first_node->next_node = node->next_node;
			free(node);
		}
		free(pos_list->first_node);
	}
	free(pos_list);
}

void sleep_sort(int *elements, size_t num_elements)
{
	_sleep_reorder(SORT, elements, num_elements);
}

void _sleep_shuffle(int *elements, size_t num_elements)
{
	_sleep_reorder(SHUFFLE, elements, num_elements);
}

void _shuffle(int *elements, size_t num_elements)
{
	size_t i, pos;
	int swap;
	for (i = 0; i < num_elements; i++) {
		pos = rand() % num_elements;
		swap = elements[i];
		elements[i] = elements[pos];
		elements[pos] = swap;
	}
}

void _random_sort(void (*shuffle_func) (int *elements, size_t num_elements),
		  int *elements, size_t num_elements)
{
	size_t i;
	int last;
	int sorted = 0;

	while (!sorted) {
		shuffle_func(elements, num_elements);
		sorted = 1;
		last = INT_MIN;
		for (i = 0; i < num_elements; i++) {
			if (elements[i] < last) {
				sorted = 0;
			}
			last = elements[i];
		}
	}
}

void random_sort(int *elements, size_t num_elements)
{
	_random_sort(_shuffle, elements, num_elements);
}

void random_sleep_sort(int *elements, size_t num_elements)
{
	_random_sort(_sleep_shuffle, elements, num_elements);
}
