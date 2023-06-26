#ifndef COMPESSED_PREFIX_TREE_INCLUDED
#define COMPESSED_PREFIX_TREE_INCLUDED


#include <types.c>


typedef struct {
	struct Prefix_Tree* children[2];
	Number32            prefix;
	Number32            prefix_size;
	Byte*               data;
}
Prefix_Tree;


Prefix_Tree* create_prefix_tree()
{
	Prefix_Tree* new_node;
	
	new_node = allocate_memory(sizeof(Prefix_Tree));
	new_node->children[0] = 0;
	new_node->children[1] = 0;
	new_node->prefix_size = 0;
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
	Number       prefix_index;
	Number       prefix_bit;
	Prefix_Tree* next_node;
	
	key_index = 0;
	
	while(key_index < key_size) {
		prefix_index = 0;
		while(
			(prefix_index < root->prefix_size
				|| (!root->children[0]
					&& !root->children[1]
					&& root->prefix_size < sizeof(root->prefix) * 8))
			&& key_index < key_size
		) {
			prefix_bit = (root->prefix >> prefix_index) & 1;
			key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
			
			if(prefix_index < root->prefix_size) {
				if(prefix_bit != key_bit) {
					//расщепить
					
					Prefix_Tree* new_node;
					new_node = create_prefix_tree();
					new_node->prefix = root->prefix >> (prefix_index + 1);
					new_node->prefix_size = root->prefix_size - (prefix_index + 1);
					new_node->children[0] = root->children[0];
					new_node->children[1] = root->children[1];
					new_node->data = root->data;
					
					next_node = create_prefix_tree();
					root->prefix_size = prefix_index;
					root->children[prefix_bit] = new_node;
					root->children[key_bit] = next_node;
					root->data = 0;
					
					break;
				}
			}
			else {
				if(root->data) {
					break;
				}
				
				root->prefix |= key_bit << prefix_index;
				++root->prefix_size;
			}
			
			++key_index;
			++prefix_index;
		}
		
		if(key_index >= key_size) {
			break;
		}
		
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
	Number prefix_index;
	Number prefix_bit;
	
	key_index = 0;
	
	while(key_index < key_size) {
		
		prefix_index = 0;
		while(prefix_index < root->prefix_size && key_index < key_size) {
			prefix_bit = (root->prefix >> prefix_index) & 1;
			key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
			
			if(prefix_bit != key_bit) {
				return 0;
			}
			
			++prefix_index;
			++key_index;
		}
		
		if(key_index >= key_size) {
			if(prefix_index != root->prefix_size) {
				return 0;
			}
			
			break;
		}
		
		key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
		root = root->children[key_bit];
		
		if(!root) {
			return 0;
		}
		
		++key_index;
	}
	
	if(!root->data) {
		return 0;
	}
	
	return root;
}


void delete_from_prefix_tree(Prefix_Tree* root, Byte* key, Number key_size, Number key_index)
{
	Number       key_bit;
	Number       prefix_index;
	Number       prefix_bit;
	Prefix_Tree* next_node;
	
	if(root && key_index == key_size) {
		root->data = 0;
		return;
	}
	
	if(root && key_index < key_size) {
		prefix_index = 0;
		while(prefix_index < root->prefix_size && key_index < key_size) {
			prefix_bit = (root->prefix >> prefix_index) & 1;
			key_bit = (key[key_index / 8] >> (key_index % 8)) & 1;
			
			if(prefix_bit != key_bit) {
				return;
			}
			
			++prefix_index;
			++key_index;
		}
		
		if(key_index == key_size) {
			root->data = 0;
			return;
		}
		
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


Number level = 0;
void print_prefix_tree(Prefix_Tree* root)
{
	Number i;
	
	if(root) {
		if(!root->children[0] && !root->children[1] && root->prefix_size) {
			for(i = 0; i < level; ++i) {
				print("  ");
			}
			
			for(i = 0; i < root->prefix_size; ++i) {
				if(root->prefix & (1 << i)) {
					print("1");
				}
				else {
					print("0");
				}
			}
			
			print("\n");
		}
		
		if(root->children[0]) {
			for(i = 0; i < level; ++i) {
				print("  ");
			}
			
			for(i = 0; i < root->prefix_size; ++i) {
				if(root->prefix & (1 << i)) {
					print("1");
				}
				else {
					print("0");
				}
			}
			
			print("[0]\n");
			++level;
			print_prefix_tree(root->children[0]);
			--level;
		}
		
		if(root->children[1]) {
			for(i = 0; i < level; ++i) {
				print("  ");
			}
			
			for(i = 0; i < root->prefix_size; ++i) {
				if(root->prefix & (1 << i)) {
					print("1");
				}
				else {
					print("0");
				}
			}
			
			print("[1]\n");
			++level;
			print_prefix_tree(root->children[1]);
			--level;
		}
	}
}


#endif//COMPESSED_PREFIX_TREE_INCLUDED

/*
Byte   key[512];
Number key_size = 0;
Byte*  default_console_writer;


void print_tree_keys(Prefix_Tree* tree, Number key_size)
{
	Number i;
	
	if(tree) {
		for(i = 0; i < tree->prefix_size; ++i) {
			if(tree->prefix & (1 << i)) {
				key[key_size / 8] |= 1 << (key_size % 8);
			}
			else {
				key[key_size / 8] &= ~(1 << (key_size % 8));
			}
			
			++key_size;
		}
		
		if(tree->data) {
			write_bytes_in_console(default_console_writer, key, key_size / 8);
			write_bytes_in_console(default_console_writer, "\n", 1);
		}
		
		if(tree->children[0]) {
			key[key_size / 8] &= ~(1 << (key_size % 8));
			print_tree_keys(tree->children[0], key_size + 1);
		}
		
		if(tree->children[1]) {
			key[key_size / 8] |= 1 << (key_size % 8);
			print_tree_keys(tree->children[1], key_size + 1);
		}
	}
}


Number main(Number number_of_arguments, Byte** arguments)
{
	Byte* default_console_reader;
	Byte  c;
	
	Prefix_Tree* t;
	
	t = create_prefix_tree();

	default_console_reader = get_default_console_reader();
	default_console_writer = get_default_console_writer();
	
	while(read_bytes_from_console(default_console_reader, &c, 1)) {
		if(c == '\r' || c == '\n') {
			do {
				if(!read_bytes_from_console(default_console_reader, &c, 1)) {
					break;
				}
			}
			while(c == '\r' || c == '\n');

			add_in_prefix_tree(t, key, key_size * 8, 1);
			
			key_size = 0;
			key[key_size] = c;
			++key_size;
		}
		else {
			if(key_size < sizeof(key)) {
				key[key_size] = c;
				++key_size;
			}
			else {
				print_error("ключ не вмещается\n");
			}
		}
	}
	
	print_error("total size: %d\n", calculate_prefix_tree_size(t));
	
	//print_prefix_tree(t);
	print_tree_keys(t, 0);
	
	destroy_prefix_tree(t);
	
	return 0;
}*/