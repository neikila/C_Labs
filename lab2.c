#include <stdio.h>
#include <stdlib.h>

#define MINLINESIZE 2

//Получение размера строки данных
int Length (char* Stroke)
{
	int i = 0;
	while ( *Stroke++ != '\0' )
	{
		++i;
	}
	return i+1;
}


//Копирования строки символов
void StrCopy (char* to, char* from)
{
	while ( *from != '\0' )
	{
		*to = *from;
		++from;
		++to;
	}
}


//Получения строки из stdin
char* GetStroke(int* Flag)
{
	char* Stroke = NULL;
	char c;
	size_t i = 0;
	size_t SizeStroke = MINLINESIZE;
	while ( (c = getchar() ) != EOF && c != '\n' )
	{
		if ( Stroke != NULL )
		{
			if( i == SizeStroke - 1 )
			{
				SizeStroke *= 2;
				Stroke = (char*)realloc( Stroke, SizeStroke*sizeof(char));
			}
		}
		else
		{
			Stroke = (char*)malloc( sizeof(char) * SizeStroke);
		}
		Stroke[i++] = c;
	}
	if ( Stroke != NULL )
	{
		Stroke[i] = '\0';
	}
	if ( c == EOF )
		*Flag = 0;		//Флаг сигнализируется об окончании строк в файле/потоке данных
	return Stroke;
}


//Ввод данных
size_t Input(char*** Text)
{
	*Text = NULL;
	size_t SizeText = 0;
	size_t i = 0;
	int Flag = 1;
	char* TempStr = NULL;
	while( Flag == 1 )
	{
		if( *Text !=  NULL )
		{
			if( i == SizeText )
			{
				SizeText *= 2;
				*Text = (char**)realloc(*Text, sizeof(char*) * SizeText);
			}
		}
		else
		{
			SizeText = 1;
			*Text = (char**)malloc( sizeof(char*) * SizeText );
		}
		TempStr = GetStroke(&Flag);
		if ( TempStr != NULL )
		{
			(*Text)[i++] = TempStr;
		}
	}
	return i;
}


//Проверка соотвествия строки условию
char* IsCorrect(char* Stroke)
{
	char* temp = Stroke;
	int count = 0;
	while( *temp != '\0' )
	{
		if( *temp == '(' )
			++count;
		if( *temp == ')' )
			--count;
		temp++;
	}
	if( count != 0 )
	{
		Stroke = NULL;
	}
	return Stroke;
}


//Выбор строк. удовлетворяющих заданному условию
size_t LeaveCorrect( char** Mas, int SizeMas, char*** Text )
{
	*Text = NULL;
	size_t SizeText = 1;
	size_t i = 0, j = 0;
	char* temp;
	size_t len = 0;
	while( j < SizeMas )
	{
		temp = IsCorrect(Mas[j]);
		if ( temp != NULL )
		{
			if( *Text !=  NULL )
			{
				if( i == SizeText )
				{
					SizeText *= 2;
					*Text = (char**)realloc( *Text, sizeof(char*) * SizeText);
				}
			}
			else
			{
				*Text = (char**)malloc( sizeof(char*)*SizeText );
			}
			len = Length( temp );
			(*Text)[i] = (char*)malloc( sizeof(char) * len );
			StrCopy( (*Text)[i], temp );
			(*Text)[i++][len - 1] = '\0';
		}
		++j;
	}
	return i;
}


//Очистка памяти
void Erase( char** mas, size_t Size )
{
	size_t i = 0;
	for ( ; i < Size; ++i)
	{
		free(mas[i]);
	}
	free(mas);
}

int main()
{
	char **mas;
	char **Result;

	//Получение массива входных данных
	size_t NumberOfLines = Input(&mas);
	if( NumberOfLines <= 0 )
	{
		printf("[error]\n");
		return 0;
	}

    	//Вызов функции отбора строк в массив, переданный третьим параметром
	size_t NumberOfLinesResult = LeaveCorrect( mas, NumberOfLines, &Result );

    	//Вывод строк удовлетворющих требованию
	size_t i = 0;
	while( i < NumberOfLinesResult )
	{
		printf("%s\n", Result[i++]);
    	}
    	//Освобождение памяти
	Erase(mas, NumberOfLines);
	Erase(Result, NumberOfLinesResult);
	return 0;
}
