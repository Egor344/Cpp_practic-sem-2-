//Катков Егор Александрович 
//БАСО-02-22
//Var-2
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#define MAX(a, b) (a > b) ? a : b

using namespace std;

struct Date
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
};
struct Record
{
	char company[20];
	int number_of_products;
	unsigned long int sales;
	double procent;
	Date date;
};

struct node {
	Record data;
	struct node* next;
	struct node* prev;
};

int countItem = 0;
struct node* myHead;

void Drawline()
{
	for (int i = 0; i < 101; i++)
	{
		cout << "-";
	}
	cout << "\n";
}

void Drawline1(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "-";
	}
	cout << "\n";
}

char* GetSpacebar(int count)
{
	char* msg = new char[count];
	for (int i = 0; i < count; i++)
	{
		msg[i] = ' ';
	}
	msg[count] = '\0';
	return msg;
}

void printDate(unsigned short day, unsigned short month, unsigned short year, int wLine)
{
	int w = 10;
	int delta = (wLine - w) / 2 - 1;
	cout << left;
	cout.width(delta); cout << " ";
	if (day > 9) {
		cout << day;
	}
	else {
		cout << "0" << day;
	}
	cout << ".";
	if (month > 9) {
		cout << month;
	}
	else {
		cout << "0" << month;
	}
	cout << ".";
	cout << year;
	cout.width(delta); cout << " ";
}

void myCentr(string s, int wLine) {
	int w = s.length();
	int delta = (wLine - w) / 2;
	cout << left;
	cout.width(delta); cout << " ";
	cout << s;
	cout.width(delta + 1); cout << " ";
}

struct Date getMaxDate(struct Record* lines)
{
	unsigned short maxYear = lines[0].date.year;
	for (int i = 1; i < 3; i++) {
		if (lines[i].date.year > maxYear)
			maxYear = lines[i].date.year;
	}

	unsigned short maxMonth = lines[0].date.month;
	for (int i = 1; i < 3; i++) {
		if (lines[i].date.year == maxYear and lines[i].date.month > maxMonth)
			maxMonth = lines[i].date.month;
	}

	unsigned short maxDay = lines[0].date.day;
	for (int i = 1; i < 3; i++) {
		if (lines[i].date.year == maxYear and lines[i].date.month == maxMonth and lines[i].date.day > maxDay)
			maxDay = lines[i].date.day;
	}
	Date date;
	date.day = maxDay;
	date.month = maxMonth;
	date.year = maxYear;
	return date;
}

template < typename T >
T Max(T a, T b, T c) {
	return MAX(a, MAX(b, c));
}

unsigned long int getMax(unsigned long int a, unsigned long int b, unsigned long int c) {
	unsigned long int max = MAX(a, MAX(b, c));
	return max;
}

void addItem(Record data)
{
	struct node* newItem = new node();
	newItem->data = data;
	newItem->prev = NULL;
	if (countItem == 0) {
		newItem->next = NULL;
	}
	else
	{
		newItem->next = myHead;
		myHead->prev = newItem;
	}
	myHead = newItem;
	countItem++;
}

void insertItem(int index, Record data) {
	if (not (index >= 0 and index <= countItem and countItem >= 0))
		return;
	if (index == 0) {
		addItem(data);
	}
	else {
		struct node* current = myHead;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		struct node* newItem = new node();
		newItem->data = data;
		newItem->next->prev = newItem;
		newItem->next = current->next;
		current->next = newItem;
		newItem->prev = current;
		countItem++;
	}
}

void editItem(int index, Record data) {
	if (index >= 0 and index < countItem and countItem>0) {
		struct node* current = myHead;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		current->data = data;
	}
	else {
		cout << endl << "Ошибка индекс не в диапазоне";
	}
}

