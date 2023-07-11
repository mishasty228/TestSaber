// TestSaber.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL 
    std::string data;
};
class List {
public:
    void Serialize(FILE* file); // сохранение в файл (файл открыт с помощью fopen(path, "wb")) 
    void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, "rb")) 

private:
    ListNode* head;
    ListNode* tail;
    int count;
};


void ToBit(int n)
{
    if (n == 0)
    {
        printf("0\n");
        return;
    }

    unsigned int bits = 1 << (sizeof(n) * 8 - 1);

    while (bits)
    {
        unsigned char c = (n & bits) ? 1 : 0;
        printf("%i", c);
        bits >>= 1;
    }
    printf("\n");
}

void RemoveDups(char* str)
{
    const char* source = str;
    char* current = str;
    while (*source)
    {
        if (current != source)
        {
            *current = *source;
        }

        *current++;

        while ((*source + 1) && *(source + 1) == *source)
        {
            *source++;
        }
        *source++;
    }
    *current = 0;
}

int main()
{
    char data[] = "PPPRRROO    GaaaaMMMMMerr";
    RemoveDups(data);
    printf("%s\n", data);
}

void List::Serialize(FILE* file)
{
}

void List::Deserialize(FILE* file)
{
}
