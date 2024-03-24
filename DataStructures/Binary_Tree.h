#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>

class binary_root;

class binary_tree {
public:
	friend class binary_root;
	std::string key;
	binary_tree* parent;
	binary_tree* left = nullptr;
	binary_tree* right = nullptr;
	std::vector<int> link;
	binary_tree(binary_tree*, std::string, int);
	void add_node(std::string, int);
	binary_tree* delete_node(std::string);
	binary_tree* find_node(std::string, int&);
	std::vector<std::vector<std::string>> output();
};

class binary_root {
	binary_tree* current_root = nullptr;
public:
	void add_node(std::string, int);
	void delete_node(std::string);
	std::vector<int> find_node(std::string, int&);
	void output();
};