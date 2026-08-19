#include <utilities.h>

// initialize trie with placeholder sentinel and empty values
trie_t *trie_init(void)
{
	trie_t *new_trie = malloc(sizeof(trie_t));
	if (!new_trie) {
		return NULL;
	}

	new_trie->root = malloc(sizeof(trie_node_t));
	if (!new_trie->root) {
		free(new_trie);
		return NULL;
	}

	new_trie->keywords = malloc(sizeof(str_dll_node_t));
	if (!new_trie->keywords) {
		free(new_trie->root);
		free(new_trie);
		return 0;
	}

	new_trie->root->value = '\0'; // trie sentinel value
	new_trie->root->nr_childs = 0;
	new_trie->root->childs = NULL;
	new_trie->root->interval_size = 0;
	new_trie->root->left_bound = NULL;
	new_trie->root->right_bound = NULL;
	new_trie->root->best_keyword = NULL;
	new_trie->root->keyword = NULL;

	new_trie->keywords->word = NULL;
	new_trie->keywords->word_size = 0;
	new_trie->keywords->word_freq = 0;
	new_trie->keywords->owner = new_trie->root;
	new_trie->keywords->next = NULL;
	new_trie->keywords->prev = NULL;

	return new_trie;
}

// create a trie node by passing in value
trie_node_t *create_trie_child(char value)
{
	trie_node_t *child_node = malloc(sizeof(trie_node_t));
	if (!child_node) {
		return NULL;
	}

	child_node->value = value;
	child_node->nr_childs = 0; // is a terminal node by default
	child_node->childs = NULL;
	child_node->interval_size = 0;
	child_node->left_bound = NULL;
	child_node->right_bound = NULL;
	child_node->best_keyword = NULL;
	child_node->keyword = NULL;

	return child_node;
}

// TODO
str_dll_node_t *previous_dll_node_lexico(trie_node_t *owner)
{
	if (!owner) {
		return NULL;
	}

	// implicitly leaf nodes hold keywords
	if (owner->nr_childs == 0) {
		// TODO
	}

	// binary search from the left interval to the right to find the right spot
}

// TODO
str_dll_node_t *create_dll_node(char *word, int word_size, int word_freq, 
								trie_node_t *owner)
{
	str_dll_node_t *new_node = malloc(sizeof(str_dll_node_t));
	if (!new_node) {
		return NULL;
	}

	new_node->word = word;
	new_node->word_size = word_size;
	new_node->word_freq = word_freq;
	new_node->owner = owner;

	str_dll_node_t *dll_list_prev = get_left_subtree_rightmost_node(owner);
	str_dll_node_t *dll_list_next = dll_list_prev->next;

	new_node->prev = dll_list_prev;
	new_node->next = dll_list_next;

	dll_list_prev->next = new_node;
	dll_list_next->prev = new_node;

	// right most from the left subtree, left most from the right subtree
	// tree is multi-nodal so get the left inside the childs[]
	
}

trie_node_t *trie_search_childs(trie_node_t *parent_node, char searched)
{
	for (int i = 0; i < parent_node->nr_childs; i++) {
		if (parent_node->childs[i]->value == searched) {
			return parent_node->childs[i];
		}
	}
	return NULL;
}

// TODO
int trie_insert(trie_t *trie, char *word, int word_freq)
{
	trie_node_t *curr_node = trie->root;
	if (!curr_node) {
		return 0;
	}

	// start from the left most block of the trie and traverse lexico
	str_dll_node_t *left_bound = trie->keywords;

	int word_len = strlen(word);
	for (int i = 0; i < word_len; i++) {
		char search_value = word[i];

		trie_node_t *next_node = trie_search_childs(curr_node, word[i]);
		if (!next_node) {
			next_node = create_trie_child(word[i]);
			if (!next_node) {
				return 0;
			}
			curr_node->childs[curr_node->nr_childs++] = next_node;
		}

		curr_node = next_node;
		left_bound = next_node->left_bound;

		if (i == word_len - 1) {
			curr_node->keyword = create_dll_node();
			// update_trie_bounds();
		}	
	}

	return 1;
}

// populate a trie with values from word frequency file
int trie_populate(trie_t *trie, FILE *in)
{
	if (!in || !trie) {
		return 0;
	}

	char *word = calloc(sizeof(char), MAX_LEN);
	if (!word) {
		return 0;
	}
	if (fscanf(in, " %99s", word) != 1) {
		free(word);
		return 0;
	}

	// file checked is not required format
	if (strcmp(word, HEADERLINE) != 0) {
		free(word);
		return 0;
	}

	int word_freq;
	while (fscanf(in, " %99s %d", word, &word_freq) == 2) {
		if (!trie_insert(trie, word, word_freq)) {
			free(word);
			return 0;
		}
	}

	free(word);

	return 1;
}
