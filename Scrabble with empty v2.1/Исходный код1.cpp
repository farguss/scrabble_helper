#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Resource {
	//char Word[20]; 
	string Word;
	//char Description[30]; 
	string Description;
	int Value;
};

int points(char letter);
void vruchnu(char *mass, int num);
void random(char *mass, int num);
int search(char *mass, int num, char *buff, char *exept2);

void GetData(Resource *M,int number_of_words, char *buff, int sum_points, int structure, char exept2);
void ShowData(Resource *M,int number_of_words);
int output(Resource *M, int number_of_words, string Transcript);
void SortData(Resource *M,int number_of_words);

void addition(char *mass, int num, int extra_letters);

int main() {
	char vidp;
	string Transcript;
	int i;
	int num = 7;
	int extra_letters;
	int number_of_words;
	int structure;
	int sum_points;
	char exept2 = ' ';
	const int N = 1000;
	const int K = 50;
	char mass[K];
	char buff[1000]; // буфер для зберігання тексту, считаного із файлу 

	system("chcp 1251 & cls");

	do{
		structure = 0;
		number_of_words = 0;
	    cout << "Задайте спосіб заповнення (vruchnu-вручну або random-випадково)";
        fflush(stdin);
        vidp=getchar();
        fflush(stdin);
        if(vidp == 'V' || vidp == 'v') {
			cout << "Введіть кількість букв які хочете ввести num = ";
			cin >> num;
			vruchnu(mass,num);
		}
        else {
			cout << "Сгенеровані букви:" << endl;
			random(mass,num);

			cout << "Ви хочете додати додаткові букви до сгенерованих? (Yes-так)";
            fflush(stdin);
            vidp=getchar();
            fflush(stdin);

			if (vidp == 'Y' || vidp == 'y') {
				cout << "Скільки букв ви хочете додати?" << endl;
				cin >> extra_letters;
				addition(mass, num, extra_letters);
				num += extra_letters;
				cout << "Остаточний набір букв:" << endl;
				for (int ind = 0; ind < num; ind++) {
					cout << mass[ind] << " ";
				}
			}
		}
	    Resource *M = new Resource[N];
		ifstream fin("C:\\Users\\Андрей\\Desktop\\Dictionary\\ALL.txt"); // відкрили файл для читання
		while(!fin.eof()) {
			sum_points = 0;
		    fin.getline(buff,sizeof(buff)); // считали рядок із файлу

			if (search(mass, num, buff, &exept2) == 1) {
				number_of_words++;
		        GetData(M, number_of_words, buff, sum_points, structure, exept2);
				structure++;
				}
			}
        fin.close(); // закрили файл

		if (number_of_words == 0) {
			cout << "No words" << endl;
		}
		else {
			SortData(M, number_of_words);
            ShowData(M, number_of_words);
		
		    cout << "Введіть слово: ";
		    cin >> Transcript;
		    if (output(M, number_of_words, Transcript) == 0) {
				cout << "\nСлово  \"" << Transcript << "\"" << " не знайдено" << endl;
			}
		}
		delete []M;

		cout << "\nПродовжити роботу? (Yes-так)";
		fflush(stdin);
		vidp = getchar();
		cout << "\n";
		fflush(stdin);
		
	}
	while (vidp == 'Y' || vidp == 'y');
	system("pause");
	return 0;
}
//підрахунок очок
int points(char letter) {
	int point = 0;
	switch (letter) {
	case 'L':
	case 'S':
	case 'U':
	case 'N': 
	case 'R':
	case 'T':
	case 'O':
	case' A':
	case 'I': 
	case 'E': 
	case 'l':
	case 's':
	case 'u':
	case 'n': 
	case 'r': 
	case 't':
	case 'o':
	case 'a': 
	case 'i':
	case 'e': point = 1; break;

	case 'G':
	case 'D':
	case 'g':
	case 'd': point = 2; break;

	case 'B':
	case 'C':
	case 'M':
	case 'P':
	case 'b':
	case 'c':
	case 'm':
	case 'p': point = 3; break;

	case 'F':
	case 'H':
	case 'V':
    case 'W':
	case 'Y':
	case 'f':
	case 'h':
	case 'v':
	case 'w':
	case 'y': point = 4; break;

	case 'K':
	case 'k': point = 5; break;

	case 'J':
	case 'X':
	case 'j':
	case 'x': point = 8; break;

	case 'Q':
	case 'Z':
	case 'q':
	case 'z': point = 10; break;
	}
	return point;
}
//ввід букв з клавіатури
void vruchnu(char *mass, int num) {
  int ind;
  for (ind = 0; ind < num; ind++) {
    cin >> mass[ind];
  }
}
//генерація випадкових букв
void random(char *mass, int num) {
  int ind;
  int flag = 0;
  srand(time (0));
  for (ind = 0; ind < num; ind++) {
    mass[ind] = rand() % 27 + 65;
	if (mass[ind] == 91 && flag == 0) {
		mass[ind] = rand() % 3;
		
		if (mass[ind] == 2) {
			mass[ind] = 42;
			flag = 1;
		}
		else {
			mass[ind] = rand() % 26 + 65;
		}
	}
	if (mass[ind] == 91 && flag == 1) {
		mass[ind] = rand() % 26 + 65;
	}
	cout << mass[ind] << " ";
  }
  cout << endl;
}
//визначення чи можна скласти поточне слово із наших букв
int search(char *mass, int num, char *buff, char *exept2) {
	int ind;
	int j, i;
	int exeption = -1;
	int exept = -1;
	char memory[35] = "         ";
	for (j = 0; buff[j] != 32; j++) {
      ind = 0;
	  for (i = 0; i < num; i++) {
		  if (mass[i] == 42) { exeption = i; }
		  if ((buff[j] == mass[i] || buff[j] == (mass[i] + 32)) && buff[j] != memory[i] && buff[j] != (memory[i] + 32)) {
			  ind = 1;
			  memory[i] = mass[i];
			  break;
		  }
	  }
	  if (exeption != -1 && exept == -1) {
		  ind = 1;
		  memory[exeption] =  buff[j];
		  exept = j;
		  *exept2 = buff[j];
	  }
	  if (ind == 0) { 
		  break;
	  }
	}
	return ind;
}
//вивід даних на екран
void ShowData(Resource *M, int number_of_words) {
	cout << "Можливі слова:" << endl;
   for (int i = 0; i < number_of_words; i++) {
	 cout << M[i].Word;
     cout << " : ";
	 cout << M[i].Value << endl;
   }
}
//заповнення структури
void GetData(Resource *M, int number_of_words, char *buff, int sum_points, int structure, char exept2) {
	int end_word;
	string local = "                    ";
	M[structure].Word = local;
	int i,j;
	for (i = 0; buff[i] != *""; i++) {
		if (i > sizeof(buff)) break;
		if(buff[i] == 32) break;
		//cout << buff[i];
		M[structure].Word.at(i) = buff[i];
		if (buff[i] == exept2) {
			exept2 = ' ';
		}
		else {
		sum_points += points(buff[i]);
		}
	}
	end_word = i;
	for (i = 1; i <= 20 - end_word; i++) {
	M[structure].Word.erase(M[structure].Word.find(' '), 1);
	}

	M[structure].Description = buff;
	M[structure].Value = sum_points;
}
//вивід на екран запиту користувача
int output(Resource *M, int number_of_words, string Transcript) {
	int ind = 0;
	for (int i = 0; i < number_of_words; i++) {
		if (Transcript == M[i].Word) {
			cout << "\nІнформація по слову \"" << Transcript << "\": " << endl;
			cout << "Слово: " << M[i].Word << endl;
			cout << "Значення слова: " << M[i].Description << endl;
			cout << "Кількість очок: " << M[i].Value << endl;
			ind = 1;
			break;
		}
	}
	return ind;
}
//сортування
void SortData(Resource *M, int number_of_words) {
	Resource temp;
	for (int i = 0; i < number_of_words +1; i++) {
		for (int j = 0; j < number_of_words +1; j++) {
			if(M[j].Value < M[j + 1].Value) {
				temp = M[j];
			    M[j] = M[j + 1];
			    M[j + 1] = temp;
			}		
		}
	}
	cout << endl << number_of_words << endl;
}
//ввід додаткових букв
void addition(char *mass, int num, int extra_letters) {
  int ind;
  for (ind = num; ind < num + extra_letters; ind++) {
    cin >> mass[ind];
  }
}