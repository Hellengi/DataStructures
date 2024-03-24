#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

class hash_table {
public:
	int table_size = 1;
	int node_num = 0;
	std::vector<std::vector<std::pair<std::string, int>>> database {{}};
	unsigned long long string_to_long(std::string);
	void hashing(std::string, int);
	void rehashing();
public:
	void add_node(std::string, int);
	void delete_node(std::string);
	std::vector<int> find_node(std::string, int&);
	void output();
};