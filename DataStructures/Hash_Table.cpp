#include "Hash_Table.h"

unsigned long long hash_table::string_to_long(std::string line) {
	unsigned long long num = 1;
	unsigned long long mult = 1;
	for (char t : line) {
		if (t >= 'A' && t <= 'Z') num += mult * (t - 'A');
		else if (t >= 'a' && t <= 'z') num += mult * (t - 'a');
		else if (t >= '0' && t <= '9') num += mult * (t - '0' + 26);
		else num += mult * 27;
		mult *= 28;
	}
	return num;
}

void hash_table::hashing(std::string key, int link) {
	if ((float)node_num / (float)table_size >= 0.75) rehashing();
	unsigned long long index = string_to_long(key);
	database[index % table_size].push_back({ key, link });
	node_num++;
}

void hash_table::rehashing() {
	table_size *= 2;
	std::vector<std::pair<std::string, int>> info_1, info_2;
	std::vector<std::vector<std::pair<std::string, int>>> new_database;
	new_database.resize(table_size);
	for (int x = 0; x < table_size / 2; x++) {
		for (std::pair<std::string, int> i : database[x]) {
			unsigned long long index = string_to_long(i.first);
			new_database[index % (table_size)].push_back(i);
		}
	}
	database = new_database;
}

void hash_table::add_node(std::string key, int link) {
	hashing(key, link);
}

void hash_table::delete_node(std::string key) {
	unsigned long long index = string_to_long(key);
	std::vector<std::pair<std::string, int>> found = {};
	for (std::pair<std::string, int> i : database[index % table_size]) {
		if (i.first != key) {
			found.push_back(i);
		}
	}
	database[index % table_size] = found;
}

std::vector<int> hash_table::find_node(std::string key, int& p) {
	unsigned long long index = string_to_long(key);
	std::vector<int> found = {};
	for (std::pair<std::string, int> i : database[index % table_size]) {
		p++;
		std::cout << p << "\n";
		if (i.first == key) {
			found.push_back(i.second);
		}
	}
	if (found.size() == 0) found.push_back(-1);
	return found;
}

void hash_table::output() {
	std::cout << "Хэш-таблица:\n";
	if (node_num == 0) std::cout << "NULL\n";
	else {
		const int size = 10;
		std::string line, line_;
		int temp, max_len = 0, max_first = 0;
		std::vector<std::string> field;
		for (std::vector<std::pair<std::string, int>> i : database) {
			if (i.size() != 0) {
				temp = string_to_long(i[0].first) % table_size;
				line = " " + std::to_string(temp % table_size);
				if (line.size() > size - 2) line = line.substr(0, size - 2);
				if (max_first < line.size()) max_first = line.size();
				while (line.size() < size) line += ' ';
				for (std::pair<std::string, int> j : i) {
					line_ = j.first;
					if (line_.size() > size - 2) line_ = line_.substr(0, size - 2);
					while (line_.size() < size) line_ += ' ';
					line += line_;
				}
				if (max_len < line.size()) max_len = line.size();
				field.push_back(line);
			}
		}
		temp = size - ((size - max_first) / 2);
		line_ = "";
		for (int i = 0; i < max_len; i++) line_ += '-';
		std::cout << line_ << "\n";
		line_[temp] = '|';
		for (std::string line : field) {
			if (line != field[0]) std::cout << line_ << "\n";
			line[temp] = '|';
			std::cout << line << "\n";
		}
		line_[temp] = '-';
		std::cout << line_ << "\n";
	}
}