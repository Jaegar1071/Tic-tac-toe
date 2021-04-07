#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <map>
#include <string> 
#include <vector> 
#include <algorithm>

//Вывод текущей позиции
void echo(std::vector<std::string> arr) {
	// Очистка консоли
	system("cls");
	// Вывод позиции
	std::cout << std::setw(50) << "" << std::setw(5) << arr[0] << std::setw(5) << arr[1] << std::setw(5) << arr[2] << std::endl;
	std::cout << std::setw(50) << "" << std::setw(5) << arr[3] << std::setw(5) << arr[4] << std::setw(5) << arr[5] << std::endl;
	std::cout << std::setw(50) << "" << std::setw(5) << arr[6] << std::setw(5) << arr[7] << std::setw(5) << arr[8] << std::endl;
}

// Конец партии
void end(int life) {
	if (life == 0) {
		std::cout << std::setw(60) << "DRAW" << std::endl;
	}
	if (life == 2) {
		std::cout << std::setw(50) << "CROSSE WON!" << std::endl;
	}
	if (life == 3) {
		std::cout << std::setw(50) << "NOUGHT WON!" << std::endl;
	}
	std::cout << std::setw(50) << "Click ENTER to play again" << std::endl;
	std::cout << std::setw(50) << "Click another button to end" << std::endl;
}

// Проверка конца партии
// Выводит: 0 - ничья, 1 - партия играется, 2 - выиграл Крестик, 3 -выиграл Нолик
int check(std::vector<std::string> arr, std::vector<int> moves) {
	// Массив для преобразования знака победившего в код
	std::map<std::string, int> transform = { {"X",2},{"0",3} };
	// Если ряд закончен (8 случаев)
	if (arr[0] == arr[1] and arr[1] == arr[2]) {
		return(transform[arr[0]]);
	}
	if (arr[3] == arr[4] and arr[4] == arr[5]) {
		return(transform[arr[3]]);
	}
	if (arr[6] == arr[7] and arr[7] == arr[8]) {
		return(transform[arr[6]]);
	}
	if (arr[0] == arr[3] and arr[3] == arr[6]) {
		return(transform[arr[0]]);
	}
	if (arr[1] == arr[4] and arr[4] == arr[7]) {
		return(transform[arr[1]]);
	}
	if (arr[2] == arr[5] and arr[5] == arr[8]) {
		return(transform[arr[2]]);
	}
	if (arr[0] == arr[4] and arr[4] == arr[8]) {
		return(transform[arr[0]]);
	}
	if (arr[2] == arr[4] and arr[4] == arr[6]) {
		return(transform[arr[2]]);
	}
	// Если никто не выиграл и все клетки заняты
	if (moves.size() == 9) {
		return(0);
	}
	// Если игра может быть продолжена
	return(1);
}

int main() {
	int fl = 0;
	// Установка начальных значений
	std::string flag = "X";
	std::vector<int> moves;
	std::vector<std::string> arr = { "1","2","3","4","5","6","7","8","9" };
	// Вывод начальной позиции
	echo(arr);
	// Главный цикл
	while (true) {
		// Если игра была перезапущена
		if (fl == 0) {
			std::cout << "Restart!" << std::endl;
			// Переустановка начальных значений
			flag = "X";
			moves = {};
			arr = { "1","2","3","4","5","6","7","8","9" };
			// Вывод начальной позиции
			echo(arr);
		}
		// Партия
		while (fl == 0) {
			// Обработка нажатий клавиатуры
			if (_kbhit()) {
				int ekey = _getch();
				// Если нажата клавиша 1-9
				if (ekey > 48 and ekey < 58) {
					// Преобразование значения ключа из 49-57 в 0-8
					int key = ekey - 49;
					//Если поле ещё не занято 
					if (find(moves.begin(), moves.end(), key) == moves.end()) {
						// Запись хода
						moves.push_back(key);
						arr[key] = flag;
						// Вывод новой позиции
						echo(arr);
						// Проверка конца партии
						int life = check(arr, moves);
						// Если партия закночилась
						if (life != 1) {
							end(life);
							fl = 1;
						}
						// Переворот флага
						if (flag == "X") {
							flag = "0";
						}
						else {
							flag = "X";
						}
						// Завершение работы по нажатию клавиши ESСAPE
						if (ekey == 27) {
							exit(0);
						}
					}
				}
			}
		}
		// После окончания партии
		// Проверка нажатий кнопки продолжения игры / выхода
		if (_kbhit()) {
			// Если нажата кнопка
			int key = _getch();
			// Если ENTER - перезапуск игры
			if (key == 13) {
				fl = 0;
				continue;
			}
			// Иначе - выход из программы
			else {
				exit(0);
			}
		}
	}
	return(0);
}