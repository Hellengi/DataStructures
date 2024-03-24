#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>

enum color { BLACK, RED };

class red_black_root;

class red_black_tree {
public:
	friend class red_black_root;
	std::string key;
	red_black_tree* parent;
	red_black_tree* left = nullptr;
	red_black_tree* right = nullptr;
	std::vector<int> link;
	color color;
	red_black_tree(red_black_tree*, std::string, int);
	void rotate_left(int&);
	void rotate_right(int&);
	void add_node(std::string, int, int&);
	void a_balancing(int&);
	red_black_tree* delete_node(std::string, int&);
	void d_balancing(int&);
	red_black_tree* find_node(std::string, int&);
	std::vector<std::vector<std::string>> output();
};

class red_black_root {
	red_black_tree* current_root = nullptr;
public:
	void add_node(std::string, int, int&);
	void delete_node(std::string, int&);
	std::vector<int> find_node(std::string, int&);
	void output();
};