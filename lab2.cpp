#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

char* GetStroke(bool* Flag)
{
	char* Stroke = NULL;
	char c;
	size_t i = 0;
	size_t SizeStroke = 2;
	while ( (c = getchar() ) != EOF && c != '\n' )
	{
		if ( Stroke != NULL )
		{
			if( i == SizeStroke - 1 )
			{
				char* temp = new char[ SizeStroke * 2 ];
				if( temp != NULL )
				{
					SizeStroke *= 2;
					memcpy(temp, Stroke, SizeStroke*sizeof(char));
					delete[] Stroke;
					Stroke = temp;
				}
			}
		}
		else
		{
			Stroke = new char [SizeStroke];	
		}
		Stroke[i++] = c;
	}
	if ( Stroke != NULL )
	{
		Stroke[i] = '\0';
	}
	if ( c == EOF )
		*Flag = false;		//Флаг сигнализируется об окончании строк в файле/потоке данных
	return Stroke;
}

int Input(char*** Text)
{

	*Text = NULL;
	size_t SizeText = 1;
	size_t i = 0;
	bool Flag = true;
	while( Flag )
	{
		if( *Text !=  NULL )
		{
			if( i == SizeText )
			{
				char** temp = new char* [ SizeText * 2 ];
				if( temp != NULL )
				{
					SizeText *= 2;
					memcpy(temp, *Text, SizeText*sizeof(char*));
					delete[] *Text;
					*Text = temp;
				}
			}

		}
		else
		{
			*Text = new char* [SizeText];	
		}
		char* temp = GetStroke(&Flag);
		if ( temp != NULL )
		{
			(*Text)[i++] = temp;
		}
	}

	return i;
}
/*
	int CountBrackets = 0;
			if ( c == '{' )
				++CountBrackets;
			if ( c == '}' )
				--CountBrackets;
			Stroke[i++] = c;	

	if ( CountBrackets != 0 )
	{
			delete[] Stroke;
			Stroke = NULL;
	}
*/

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
		return NULL;
	}
	return Stroke;
}

int LeaveCorrect( char** Mas, int SizeMas, char*** Text )
{
	*Text = NULL;
	size_t SizeText = 1;
	size_t i = 0, j = 0;
	char* temp;
	while( j < SizeMas )
	{
		temp = IsCorrect(Mas[j]);
		if ( temp != NULL )
		{
			if( *Text !=  NULL )
			{
				if( i == SizeText )
				{
					char** TempResult = new char* [ SizeText * 2 ];
					if( TempResult != NULL )
					{
						SizeText *= 2;
						memcpy(TempResult, *Text, SizeText*sizeof(char*));
						delete[] *Text;
						*Text = TempResult;
					}
				}
			}
			else
			{
				*Text = new char* [SizeText];	
			}
			(*Text)[i++] = temp;
		}
		++j;
	}
	return i;
}

void Erase( char** mas, size_t Size )
{
	size_t i = 0;
	for ( ; i < Size; ++i)
	{
		delete[] mas[i];
	}
	delete[] mas;
}

int main()
{
	char **mas;
	char** Result;
	int NumberOfLines = Input(&mas);
	int NumberOfLinesResult = LeaveCorrect( mas, NumberOfLines, &Result ); 
	int i = 0;
	while( i < NumberOfLinesResult )
	{
		printf("%s\n", Result[i++]);
	}
	Erase(mas, NumberOfLines);
	Erase(Result, NumberOfLinesResult);
}
