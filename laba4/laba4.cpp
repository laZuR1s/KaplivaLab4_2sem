#include <iostream>
#include <fstream>
#include <Windows.h>

const int n = 35;
const int m = 15;
const int LEN = 255;

// interface

int check_file(std::ifstream& file);
int create_matrix(std::ifstream& file, char matrix[][m], char* combination);
void out_word(std::ofstream& file, char* word);
void out_matrix(std::ofstream& file, char matrix[][m], int row);
void enter_file_name(char* file_name);
void enter_combination(char* file_name);

// task

bool contains_on(char* word, char* combination);
void reverseStr(char* word);
void swap_words(char* word1, char* word2);
void simple_choice_sort(char matrix[][m], int row);
void task(std::ifstream& input, std::ofstream& output, char* combination);

int main()
{
	SetConsoleOutputCP(1251);
	char file_name[LEN];
	enter_file_name(file_name);
	std::ifstream input(file_name);


	switch (check_file(input))
	{
	case -1:
		std::cout << "File not found\n";
		break;
	case 0:
		std::cout << "Empty file\n";
		break;
	default:
		std::ofstream output("output.txt");
		char combination[LEN];
		enter_combination(combination);
		std::cout << "File output.txt is created\n";

		task(input, output, combination);
		output.close();
	}
	std::cin.ignore(std::cin.rdbuf()->in_avail()).get();
}

// interface

void enter_file_name(char* file_name)
{
	std::cout << "\nВведите название файла без 'txt': ";
	char c = getchar();
	int i{};
	while (c != '\n')
	{
		file_name[i++] = c;
		c = getchar();
	}
	file_name[i] = '\0';
	char ending[] = ".txt";
	strcat_s(file_name, m, ending);
}

void enter_combination(char* file_name)
{

	bool flag = false;

		std::cout << "\nВведите подстроку из двух символов: ";
		char c = getchar();
		int i{};
		while (c != '\n')
		{
			file_name[i++] = c;
			c = getchar();
		}

		file_name[i] = '\0';
	

}

int check_file(std::ifstream& file)
{
	int res = 1;
	if (!file)
	{
		res = -1; // Файл не найден!
	}
	else
		if (file.peek() == EOF)
			res = 0; // Файл пустой!
	return res;
}

int create_matrix(std::ifstream& file, char matrix[][m], char* combination)
{
	int row{};
	char* context{}, * ptr{}, line[LEN];
	while (file.getline(line, LEN) && row < n)
	{
		ptr = strtok_s(line, " ,.;:-", &context);
		while (ptr && row < n)
		{
			strcpy_s(matrix[row], m, ptr);
			ptr = strtok_s(0, " ,.;:-", &context);
			if (contains_on(matrix[row], combination))
				++row;
		}
	}
	return row;
}

void out_word(std::ofstream& file, char* word)
{
	size_t len = strlen(word);
	for (size_t i{}; i < len; ++i)
		file << word[i];
	file << '\n';
}

void out_matrix(std::ofstream& file, char matrix[][m], int row)
{
	for (int i{}; i < row; ++i)
		out_word(file, matrix[i]);
}

// task

bool contains_on(char* word, char* combination)
{
	bool result = false;
	int i = 0;
	char* p = 0;
	
	//while (i < strlen(word) && !result)
	//{
	//	//if (word[i] == combination[0] && word[i + 1] == combination[1] || word[i] == combination[1] && word[i + 1] == combination[0])
	//	//	result = true;
	//	//++i;
	//}
		p = (char*)std::memchr(word,combination[0],strlen(word));
		if (p)
		{
			if (strncmp(combination, p, strlen(combination)) == 0)
				result = true;
			
		}
		
		reverseStr(combination);
		
		p = 0;
		p = (char*)std::memchr(word, combination[0], strlen(word));
		if (p)
		{
			if (strncmp(combination, p, strlen(combination)) == 0)
				result = true;

		}

	return result;
}


void reverseStr(char* word)

{

	int n = strlen(word);
	for (int i = 0; i < n / 2; i++)

		std::swap(word[i], word[n - i - 1]);

}

void swap_words(char* word1, char* word2)
{
	char temp[m];
	strcpy_s(temp, sizeof(temp), word1);
	strcpy_s(word1, strlen(word2) + 1, word2);
	strcpy_s(word2, strlen(temp) + 1, temp);
}

void simple_choice_sort(char matrix[][m], int row)
{
	for (int i{}; i < row; ++i)
		for (int j{}; j < row - i - 1; ++j)
		{
			if (strcmp(matrix[j], matrix[j + 1]) > 0)
				swap_words(matrix[j], matrix[j + 1]);
		}
}

void task(std::ifstream& input, std::ofstream& output, char* combination)
{
	char matrix[n][m];
	int row = create_matrix(input, matrix, combination);
	simple_choice_sort(matrix, row);
	out_matrix(output, matrix, row);
}

