#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MIN_WORD_AUTOCOMPLETE_LEN 4
#define FILENAME './data/memorisation_file__example.txt'
#define HEADERLINE 'MKCLI'

typedef struct {
	char *word;
	int word_size;
	int word_freq;

	struct dll_node_t *next, *prev;
} str_dll_node_t;

typedef struct str_dll_t{
	str_dll_node_t *root;
	int nr_nodes;
} str_dll_t;

typedef struct trie_node_t{
	char value;

	int nr_childs;
	struct trie_node_t **childs;

	int nr_keywords_below;
	str_dll_t **keyword_dll;
} trie_node_t;

typedef struct {
	trie_node_t *root;
} trie_t;

#endif