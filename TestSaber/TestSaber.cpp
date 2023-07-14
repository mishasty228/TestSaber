// TestSaber.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL 
    std::string data;

    ListNode() {
        prev = this;
        next = this;
        rand = this;
        data = std::string(64, '\0');
    }
    ListNode(std::string NewData)
    {
        prev = this;
        next = this;
        rand = this;
        data = NewData;
    }
};
class List {
public:
    void Serialize(FILE* file); // сохранение в файл (файл открыт с помощью fopen(path, "wb")) 
    void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, "rb")) 

private:
    ListNode* head;
    ListNode* tail;
    int count = 0;
public: 
    ListNode* GetRand()
    {
        ListNode* Target = head;
        int RandElem = std::rand() % (count + 1);
        for (int i = 0; i < RandElem; i++)
        {
            Target = Target->next;
        }
        return Target;
    }
    ListNode* FindElem(std::string Search)
    {
        ListNode Target = *head;
        for (int i = 0; i < count; i++)
        {
            bool Found = Target.data.c_str() == Search.c_str();
            if (Found) return &Target;
            Target = *Target.next;
        }
        return NULL;
    }
    int GetIndexAtNode(ListNode* Node)
    {
        ListNode* Target = head;
        for (int i = 0; i < count; i++)
        {
            if (Node == Target) return i;
            Target = Target->next;
        }
        return 0;
    }
    ListNode* GetNodeAtIndex(int Index)
    {
        ListNode* Target = head;
        for (int i = 0; i < Index; i++)
        {
            Target = Target->next;
        }
        return Target;
    }
    ListNode* AddNode(std::string Data)
    {
        ListNode* NewNode = new ListNode(Data);
        NewNode->prev = tail;
        if (tail != NULL)
            tail->next = NewNode;
        if (head == NULL)
            head = NewNode;
        tail = NewNode;
        count++;
        return NewNode;
    }
    void RandomizeList()
    {
        ListNode* Current = head;
        for (int i = 0; i < count; i++)
        {
            Current->rand = GetRand();
            Current = Current->next;
        }
    }
};

void InitializeNodes(List* NodeList)
{
    int ListLen = 0;
    printf("Enter NodeList Length: ");
    std::cin >> ListLen;
    for (int i = 0; i < ListLen; i++)
    {
        std::string Data;
        printf("Enter %i element data: ", i);
        std::cin >> Data;
        NodeList->AddNode(Data);
    }
    NodeList->RandomizeList();
    
}

void List::Serialize(FILE* file)
{
    ListNode* CurrentNode = head;

    fwrite(&count, sizeof(count), 1, file);
    for (int i = 0; i < count; i++)
    {
        unsigned int DataLen(CurrentNode->data.size());
        fwrite(&DataLen, sizeof(DataLen), 1, file);
        fwrite(CurrentNode->data.c_str(), CurrentNode->data.length(), 1, file);

        CurrentNode = CurrentNode->next;
    }
    CurrentNode = head;
    for (int i = 0; i < count; i++)
    {
        int RandDataInd = GetIndexAtNode(CurrentNode->rand);

        fwrite(&RandDataInd, sizeof(RandDataInd), 1, file);

        CurrentNode = CurrentNode->next;
    }
}

void List::Deserialize(FILE* file)
{
    ListNode* CurrentNode;
    unsigned int ListLen(0);
    fread(&ListLen, sizeof(ListLen), 1, file);
    count = ListLen;
    for (int i = 0; i < ListLen; i++)
    {
        AddNode("");
    }
    count = ListLen;
    CurrentNode = head;
    for (int i = 0; i < count; i++)
    {
        unsigned int DataLen(0);
        fread(&DataLen, sizeof(DataLen), 1, file);
        fread(&CurrentNode->data[0], 1, DataLen, file);
        std::cout << i << "===" << CurrentNode->data.c_str() << std::endl;
        CurrentNode = CurrentNode->next;
    }

    CurrentNode = head;
    for (int i = 0; i < count; i++)
    {
        int RandDataInd;
        std::string RandString = "";
        fread(&RandDataInd, sizeof(RandDataInd), 1, file);
        std::cout << "Random index: " << RandDataInd << std::endl;
        CurrentNode->rand = GetNodeAtIndex(RandDataInd);
        
        std::cout << CurrentNode->data.c_str() << "-------" 
            << CurrentNode->rand->data.c_str() << std::endl;

        CurrentNode = CurrentNode->next;
    }
}

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
    ToBit(237);
    ToBit(-163);

    char data[] = "PPPRRROO    GaaaaMMMMMerr";
    RemoveDups(data);
    printf("%s\n", data);

    srand(time(NULL));

    List NodeList = List();
    FILE* stream;
    errno_t err;

    int Select = 0;

    std::cout << "Choose action (1 - Initialize and serialize, 2 - deserialize): ";
    std::cin >> Select;
    switch (Select)
    {
    case 1:
        InitializeNodes(&NodeList);

        err = fopen_s(&stream, "NodeList.bin", "wb");
        if (err == 0) NodeList.Serialize(stream);
        err = fclose(stream);
        break;
    case 2:

        err = fopen_s(&stream, "NodeList.bin", "rb");
        if (err == 0) NodeList.Deserialize(stream);
        err = fclose(stream);
        break;
    default: 
        break;
    }
    
    return 0;
}
