#include <iostream>

#define STR_LENGTH 30

using namespace std;


//Структура для хранения единичногоузла списка
typedef struct ListNodeType
{
	char sportName[STR_LENGTH];
	char firstPlaceName[STR_LENGTH];
	char firstPlaceCountry[STR_LENGTH];
	double firstPlaceResult;
	double firstPlaceBest;
	char secondPlaceName[STR_LENGTH];
	char secondPlaceCountry[STR_LENGTH];
	double secondPlaceResult;
	double secondPlaceBest;
	char thirdPlaceName[STR_LENGTH];
	char thirdPlaceCountry[STR_LENGTH];
	double thirdPlaceResult;
	double thirdPlaceBest;
	ListNodeType* next;
} ListNode;

//Структура хранящая информацию о начальном элементе и их колличестве
typedef struct ListHeadType
{
	ListNode* first = nullptr;
	int elementCount = 0;
} ListHead;


//Ожидание нажатия любой клавиши
void pause();

//Ручной ввод данных
ListNode* getNode();

//Функция безопасного ввода дробного числа
void getDouble(const char*, double&);

//Функция безопасного ввода целого числа
void getInteger(const char*, int&);

//Функция безопасного строки
void getString(const char*, char*);

//Вывести на экран данные одного узла списка
void printNode(ListNode*);

//Добавить элемент в список
void addNode(ListHead&, ListNode*, int);

//Вывести данные всего списка
void printData(ListHead&);

//Вывести главное меню
void printMenu();

//Удалить элемент списка по индексу
void deleteNode(ListHead& listHead, int number);

//Сохранить список в бинарный файл
void saveToFile(ListHead& listHead);

//Считать данные с бинарного файла
void readFromFile(ListHead& listHead);

//Получение информации о всех спортсменах
void sportsmenData(ListHead& listHead);

//Сортировать сортивные дисциплины по названию
void sortByName(ListHead& listHead);

//Напечатать разделитель 
void printSeparator(const char symb);

//Редактировать данные элемента по индексу
void editNode(ListHead& listHead, int number);

//Поиск спортивной дисциплины по названию
void sportSearch(ListHead& listHead, char* sportName);

//Поиск спотсменов по стране
void countrySearch(ListHead& listHead, char* countryName);

//Поиск спортсменов, улучшевших свой результат
void newBest(ListHead& listHead);

//Получить информацию об общих результатах страны
void getCountryResults(ListHead& listHead);

int main()
{
	system("chcp 1251");
	system("cls");
	system("mode con cols=150");
	ListHead competitionList;
	readFromFile(competitionList);
	int action;
	int number;
	char tmp[STR_LENGTH];
	do
	{
		printMenu();
		getInteger("Оберіть код операції: ", action);
		system("cls");
		switch (action)
		{
			case 1: 
			{
				printData(competitionList);
				pause();
				break;
			}
			case 2: 
			{
				printData(competitionList);
				do 
				{
					cout << "Введіть значення від 1 до " << competitionList.elementCount + 1 << endl;
					getInteger("Введіть позицію елемента для додавання (0 для скасування): ", number);
				} while (number < 0 || number > competitionList.elementCount + 1);
				system("cls");
				if (number != 0)
					addNode(competitionList, getNode(), number);
				else
					cout << "Операцію скасовано" << endl;
				pause();
				break;
			}
			case 3:
			{
				printData(competitionList);
				if (competitionList.elementCount != 0)
				{
					do
					{
						cout << "Ви можете видалити елемент від 1 до " << competitionList.elementCount << endl;
						getInteger("Введіть позицію елемента для видалення (0 для скасування): ", number);
					} while (number < 0 || number > competitionList.elementCount);
					if (number != 0)
						deleteNode(competitionList, number);
					else
						cout << "Операцію скасовано" << endl;
				}
				pause();
				break;
			}
			case 4:
			{
				printData(competitionList);
				do
				{
					cout << "Ви можете змінити елемент від 1 до " << competitionList.elementCount << endl;
					getInteger("Введіть позицію елемента для коригування (0 для скасування): ", number);
				} while (number < 0 || number > competitionList.elementCount);
				if (number != 0)
					editNode(competitionList, number);
				else
					cout << "Операцію скасовано" << endl;
				pause();
				break;
			}
			case 5:
			{
				sportsmenData(competitionList);
				pause();
				break;
			}
			case 6:
			{
				getString("Введіть назву спортивної дисципліни: ", tmp);
				sportSearch(competitionList, tmp);
				pause();
				break;
			}
			case 7:
			{
				newBest(competitionList);
				pause();
				break;
			}
			case 8:
			{
				getString("Введіть назву країни: ", tmp);
				countrySearch(competitionList, tmp);
				pause();
				break;
			}
			case 9:
			{
				getCountryResults(competitionList);
				pause();
				break;
			}
			case 10: 
			{
				sortByName(competitionList);
				pause();
				break;
			}
			case 11: saveToFile(competitionList); pause();  break;
			case 12: break;
			default: break;
		}
	} while(action != 11 && action != 12);
	return 0;
}

