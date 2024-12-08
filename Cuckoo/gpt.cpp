#include "gpt.h"

int main()
{
    HashTable<string, StringHashFamily> hashTable(101, 2);
    // 插入一些元素
    string element = "hello";
    hashTable.insert(element);
    cout << hashTable.contains("hello") << endl;
    return 0;
}
