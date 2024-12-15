#include "cuckoo.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

/////////////////////////////////// STRING HASH TEST ///////////////////////////////////
// 用于生成足够多的测试字符串
string generateRandomString(int length) {
    string str;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; ++i) {
        str += charset[ rand() % (sizeof(charset) - 1)];
    }
    return str;
}

// // 测试String类的哈希值计算（用这个函数可以仔细看string的哈希算法，在主程序中未演示）
// void HashCalculation(string elem,int count) {
//     StringHashFamily hashFamily(count);  // 定义 count 个哈希函数
//     cout << "Hashing '" << elem << "' with hash functions:" << endl;
//     for (int i = 0; i < count; ++i) {
//         cout << "Hash of '" << elem << "' using function " << i << " (multiplier " << i << "): "
//              << hashFamily.hash(elem, i) << endl;
//     }
//     hashFamily.printMultipliers();
// }

void test_stringHash()
{
    cout<< "****************************************"<< "\n";
    cout<< "************* TEST STRING **************"<< "\n";
    cout<< "****************************************"<< "\n" << endl;
    srand(time(0));  // 传入当前时间作为种子
    HashTable<std::string,StringHashFamily> Table1(5,3);
    Table1.print_Functions();
    std::string str = "hello";
    Table1.insert(str, true); /// debug=true，可视化步骤细节
    Table1.print_Table();
    int same = 0;
    for(int i=0;i<10;i++)
    {
        bool fail = Table1.insert(generateRandomString(5),true);/// debug=true，可视化步骤细节
        if (fail == false)
            same ++;
        Table1.print_Table();
        Table1.print_TableSize();
        Table1.print_currentSize();

    }
    cout<<"contain hello? " << Table1.contains("hello")<< endl;
    Table1.remove("hello");
    Table1.print_Table();
    Table1.print_currentSize();
    cout<<"contain hello? " << Table1.contains("hello")<< endl;

    cout << "same is "<< same << endl;
}
/////////////////////////////////// STRING HASH TEST ////////////////////////////////->end

////////////////////////////////////// INT HASH TEST /////////////////////////////////////
void test_intHash()
{
    cout<< "****************************************"<< "\n";
    cout<< "*************** TEST INT ***************"<< "\n";
    cout<< "****************************************"<< "\n" << endl;
    srand(time(0));  // 传入当前时间作为种子
    HashTable<int,IntHashFamily> Table2(5,3);
    Table2.print_Functions();
    Table2.print_Table();
    Table2.insert(104133,true); /// debug=true，可视化步骤细节
    Table2.print_Table();
    int same = 0;
    for(int i=0;i<10;i++)
    {
        ///  随机生成100000以内的整数
        bool fail = Table2.insert(abs(rand())%100000,true); /// debug=true，可视化步骤细节
        if (fail == false)
            same ++;
        Table2.print_Table();
        Table2.print_TableSize();
        Table2.print_currentSize();
    }
    cout<<"contain 104133? " << Table2.contains(104133)<< endl;
    Table2.remove(104133);
    Table2.print_Table();
    Table2.print_currentSize();
    cout<<"contain 104133? " << Table2.contains(104133)<< endl;

    cout << "same is "<< same << endl;

}
////////////////////////////////////// INT HASH TEST ////////////////////////////////->end


//////////////////////////////////// EFFICIENCY TEST /////////////////////////////////////

void efficiency_helper(int tablesize,int function_number)
{
    HashTable<int,IntHashFamily> Table3(tablesize,function_number);
    Table3.print_TableSize();
    int same =0;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<tablesize/2;i++)
    {
        ///  随机生成50倍tablesize以内的整数
        bool fail = Table3.insert(abs(rand())%(50*tablesize),false); /// debug=false，关闭步骤可视化
        if (fail == false)
            same ++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end-start;
    Table3.print_TableSize();
    Table3.print_currentSize();
    cout << "same is "<< same << endl;
    cout << "TIME COST " <<  duration.count() << "\n" << endl;
}

void test_efficiency()
{
    cout<< "****************************************"<< "\n";
    cout<< "************ TEST EFFICIENCY ***********"<< "\n";
    cout<< "****************************************"<< "\n" << endl;

    for(int j =1;j<10;j++)
    {
      efficiency_helper(j*10000000,3);
    }
}
//////////////////////////////////// EFFICIENCY TEST ////////////////////////////////->end


int main()
{
    test_stringHash();
    test_intHash();
    test_efficiency();
    return 0;
}
