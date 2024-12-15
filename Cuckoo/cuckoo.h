#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

/// 两个工具函数，功用如其名（实现见文件末尾）
bool isPrime(int n);
int nextPrime(int n);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// STRING HASH /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// StringHashFamily：
/// 这个类是用来记录生成针对string用的Hash函数的，其功能有：
/// 1. 生成一个count那么多的Hash函数
/// 2. 能够调用getNumberOfFunctions返回有几个函数
/// 3. 能够给传入的str提供一个Hash值
class StringHashFamily
{
  public:

    // 构造函数：传入count这一整型，用于生成count个Hash函数
    StringHashFamily(int count) : MULTIPLIERS(count)
    {
        generateNewFunctions();
    }

    int getNumberOfFunctions() const
    {
        return MULTIPLIERS.size(); // 返回存着的Hash函数个数
    }

    void generateNewFunctions()
    {
        int r = rand()% 60 + 1 ; // 先把一个大小为1到50之间的随机数存在r中
        for (auto& mult : MULTIPLIERS)
        {
          r = nextPrime(r+5);
          mult = r;  // 得到一个质数
        }
    }

    size_t hash(const string& x, int which) const /// 必须要用size_t，否则用int会有负号，导致得到数组范围外的下标
    {
        const int multiplier = MULTIPLIERS[which];
        size_t hashVal = 0;

        for (auto ch : x) {
            hashVal = multiplier * hashVal + ch;
        }

        return hashVal;
    }

    // 打印 MULTIPLIERS 的函数
    void printMultipliers() const
    {
        cout << "Multipliers: ";
        for (int mult : MULTIPLIERS) {
            cout << mult << " ";
        }
        cout << endl;
    }

  private:
    vector<int> MULTIPLIERS;  // 存储哈希函数的乘数
};
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// STRING HASH //////////////////////////////->end
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// INT HASH ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// / IntHashFamily：
// / 这个类是用来记录生成针对整型对象的Hash函数的，其功能有：
// / 1. 生成一个count那么多的Hash函数
// / 2. 能够调用getNumberOfFunctions返回有几个函数
// / 3. 能够给传入的int提供一个Hash值
class IntHashFamily
{
  public:
    /// 构造函数：
    IntHashFamily(int count) : MULTIPLIERS(count)
    {
        generateNewFunctions();
    }

    int getNumberOfFunctions() const
    {
        return MULTIPLIERS.size(); // 返回存着的Hash函数个数
    }

    void generateNewFunctions()
    {
        int r = rand()% 600 + 1 ; // 先把一个大小为1到600之间的随机数存在r中
        for (auto& mult : MULTIPLIERS)
        {
          r = nextPrime(r+50);
          mult = r;  // 得到一个质数（跨度更大）
        }
    }

    /// 必须用size_t，用int会有负号，导致得到数组范围外的下标
    size_t hash(const int & x, int which) const
    {
      const int multiplier = MULTIPLIERS[which];
      size_t hashVal = 0;
      hashVal = multiplier * x;
      return hashVal;
    }

    // 打印 MULTIPLIERS 的函数
    void printMultipliers() const
    {
        cout << "Multipliers: ";
        for (int mult : MULTIPLIERS) {
            cout << mult << " ";
        }
        cout << endl;
    }

  private:
    vector<int> MULTIPLIERS; // 存储哈希函数的乘数
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// INT HASH ///////////////////////////////->end
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// HASH TABLE /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// HashTable
/// 这个类是一个Hash表，能够实现：
/// insert
template <typename Datatype, typename FunctionFamily>
class HashTable
{
  public:

    /// 构造函数如下：
    HashTable(int TableSize = 101, int numHashFunctions = 3) : TableSize(TableSize), currentSize(0), numHashFunctions(numHashFunctions), hashFunctions(numHashFunctions)
    {
      /// 直接把numHashFunctions这个值更新为hashFunctions这个实例中MULTIPLIER的大小
      /// numHashFunctions = hashFunctions.getNumberOfFunctions();
      array.resize(TableSize);
      makeEmpty( );
    }

    void makeEmpty()
    {
      currentSize = 0; /// 初始，没有元素，填充量为0
      for( auto & entry : array ) ///各个entry占用与否都显示false
        entry.isActive = false;
    }