//Ожидание нажатия любой клавиши
void pause() 
{
	cout << endl << "Натисніть будь-яку клавішу, щоб продовжити...";
	cin.ignore();
	system("cls");
}

//Ручной ввод данных
ListNode* getNode() 
{
	ListNode* node = new ListNode;
	printSeparator('-');
	getString("Введіть назву виду спорту:                                       | ", node->sportName);
	printSeparator('-');
	getString("Введіть ім'я спортсмена, що посів перше місце:                   | ", node->firstPlaceName);
	printSeparator('-');
	getString("Введіть країну спортсмена, що посів перше місце:                 | ", node->firstPlaceCountry);
	printSeparator('-');
	getDouble("Введіть результат спортсмена, що посів перше місце:              | ", node->firstPlaceResult);
	printSeparator('-');
	getDouble("Введіть персональний рекорд спортсмена, що посів перше місце:    | ", node->firstPlaceBest);
	printSeparator('-');
	getString("Введіть ім'я спортсмена, що посів друга місце:                   | ", node->secondPlaceName);
	printSeparator('-');
	getString("Введіть країну спортсмена, що посів друга місце:                 | ", node->secondPlaceCountry);
	printSeparator('-');
	getDouble("Введіть результат спортсмена, що посів друга місце:              | ", node->secondPlaceResult);
	printSeparator('-');
	getDouble("Введіть персональний рекорд спортсмена, що посів друга місце:    | ", node->secondPlaceBest);
	printSeparator('-');
	getString("Введіть ім'я спортсмена, що посів третє місце:                   | ", node->thirdPlaceName);
	printSeparator('-');
	getString("Введіть країну спортсмена, що посів третє місце:                 | ", node->thirdPlaceCountry);
	printSeparator('-');
	getDouble("Введіть результат спортсмена, що посів третє місце:              | ", node->thirdPlaceResult);
	printSeparator('-');
	getDouble("Введіть персональний рекорд спортсмена, що посів третє місце:    | ", node->thirdPlaceBest);
	printSeparator('-');
	return node;
}


void printData(ListHead& listHead)
{

	if (listHead.first == nullptr)
	{
		printf("Список пустий!");
	}
	else
	{
		printSeparator('-');
		printf("  Назва спортивної дисципліни   |  №  |         Ім'я спортсмена        |");
		printf("             Країна             |       Результат       |  Особистий рекорд  |\n");
		ListNode* current = listHead.first;
		printSeparator('-');
		while (current != nullptr)
		{
			printNode(current);
			current = current->next;
		}
	}
}

