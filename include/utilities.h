#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MIN_WORD_AUTOCOMPLETE_LEN 4
#define FILENAME "./data/memorisation_file__example.txt"
#define HEADERLINE "MKCLI"

typedef struct {
	char *word;
	int word_size;
	int word_freq;

	struct trie_node_t *owner;
	struct dll_node_t *next, *prev;
} str_dll_node_t;

typedef struct str_dll_t{
	str_dll_node_t *head, *tail;
	int nr_nodes;
} str_dll_t;

typedef struct trie_node_t{
	char value;

	int nr_childs;
	struct trie_node_t **childs; // sorted lexicographically

	int interval_size; // amount of keywords in subtree
	// holds references to interval bounds of dll keywords
	str_dll_node_t *left_bound, *right_bound;
	str_dll_node_t *best_keyword;
	str_dll_node_t *keyword; // NULL if the node doesnt hold keywords
} trie_node_t;

typedef struct {
	trie_node_t *root;
	str_dll_node_t *keywords;
} trie_t;

#endif