    void print_Table()
    {
      for( auto & entry : array ) ///如果isActive就打印里面的element，否则不打印
        if(entry.isActive == true )
          cout << entry.element << "\t" ;
        else
          cout << "\t";
      cout << endl;
    }

    void print_TableSize() /// 打印表的大小
    {
      cout<< "Table Size is "<< TableSize << endl;
    }

    void print_currentSize() /// 打印目前存储数据的大小
    {
      cout<< "current elemment size is "<< currentSize << endl;
    }

    void print_Functions() /// 打印出现在的hash函数（几个乘子）
    {
      hashFunctions.printMultipliers();
    }

    bool contains( const Datatype & x ) const
    {
      /// 直接调用find_element_pos函数，这个函数在找不到x时会返回-1
      return find_element_pos(x) != -1;
    }

    bool insert(Datatype & x, bool debug = false)  /// 将一个数据类型为Datatype的元素x加入到表中，debug是调试用的参数，默认为false，即不打印任何结果到终端中，若为true，将会打印insert的详细步骤
    {
      /// 如果有x元素了，直接返回false，不允许有重复元素
      if( contains(x) )
        return false;

      /// 调用private的函数insert_element完成任务
      return insert_element(x, debug);

    }

    bool insert(Datatype && x, bool debug = false)  /// 将一个数据类型为Datatype的元素x加入到表中（右值版本）debug是调试用的参数，默认为false，即不打印任何结果到终端中，若为true，将会打印详细步骤
    {
      /// 如果有x元素了，直接返回false，不允许有重复元素
      if( contains(x) )
        return false;
      /// 调用private的函数insert_element完成任务
      return insert_element(std::move(x),debug); /// 转换为右值传入

    }


    bool remove( const Datatype & x )
    {
        int current_pos = find_element_pos(x);
        if( current_pos == -1 )
          return false; /// 发现未使用（即不存在该元素）
        /// 否则，就是找到了
        array[current_pos].isActive = false;
        currentSize -= 1;
        return true;
    }

    bool remove( const Datatype && x )
    {
        int current_pos = find_element_pos(std::move(x));
        if( current_pos == -1 )
          return false; /// 发现未使用（即不存在该元素）
        /// 否则，就是找到了
        array[current_pos].isActive = false;
        currentSize -= 1;
        return true;
    }

  private:

    struct HashEntry /// 这个结构可以视为一个有序对，(element,1 or 0)，前一个位置存放元素，后一个位置存放这个位置是否被激活过
    {
        Datatype element;
        bool isActive;
        /// 拷贝构造函数
        HashEntry( const Datatype & element = Datatype(), bool isActive = false)
          : element{ element }, isActive{ isActive } { }
        /// 移动构造函数
        HashEntry( Datatype && element, bool isActive = false )
          : element{ std::move( element ) }, isActive{ isActive } { }
    };

    vector<HashEntry> array; /// 表的本体就是这个array
    int TableSize; /// 表的大小
    int currentSize;
    int numHashFunctions; /// 记录这个表有几个Hash函数，其实就从hashFunctions这个实例里得来
    FunctionFamily hashFunctions; /// 根据设定的FunctionFamily得知是什么Hash函数类型，hashFunctions就是对应的那个实例，记录了这个表所用到的Hash函数们

    /// 下面是一些Private函数

    /// rehash函数，在碰撞次数过多时就会触发了
    void rehash( int newSize , bool debug) /// 传入参数的大小是指新表的大小
    {
      if (debug == true) ///若处于debug模式，则打印出来
        cout<< "############# rehash trigger #############" <<endl;
      hashFunctions.generateNewFunctions();
      vector<HashEntry> old = std::move(array); //std::move(array);
      array.resize(nextPrime(newSize)); /// 新表，大小为newSize
      TableSize = array.size();
      makeEmpty(); /// 清空里面的所有
      /// 接下来把old中的元素一个个插入进新表中：
      for( auto & entry : old )
        if( entry.isActive )
          insert( std::move(entry.element),debug); /// 转化为右值，接管
    }

    /// 如下是一个辅助函数，返回第i个Hash函数规则下，元素x的位置
    int find_position(Datatype x, int i) const
    {
      /// 计算规则很简单，只用先把x和i传给hashFunctions对象的hash函数，就会得到hash值，再填入Table中（考虑到实际大小对TableSize取模就行）
      return (hashFunctions.hash(x,i) % TableSize);
    }