//Вывести на экран данные одного узла списка
void printNode(ListNode* node)
{
	printf(" %-30s | № 1 | %-30s | %-30s | Результат: %10.2lf | Рекорд: %10.2lf |\n",
		node->sportName,
		node->firstPlaceName,
		node->firstPlaceCountry,
		node->firstPlaceResult,
		node->firstPlaceBest);
	printf(" %-30s | № 2 | %-30s | %-30s | Результат: %10.2lf | Рекорд: %10.2lf |\n",
		"",
		node->secondPlaceName,
		node->secondPlaceCountry,
		node->secondPlaceResult,
		node->secondPlaceBest);
	printf(" %-30s | № 3 | %-30s | %-30s | Результат: %10.2lf | Рекорд: %10.2lf |\n",
		"",
		node->thirdPlaceName,
		node->thirdPlaceCountry,
		node->thirdPlaceResult,
		node->thirdPlaceBest);
	printSeparator('-');

}

//Функция безопасного ввода дробного числа
void getDouble(const char* message, double& number)
{
	cout << message;
	cin >> number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Помилка введення." << endl;
		cout << message;
		cin >> number;
	}
	cin.ignore();
}

//Функция безопасного ввода целого числа
void getInteger(const char* message, int& number)
{
	cout << message;
	cin >> number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Помилка введення." << endl;
		cout << message;
		cin >> number;
	}
	cin.ignore();
}

