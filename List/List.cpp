#include <iostream>
#include <string>
#include "List.h"
// #include "myList.h"

int main() {
    // 测试默认构造函数
    List<int> list1;
    std::cout << "List 1 size: " << list1.size() << " empty? "<< list1.empty() <<std::endl;

    // 测试初始化列表构造函数
    List<int> list2 = {1, 2, 3, 4, 5};
    std::cout << "List 2 size: " << list2.size() << std::endl;

    // 测试拷贝构造函数
    List<int> list3(list2);
    std::cout << "List 3 size: " << list3.size() << std::endl;

    // 测试移动构造函数
    List<int> list4(std::move(list2));
    std::cout << "List 4 size: " << list4.size() << ", List 2 size after move: " << list2.size() << std::endl;

    //测试接连赋值是否会出错(引用传递)
    list2 = list3 = list4;
    std::cout << "List 2's size becomes: " << list2.size() << " again "  << std::endl;
    std::cout <<"Now List2's elements are: ";
    for (auto it : list2)
    {
        std::cout << it <<" ";
    }
    std::cout<<std::endl;

    //测试自我赋值时
    list3=list3;
    std::cout <<"After list3=list3, list3's elements are: ";
    for (auto it : list3)
    {
        std::cout << it <<" ";
    }
    std::cout<<std::endl;

    //////////////////////////////////////////////////
    std::cout << "Let's test push and pop"<< std::endl;
    //////////////////////////////////////////////////

    // 测试插入和迭代器，前置++/--与后置++/--均测试
    int temp = 10;
    list1.push_back(temp);
    list1.push_back(-4-1);
    list1.push_front(20);
    list1.push_front(20+10);
    std::cout << "List1 front is : "<<list1.front() <<" back is : "<<list1.back() << std::endl;
    std::cout << "List1 is (by ++i): ";
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "List1 is (by i++): ";
    for (auto it = list1.begin(); it != list1.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "inverse List1 is (by --i): ";
    auto it = list1.end();
    for (; --it != list1.begin(); ) {
        std::cout << *it << " ";
    }
    std::cout <<*it<<" "<< std::endl;

    std::cout << "inverse List1 is (by i--): ";
    for (auto it = list1.end(); it-- != list1.begin(); ) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // 测试const是否有效
    const List<int> const_list={100,200,300};
    auto const_it = const_list.begin();
    std::cout <<"*const_it : " <<*const_it <<std::endl;
    const_it = const_list.end();
    std::cout <<"*Now --const_it : " <<*--const_it <<std::endl;

    // 测试插入指定位置
    list1.insert(++list1.begin(), 25);
    list1.insert(list1.begin(), 10+1);
    std::cout << "List1 after insert: ";
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    //测试pop
    list1.pop_back();
    list1.pop_front();
    // 测试删除元素
    list1.erase(++list1.begin()); // 应该删除25
    std::cout << "List1 after pop 1st element, then erase 2nd element and pop the last element: ";
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    list1.erase(--list1.end()); // 应该删除最末一个
    std::cout << "List1 after erase the last element: ";
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // 测试清空列表
    list1.clear();
    std::cout << "List1 size after clear: " << list1.size() << std::endl;

    std::cout << "List1's content now : ";
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //尝试clear一个空列表
    list1.clear();


    //接下来测试string类别
    List<std::string> strlist1;
    std::cout << "StringList 1 size: " << strlist1.size() << std::endl;

    List<std::string> strlist2 = {"Hello", "this", "is", "Maythics"};
    std::cout << "StringList 2 size: " << strlist2.size() << std::endl;

    std::cout << "StringList 2 content: ";
    for (auto it = strlist2.begin(); it != strlist2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "StringList 2 content: ";
    auto iter = strlist2.end();
    strlist2.insert(iter,"' homepage");
    for (auto it = strlist2.begin(); it != strlist2.end(); ++it) {
        std::cout << *it << " ";
        *it = "a";
    }
    std::cout << std::endl;

    for (auto it = strlist2.begin(); it != strlist2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

// /////////////////////////////////////////////
// /////////// BUG SECTION  ////////////////////
// /////////////////////////////////////////////
//     auto iterator = strlist2.end();
//     iterator++;
//     std::cout<<"After illegal move: "<<std::endl;
//     std::cout<<*iterator<<std::endl;
// /////////////////////////////////////////////
// /////////////////////////////////////////////
//     std::cout<<"Try to erase an empty list: "<<std::endl;
//     list1.erase(list1.end());
// ////////////////////////////////////////////
// ////////////////////////////////////////////

    return 0;
}
