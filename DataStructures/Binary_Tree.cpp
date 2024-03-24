#include "Binary_Tree.h"

binary_tree::binary_tree(binary_tree* parent, std::string key, int link) {
	this->key = key;
	this->parent = parent;
	this->link.push_back(link);
}

void binary_tree::add_node(std::string key, int link) {
	if (key == this->key) {
		this->link.push_back(link);
	}
	else if (key < this->key) {
		if (left != nullptr) left->add_node(key, link);
		else {
			left = new binary_tree(this, key, link);
		}
	}
	else {
		if (right != nullptr) right->add_node(key, link);
		else {
			right = new binary_tree(this, key, link);
		}
	}
}

binary_tree* binary_tree::delete_node(std::string key) {
	int p = 0;
	binary_tree* pivot = find_node(key, p);
	if (pivot != nullptr) {
		if (pivot->left != nullptr and pivot->right != nullptr) {
			binary_tree* new_pivot = pivot->left;
			while (new_pivot->right != nullptr) new_pivot = new_pivot->right;
			pivot->key = new_pivot->key;
			pivot->link = new_pivot->link;
			pivot = new_pivot;
		}
		if (pivot->left != nullptr) {
			pivot->left->parent = pivot->parent;
			if (pivot->parent != nullptr) {
				if (pivot->parent->left == pivot) pivot->parent->left = pivot->left;
				else if (pivot->parent->right == pivot) pivot->parent->right = pivot->left;
			}
		}
		else if (pivot->right != nullptr) {
			pivot->right->parent = pivot->parent;
			if (pivot->parent != nullptr) {
				if (pivot->parent->left == pivot) pivot->parent->left = pivot->right;
				else if (pivot->parent->right == pivot) pivot->parent->right = pivot->right;
			}
		}
		else {
			if (pivot->parent != nullptr) {
				if (pivot->parent->left == pivot) pivot->parent->left = nullptr;
				else if (pivot->parent->right == pivot) pivot->parent->right = nullptr;
			}
		}
		delete pivot;
	}
	pivot = this;
	while (pivot->parent != nullptr) pivot = pivot->parent;
	return pivot;
}

binary_tree* binary_tree::find_node(std::string key, int& p) {
	if (key == this->key) return this;
	else if (key < this->key) {
		if (left != nullptr) {
			p++;
			return left->find_node(key, p);
		}
		else return nullptr;
	}
	else {
		if (right != nullptr) {
			p++;
			return right->find_node(key, p);
		}
		else return nullptr;
	}
}

std::vector<std::vector<std::string>> binary_tree::output() {
	const int size = 24;
	std::string line = key;
	if (line.size() > size - 4) line = line.substr(0, size - 4);
	while (line.size() < size) line += " ";
	line[size - 1] = 'E';
	if (left == nullptr and right == nullptr) {
		std::vector<std::vector<std::string>> field {{ line }};
		return field;
	}
	int height, x;
	std::string space(size, ' ');
	std::vector<std::vector<std::string>> field, left_field, right_field;
	if (right != nullptr) {
		field = right->output();
		height = field.size();
		for (x = 0; x < height; x++) {
			right_field.push_back({ space });
			right_field[x].insert(right_field[x].end(), field[x].begin(), field[x].end());
		}
	}
	if (left != nullptr) {
		field = left->output();
		height = field.size();
		for (x = 0; x < height; x++) {
			left_field.push_back({ space });
			left_field[x].insert(left_field[x].end(), field[x].begin(), field[x].end());
		}
	}
	right_field.insert(right_field.end(), left_field.begin(), left_field.end());
	right_field[0][0] = line;
	return right_field;
}

void binary_root::add_node(std::string key, int link) {
	if (current_root != nullptr) current_root->add_node(key, link);
	else current_root = new binary_tree(nullptr, key, link);
	while (current_root->parent != nullptr) current_root = current_root->parent;
}

void binary_root::delete_node(std::string key) {
	if (current_root == nullptr);
	else if (current_root->left == nullptr and current_root->right == nullptr and current_root->key == key) {
		delete current_root;
		current_root = nullptr;
	}
	else current_root = current_root->delete_node(key);
}

std::vector<int> binary_root::find_node(std::string key, int& p) {
	if (current_root == nullptr) return { -1 };
	binary_tree* found = current_root->find_node(key, p);
	if (found == nullptr) return { -1 };
	else return found->link;
}

void binary_root::output() {
	std::cout << "Ѕинарное дерево:\n";
	if (current_root == nullptr) std::cout << "NULL\n";
	else {
		std::vector<std::vector<std::string>> field = current_root->output();
		int br, size = field[0][0].size();
		for (int y = 0; y < field.size(); y++) {
			for (int x = 1; x < field[y].size(); x++) {
				if (field[y][x][size - 1] == ' ');
				else if (field[y][x - 1][size - 1] != ' ') {
					for (int b = size - 2; b >= 0; b--) {
						if (field[y][x - 1][b] == ' ') field[y][x - 1][b] = '_';
						else break;
					}
				}
				else {
					for (int i = x - 1; i >= 0; i--) {
						for (int j = y - 1; j >= 0; j--) {
							if (field[j][i][size - 1] != ' ') {
								for (br = size - 2; br >= 0; br--) {
									if (field[j][i][br] != ' ' && field[j][i][br] != '_') break;
								}
								for (int a = j + 1; a < y; a++) {
									field[a][i][br] = '|';
								}
								field[y][i][br] = '\\';
								for (int b = br; b < size; b++) {
									if (field[y][i][b] == ' ') field[y][i][b] = '_';
								}
								for (int a = i + 1; a < x; a++) {
									for (int b = 0; b < size; b++) {
										if (field[y][a][b] == ' ') field[y][a][b] = '_';
									}
								}
								i = 0;
								j = 0;
							}
						}
					}
				}
			}
		}
		std::string temp_s1, temp_s2;
		for (std::vector<std::string> temp_vector : field) {
			for (std::string temp_string : temp_vector) {
				temp_string[size - 1] = temp_string[size - 2];
				for (br = size - 1; br >= 0; br--) {
					if (temp_string[br] != ' ' && temp_string[br] != '_') break;
				}
				std::cout << temp_string;
			}
			std::cout << "\n";
		}
	}
}