#include "red_black_Tree.h"

red_black_tree::red_black_tree(red_black_tree* parent, std::string key, int link) {
	this->key = key;
	this->parent = parent;
	this->link.push_back(link);
	if (parent == nullptr) color = BLACK;
	else color = RED;
}

void red_black_tree::rotate_left(int& count) {
	if (parent) (parent->left == this ? parent->left : parent->right) = right;
	right->parent = parent;
	parent = right;
	if (right->left) right->left->parent = this;
	right = right->left;
	parent->left = this;
	count++;
}

void red_black_tree::rotate_right(int& count) {
	if (parent) (parent->left == this ? parent->left : parent->right) = left;
	left->parent = parent;
	parent = left;
	if (left->right) left->right->parent = this;
	left = left->right;
	parent->right = this;
	count++;
}

void red_black_tree::add_node(std::string key, int link, int& count) {
	if (key == this->key) {
		this->link.push_back(link);
	}
	else if (key < this->key) {
		if (left != nullptr) left->add_node(key, link, count);
		else {
			left = new red_black_tree(this, key, link);
			left->a_balancing(count);
		}
	}
	else {
		if (right != nullptr) right->add_node(key, link, count);
		else {
			right = new red_black_tree(this, key, link);
			right->a_balancing(count);
		}
	}
}

void red_black_tree::a_balancing(int& count) {
	red_black_tree* grandparent = parent != nullptr ? parent->parent : nullptr;
	red_black_tree* uncle = grandparent != nullptr ? grandparent->left == parent ? grandparent->right : grandparent->left : nullptr;
	if (parent == nullptr) color = BLACK;
	else if (parent->color == BLACK or grandparent == nullptr) return;
	else if (uncle != nullptr and uncle->color == RED) {
		parent->color = BLACK;
		uncle->color = BLACK;
		grandparent->color = RED;
		grandparent->a_balancing(count);
	}
	else if (grandparent->left != nullptr and grandparent->left->right == this) {
		parent->rotate_left(count);
		left->a_balancing(count);
	}
	else if (grandparent->right != nullptr and grandparent->right->left == this) {
		parent->rotate_right(count);
		right->a_balancing(count);
	}
	else if (grandparent->left != nullptr and grandparent->left->left == this) {
		grandparent->color = RED;
		parent->color = BLACK;
		grandparent->rotate_right(count);
	}
	else if (grandparent->right != nullptr and grandparent->right->right == this) {
		grandparent->color = RED;
		parent->color = BLACK;
		grandparent->rotate_left(count);
	}
}

red_black_tree* red_black_tree::delete_node(std::string key, int& count) {
	int p = 0;
	red_black_tree* pivot = find_node(key, p);
	if (pivot != nullptr) {
		if (pivot->left != nullptr and pivot->right != nullptr) {
			red_black_tree* new_pivot = pivot->left;
			while (new_pivot->right != nullptr) new_pivot = new_pivot->right;
			pivot->key = new_pivot->key;
			pivot->link = new_pivot->link;
			pivot = new_pivot;
		}
		if (pivot->color == RED) {
			pivot->parent->left == pivot ? pivot->parent->left = nullptr : pivot->parent->right = nullptr;
		}
		else if (pivot->left != nullptr or pivot->right != nullptr) {
			red_black_tree* new_pivot = pivot->left != nullptr ? pivot->left : pivot->right;
			pivot->key = new_pivot->key;
			pivot->link = new_pivot->link;
			pivot->left = nullptr;
			pivot->right = nullptr;
			pivot = new_pivot;
		}
		else {
			pivot->d_balancing(count);
			pivot->parent->left == pivot ? pivot->parent->left = nullptr : pivot->parent->right = nullptr;
		}
		delete pivot;
	}
	pivot = this;
	while (pivot->parent != nullptr) pivot = pivot->parent;
	return pivot;
}

void red_black_tree::d_balancing(int& count) {
	red_black_tree* sibling = parent != nullptr ? parent->left == this ? parent->right : parent->left : nullptr;
	if (parent == nullptr);
	else if (sibling->color == RED) {
		parent->color = RED;
		sibling->color = BLACK;
		parent->left == this ? parent->rotate_left(count) : parent->rotate_right(count);
		d_balancing(count);
	}
	else if ((sibling->left == nullptr or sibling->left->color == BLACK) and (sibling->right == nullptr or sibling->right->color == BLACK)) {
		sibling->color = RED;
		if (parent->color == BLACK) parent->d_balancing(count);
		else parent->color = BLACK;
	}
	else if (parent->left == this and (sibling->right == nullptr or sibling->right->color == BLACK)) {
		sibling->color = RED;
		sibling->left->color = BLACK;
		sibling->rotate_right(count);
		d_balancing(count);
	}
	else if (parent->right == this and (sibling->left == nullptr or sibling->left->color == BLACK)) {
		sibling->color = RED;
		sibling->right->color = BLACK;
		sibling->rotate_left(count);
		d_balancing(count);
	}
	else if (parent->left == this and sibling->right != nullptr) {
		sibling->right->color = BLACK;
		sibling->color = parent->color;
		parent->color = BLACK;
		parent->rotate_left(count);
	}
	else if (parent->right == this and sibling->left != nullptr) {
		sibling->left->color = BLACK;
		sibling->color = parent->color;
		parent->color = BLACK;
		parent->rotate_right(count);
	}
}

red_black_tree* red_black_tree::find_node(std::string key, int& p) {
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

std::vector<std::vector<std::string>> red_black_tree::output() {
	const int size = 24;
	std::string line = key;
	if (line.size() > size - 4) line = line.substr(0, size - 4);
	while (line.size() < size) line += " ";
	if (color == RED) line[size - 1] = 'R';
	else line[size - 1] = 'B';
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

void red_black_root::add_node(std::string key, int link, int& count) {
	if (current_root != nullptr) current_root->add_node(key, link, count);
	else current_root = new red_black_tree(nullptr, key, link);
	while (current_root->parent != nullptr) current_root = current_root->parent;
}

void red_black_root::delete_node(std::string key, int& count) {
	if (current_root == nullptr);
	else if (current_root->left == nullptr and current_root->right == nullptr and current_root->key == key) {
		delete current_root;
		current_root = nullptr;
	}
	else current_root = current_root->delete_node(key, count);
}

std::vector<int> red_black_root::find_node(std::string key, int& p) {
	if (current_root == nullptr) return { -1 };
	red_black_tree* found = current_root->find_node(key, p);
	if (found == nullptr) return { -1 };
	else return found->link;
}

void red_black_root::output() {
	std::cout << "Черно-красное дерево:\n";
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
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		for (std::vector<std::string> temp_vector : field) {
			for (std::string temp_string : temp_vector) {
				if (temp_string[size - 1] == 'R') SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				else if (temp_string[size - 1] == 'B') SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				temp_string[size - 1] = temp_string[size - 2];
				for (br = size - 1; br >= 0; br--) {
					if (temp_string[br] != ' ' && temp_string[br] != '_') break;
				}
				temp_s1 = temp_string.substr(0, br + 1);
				temp_s2 = temp_string.substr(br + 1);
				std::cout << temp_s1;
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << temp_s2;
			}
			std::cout << "\n";
		}
	}
}