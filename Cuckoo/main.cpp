#include "cuckoo.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

/////////////////////////////////// STRING HASH TEST ///////////////////////////////////
// 用于生成足够多的测试字符串
std::string generateRandomString(int length) {
    std::string str;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; ++i) {
        str += charset[ rand() % (sizeof(charset) - 1)];
    }
    return str;
}

// 测试String类的哈希值计算
void HashCalculation(std::string elem,int count) {
    StringHashFamily hashFamily(count);  // 定义 count 个哈希函数
    cout << "Hashing '" << elem << "' with hash functions:" << endl;
    for (int i = 0; i < count; ++i) {
        cout << "Hash of '" << elem << "' using function " << i << " (multiplier " << i << "): "
             << hashFamily.hash(elem, i) << endl;
    }
    hashFamily.printMultipliers();
}

void test_stringHash()
{
    srand(time(0));  // 传入当前时间作为种子
    HashTable<std::string,StringHashFamily> Table1(10,4);
    Table1.print_Functions();
    std::string str = "hello";
    Table1.insert(str);
    int same = 0;
    for(int i=0;i<15;i++)
    {
        bool fail = Table1.insert(generateRandomString(5));
        if (fail == false)
            same ++;
        Table1.print_TableSize();
        Table1.print_Table();
        Table1.print_currentSize();

    }
    cout<<Table1.contains("hello")<< endl;
    Table1.remove("hello");
    Table1.print_currentSize();
    Table1.print_Table();
    cout<<Table1.contains("hello")<< endl;
    Table1.print_TableSize();

    cout << "same is "<< same << endl;
}
/////////////////////////////////// STRING HASH TEST ////////////////////////////////->end





int main()
{
    srand(time(0));  // 传入当前时间作为种子
    HashTable<std::string,StringHashFamily> Table1(10,4);
    Table1.print_Functions();
    std::string str = "hello";
    Table1.insert(str);
    int same = 0;
    for(int i=0;i<15;i++)
    {
        string new_str  =generateRandomString(15);
        bool fail = Table1.insert(new_str);
        if (fail == false)
            same ++;
        Table1.print_TableSize();
        Table1.print_Table();
        Table1.print_currentSize();

    }
    cout<<Table1.contains("hello")<< endl;
    Table1.remove("hello");
    Table1.print_currentSize();
    Table1.print_Table();
    cout<<Table1.contains("hello")<< endl;
    Table1.print_TableSize();

    cout << "same is "<< same << endl;


    return 0;
}

// int vectorSize = 10; // 向量的大小
    // vector<string> vec(vectorSize);

    // // 使用 generateRandomString 函数填充向量
    // for (auto & elem : vec)
    // {
    //     elem = generateRandomString(5);
    //     cout << elem << endl;
    //     HashCalculation(elem,5);
    // }
// Table1.insert("hello");

    // Table1.insert("goodbye");

    // cout << Table1.contains("gello") << endl;


// srand(time(0));  // 传入当前时间作为种子
    // HashTable<std::string,StringHashFamily> Table1(200,4);
    // Table1.print_Functions();
    // std::string str = "hello";
    // Table1.insert(str);
    // int same = 0;
    // for(int i=0;i<15;i++)
    // {
    //     bool fail = Table1.insert(generateRandomString(5));
    //     if (fail == false)
    //         same ++;
    //     Table1.print_TableSize();
    //     Table1.print_Table();
    //     Table1.print_currentSize();

    // }
    // cout<<Table1.contains("hello")<< endl;
    // Table1.remove("hello");
    // Table1.print_currentSize();
    // Table1.print_Table();
    // cout<<Table1.contains("hello")<< endl;
    // Table1.print_TableSize();

    // cout << "same is "<< same << endl;