void deleteItem(int index) {
	if (index >= 0 and index < countItem and countItem>0) {
		struct node* current = myHead;
		struct node* old;
		if (index == 0) {
			old = myHead;
			myHead = current->next;
			delete old;
			if (myHead != NULL) {
				myHead->prev = NULL;
			}
			countItem--;
		}
		else {
			int i = 0;
			while (current) {
				if (i == index - 1) {
					old = current->next->next;
					delete current->next;
					current->next = old;
					if (NULL != old)
					{
						old->prev = current;
					}
					countItem--;
					break;
				}
				i++;
				current = current->next;
			}
		}
	}

}

void Delete_double(double for_del) {
	struct node* current = myHead;
	for (int i = 0; i < countItem - 1; i++) {
		current = current->next;
	}
	int current_index = countItem - 1;
	while (current_index >= 0)
	{
		if (current->data.procent == for_del) {
			current = current->prev;
			deleteItem(current_index);
			current_index--;
		}
		else {
			current = current->prev;
			current_index--;
		}
	}
}

void printMyList() {
	struct node* current = myHead;
	cout << endl;
	while (current) {
		cout << " " << current->data.procent;
		current = current->next;
	}
}

void DrawWithList() {
	Drawline1(103);
	cout << "| Фирмы - производители СКБД" << GetSpacebar(103 - sizeof("| Фирмы - производители СКБД")) << "|\n";
	Drawline1(103);
	cout << left << "|"; myCentr("Фирма", 16);
	cout << left << "|"; myCentr("Количество продуктов", 11);
	cout << left << "|"; myCentr("Годовой объем продажи($)", 10);
	cout << left << "|"; myCentr("Часть рынка(%)", 10);
	cout << left << " |"; myCentr("Дата основания", 14);
	cout << "|" << endl;
	Drawline1(103);
	struct node* current = myHead;
	while (current) {
		cout << left << "|"; cout.width(16); cout << left << current->data.company;
		cout << left << "|"; cout.width(22); cout << left << current->data.number_of_products;
		cout << left << "|"; cout.width(26); cout << left << current->data.sales;
		std::cout.precision(1);
		cout << left << "|"; cout.width(17); cout << left << fixed << current->data.procent;
		cout << left << "|";
		printDate(current->data.date.day, current->data.date.month, current->data.date.year, 18);
		cout << "|" << endl;
		current = current->next;
	}
	Drawline1(103);
	cout.fill(' '); cout.width(102);  cout << left << "| Примечание: по данным Gartner Group за 1999г"; cout << "|" << endl;
	Drawline1(103);
}

