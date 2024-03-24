#include "File_Management.h"
int current_time() {
	return std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count() % 2147483648;
}
int main() {
	setlocale(LC_ALL, "Russian");
	int tr, op, index;
	int number;
	std::string key, ney;
	hash_table* tree_1 = new hash_table();
	binary_root* tree_2 = new binary_root();
	red_black_root* tree_3 = new red_black_root();
	file_management* file_manager = new file_management();
	std::cout << "Выберите используемую систему поиска\n";
	std::cout << "1 - хеш-таблица\n";
	std::cout << "2 - двоичное дерево поиска\n";
	std::cout << "3 - черно-красное дерево\n";
	std::cin >> tr;
	std::cout << "Работа с системой поиска:\n";
	std::cout << "1 - Добавить элемент\n";
	std::cout << "2 - Удалить элемент\n";
	std::cout << "3 - Найти элемент\n";
	std::cout << "4 - Вывести на экран\n";
	std::cout << "Управление файлами:\n";
	std::cout << "5 - Создание файла со случайными записями\n";
	std::cout << "6 - Вывод содержимого текстового файла\n";
	std::cout << "7 - Сконвертировать текстовый файл в бинарный\n";
	std::cout << "8 - Сконвертировать бинарный файл в текстовый\n";
	std::cout << "9 - Вывод содержимого бинарного файла\n";
	std::cout << "10 - Найти запись по порядковому номеру\n";
	std::cout << "11 - Добавить содержимое бинарного файла в систему поиска\n";
	std::cout << "12 - Поиск записи в файле с использованием системы поиска\n";
	std::cout << "13 - Вывод емкостной сложности\n";
	std::cout << "0 - Завершить работу\n";
	while (true) {
		std::cout << "Введите номер операции, которую требуется выполнить:\n";
		std::cin >> op;
		switch (op) {
		case(1): {
			std::cout << "Введите ключ элемента\n";
			std::cin >> key;
			std::cout << "Введите индекс элемента\n";
			std::cin >> index;
			int m = 0;
			switch (tr) {
			case(1): tree_1->add_node(key, index); break;
			case(2): tree_2->add_node(key, index); break;
			case(3): tree_3->add_node(key, index, m); break;
			}
			break;
		}
		case(2): {
			std::cout << "Введите ключ элемента\n";
			std::cin >> key;
			int m = 0;
			switch (tr) {
			case(1): tree_1->delete_node(key); break;
			case(2): tree_2->delete_node(key); break;
			case(3): tree_3->delete_node(key, m); break;
			}
			break;
		}
		case(3): {
			std::cout << "Введите ключ элемента\n";
			std::cin >> key;
			int p = 0;
			switch (tr) {
			case(1): std::cout << tree_1->find_node(key, p)[0] << "\n"; break;
			case(2): std::cout << tree_2->find_node(key, p)[0] << "\n"; break;
			case(3): std::cout << tree_3->find_node(key, p)[0] << "\n"; break;
			}
			break;
		}
		case(4): {
			switch (tr) {
			case(1): tree_1->output(); break;
			case(2): tree_2->output(); break;
			case(3): tree_3->output(); break;
			}
			break;
		}
		case(5): {
			std::cout << "Введите название файла\n";
			std::cin >> key;
			std::cout << "Введите количество записей\n";
			std::cin >> index;
			file_manager->new_file(key, index);
			number = index;
			break;
		}
		case(6): {
			std::cout << "Введите название файла\n";
			std::cin >> key;
			file_manager->output_from_txt(key);
			break;
		}
		case(7): {
			std::cout << "Введите название текстового файла\n";
			std::cin >> key;
			std::cout << "Введите название нового файла\n";
			std::cin >> ney;
			file_manager->txt_to_bin(key, ney);
			break;
		}
		case(8): {
			std::cout << "Введите название бинарного файла\n";
			std::cin >> key;
			std::cout << "Введите название нового файла\n";
			std::cin >> ney;
			file_manager->bin_to_txt(key, ney);
			break;
		}
		case(9): {
			std::cout << "Введите название файла\n";
			std::cin >> key;
			file_manager->output_from_bin(key);
			break;
		}
		case(10): {
			std::cout << "Введите название файла\n";
			std::cin >> key;
			std::cout << "Введите индекс записи\n";
			std::cin >> index;
			std::cout << file_manager->find_record(key, index) << "\n";
			break;
		}
		case(11): {
			std::cout << "Введите название файла\n";
			std::cin >> key;
			switch (tr) {
			case(1): file_manager->bin_to_tree_1(key, tree_1); break;
			case(2): file_manager->bin_to_tree_2(key, tree_2); break;
			case(3): {
				int n = 0, m = 0;
				file_manager->bin_to_tree_3(key, tree_3, n, m);
				std::cout << "Общее количество выполненных поворотов: " << n << "\n";
				std::cout << "Количество добавленных записей: " << m << "\n";
				std::cout << "Среднее количество поворотов: " << (double)n / m << "\n";
				break;
			}
			}
			break;
		}
		case(12): {
			std::cout << "Введите название файла\n";
			std::cin >> key;
			std::cout << "Введите ключ элемента\n";
			std::cin >> ney;
			int q = current_time();
			int p = 0;
			switch (tr) {
			case(1): std::cout << file_manager->find_record(key, tree_1->find_node(ney, p)[0]) << '\n'; break;
			case(2): std::cout << file_manager->find_record(key, tree_2->find_node(ney, p)[0]) << '\n'; break;
			case(3): std::cout << file_manager->find_record(key, tree_3->find_node(ney, p)[0]) << '\n'; break;
			}
			std::cout << "Количество операций сравнения: " << p << "\n";
			q = current_time() - q;
			std::cout << "Затраченное время: " << q << " миллисекунд\n";
			break;
		}
		case(13): {
			switch (tr) {
			case(1): {
				std::string str = "            ";
				int a = 0;
				std::cout << sizeof(*tree_1) + tree_1->node_num * (sizeof(str) + sizeof(a)) << " байт\n"; break;
			}
			case(2): {
				binary_tree* tree = new binary_tree(nullptr, "", 0);
				std::cout << sizeof(*tree) << " байт\n"; break;
			}
			case(3): {
				red_black_tree* tree = new red_black_tree(nullptr, "", 0);
				std::cout << sizeof(*tree) << " байт\n"; break;
			}
			}
			break;
		}
		case(0): exit(0);
		}
	}
}