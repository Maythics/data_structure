#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
template <typename Comparable>
void Downward_sift( vector<Comparable> & arr, int root, int end );
template <typename Comparable>
void my_sort( vector<Comparable> & arr );

/* 调试用的函数，用于打印vector */
template <typename Comparable>
void print(vector<Comparable>& vc){
  for(auto i : vc)
   {cout << i << " ";}
   cout << endl;
}

template <typename Comparable>
void my_sort( vector<Comparable> & arr ) // 要求传入的arr必须已经是一个heap了
{
  for( int j = arr.size() - 1; j > 0; --j ) // 依次看最后一个，准备移到根部
  {
    swap( arr[0], arr[j] ); // 根部的即最大元弹出，根部位置由a[j]补充
    Downward_sift(arr,0,j-1); // 调用下滤函数，将根部的元素下滤到合适位置
    /// print(arr);
  }
}

/* 下滤操作*/
template <typename Comparable>
void Downward_sift( vector<Comparable> & arr, int root, int end )
{
  int maxChild; // 左右孩子中较大的那个，下标maxChild

  while((root*2+1)<= end)
  {
    if((2*root+2)<=end && arr[2*root+1]< arr[2*root+2])
    {
      maxChild = 2 * root + 2; // 右孩子的下标
    }
    else
    {
      maxChild = 2 * root + 1; // 左孩子的下标
    }

    if(arr[root] < arr[maxChild]) // 比较，判断是否下滤
    {
      swap(arr[root],arr[maxChild]); // 向下交换
      root = maxChild; // 交换后，root指向孩子
    }
    else // 若不交换，就直接退出
    {
      return;
    }
  }
}
