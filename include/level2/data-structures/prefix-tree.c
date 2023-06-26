#ifndef PREFIX_TREE_INCLUDED
#define PREFIX_TREE_INCLUDED


#include <types.c>


typedef struct {
	struct Prefix_Tree* children[2];
	Byte*               data;
}
Prefix_Tree;


Prefix_Tree* create_prefix_tree()
{
	Prefix_Tree* new_node;
	
	new_node = allocate_memory(sizeof(Prefix_Tree));
	new_node->children[0] = 0;
	new_node->children[1] = 0;
	new_node->data = 0;
	
	return new_node;
}


void destroy_prefix_tree(Prefix_Tree* root)
{
	if(!root) {
		return;
	}
	
	destroy_prefix_tree(root->children[0]);
	destroy_prefix_tree(root->children[1]);
	
	free_memory(root);
}


void add_in_prefix_tree(Prefix_Tree* root, Byte* key, Number key_size, Byte* data)
{
	Number       key_index;
	Number       key_bit;
	Prefix_Tree* next_node;
	
	key_index = 0;
	
	while(key_index < key_size) {
		key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
		
		next_node = root->children[key_bit];
		
		if(!next_node) {
			next_node = create_prefix_tree();
			root->children[key_bit] = next_node;
		}
		
		root = next_node;
		
		++key_index;
	}
	
	root->data = data;
}


Prefix_Tree* find_in_prefix_tree(Prefix_Tree* root, Byte* key, Number key_size)
{
	Number key_index;
	Number key_bit;
	
	key_index = 0;
	
	while(key_index < key_size) {
		key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
		
		root = root->children[key_bit];
		
		if(!root) {
			return 0;
		}
		
		++key_index;
	}
	
	return root;
}


void delete_from_prefix_tree(Prefix_Tree* root, Byte* key, Number key_size, Number key_index)
{
	Number       key_bit;
	Prefix_Tree* next_node;
	
	if(root && key_index == key_size) {
		root->data = 0;
		return;
	}
	
	if(root && key_index < key_size) {
		key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
		
		next_node = root->children[key_bit];
		delete_from_prefix_tree(next_node, key, key_size, key_index + 1);
		
		if(!next_node->data && !next_node->children[0] && !next_node->children[1]) {
			destroy_prefix_tree(next_node);
			root->children[key_bit] = 0;
		}
	}
}


Number calculate_prefix_tree_size(Prefix_Tree* root)
{
	Number size;
	
	size = 0;
	
	if(root) {
		size += calculate_prefix_tree_size(root->children[0]);
		size += calculate_prefix_tree_size(root->children[1]);
		size += sizeof(Prefix_Tree);
	}
	
	return size;
}


#endif//PREFIX_TREE_INCLUDED

/*
Number main()
{
	Prefix_Tree* t;
	
	t = create_prefix_tree();
	
	add_in_prefix_tree(t, "1", 8, 1);
	add_in_prefix_tree(t, "2", 8, 2);
	add_in_prefix_tree(t, "11", 16, 3);
	print("total size: %d\n", calculate_prefix_tree_size(t));
	
	delete_from_prefix_tree(t, "1", 8, 0);
	delete_from_prefix_tree(t, "2", 8, 0);
	delete_from_prefix_tree(t, "11", 16, 0);
	print("size after remove node: %d\n", calculate_prefix_tree_size(t));
	
	add_in_prefix_tree(t, "1", 8, 1);
	add_in_prefix_tree(t, "2", 8, 2);
	add_in_prefix_tree(t, "11", 16, 3);
	print("total size: %d\n", calculate_prefix_tree_size(t));
	
	print("%d\n", find_in_prefix_tree(t, "1", 8));
	print("%d\n", find_in_prefix_tree(t, "2", 8));
	print("%d\n", find_in_prefix_tree(t, "11", 16));
	print("%d\n", find_in_prefix_tree(t, "12", 16));
	
	destroy_prefix_tree(t);
	
	return 0;
}*/