void Draw(struct Record* records, int num) {
	Drawline1(103);
	cout << "| Фирмы - производители СКБД" << GetSpacebar(103 - sizeof("| Фирмы - производители СКБД")) << "|\n";
	Drawline1(103);
	cout << left << "|"; myCentr("Фирма", 16);
	cout << left << "|"; myCentr("Количество продуктов", 11);
	cout << left << "|"; myCentr("Годовой объем продажи($)", 10);
	cout << left << "|"; myCentr("Часть рынка(%)", 10);
	cout << left << " |"; myCentr("Дата основания", 14);
	cout << "|" << endl;
	Drawline1(103);
	for (int i = 0; i < num; i++) {
		cout << left << "|"; cout.width(16); cout << left << records[i].company;
		cout << left << "|"; cout.width(22); cout << left << records[i].number_of_products;
		cout << left << "|"; cout.width(26); cout << left << records[i].sales;
		std::cout.precision(2);
		cout << left << "|"; cout.width(17); cout << left << fixed << records[i].procent;
		cout << left << "|";
		printDate(records[i].date.day, records[i].date.month, records[i].date.year, 18);
		cout << "|" << endl;
	}
	Drawline1(103);
	cout.fill(' '); cout.width(102);  cout << left << "| Примечание: по данным Gartner Group за 1999г"; cout << "|" << endl;
	Drawline1(103);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Record lines[4];
	lines[0] = { "Oracle", 3, 2488000000, 31.1, {01,02,2010} };
	lines[1] = { "IBM", 2, 2392000000, 29.9, {02,03,2020} };
	lines[2] = { "Microsoft", 3, 1048000000, 13.1, {12,12,2012} };
	Date maxdate = getMaxDate(lines);
	lines[3] = { "Microsoft", Max(lines[0].number_of_products, lines[1].number_of_products, lines[2].number_of_products) ,
		getMax(lines[0].sales, lines[1].sales, lines[2].sales),
		Max(lines[0].procent, lines[1].procent, lines[2].procent), {maxdate.day, maxdate.month, maxdate.year} };

	Drawline();
	cout << "| Фирмы - производители СКБД" << GetSpacebar(101 - sizeof("| Фирмы - производители СКБД")) << "|\n";
	Drawline();
	cout << left << "|"; myCentr("Фирма", 14);
	cout << left << "|"; myCentr("Количество продуктов", 22);
	cout << left << "|"; myCentr("Годовой объем продажи($)", 18);
	cout << left << "|"; myCentr("Часть рынка(%)", 14);
	cout << left << "|"; myCentr("Дата основания", 14);
	cout << "|" << endl;
	Drawline();
	for (int i = 0; i < 4; i++)
	{
		cout << "| " << lines[i].company << GetSpacebar(13 - strlen(lines[i].company));
		cout << "| " << lines[i].number_of_products << GetSpacebar(25 - sizeof(lines[i].number_of_products));
		cout << "| " << lines[i].sales << GetSpacebar(19 - sizeof(lines[i].sales));
		cout << "| " << lines[i].procent << GetSpacebar(19 - sizeof(lines[i].procent)) << "|";
		printDate(lines[i].date.day, lines[i].date.month, lines[i].date.year, 19);
		cout << "|" << endl;
		Drawline();
	}
	cout << "| Примечание: по данным Gartner Group за 1999г" << GetSpacebar(101 - sizeof("| Примечание: по данным Gartner Group за 1999г")) << "|\n";
	Drawline();

	Record* A;
	Record** B;
	B = (Record**) new Record * [10];
	A = (Record*)calloc(10, sizeof(Record));
	for (int i = 0; i < 10; i++) {
		A[i] = lines[i % 3];
		B[i] = (Record*) new Record;
		*(B[i]) = lines[i % 3];
	}

	A = (Record*)realloc(A, 10 * sizeof(Record));
	cout << endl;

	Drawline1(58);
	cout << "| Адреса первых элементов массива" << GetSpacebar(58 - sizeof("| Адреса первых элементов массива")) << "|\n";
	Drawline1(58);
	cout << left << "|"; myCentr("Table", 18);
	cout << left << "|"; myCentr("A", 18);
	cout << left << "|"; myCentr("B", 18);
	cout << "|" << endl;
	Drawline1(58);
	cout << left << "|"; cout.width(18); cout << left << &lines[0];
	cout << left << "|"; cout.width(18); cout << left << &A[0];
	cout << left << "|"; cout.width(18); cout << left << &B[0] << "|" << endl;
	Drawline1(58);
	cout << endl;

	Drawline1(123);
	cout << "| Адреса и значения массива A" << GetSpacebar(123 - sizeof("| Адреса и значения массива A")) << "|\n";
	Drawline1(123);
	cout << left << "|"; myCentr("i", 1);
	cout << left << "|"; myCentr("Адрес", 18);
	cout << left << "|"; myCentr("Фирма", 14);
	cout << left << "|"; myCentr("Количество продуктов", 20);
	cout << left << "|"; myCentr("Годовой объем продажи($)", 18);
	cout << left << "|"; myCentr("Часть рынка(%)", 14);
	cout << left << "|"; myCentr("Дата основания", 14);
	cout << "|" << endl;
	Drawline1(123);
	for (int i = 0; i < 10; i++) {
		cout << left << "|"; cout.width(3); cout << left << i;
		cout << left << "|"; cout.width(18); cout << left << &A[i];
		cout << left << "|"; cout.width(14); cout << left << A[i].company;
		cout << left << "|"; cout.width(22); cout << left << A[i].number_of_products;
		cout << left << "|"; cout.width(26); cout << left << A[i].sales;
		cout << left << "|"; cout.width(16); cout << left << A[i].procent << "|";
		printDate(A[i].date.day, A[i].date.month, A[i].date.year, 18);
		cout << "|" << endl;
		Drawline1(123);
	}
	cout << endl;

	Drawline1(123);
	cout << "| Адреса и значения массива B" << GetSpacebar(123 - sizeof("| Адреса и значения массива B")) << "|\n";
	Drawline1(123);
	cout << left << "|"; myCentr("i", 1);
	cout << left << "|"; myCentr("Адрес", 18);
	cout << left << "|"; myCentr("Фирма", 14);
	cout << left << "|"; myCentr("Количество продуктов", 20);
	cout << left << "|"; myCentr("Годовой объем продажи($)", 18);
	cout << left << "|"; myCentr("Часть рынка(%)", 14);
	cout << left << "|"; myCentr("Дата основания", 14);
	cout << "|" << endl;
	Drawline1(123);
	for (int i = 0; i < 10; i++) {
		cout << left << "|"; cout.width(3); cout << left << i;
		cout << left << "|"; cout.width(18); cout << left << &B[i];
		cout << left << "|"; cout.width(14); cout << left << B[i]->company;
		cout << left << "|"; cout.width(22); cout << left << B[i]->number_of_products;
		cout << left << "|"; cout.width(26); cout << left << B[i]->sales;
		cout << left << "|"; cout.width(16); cout << left << B[i]->procent << "|";
		printDate(B[i]->date.day, B[i]->date.month, B[i]->date.year, 18);
		cout << "|" << endl;
		Drawline1(123);
	}

	free(A);

	for (int i = 0; i < 10; i++) {
		delete B[i];
	}
	delete[]B;

	cout << "Практика 3 Динамический список" << endl;

	double a;
	addItem(lines[0]);
	addItem(lines[1]);
	addItem(lines[2]);
	addItem(lines[3]);
	DrawWithList();

	cout << endl << "Введите вещественное число: ";
	cin >> a;
	cout << endl;
	Delete_double(a);
	DrawWithList();

	cout << endl << "Практика 4" << endl << endl;

	FILE* MyFileTxt;
	fopen_s(&MyFileTxt, "MyFileTxt.txt", "w+");
	for (int i = 0; i < 3; i++) {
		fprintf(MyFileTxt, "%s %d %lu %lf %hu %hu %hu \n", \
			lines[i].company, \
			lines[i].number_of_products, \
			lines[i].sales, \
			lines[i] .procent, \
			lines[i].date.day, lines[i].date.month, lines[i].date.year);
	}
	fclose(MyFileTxt);
	
	fopen_s(&MyFileTxt, "MyFileTxt.txt", "r");
	Record readRecords[3];
	for (int i = 0; i < 3; i++) {
		fscanf_s(MyFileTxt, "%s", readRecords[i].company, _countof(readRecords[i].company));
		fscanf_s(MyFileTxt, "%d", &readRecords[i].number_of_products);
		fscanf_s(MyFileTxt, "%lu", &readRecords[i].sales);
		fscanf_s(MyFileTxt, "%lf", &readRecords[i].procent);
		fscanf_s(MyFileTxt, "%hu", &readRecords[i].date.day);
		fscanf_s(MyFileTxt, "%hu", &readRecords[i].date.month);
		fscanf_s(MyFileTxt, "%hu", &readRecords[i].date.year);
	}
	fclose(MyFileTxt);
	Draw(readRecords, 3);

	/*FILE* MyFileBinary;
	fopen_s(&MyFileBinary, "MyFileBinary.bin", "w+");
	for (int i = 0; i < 3; i++) {
		fprintf(MyFileBinary, "%s %d %lu %lf %hu %hu %hu \n", \
			lines[i].company, \
			lines[i].number_of_products, \
			lines[i].sales, \
			lines[i].procent, \
			lines[i].date.day, lines[i].date.month, lines[i].date.year);
	}
	fclose(MyFileBinary);

	fopen_s(&MyFileBinary, "MyFileBinary.bin", "r");
	Record readRecords[3];
	for (int i = 0; i < 3; i++) {
		fscanf_s(MyFileBinary, "%s", readRecords[i].company, _countof(readRecords[i].company));
		fscanf_s(MyFileBinary, "%d", &readRecords[i].number_of_products);
		fscanf_s(MyFileBinary, "%lu", &readRecords[i].sales);
		fscanf_s(MyFileBinary, "%lf", &readRecords[i].procent);
		fscanf_s(MyFileBinary, "%hu", &readRecords[i].date.day);
		fscanf_s(MyFileBinary, "%hu", &readRecords[i].date.month);
		fscanf_s(MyFileBinary, "%hu", &readRecords[i].date.year);
	}
	fclose(MyFileBinary);
	Draw(readRecords, 3);*/

	Record inRecord;
	char company[20];
	int number_of_products;
	unsigned long int sales;
	double procent;
	struct Date date;
	cout << "Введите фирму: ";
	cin >> inRecord.company;
	cout << "Введите количество продуктов: ";
	cin >> inRecord.number_of_products;
	cout << "Введите объем продаж($): ";
	cin >> inRecord.sales;
	cout << "Введите часть рынка(%): ";
	cin >> inRecord.procent;
	cout << "Введите дату основания (день): ";
	cin >> inRecord.date.day;
	cout << "Введите дату основания (месяц): ";
	cin >> inRecord.date.month;
	cout << "Введите дату основания (год): ";
	cin >> inRecord.date.year;


	fopen_s(&MyFileTxt, "MyFileTxt.txt", "a");
	fprintf(MyFileTxt, "%s %d %lu %lf %hu %hu %hu \n", \
		inRecord.company, \
		inRecord.number_of_products, \
		inRecord.sales, \
		inRecord.procent, \
		inRecord.date.day, inRecord.date.month, inRecord.date.year);
	fclose(MyFileTxt);

	Record fileRecords[4];
	fopen_s(&MyFileTxt, "./MyFileTxt.txt", "r");
	for (int i = 0; i < 4; i++) {
		fscanf_s(MyFileTxt, "%s", fileRecords[i].company, _countof(fileRecords[i].company));
		fscanf_s(MyFileTxt, "%d", &fileRecords[i].number_of_products);
		fscanf_s(MyFileTxt, "%lu", &fileRecords[i].sales);
		fscanf_s(MyFileTxt, "%lf", &fileRecords[i].procent);
		fscanf_s(MyFileTxt, "%hu", &fileRecords[i].date.day);
		fscanf_s(MyFileTxt, "%hu", &fileRecords[i].date.month);
		fscanf_s(MyFileTxt, "%hu", &fileRecords[i].date.year);
	}
	fclose(MyFileTxt);
	Draw(fileRecords, 4);

	fopen_s(&MyFileTxt, "MyFileTxt.txt", "r");
	for (int i = 0; i < 4; i++) {
		fscanf_s(MyFileTxt, "%s", fileRecords[i].company, _countof(fileRecords[i].company));
		fscanf_s(MyFileTxt, "%d", &fileRecords[i].number_of_products);
		fscanf_s(MyFileTxt, "%lu", &fileRecords[i].sales);
		fscanf_s(MyFileTxt, "%lf", &fileRecords[i].procent);
		fscanf_s(MyFileTxt, "%hu", &fileRecords[i].date.day);
		fscanf_s(MyFileTxt, "%hu", &fileRecords[i].date.month);
		fscanf_s(MyFileTxt, "%hu", &fileRecords[i].date.year);
	}
	
	swap(fileRecords[2].company, fileRecords[3].company);
	fclose(MyFileTxt);
	fopen_s(&MyFileTxt, "MyFileTxt.txt", "w+");
	for (int i = 0; i < 4; i++) {
		fprintf(MyFileTxt, "%s %d %lu %lf %hu %hu %hu \n", \
			fileRecords[i].company, \
			fileRecords[i].number_of_products, \
			fileRecords[i].sales, \
			fileRecords[i].procent, \
			fileRecords[i].date.day, fileRecords[i].date.month, fileRecords[i].date.year);
	}
	fclose(MyFileTxt);
	Draw(fileRecords, 4);
}