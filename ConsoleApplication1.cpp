/*
Всі роботи проводяться з файлом у бінарному режимі.
Використовувати масив не можна.
Написати такі функції:
1. Згенерувати у файл випадкові цілі числа від -100 до 100. Кількість чисел випадкова від 1 – 100.
2. Підрахувати кількість чисел у файлі;
3. Підрахувати суму чисел у файлі;
4. Підрахувати середнє арифметичне чисел у файлі;
5. Вивести числа більші за середнє арифметичне.
6. Відсортувати числа у файлі за зростанням. Зробити меню для тестування функцій.
*/
#include <string.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <algorithm>
//#define GetRnd(min, max) ((min)+rand()%(int)((max)-(min)+1))
using namespace std;
#define MENUTOP 0 
#define MENULEFT 0 
#define BACKGROUND 0                     
#define FOREGROUND 10                         
#define SELECTITEM 13
void gotorc(short r, short c) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { c,r });
}
void Color(unsigned short Back, unsigned short Forg) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F);
	SetConsoleTextAttribute(handle, c);
}
void paintmenu(const char** s, int sizem, int  pm, int left, int top) {
	system("cls");
	gotorc(top, left);
	Color(BACKGROUND, FOREGROUND);
	cout << "Всі роботи проводяться з файлом у бінарному режимі. Використовувати масив не можна. Написати такі функції :";
	for (int i = 0; i < sizem; i++)
	{
		gotorc(top + i + 1, left);
		cout << (i == pm ? Color(BACKGROUND, SELECTITEM), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int  pm = 0, int left = MENULEFT, int top = MENUTOP) {
	char c = 80;
	while (true)
	{
		if (c == 72 || c == 80) paintmenu(s, sizem, pm, left, top);
		c = _getch();
		switch (c)
		{
		case 27: //код кнопки "esc" 27
			return -1;
		case 80: //down
			pm++;
			if (pm == sizem) pm = 0;
			break;
		case 72: //up
			if (pm == 0) pm = sizem;
			pm--;
			break;
		case 13: //enter
			return pm;
		}
	}
}
//******************************************************************************************************
void SaveInt() {
	int a = 1;
	int b = 100;
	size_t n = a + rand() % (b - a + 1);
	int temp = 0;
	FILE* fs = NULL;
	if (fopen_s(&fs, "rnd.bin", "wb")) {
		cout << "Error create file";
		exit(2);
	}
	int a_temp = -100;
	int b_temp = 100;
	for (size_t i = 0; i < n; i++) {
		temp = a_temp + rand() % (b_temp - a_temp + 1);
		fwrite(&temp, sizeof(int), 1, fs);
	}
	fclose(fs);
}
void PrintInt() {
	FILE* fs = NULL;
	int temp = 0;
	if (fopen_s(&fs, "rnd.bin", "rb")) {
		cout << "Error create file";
		exit(2);
	}
	fseek(fs, 0, SEEK_END);
	int n = ftell(fs) / sizeof(int); // ftell показує де стоїть маркер
	fseek(fs, 0, SEEK_SET);
	for (size_t i = 0; i < n; i++)
	{
		fread(&temp, sizeof(int), 1, fs);
		cout << temp << '\t';
	}
	fclose(fs);
}
int NumbersInFile() {
	FILE* fs = NULL;
	if (fopen_s(&fs, "rnd.bin", "rb")) {
		cout << "Error create file";
		exit(2);
	}
	fseek(fs, 0, SEEK_END);
	int n = ftell(fs) / sizeof(int);
	fclose(fs);
	return n;
}
int SumOfNumbersInFile() {
	FILE* fs = NULL;
	if (fopen_s(&fs, "rnd.bin", "rb")) {
		cout << "Error create file";
		exit(2);
	}
	int sum = 0;
	fseek(fs, 0, SEEK_SET);
	for (size_t i = 0; i < NumbersInFile(); i++)
	{
		int temp = 0;
		fread(&temp, sizeof(int), 1, fs);
		sum = sum + temp;
	}
	fclose(fs);
	return sum;
}
int ArithmeticMeanOfTheFile() {
	float ArMeOfTheFile = SumOfNumbersInFile() / NumbersInFile();
	return ArMeOfTheFile;
}
void NumbersGreaterThanArithmeticMean() {
	FILE* fs = NULL;
	int temp = 0;
	if (fopen_s(&fs, "rnd.bin", "rb")) {
		cout << "Error create file";
		exit(2);
	}
	fseek(fs, 0, SEEK_END);
	int n = ftell(fs) / sizeof(int); // ftell показує де стоїть маркер
	fseek(fs, 0, SEEK_SET);
	for (size_t i = 0; i < n; i++)
	{
		fread(&temp, sizeof(int), 1, fs);
		if (temp > ArithmeticMeanOfTheFile())
			cout << temp << '\t';
	}
	fclose(fs);
}
void SortNumbersInFileInAscendingOrder() {
	FILE* fs = NULL;
	int temp1 = 0;
	int temp2 = 0;
	if (fopen_s(&fs, "rnd.bin", "r+b")) {
		cout << "Error create file";
		exit(2);
	}
	fseek(fs, 0, SEEK_END);
	int n = ftell(fs) / sizeof(int); // ftell показує де стоїть маркер
	fseek(fs, 0, SEEK_SET);
	for (size_t i = 0; i < n; i++) {
		fread(&temp1, sizeof(int), 1, fs);
		fseek(fs, 0, SEEK_CUR);
		fread(&temp2, sizeof(int), 1, fs);
		/*while (temp1 > temp2) {

			swap(temp1, temp2);
			fwrite(&temp2, sizeof(int), 1, fs);
		}*/
		int tmp;
		if (temp1 < temp2) { 
			tmp = temp1; 
			temp1 = temp2;
			temp2 = tmp;
		}
	}
	fclose(fs);
	//PrintInt();
}
int main() {
	setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	SetConsoleCP(1251); //встановлює потрібну кодову таблицю, на потік введення
	SetConsoleOutputCP(1251); //встановлює потрібну кодову таблицю, на потік виводу.	
	srand(time(0));
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	const char* Main_menu[]{
		"1. Згенерувати у файл випадкові цілі числа від - 100 до 100. Кількість чисел випадкова від 1 – 100",
		"2. Підрахувати кількість чисел у файлі",
		"3. Підрахувати суму чисел у файлі",
		"4. Підрахувати середнє арифметичне чисел у файлі",
		"5. Вивести числа більші за середнє арифметичне",
		"6. Відсортувати числа у файлі за зростанням",
	};
	int size_of_Main_menu = sizeof(Main_menu) / 4;
	bool bo = true;
	int pm = 0;
	while (true)
	{
		pm = menu(Main_menu, size_of_Main_menu, pm);
		system("cls");
		switch (pm) // Main_menu
		{
		case -1:
			return 0;
		case 0: // "1. Згенерувати у файл випадкові цілі числа від - 100 до 100. Кількість чисел випадкова від 1 – 100",
			cout << "Випадкові цілі числа від - 100 до 100. Кількість чисел випадкова від 1 – 100" << endl << endl;
			SaveInt();
			PrintInt();
			break;
		case 1: // "2. Підрахувати кількість чисел у файлі",
			cout << "Кількість чисел у файлі = " << NumbersInFile();
			break;
		case 2: // "3. Підрахувати суму чисел у файлі",
			cout << "Сума чисел у файлі = " << SumOfNumbersInFile();
			break;
		case 3: // "4. Підрахувати середнє арифметичне чисел у файлі",
			cout << "Середнє арифметичне чисел у файлі : " << ArithmeticMeanOfTheFile();
			break;
		case 4: // "5. Вивести числа більші за середнє арифметичне",
			cout << "Випадкові цілі числа від - 100 до 100. Кількість чисел випадкова від 1 – 100" << endl << endl;
			PrintInt();
			cout << "\nСереднє арифметичне чисел у файлі : " << ArithmeticMeanOfTheFile();
			cout << "\nЧисла більші за середнє арифметичне:" << endl;
			NumbersGreaterThanArithmeticMean();
			break;
		case 5: // "6. Відсортувати числа у файлі за зростанням",
			cout << "Випадкові цілі числа від - 100 до 100. Кількість чисел випадкова від 1 – 100" << endl << endl;
			PrintInt();
			cout << "\nЧисла у файлі за зростанням: " << endl;
			SortNumbersInFileInAscendingOrder();
			PrintInt();
			break;
		}
		Color(BACKGROUND, 2);
		cout << "\n\nОперацію виконано успішно !\n";
		_getch();
	}	
}