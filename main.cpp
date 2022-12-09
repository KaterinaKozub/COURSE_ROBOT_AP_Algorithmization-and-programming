#include <iostream>

#define STR_LENGTH 30

using namespace std;


//��������� ��� �������� �������������� ������
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

//��������� �������� ���������� � ��������� �������� � �� �����������
typedef struct ListHeadType
{
	ListNode* first = nullptr;
	int elementCount = 0;
} ListHead;


//�������� ������� ����� �������
void pause();

//������ ���� ������
ListNode* getNode();

//������� ����������� ����� �������� �����
void getDouble(const char*, double&);

//������� ����������� ����� ������ �����
void getInteger(const char*, int&);

//������� ����������� ������
void getString(const char*, char*);

//������� �� ����� ������ ������ ���� ������
void printNode(ListNode*);

//�������� ������� � ������
void addNode(ListHead&, ListNode*, int);

//������� ������ ����� ������
void printData(ListHead&);

//������� ������� ����
void printMenu();

//������� ������� ������ �� �������
void deleteNode(ListHead& listHead, int number);

//��������� ������ � �������� ����
void saveToFile(ListHead& listHead);

//������� ������ � ��������� �����
void readFromFile(ListHead& listHead);

//��������� ���������� � ���� �����������
void sportsmenData(ListHead& listHead);

//����������� ��������� ���������� �� ��������
void sortByName(ListHead& listHead);

//���������� ����������� 
void printSeparator(const char symb);

//������������� ������ �������� �� �������
void editNode(ListHead& listHead, int number);

//����� ���������� ���������� �� ��������
void sportSearch(ListHead& listHead, char* sportName);

//����� ���������� �� ������
void countrySearch(ListHead& listHead, char* countryName);

//����� �����������, ���������� ���� ���������
void newBest(ListHead& listHead);

//�������� ���������� �� ����� ����������� ������
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
		getInteger("������ ��� ��������: ", action);
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
					cout << "������ �������� �� 1 �� " << competitionList.elementCount + 1 << endl;
					getInteger("������ ������� �������� ��� ��������� (0 ��� ����������): ", number);
				} while (number < 0 || number > competitionList.elementCount + 1);
				system("cls");
				if (number != 0)
					addNode(competitionList, getNode(), number);
				else
					cout << "�������� ���������" << endl;
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
						cout << "�� ������ �������� ������� �� 1 �� " << competitionList.elementCount << endl;
						getInteger("������ ������� �������� ��� ��������� (0 ��� ����������): ", number);
					} while (number < 0 || number > competitionList.elementCount);
					if (number != 0)
						deleteNode(competitionList, number);
					else
						cout << "�������� ���������" << endl;
				}
				pause();
				break;
			}
			case 4:
			{
				printData(competitionList);
				do
				{
					cout << "�� ������ ������ ������� �� 1 �� " << competitionList.elementCount << endl;
					getInteger("������ ������� �������� ��� ����������� (0 ��� ����������): ", number);
				} while (number < 0 || number > competitionList.elementCount);
				if (number != 0)
					editNode(competitionList, number);
				else
					cout << "�������� ���������" << endl;
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
				getString("������ ����� ��������� ���������: ", tmp);
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
				getString("������ ����� �����: ", tmp);
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

//�������� ������� ����� �������
void pause() 
{
	cout << endl << "�������� ����-��� ������, ��� ����������...";
	cin.ignore();
	system("cls");
}

//������ ���� ������
ListNode* getNode() 
{
	ListNode* node = new ListNode;
	printSeparator('-');
	getString("������ ����� ���� ������:                                       | ", node->sportName);
	printSeparator('-');
	getString("������ ��'� ����������, �� ���� ����� ����:                   | ", node->firstPlaceName);
	printSeparator('-');
	getString("������ ����� ����������, �� ���� ����� ����:                 | ", node->firstPlaceCountry);
	printSeparator('-');
	getDouble("������ ��������� ����������, �� ���� ����� ����:              | ", node->firstPlaceResult);
	printSeparator('-');
	getDouble("������ ������������ ������ ����������, �� ���� ����� ����:    | ", node->firstPlaceBest);
	printSeparator('-');
	getString("������ ��'� ����������, �� ���� ����� ����:                   | ", node->secondPlaceName);
	printSeparator('-');
	getString("������ ����� ����������, �� ���� ����� ����:                 | ", node->secondPlaceCountry);
	printSeparator('-');
	getDouble("������ ��������� ����������, �� ���� ����� ����:              | ", node->secondPlaceResult);
	printSeparator('-');
	getDouble("������ ������������ ������ ����������, �� ���� ����� ����:    | ", node->secondPlaceBest);
	printSeparator('-');
	getString("������ ��'� ����������, �� ���� ���� ����:                   | ", node->thirdPlaceName);
	printSeparator('-');
	getString("������ ����� ����������, �� ���� ���� ����:                 | ", node->thirdPlaceCountry);
	printSeparator('-');
	getDouble("������ ��������� ����������, �� ���� ���� ����:              | ", node->thirdPlaceResult);
	printSeparator('-');
	getDouble("������ ������������ ������ ����������, �� ���� ���� ����:    | ", node->thirdPlaceBest);
	printSeparator('-');
	return node;
}


void printData(ListHead& listHead)
{

	if (listHead.first == nullptr)
	{
		printf("������ ������!");
	}
	else
	{
		printSeparator('-');
		printf("  ����� ��������� ���������   |  �  |         ��'� ����������        |");
		printf("             �����             |       ���������       |  ��������� ������  |\n");
		ListNode* current = listHead.first;
		printSeparator('-');
		while (current != nullptr)
		{
			printNode(current);
			current = current->next;
		}
	}
}

//������� �� ����� ������ ������ ���� ������
void printNode(ListNode* node)
{
	printf(" %-30s | � 1 | %-30s | %-30s | ���������: %10.2lf | ������: %10.2lf |\n",
		node->sportName,
		node->firstPlaceName,
		node->firstPlaceCountry,
		node->firstPlaceResult,
		node->firstPlaceBest);
	printf(" %-30s | � 2 | %-30s | %-30s | ���������: %10.2lf | ������: %10.2lf |\n",
		"",
		node->secondPlaceName,
		node->secondPlaceCountry,
		node->secondPlaceResult,
		node->secondPlaceBest);
	printf(" %-30s | � 3 | %-30s | %-30s | ���������: %10.2lf | ������: %10.2lf |\n",
		"",
		node->thirdPlaceName,
		node->thirdPlaceCountry,
		node->thirdPlaceResult,
		node->thirdPlaceBest);
	printSeparator('-');

}

//������� ����������� ����� �������� �����
void getDouble(const char* message, double& number)
{
	cout << message;
	cin >> number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������� ��������." << endl;
		cout << message;
		cin >> number;
	}
	cin.ignore();
}

