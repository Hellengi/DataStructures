#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "Hash_Table.h"
#include "Binary_Tree.h"
#include "Red_Black_Tree.h"

struct data {
	char name[12];
	char prod[12];
	int volume;
};

class file_management {
	std::string random_word();
public:
	file_management();
	void new_file(std::string, int);
	void output_from_txt(std::string);
	void txt_to_bin(std::string, std::string);
	void bin_to_txt(std::string, std::string);
	void output_from_bin(std::string);
	std::string find_record(std::string, int);
	void bin_to_tree_1(std::string, hash_table*);
	void bin_to_tree_2(std::string, binary_root*);
	void bin_to_tree_3(std::string, red_black_root*, int&, int&);
};