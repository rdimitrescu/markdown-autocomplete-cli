#include <utilities.h>

trie_node_t *create_trie_child(void)
{
	trie_node_t *node = calloc(sizeof(trie_node_t), 1);
	if (!node) {
		return NULL;
	}

	return node;
}

trie_node_t *trie_search_childs(trie_node_t *curr_node, char searched)
{
	for (int i = 0; i < curr_node->nr_childs; i++) {
		if (curr_node->childs[i]->value == searched) {
			return curr_node->childs[i];
		}
	}
	return NULL;
}

int trie_insert(trie_t *trie, char *word, int word_freq)
{
	trie_node_t *curr_node = trie->root;

	int word_len = strlen(word);
	for (int i = 0; i < word_len; i++) {
		if (!curr_node) {
			curr_node = create_trie_child();
			if (!curr_node) {
				return 0;
			}
		}

		curr_node->value = word[i];
		curr_node->nr_childs++;
		if (!trie_search_childs(curr_node, word[i])) {
			// create the child
			
		}

		// keep going down / or if at the end add the word to the keyword_dll
	}

	return 1;
}

int trie_populate(trie_t *trie, FILE *in) 
{
	if (!in || !trie) {
		return 0;
	}

	char *word = calloc(sizeof(char), MAX_LEN);
	if (!word || !fscanf(in, "%s", word)) {
		return 0;
	}

	// file checked is not required format
	if (strcmp(word, HEADERLINE) != 0) {
		free(word);
		return 0;
	}

	int word_freq;
	while (fscanf(" %100s %d ", word, word_freq) == 2) {
		if (!trie_insert(trie, word, word_freq)) {
			free(word);
			return 0;
		}
	}

	free(word);

	return 1;
}