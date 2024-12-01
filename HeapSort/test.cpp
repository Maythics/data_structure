#include "HeapSort.h"
#include <random>
#include <chrono>

/* 测试结果是否准确的函数check，比较两者是否相等 */
template <typename Comparable>
bool check(std::vector<Comparable>&  a1, std::vector<Comparable>&  a2)
{
    return a1 == a2;
}


/* 打印结果的函数 */
template <typename Comparable>
void print_result(std::chrono::duration<double> duration, std::chrono::duration<double> duration_copy,std::vector<Comparable> &arr,std::vector<Comparable> &arr_copy)
{
    std::cout << " sort_heap: " << duration.count() << "\n my_sort: " << duration_copy.count() << "\n check result: " << check(arr,arr_copy) << std::endl;
}


int main()
{
    std::random_device rd;  // 获取随机种子
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1500000);  // 生成1到1500000之间的随机整数

    const int length = 1500000;


    //////////////////////* 进行随机序列测试 *//////////////////////
    std::vector<int> arr1(length);

    // 填充随机数
    for (int i = 0; i < length; ++i) {
        arr1[i] = dis(gen);
    }

    // 构建初始堆（最大在上的堆）
    make_heap(arr1.begin(), arr1.end());

    // 拷贝一份arr用于测试我的算法
    std::vector<int> arr1_copy(arr1);

    // 排序（分别使用库里的sort_heap，以及my_sort）
    auto start1 = std::chrono::high_resolution_clock::now();
    std::sort_heap(arr1.begin(), arr1.end());
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;

    auto start1_copy = std::chrono::high_resolution_clock::now();
    my_sort(arr1_copy);
    auto end1_copy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1_copy = end1_copy - start1_copy;

    //结果打印
    std::cout << "**Random Input**" << std::endl;
    print_result(duration1, duration1_copy, arr1,arr1_copy);


    /////////////////////////* 进行单增序列测试 *////////////////////////
    std::vector<int> arr2(length);

    // 填单增序列
    for (int i = 0; i < length; ++i)
    {
        arr2[i] = i;
    }
    make_heap(arr2.begin(), arr2.end());

    // 拷贝一份arr用于测试我的算法
    std::vector<int> arr2_copy(arr2);

    // 排序（分别使用库里的sort_heap，以及my_sort）
    auto start2 = std::chrono::high_resolution_clock::now();
    std::sort_heap(arr2.begin(), arr2.end());
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    auto start2_copy = std::chrono::high_resolution_clock::now();
    my_sort(arr2_copy);
    auto end2_copy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2_copy = end2_copy - start2_copy;

    //结果打印
    std::cout << "**Increasing Input**" << std::endl;
    print_result(duration2,duration2_copy,arr2,arr2_copy);


    ///////////////////////* 进行单减序列测试 *///////////////////
    std::vector<int> arr3(length);
    // 填单减序列
    for (int i = 0; i < length; ++i)
    {
        arr3[i] = length - i;
    }
    make_heap(arr3.begin(), arr3.end());
    // 拷贝一份arr用于测试我的算法
    std::vector<int> arr3_copy(arr3);

    // 排序（分别使用库里的sort_heap，以及my_sort）
    auto start3 = std::chrono::high_resolution_clock::now();
    std::sort_heap(arr3.begin(), arr3.end());
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3 = end3 - start3;

    auto start3_copy = std::chrono::high_resolution_clock::now();
    my_sort<int>(arr3_copy);
    auto end3_copy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3_copy = end3_copy - start3_copy;

    //结果打印
    std::cout << "**Decreasing Input**" << std::endl;
    print_result(duration3, duration3_copy, arr3,arr3_copy);


    ///////////////////////* 进行随机重复序列测试 *//////////////////////
    std::vector<int> arr4(length);
    std::uniform_int_distribution<> new_dis(1, 1000000); // 生成1到1000000之间的随机整数
    // 填充随机数，根据抽屉原理，必有重复
    for (int i = 0; i < length; ++i) {
        arr4[i] = new_dis(gen);
    }
    make_heap(arr4.begin(), arr4.end());
    // 拷贝一份arr用于测试我的算法
    std::vector<int> arr4_copy(arr4);

    // 排序（分别使用库里的sort_heap，以及my_sort）
    auto start4 = std::chrono::high_resolution_clock::now();
    std::sort_heap(arr4.begin(), arr4.end());
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration4 = end4 - start4;

    auto start4_copy = std::chrono::high_resolution_clock::now();
    my_sort(arr4_copy);
    auto end4_copy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration4_copy = end4_copy - start4_copy;

    //结果打印
    std::cout << "**Random with Repeat Input**" << std::endl;
    print_result(duration4,duration4_copy,arr4,arr4_copy);

    return 0;
}
