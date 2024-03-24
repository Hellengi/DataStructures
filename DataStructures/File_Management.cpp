#include "File_Management.h"
file_management::file_management() {
	srand(time(nullptr));
}
std::string file_management::random_word() {
	std::string line = "";
	int len = rand() % 8 + 3;
	while (len > 0) {
		len--;
		line.push_back(97 + rand() % 26);
	}
	return line;
}

void file_management::new_file(std::string file_name, int num = 0) {
	std::fstream file(file_name, std::ios::out);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	if (num == 0) {
		std::string line;
		std::cout << "¬ведите содержимое файла. ¬ведите exit дл¤ завершени¤ работы с файлом.\n";
		std::cout << "”кажите через пробел: название завода (меньше 12 символов), производимый продукт (меньше 12 символов), объем производства в неделю\n";
		while (true) {
			getline(std::cin, line);
			if (line != "exit") file << line << std::endl;
			else break;
		}
	}
	else {
		while (num > 0) {
			num--;
			file << random_word() << " " << random_word() << " " << std::to_string(rand()) << std::endl;
		}
	}
	file.close();
}

void file_management::output_from_txt(std::string file_name) {
	std::fstream file(file_name, std::ios::in);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	std::string line;
	while (getline(file, line)) {
		if (line != "")	std::cout << line << std::endl;
	}
	file.close();
}

void file_management::txt_to_bin(std::string file_name, std::string new_file_name) {
	std::fstream file(file_name, std::ios::in), new_file(new_file_name, std::ios::binary | std::ios::out);
	if (!(file.is_open()) or !(new_file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	std::string line;
	std::vector<data> table;
	data data;
	std::string name = "", prod = "";
	int volume = 0, count = 0;
	bool swt = true;
	while (getline(file, line)) {
		line += '\n';
		for (char x : line) {
			if (x == '\n' or count == 3) {
				for (int t = 0; t < name.length(); t++) data.name[t] = name[t];
				data.name[name.length()] = '\0';
				for (int t = 0; t < prod.length(); t++) data.prod[t] = prod[t];
				data.prod[prod.length()] = '\0';
				data.volume = volume;
				name = "";
				prod = "";
				volume = 0;
				count = 0;
				table.push_back(data);
				break;
			}
			if (x == ' ' && swt == false) {
				swt = true;
				count++;
			}
			else if (x != ' ') {
				swt = false;
				switch (count) {
				case(0): name.push_back(x); break;
				case(1): prod.push_back(x); break;
				case(2): volume = volume * 10 + x - '0';
				}
			}
		}
	}
	new_file.write((char*)&(table[0]), table.size() * sizeof(table[0]));
	file.close();
	new_file.close();
}

void file_management::bin_to_txt(std::string file_name, std::string new_file_name) {
	std::fstream file(file_name, std::ios::binary | std::ios::in), new_file(new_file_name, std::ios::out);
	if (!(file.is_open()) or !(new_file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	data data;
	while (file.read((char*)&data, sizeof(data))) {
		new_file << data.name << " " << data.prod << " " << data.volume << "\n";
	}
	file.close();
	new_file.close();
}

void file_management::output_from_bin(std::string file_name) {
	std::fstream file(file_name, std::ios::binary | std::ios::in);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	data data;
	while (file.read((char*)&data, sizeof(data))) {
		std::cout << data.name << " " << data.prod << " " << data.volume << "\n";
	}
	file.close();
}

std::string file_management::find_record(std::string file_name, int num) {
	std::fstream file(file_name, std::ios::binary | std::ios::in);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return "";
	}
	data data;
	std::string line = "";
	file.seekg(num * sizeof(data));
	file.read((char*)&data, sizeof(data));
	if (!(file.good())) return "";
	file.close();
	for (char t : data.name) {
		if (t == '\0') break;
		line.push_back(t);
	}
	line.push_back(' ');
	for (char t : data.prod) {
		if (t == '\0') break;
		line.push_back(t);
	}
	line.push_back(' ');
	line += std::to_string(data.volume);
	return line;
}

void file_management::bin_to_tree_1(std::string file_name, hash_table* tree) {
	std::fstream file(file_name, std::ios::binary | std::ios::in);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	data data;
	int num = 0;
	while (file.read((char*)&data, sizeof(data))) {
		tree->add_node(data.name, num);
		num++;
	}
	file.close();
}

void file_management::bin_to_tree_2(std::string file_name, binary_root* tree) {
	std::fstream file(file_name, std::ios::binary | std::ios::in);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	data data;
	int num = 0;
	while (file.read((char*)&data, sizeof(data))) {
		tree->add_node(data.name, num);
		num++;
	}
	file.close();
}

void file_management::bin_to_tree_3(std::string file_name, red_black_root* tree, int& count, int& num_) {
	std::fstream file(file_name, std::ios::binary | std::ios::in);
	if (!(file.is_open())) {
		std::cout << "Ошибка открыти¤ файла\n";
		return;
	}
	data data;
	int num = 0;
	while (file.read((char*)&data, sizeof(data))) {
		tree->add_node(data.name, num, count);
		num++;
		num_++;
	}
	file.close();
}