//������� ����������� ����� ������ �����
void getInteger(const char* message, int& number)
{
	cout << message;
	cin >> number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������� ��������." << endl;
		cout << message;
		cin >> number;
	}
	cin.ignore();
}

//������� ����������� ����� ������
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

//�������� ������� � ������
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

//������� ������� ����
void printMenu()
{
	system("cls");
	printf("%62s������ ��������� �������\n", "");
	printSeparator('~');
	printf("%20s 1) ������� ������ �� �����          2) ������ ����� �����           3) �������� �������� �����\n", "");
	printf("%20s 4) ���������� ���                  5) ��� ��� ��� ����������    6) ��� �� ����� ������\n", "");
	printf("%20s 7) ���������� � ����� ��������      8) ����� �� ������             9) ������� ����\n", "");
	printf("%20s10) ���������� �� ������ ������      11) �������� �� �����           12) ����� ��� ����������\n", "");
	printSeparator('~');
}

//��������� ������ � �������� ����
void saveToFile(ListHead& listHead)
{
	FILE* file = nullptr;
	ListNode* current = listHead.first;
	if ((file = fopen("data.bin", "wb")) == nullptr)
	{
		cout << "������� �������� �����, ���������� ���������!" << endl << endl;
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

//������� ������ � ��������� �����
void readFromFile(ListHead& listHead)
{
	FILE* file;
	if ((file = fopen("data.bin", "rb")) == nullptr)
	{
		cout << "������� ������� �����!" << endl << endl;
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

//������� ������� ������ �� �������
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

//��������� ���������� � ���� �����������
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
				printf(" 1 ���� | ���������: %10.2lf | ������: %10.2lf |\n", current->firstPlaceResult, current->firstPlaceBest);
				isFirst = false;
			}
			if (strcmp(current->secondPlaceName, sportsmen[i]) == 0) {
				if (!isFirst) printf(" %30s", "");
				printf("  |%-30s |", current->sportName);
				printf(" 2 ���� | ���������: %10.2lf | ������: %10.2lf |\n", current->secondPlaceResult, current->secondPlaceBest);
				isFirst = false;
			}
			if (strcmp(current->thirdPlaceName, sportsmen[i]) == 0) {
				if (!isFirst) printf(" %30s", "");
				printf("  |%-30s |", current->sportName);
				printf(" 3 ���� | ���������: %10.2lf | ������: %10.2lf |\n", current->thirdPlaceResult, current->thirdPlaceBest);
				isFirst = false;
			}
			current = current->next;
		}

	}
	printSeparator('-');
}

//����������� ��������� ���������� �� ��������
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

//���������� ����������� 
void printSeparator(const char symb)
{
	for (int i = 0; i < 150; i++) printf("%c", symb);
	printf("\n");
}

//������������� ������ �������� �� �������
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
	printf("%75s\n", "1 ����");
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
	printf("%75s\n", "2 ����");
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
	printf("%75s\n", "3 ����");
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

//����� ���������� ���������� �� ��������
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
		cout << "ͳ���� �� ��������!" << endl << endl;
}

//����� ���������� �� ������
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
		cout << "���������� � ������ ���� �� ��������!" << endl << endl;
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

//����� �����������, ���������� ���� ���������
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
		cout << "����� ������� �� �����������!" << endl;
	else printSeparator('-');
}

//�������� ���������� �� ����� ����������� ������
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
	if (k == 0) cout << "ͳ���� �� ��������!" << endl << endl;
	else printSeparator('-');
	for (int i = 0; i < k; i++)
	{
		printf(" %-30s | ������: %3d | �����: %3d | ������: %3d |\n",
			countryResult[i].country,
			countryResult[i].firstCount,
			countryResult[i].secondCount,
			countryResult[i].thirdCount);
		printSeparator('-');
	}
	

}