    /// find_element_pos会找传入的元素是否存在，如果真能找到，会返回其在表中的位置
    int find_element_pos( const Datatype & x ) const
    {
      for( int i = 0; i < numHashFunctions; ++i ) /// 逐个尝试该元素x对应的Hash值
      {
        int pos = find_position(x, i); /// position 函数返回x元素，在第i个Hash函数下，应该在表中的位置
          /// 如果该位置是active的，并且，其中的元素就是要找的x，则返回此位置
        if( array[ pos ].isActive == 1 && array[ pos ].element == x )
        {
          return pos;
        }
      }
      /// 没找到返回-1
      return -1;
    }

    /// 插入元素的核心函数，在调用它时，已排除了相同元素的可能
    bool insert_element(Datatype & x, bool debug)
    {
      int KICK = 0 ;
      int MAX_KICK = 1+min(currentSize/4,99); /// 以此设置为最多的碰撞踢除数量
      while( KICK < MAX_KICK )
      {
        for( int i = 0; i < numHashFunctions; ++i ) /// 逐个尝试该元素x对应的Hash值
        {
          int current_pos = find_position(x, i);
          /// 若这个位置未使用，那是ok的
          if(array[current_pos].isActive == false)
          {
            /// 将(x,True)填入该位置，并直接返回
            array[current_pos] = std::move(HashEntry{ std::move(x), true});
            currentSize +=1;
            return true;
          }
        }
        /// 否则，没有一个位置是ok的，那就开始驱逐旧元素的操作
        /// 任意选择一个老人踢出去，是坐在第kick_off个位置上的那个
        int kick_off = rand() % numHashFunctions;
        int final_pos = find_position(x ,kick_off);
        /// 采用swap的策略，现在x就获得了被踢出来的元素，他将继续寻找下家
        std::swap( x, array[ final_pos ].element );
        KICK+=1;
        if (debug == true) ///若处于debug模式，则打印出来
          cout << "<<<<<<<<<<<< kick!!!<<< " << x << " <<<<< "<< endl;
      }
      rehash(2*TableSize,debug);
      return insert_element(x,debug);
    }

    bool insert_element(Datatype && x,bool debug)
    {
      int KICK = 0 ;
      int MAX_KICK = 1+min(currentSize/4,99); /// 以此设置为最多的碰撞踢除数量
      while( KICK < MAX_KICK )
      {
        for( int i = 0; i < numHashFunctions; ++i ) /// 逐个尝试该元素x对应的Hash值
        {
          int current_pos = find_position(x, i);
          /// 若这个位置未使用，那是ok的
          if(array[current_pos].isActive == false)
          {
            /// 将(x,True)填入该位置，并直接返回
            array[current_pos] = std::move(HashEntry{ std::move(x), true});
            currentSize +=1;
            return true;
          }
        }
        /// 否则，没有一个位置是ok的，那就开始驱逐旧元素的操作
        /// 任意选择一个老人踢出去
        int kick_off = rand() % numHashFunctions;
        int final_pos = find_position(x ,kick_off);
        /// 采用swap的策略，现在x就获得了被踢出来的元素，他将继续寻找下家
        std::swap( x, array[ final_pos ].element );
        KICK+=1;
        if (debug == true) ///若处于debug模式，则打印出来
          cout << "<<<<<<<<<<<< kick!!!<<< " << x << " <<<<< "<< endl;
      }
      rehash(2*TableSize,debug);
      return insert_element(std::move(x),debug);
    }

};
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// HASH TABLE //////////////////////////////->end
//////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// UTILITIES /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// 工具函数，用来辅助Hash映射的生成等
/// 判断是否是质数：
bool isPrime(int n)
{
    if( n == 2 || n == 3 )
        return true; /// 2和3直接true
    if( n == 1 || n % 2 == 0 )
        return false; /// 直接否决偶数，更快速一些
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}
int nextPrime(int n) /// 返回n的紧接质数后元
{
    if( n % 2 == 0 )
        ++n; /// 偶数否决
    for( ; !isPrime( n ); n += 2 )
        ; ///奇数递增试凑

    return n;
}
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// UTILITIES ////////////////////////////////->end
////////////////////////////////////////////////////////////////////////////////