//Функция безопасного ввода строки
void getString(const char* message, char* stringValue)
{
	cout << message;
	cin.getline(stringValue, STR_LENGTH);
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

//Добавить элемент в список
void addNode(ListHead& listHead, ListNode* node, int position)
{
	listHead.elementCount++;
	node->next = nullptr;
	if (listHead.first == nullptr)
	{
		listHead.first = node;
	}
	else
	{
		ListNode* current = listHead.first;
		ListNode* previous = nullptr;
		for (int i = 1; i < position; i++)
		{
			previous = current;
			current = current->next;
		}
		node->next = current;
		(previous == nullptr) ? (listHead.first = node) : (previous->next = node);
	}
}

//Вывести главное меню
void printMenu()
{
	system("cls");
	printf("%62sСписок доступних варіантів\n", "");
	printSeparator('~');
	printf("%20s 1) Вивести список на екран          2) Додати новий запис           3) Видалити існуючий запис\n", "");
	printf("%20s 4) Коригувати дані                  5) Дані про всіх спортсменів    6) Дані за видом спорту\n", "");
	printf("%20s 7) Спортсмени з новим рекордом      8) Пошук за країною             9) Рейтинг країн\n", "");
	printf("%20s10) Сортування за назвою спорту      11) Зберегти та вийти           12) Вийти без збереження\n", "");
	printSeparator('~');
}

//Сохранить список в бинарный файл
void saveToFile(ListHead& listHead)
{
	FILE* file = nullptr;
	ListNode* current = listHead.first;
	if ((file = fopen("data.bin", "wb")) == nullptr)
	{
		cout << "Помилка відкриття файлу, збереження неможливе!" << endl << endl;
	}
	else
	{
		while (current != nullptr)
		{
			fwrite(current, sizeof(ListNode) - sizeof(ListNode*), 1, file);
			current = current->next;
		}
		fclose(file);
	}
}

//Считать данные с бинарного файла
void readFromFile(ListHead& listHead)
{
	FILE* file;
	if ((file = fopen("data.bin", "rb")) == nullptr)
	{
		cout << "Помилка читання файлу!" << endl << endl;
	}
	else
	{

		ListNode* previous = nullptr;
		while (!feof(file))
		{
			ListNode* current = new ListNode;
			fread(current, sizeof(ListNode) - sizeof(ListNode*), 1, file);
			if (!feof(file))
			{
				addNode(listHead, current, listHead.elementCount + 1);
			}
			else delete current; 
		}
	}
}

//Удалить элемент списка по индексу
void deleteNode(ListHead& listHead, int number)
{
	ListNode* current = listHead.first;
	ListNode* previous = nullptr;
	listHead.elementCount--;
	for (int i = 1; i < number; i++)
	{
		previous = current;
		current = current->next;
	}
	(previous == nullptr) ? (listHead.first = current->next) : (previous->next = current->next);
	delete current;
}

//Получение информации о всех спортсменах
void sportsmenData(ListHead& listHead)
{
	char** sportsmen = new char*[listHead.elementCount];
	for (int i = 0; i < listHead.elementCount; i++)
	{
		sportsmen[i] = new char[STR_LENGTH];
	}
	int k = 0;
	ListNode* current = listHead.first;
	while (current != nullptr) 
	{
		bool isHere = false;
		for (int i = 0; i < k; i++)
		{
			if (strcmp(current->firstPlaceName, sportsmen[i]) == 0)
			{
				isHere = true;
				break;
			}
		}
		if (!isHere) sportsmen[k++] = current->firstPlaceName;
		isHere = false;
		for (int i = 0; i < k; i++)
		{
			if (strcmp(current->secondPlaceName, sportsmen[i]) == 0)
			{
				isHere = true;
				break;
			}
		}
		if (!isHere) sportsmen[k++] = current->secondPlaceName;
		isHere = false;
		for (int i = 0; i < k; i++)
		{
			if (strcmp(current->thirdPlaceName, sportsmen[i]) == 0)
			{
				isHere = true;
				break;
			}
		}
		if (!isHere) sportsmen[k++] = current->thirdPlaceName;
		current = current->next;
	}
	for (int i = 0; i < k; i++)
	{
		printSeparator('-');
		printf(" %-30s", sportsmen[i]);
		bool isFirst = true;
		current = listHead.first;
		while (current != nullptr)
		{
			if (strcmp(current->firstPlaceName, sportsmen[i]) == 0) {
				if (!isFirst) printf(" %30s", "");
				printf("  |%-30s |", current->sportName);
				printf(" 1 місце | Результат: %10.2lf | Рекорд: %10.2lf |\n", current->firstPlaceResult, current->firstPlaceBest);
				isFirst = false;
			}
			if (strcmp(current->secondPlaceName, sportsmen[i]) == 0) {
				if (!isFirst) printf(" %30s", "");
				printf("  |%-30s |", current->sportName);
				printf(" 2 місце | Результат: %10.2lf | Рекорд: %10.2lf |\n", current->secondPlaceResult, current->secondPlaceBest);
				isFirst = false;
			}
			if (strcmp(current->thirdPlaceName, sportsmen[i]) == 0) {
				if (!isFirst) printf(" %30s", "");
				printf("  |%-30s |", current->sportName);
				printf(" 3 місце | Результат: %10.2lf | Рекорд: %10.2lf |\n", current->thirdPlaceResult, current->thirdPlaceBest);
				isFirst = false;
			}
			current = current->next;
		}

	}
	printSeparator('-');
}

//Сортировать сортивные дисциплины по названию
void sortByName(ListHead& listHead)
{
	ListNode* previous;
	ListNode* current;
	ListNode* next;
	for (int i = 1; i <= listHead.elementCount; i++)
	{
		current = listHead.first;
		previous = nullptr;
		for (int j = 1; j <= listHead.elementCount - i ; j++)
		{
			if (current != nullptr)
			{
				if (current->next != nullptr)
				{
					next = current->next; 
					if (next!= nullptr && strcmp(current->sportName, next->sportName) > 0)
					{
						if (previous != nullptr) previous->next = next;
						else listHead.first = next;
						current->next = next->next;
						next->next = current;
						current = next;
					}
					previous = current; 
					current = current->next; 
				}
			}
		}
	}

}

//Напечатать разделитель 
void printSeparator(const char symb)
{
	for (int i = 0; i < 150; i++) printf("%c", symb);
	printf("\n");
}

//Редактировать данные элемента по индексу
void editNode(ListHead& listHead, int number)
{
	ListNode* current = listHead.first;
	for (int i = 1; i < number; i++)
	{
		current = current->next;
	}
	printSeparator('-');
	printf("%65s >>>>>>> ", current->sportName);
	getString("", current->sportName);
	printSeparator('-');
	printf("%75s\n", "1 місце");
	printSeparator('-');
	printf("%70s ", current->firstPlaceName);
	getString(">>>>>>> ", current->firstPlaceName);
	printSeparator('-');
	printf("%70s ", current->firstPlaceCountry);
	getString(">>>>>>> ", current->firstPlaceCountry);
	printSeparator('-');
	printf("%70.2lf ", current->firstPlaceResult);
	getDouble(">>>>>>> ", current->firstPlaceResult);
	printSeparator('-');
	printf("%70.2lf ", current->firstPlaceBest);
	getDouble(">>>>>>> ", current->firstPlaceBest);

	printSeparator('-');
	printf("%75s\n", "2 місце");
	printSeparator('-');
	printf("%70s ", current->secondPlaceName);
	getString(">>>>>>> ", current->secondPlaceName);
	printSeparator('-');
	printf("%70s ", current->secondPlaceCountry);
	getString(">>>>>>> ", current->secondPlaceCountry);
	printSeparator('-');
	printf("%70.2lf ", current->secondPlaceResult);
	getDouble(">>>>>>> ", current->secondPlaceResult);
	printSeparator('-');
	printf("%70.2lf ", current->secondPlaceResult);
	getDouble(">>>>>>> ", current->secondPlaceResult);

	printSeparator('-');
	printf("%75s\n", "3 місце");
	printSeparator('-');
	printf("%70s ", current->thirdPlaceName);
	getString(">>>>>>> ", current->thirdPlaceName);
	printSeparator('-');
	printf("%70s ", current->thirdPlaceCountry);
	getString(">>>>>>> ", current->thirdPlaceCountry);
	printSeparator('-');
	printf("%70.2lf ", current->thirdPlaceResult);
	getDouble(">>>>>>> ", current->thirdPlaceResult);
	printSeparator('-');
	printf("%70.2lf ", current->thirdPlaceResult);
	getDouble(">>>>>>> ", current->thirdPlaceResult);
	printSeparator('-');

}

//Поиск спортивной дисциплины по названию
void sportSearch(ListHead& listHead, char* sportName)
{
	ListNode* current = listHead.first;
	int isPrinted = false;
	while (current != nullptr) {
		if (strcmp(current->sportName, sportName) == 0)
		{
			if (!isPrinted) printSeparator('-');
			printNode(current);
			isPrinted = true;
		}
		current = current->next;
	}
	if (!isPrinted)
		cout << "Нічого не знайдено!" << endl << endl;
}

//Поиск спотсменов по стране
void countrySearch(ListHead& listHead, char* countryName)
{
	char** sportsmen = new char* [listHead.elementCount];
	for (int i = 0; i < listHead.elementCount; i++)
	{
		sportsmen[i] = new char[STR_LENGTH];
	}
	int k = 0;
	ListNode* current = listHead.first;
	while (current != nullptr)
	{
		bool isHere = true;

		if (strcmp(current->firstPlaceCountry, countryName) == 0)
		{
			isHere = false;
			for (int i = 0; i < k; i++)
			{
				if (strcmp(current->firstPlaceName, sportsmen[i]) == 0)
				{
					isHere = true;
					break;
				}
			}
		}
		if (!isHere) sportsmen[k++] = current->firstPlaceName;
		isHere = true;
		if (strcmp(current->secondPlaceCountry, countryName) == 0)
		{
			isHere = false;
			for (int i = 0; i < k; i++)
			{
				if (strcmp(current->secondPlaceName, sportsmen[i]) == 0)
				{
					isHere = true;
					break;
				}
			}
		}
		if (!isHere) sportsmen[k++] = current->secondPlaceName;
		isHere = true;
		if (strcmp(current->thirdPlaceCountry, countryName) == 0)
		{
			isHere = false;
			for (int i = 0; i < k; i++)
			{
				if (strcmp(current->thirdPlaceName, sportsmen[i]) == 0)
				{
					isHere = true;
					break;
				}
			}
		}
		if (!isHere) sportsmen[k++] = current->thirdPlaceName;
		current = current->next;
	}
	if (k == 0)
	{
		cout << "Спортсменів в заданій країні не знайдено!" << endl << endl;
	}
	else
	{
		for (int i = 0; i < k; i++)
		{
			printSeparator('-');
			cout << sportsmen[i] << endl;
		}
		printSeparator('-');
	}

}

//Поиск спортсменов, улучшевших свой результат
void newBest(ListHead& listHead)
{
	ListNode* current = listHead.first;
	bool isPrinted = false;
	while (current != nullptr) 
	{
		if (current->firstPlaceResult < current->firstPlaceBest)
		{
			printSeparator('-');
			printf(" %-30s | %-30s | %-30s |   %-10.2lf -> %10.2lf\n",
				current->sportName,
				current->firstPlaceName,
				current->firstPlaceCountry,
				current->firstPlaceBest,
				current->firstPlaceResult);
			isPrinted = true;
		}
		if (current->secondPlaceResult < current->secondPlaceBest)
		{
			printSeparator('-');
			printf(" %-30s | %-30s | %-30s |   %-10.2lf -> %10.2lf\n",
				current->sportName,
				current->secondPlaceName,
				current->secondPlaceCountry,
				current->secondPlaceBest,
				current->secondPlaceResult);
			isPrinted = true;
		}
		if (current->thirdPlaceResult < current->thirdPlaceBest)
		{
			printSeparator('-');
			printf(" %-30s | %-30s | %-30s |   %-10.2lf -> %10.2lf\n",
				current->sportName,
				current->thirdPlaceName,
				current->thirdPlaceCountry,
				current->thirdPlaceBest,
				current->thirdPlaceResult);
			isPrinted = true;
		}
		current = current->next;
	}

	if (!isPrinted)
		cout << "Нових рекордів не зафіксовано!" << endl;
	else printSeparator('-');
}

//Получить информацию об общих результатах страны
void getCountryResults(ListHead& listHead)
{
	struct CountryResults
	{
		char country[STR_LENGTH];
		int firstCount = 0;
		int secondCount = 0;
		int thirdCount = 0;
	} *countryResult = new CountryResults[listHead.elementCount * 3];

	ListNode* current = listHead.first;
	int k = 0;
	while (current != nullptr)
	{
		bool isHere = false;
		for (int i = 0; i < k; i++)
		{
			if (strcmp(current->firstPlaceCountry, countryResult[i].country) == 0)
			{
				countryResult[i].firstCount++;
				isHere = true;
				break;
			}
		}
		if (!isHere)
		{
			strcpy(countryResult[k].country, current->firstPlaceCountry);
			countryResult[k].firstCount = 1;
			k++;
		}
		isHere = false;
		for (int i = 0; i < k; i++)
		{

			if (strcmp(current->secondPlaceCountry, countryResult[i].country) == 0)
			{
				countryResult[i].secondCount++;
				isHere = true;
				break;
			}
		}
		if (!isHere)
		{
			strcpy(countryResult[k].country, current->secondPlaceCountry);
			countryResult[k].secondCount = 1;
			k++;
		}
		isHere = false;
		for (int i = 0; i < k; i++)
		{
			if (strcmp(current->thirdPlaceCountry, countryResult[i].country) == 0)
			{
				countryResult[i].thirdCount++;
				isHere = true;
				break;
			}
		}
		if (!isHere)
		{
			strcpy(countryResult[k].country, current->thirdPlaceCountry);
			countryResult[k].thirdCount = 1;
			k++;
		}
		current = current->next;
	}
	if (k == 0) cout << "Нічого не знайдено!" << endl << endl;
	else printSeparator('-');
	for (int i = 0; i < k; i++)
	{
		printf(" %-30s | Золото: %3d | Срібло: %3d | Бронза: %3d |\n",
			countryResult[i].country,
			countryResult[i].firstCount,
			countryResult[i].secondCount,
			countryResult[i].thirdCount);
		printSeparator('-');
	}
	

}
